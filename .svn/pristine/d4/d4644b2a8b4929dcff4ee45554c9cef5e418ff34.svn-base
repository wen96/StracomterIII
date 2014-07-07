#Carpeta lib de resources CORE

file(GLOB core_src "*.cc")

add_library(StraCore ${core_src})

target_link_libraries(StraCore StraGraphics StraAI StraOptimization StraAudio TinyXML ${GLUT_LIBRARY} sfml-system WankelParticles)
