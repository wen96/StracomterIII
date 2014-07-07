# CMake para la compilacion de 3DParty

include_directories(tinyXML/include)
include_directories(FTGL)
include_directories(WankelParticles/include)

add_subdirectory(tinyXML)
add_subdirectory(FTGL)
add_subdirectory(WankelParticles)