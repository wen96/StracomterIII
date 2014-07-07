#CMake para la compilacion de MOTOR2D

include_directories(../../core/include)
include_directories(../../motorFisica/include)
include_directories(include)
include_directories(../../core/maths/include)

#Llamada a las subcarpetas necesarias para la compilacion.
add_subdirectory(lib)
add_subdirectory(src)
