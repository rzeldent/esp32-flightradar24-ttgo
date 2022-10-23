#!/bin/sh
python3 -m pip install --upgrade pip setuptools wheel
python3 -m pip install Pillow

python3 ./images_to_png_cpp.py './images/*.*' raw './include/images.h'
python3 ./images_to_png_cpp.py './images/airline_logos/*.*' gif './include/airline_logos.h' 40 40
python3 ./images_to_png_cpp.py './images/country_flags/*.png' gif './include/country_flags.h' 24 12