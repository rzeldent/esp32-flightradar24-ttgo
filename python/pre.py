import subprocess

subprocess.call('python3 ./python/images_to_cpp.py ./images ./src/images.c ./include/images.h')
subprocess.call('python3 ./python/images_to_cpp.py ./images/airline_logos ./src/airline_logos.c ./include/airline_logos.h')
subprocess.call('python3 ./python/images_to_cpp.py ./images/country_flags ./src/country_flags.c ./include/country_flags.h')