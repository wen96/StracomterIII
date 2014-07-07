#Cmake para la compilacion de src MOTORFISICA


include_directories(../motorGrafico/motor2D/include)
include_directories(../core/include)
#Llamada a las subcarpetas necesarias para la compilacion
add_subdirectory(lib)
add_subdirectory(src)
