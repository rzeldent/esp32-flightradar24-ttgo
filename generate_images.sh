#!/bin/sh
python3 -m pip install --upgrade pip setuptools wheel
python3 -m pip install Pillow

python3 ./import/images_to_cpp.py ./images ./include/images.h
python3 ./import/images_to_cpp.py ./images/airline_logos ./include/airline_logos.h 40 40
python3 ./import/images_to_cpp.py ./images/country_flags ./include/country_flags.h 24 12