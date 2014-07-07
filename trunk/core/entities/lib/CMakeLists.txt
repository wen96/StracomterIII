#Carpeta lib de Entities

file(GLOB ent_src "*.cc")

add_library(StraEnt ${ent_src})

target_link_libraries(StraEnt StraGraphics StraAI StraOptimization TinyXML ${GLUT_LIBRARY} sfml-system)
