#CMake para la compilación de IABASE
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_BINARY_DIR}/lib)

add_subdirectory(lib)
#add_subdirectory(src)