# pip install Pillow

import os
import sys
import hashlib
from PIL import Image

if (len(sys.argv) <= 3):
    print('Usage: images_to_cpp.py <input_dir> <file.c> <file.h> <width> <height>')
    sys.exit(1)

input_dir = sys.argv[1]
file_c = sys.argv[2]
file_h = sys.argv[3]

resize = None

if (len(sys.argv) >= 5):
    resize = (int(sys.argv[4]), int(sys.argv[5]))

converted = []

file_names = os.listdir(input_dir)
file_names = filter(lambda x: os.path.isfile(os.path.join(input_dir, x)), file_names)
file_names = sorted(file_names)

output_file = open(file_c, 'w')
output_file.write('//*******************************************************************************\n')
output_file.write('// Type: R5G6B5\n')
output_file.write('// Scan: top_to_bottom then forward\n')
if (resize != None):
    output_file.write('// Resize: ' + str(resize[0]) + 'x' + str(resize[1]) + '\n')
output_file.write('// ******************************************************************************\n')
output_file.write('\n')

output_file.write('#include <image.h>\n')
output_file.write('\n')

hashes = {}

mappings = {}

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

        output_file.write('\n')
        output_file.write('static const uint16_t ' + image_data_name + '[' + str(height * width) + '] = {\n')

        convert_R8G8B8_to_R5G6B5 = lambda rgb: (rgb[0] >> 3) << 11 | (rgb[1] >> 2) << 5 | (rgb[2] >> 3)

        for y in range(0, height):
            for x in range(width):
                value = pixels[y * width + x]
                output_file.write('0x' + hex(convert_R8G8B8_to_R5G6B5(value))[2:].zfill(4) + ', ')
            output_file.write('\n')

        output_file.write('};\n')
        output_file.write('const image_t ' + base_name + ' = { ' + image_data_name + ', ' + str(width) + ', ' + str(height) + ' };\n')

    else:
        mappings[base_name] = hashes[hash]

        image.close()

    converted.append(base_name)

output_file.close()

output_file = open(file_h, 'w')

output_file.write('#pragma once\n')
output_file.write('\n')
output_file.write('#include <image.h>\n')
output_file.write('\n')

for base_name in converted:
    output_file.write('extern const image_t ' + base_name + ';\n')

output_file.write('\n')
for mapping in mappings:
    output_file.write('#define ' + mapping + ' ' + mappings[mapping] + '\n')

output_file.close()

print('Done.')