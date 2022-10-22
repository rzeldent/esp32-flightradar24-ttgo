# pip install Pillow
import io
import glob
import os
from pickletools import optimize
import sys
import hashlib

from glob import glob
from turtle import width
from PIL import Image

if (len(sys.argv) <= 2):
    print('Usage: images_to_cpp.py <input_files> <file.h> <maxwidth> <maxheight>')
    sys.exit(1)

print (','.join(sys.argv))


files = glob(sys.argv[1])
file_h = sys.argv[2]
resize = None
if (len(sys.argv) >= 4):
    resize= (int(sys.argv[3]), int(sys.argv[4]))

output_file = open(file_h, 'w')
output_file.write(
    '//*******************************************************************************\n'
    '// Type: LVGL\n')
if (resize != None):
    output_file.write('// Resize: ' + str(resize[0]) + 'x' + str(resize[1]) + '\n')

output_file.write(
    '// ******************************************************************************\n\n'
    '#if defined(LV_LVGL_H_INCLUDE_SIMPLE)\n'
    '#include "lvgl.h"\n'
    '#else\n'
    '#include "lvgl/lvgl.h"\n'
    '#endif\n\n')

hashes = {}
duplicates = {}

for file_name in files:
    print(f'Processing: {file_name}... ')
    image = Image.open(file_name)

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

    # Create transparent background
    #background = Image.new('RGBA', size, (0, 0, 0, 255))
    #background.paste(image, (0, 0), image)
    hash = hashlib.md5(image.tobytes()).hexdigest()

    base_name = os.path.splitext(os.path.basename(file_name))[0]

    if (not hash in hashes):
        hashes[hash]= base_name
        
        output_file.write('\n')
        output_file.write('constexpr unsigned char ' + base_name + '_map[] = { \n')

        # PNG
        byte_io = io.BytesIO()
        image.save(byte_io, optimize=True, format='PNG')

        output_file.write('// PNG Data\n')
        output_file.write(','.join(f'0x{(i):02x}' for i in byte_io))
        output_file.write('\n')

        """
        convert_RGB888_to_RGB332 = lambda rgb: (rgb[0] >> 5) << 5 | (rgb[1] >> 6) << 2 | (rgb[2] >> 6)
        convert_RGB888_to_RGB565 = lambda rgb: (rgb[0] >> 3) << 11 | (rgb[1] >> 2) << 5 | (rgb[2] >> 3)

        output_file.write('#if LV_COLOR_DEPTH == 1 || LV_COLOR_DEPTH == 8\n'
            '// Pixel format: RGB332 Red: 3 bit, Green: 3 bit, Blue: 2 bit\n')
        output_file.write(', '.join(f'0x{(i):02x}' for i in map(convert_RGB888_to_RGB332, image.getdata())))
        output_file.write('\n#endif\n')

        output_file.write('#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP == 0\n'
            '// Pixel format: RGB565 Red: 5 bit, Green: 6 bit, Blue: 5 bit\n')
        output_file.write(', '.join(f'0x{(i & 0xff):02x},0x{(i >> 8):02x}' for i in map(convert_RGB888_to_RGB565, image.getdata())))
        output_file.write('\n#endif\n')
        
        output_file.write('#if LV_COLOR_DEPTH == 16 && LV_COLOR_16_SWAP != 0\n'
            '// Pixel format: RGB565 Red: 5 bit, Green: 6 bit, Blue: 5 bit BUT the 2 bytes are swapped\n')
        output_file.write(', '.join(f'0x{(i >> 8):02x},0x{(i & 0xff):02x}' for i in map(convert_RGB888_to_RGB565, image.getdata())))
        output_file.write('\n#endif\n')
        
        output_file.write('#if LV_COLOR_DEPTH == 32\n'
            '// Pixel format: RGBA8888 Red: 8 bit, Green: 8 bit, Blue: 8 bit, Alpha: 8 bit \n')
        output_file.write(', '.join(f'0x{i[0]:02x},0x{(i[1]):02x},0x{(i[2]):02x},0x{(i[3]):02x}' for i in image.getdata()))
        output_file.write('\n#endif\n')
        """

        output_file.write('};\n')

        output_file.write(
            f'const lv_img_dsc_t {base_name} = {{\n'
            '  .header = {\n'
#            '    .cf = LV_IMG_CF_TRUE_COLOR,\n'
            '    .cf = LV_IMG_SRC_VARIABLE,\n'
            '    .always_zero = 0,\n'
            f'    .w = {image.width},\n'
            f'    .h = {image.height}}},\n'
            f'  .data_size = sizeof({base_name + "_map"}),\n'
            f'  .data = {base_name + "_map"}}};\n')

    else:
        duplicates[base_name] = hashes[hash]
        print(f'Duplicate: {hashes[hash]}')

    image.close()

output_file.write('\n\n')
for mapping in duplicates:
    output_file.write('#define ' + mapping + ' ' + duplicates[mapping] + '\n')

output_file.close()

print('Done.')