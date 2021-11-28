# pip install Pillow

import os
import sys
import hashlib
from PIL import Image

def encode_variable_lenght(i):
    if i < 0x80:
        return [i]
    elif i < 0x4000:
        return [0x80 | (i >> 7), i & 0x7f]
    elif i < 0x200000:
        return [0x80 | (i >> 14), 0x80 | (i >> 7) & 0x7f, i & 0x7F]
    elif i < 0x10000000:
        return [0x80 | (i >> 21), 0x80 | (i >> 14) & 0x7F, 0x80 | (i >> 7) & 0x7F, i & 0x7F]

def encode_RLE(data):
    encoded = []
    i = 0
    while i < len(data):
        count = 1
        while i + count < len(data) and data[i] == data[i + count]:
            count += 1
        encoded.append((encode_variable_lenght(count), data[i]))
        i += count
    return encoded


if (len(sys.argv) <= 2):
    print('Usage: images_to_cpp.py <input_dir> <file.h> <width> <height>')
    sys.exit(1)

input_dir = sys.argv[1]
file_h = sys.argv[2]

resize = None

if (len(sys.argv) >= 4):
    resize = (int(sys.argv[3]), int(sys.argv[4]))

converted = []

file_names = os.listdir(input_dir)
file_names = filter(lambda x: x[0] != '.' and os.path.isfile(os.path.join(input_dir, x)), file_names)
file_names = sorted(file_names)

output_file = open(file_h, 'w')
output_file.write('//*******************************************************************************\n')
output_file.write('// Type: R5G6B5\n')
output_file.write('// Scan: top_to_bottom then forward\n')
if (resize != None):
    output_file.write('// Resize: ' + str(resize[0]) + 'x' + str(resize[1]) + '\n')
output_file.write('// ******************************************************************************\n')
output_file.write('\n')

output_file.write('#include <image.h>\n')

hashes = {}

duplicates = {}

for file_name in file_names:
    print('Processing: ' + file_name)

    image_path = os.path.join(input_dir, file_name)
    base_name = os.path.splitext(file_name)[0]

    image_data_name = 'image_data_' + base_name
    image = Image.open(image_path)
    if (resize != None):
        image = image.resize(resize)

    image = image.convert('RGBA')

    width, height = image.size

    hash = hashlib.md5(image.tobytes()).hexdigest()

    if (not hash in hashes):
        hashes[hash]= base_name

        pixels = list(image.getdata())
        original_size = len(pixels)
        compressed_size = 0

        convert_R8G8B8_to_R5G6B5 = lambda rgb: (rgb[0] >> 3) << 11 | (rgb[1] >> 2) << 5 | (rgb[2] >> 3)

        image_data = []
        for y in range(0, height):
            for x in range(width):
                image_data.append(convert_R8G8B8_to_R5G6B5(pixels[y * width + x]))

        image_data = encode_RLE(image_data)

        output_file.write('\n')
        output_file.write('constexpr unsigned short ' + image_data_name + '[] = {\n\t')
        for i in range(0, len(image_data)):
            length = image_data[i][0]
            for l in range(0, len(length)):
                output_file.write('0x' + hex(length[l])[2:].zfill(2) + ', ')
            output_file.write('0x' + hex(image_data[i][1])[2:].zfill(4) + ', ')
            compressed_size += len(length) + 1
        output_file.write('\n')
        output_file.write('};\n')
        output_file.write('constexpr image_data_t ' + base_name + ' = { ' + image_data_name + ', ' + str(width) + ', ' + str(height) + ' };\n')

        print('Original size ' + str(original_size) + '. Compressed size: ' + str(compressed_size) + ' (' + str(100.0 * compressed_size / original_size) + '%)')

    else:
        duplicates[base_name] = hashes[hash]

        image.close()

    converted.append(base_name)

output_file.write('\n\n')
for mapping in duplicates:
    output_file.write('#define ' + mapping + ' ' + duplicates[mapping] + '\n')

output_file.close()

print('Done.')