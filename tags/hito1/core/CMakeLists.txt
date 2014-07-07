#CMake para la compilacion de CORE

include_directories(maths/include)
include_directories(../motorFisica/include)
include_directories(../motorGrafico/motor2D/include)
#Llamada a las subcarpetas necesarias para la compilacion.
add_subdirectory(lib)
add_subdirectory(src)
#add_subdirectory(maths)
