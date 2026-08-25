. python -m pip install --upgrade pip setuptools wheel
. python -m pip install Pillow

. python ./images_to_lvgl.py './images/*.*' raw './include/images.h'
. python ./images_to_lvgl.py './images/airline_logos/*.*' gif './include/airline_logos.h' 40 40
. python ./images_to_lvgl.py './images/country_flags/*.png' gif './include/country_flags.h' 24 12