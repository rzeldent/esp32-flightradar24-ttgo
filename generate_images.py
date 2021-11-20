import subprocess

# pip install Pillow
# run using: python3 generate_images.py

subprocess.call('python3 ./import/images_to_cpp.py ./images ./src/images.c ./include/images.h')
subprocess.call('python3 ./import/images_to_cpp.py ./images/airline_logos ./src/airline_logos.c ./include/airline_logos.h 40 40')
subprocess.call('python3 ./import/images_to_cpp.py ./images/country_flags ./src/country_flags.c ./include/country_flags.h')