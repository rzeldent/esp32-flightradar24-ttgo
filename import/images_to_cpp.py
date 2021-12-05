# pip install Pillow

import os
import sys
import hashlib
import struct
import zlib
from PIL import Image

if (len(sys.argv) <= 2):
    print('Usage: images_to_cpp.py <input_dir> <file.h> <maxwidth> <maxheight>')
    sys.exit(1)

input_dir = sys.argv[1]
file_h = sys.argv[2]

resize = None

if (len(sys.argv) >= 4):
    resize= (int(sys.argv[3]), int(sys.argv[4]))

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

output_file.write('#include <zimage.h>\n')

hashes = {}
duplicates = {}

for file_name in file_names:
    print(f'Processing: {file_name}... ', end='')

    image_path = os.path.join(input_dir, file_name)
    base_name = os.path.splitext(file_name)[0]

    image_data_name = f'image_data_{base_name}'
    image = Image.open(image_path)

    if (resize != None):
        aspectRatio = image.size[0] / image.size[1]
        if (aspectRatio > 1):
            size = (resize[0], int(resize[0] / aspectRatio))
        else:
            size = (int(resize[1] * aspectRatio), resize[1])
        image = image.resize(size)
    else:
        size = image.size

    image = image.convert('RGBA')
    width, height = size

    # Create white background
    background = Image.new('RGBA', size, (255, 255, 255, 0))
    background.paste(image, (0, 0), image)
    image = background

    hash = hashlib.md5(image.tobytes()).hexdigest()

    if (not hash in hashes):
        hashes[hash]= base_name

        pixels = list(image.getdata())
        compressed_size = 0

        convert_R8G8B8_to_R5G6B5 = lambda rgb: (rgb[0] >> 3) << 11 | (rgb[1] >> 2) << 5 | (rgb[2] >> 3)

        image_data = bytearray()
        for y in range(0, height):
            for x in range(width):
                pixel = convert_R8G8B8_to_R5G6B5(pixels[y * width + x])
                image_data += struct.pack('<H', pixel)

        original_size = len(image_data)
        compressed_image_data = zlib.compress(image_data, zlib.Z_BEST_COMPRESSION)
        # Option? Remove header: 0x78, 0xda => Best compression
        # compressed_image_data = compressed_image_data[2:]
        compressed_size = len(compressed_image_data)

        output_file.write('\n')
        output_file.write('constexpr unsigned char ' + image_data_name + '[] = { ')
        for i in compressed_image_data:
            output_file.write(f'0x{i:02x}, ')
        output_file.write(' };\n')
        output_file.write('constexpr z_image_data_t ' + base_name + ' = { ' + image_data_name + ', sizeof(' + image_data_name + '), ' + str(width) + ', ' + str(height) + ' };\n')
        print(f'Original: {original_size}, compressed: {compressed_size} ({compressed_size / original_size:.2%})')

    else:
        duplicates[base_name] = hashes[hash]
        print(f'Duplicate: {hashes[hash]}')

        image.close()

output_file.write('\n\n')
for mapping in duplicates:
    output_file.write('#define ' + mapping + ' ' + duplicates[mapping] + '\n')

output_file.close()

print('Done.')