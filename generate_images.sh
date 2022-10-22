#!/bin/sh
python3 -m pip install --upgrade pip setuptools wheel
python3 -m pip install Pillow

python3 ./images_to_png_cpp.py './images/*.*' './include/images.h'
python3 ./images_to_png_cpp.py './images/airline_logos/*.*' './include/airline_logos.h' 40 40
python3 ./images_to_png_cpp.py './images/country_flags/*.png' './include/country_flags.h' 24 12