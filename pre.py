

Import('env')

#print(env.Dump())

print('convert_images')
env.Execute("$PYTHONEXE -m pip install Pillow")
env.Execute("$PYTHONEXE $PROJECT_DIR/import/images_to_cpp.py $PROJECT_DIR/images $PROJECT_DIR/include/images.h")
env.Execute("$PYTHONEXE $PROJECT_DIR/import/images_to_cpp.py $PROJECT_DIR/images/airline_logos $PROJECT_DIR/include/airline_logos.h")
env.Execute("$PYTHONEXE $PROJECT_DIR/import/images_to_cpp.py $PROJECT_DIR/images/country_flags $PROJECT_DIR/include/country_flags.h")
print('convert_images done')

