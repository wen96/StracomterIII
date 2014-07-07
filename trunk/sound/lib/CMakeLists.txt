#Carpeta lib sound

file(GLOB sound_src "*.cc")

add_library(StraAudio ${sound_src})

#Linkar librerias necesarias
target_link_libraries(StraAudio ${SFML_LIBRARIES})
