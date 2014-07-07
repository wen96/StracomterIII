#CMake para la compilacion de stracomper

#Comprobacion de version de cmake
cmake_minimum_required(VERSION 2.6)

include_directories(${stracomter_SOURCE_DIR}/core/maths/include)
include_directories(${stracomter_SOURCE_DIR}/core/include)
include_directories(${stracomter_SOURCE_DIR}/motorGrafico/motor2D/include)
include_directories(${stracomter_SOURCE_DIR}/motorGrafico/motor3D/include)
include_directories(${stracomter_SOURCE_DIR}/motorOptimizacion/include)
include_directories(${stracomter_SOURCE_DIR}/motorFisica/include)
include_directories(${stracomter_SOURCE_DIR}/IABase/include)

set(CMAKE_CXX_FLAGS "-g -Wall")

link_directories(${stracomter_SOURCE_DIR}/motorFisica/include)
#Nombre del proyecto
project(stracomter)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

#Llamada a las subcarpetas necesarias para la compilacion
add_subdirectory(core/maths)
add_subdirectory(motorFisica)
add_subdirectory(core)
add_subdirectory(motorGrafico)
add_subdirectory(motorOptimizacion)
add_subdirectory(IABase)

