#CMake para el src OPTIMIZACION

add_executable(Simplex test.cc)
add_executable(pruebaOpti testOpti.cc)

include_directories(../include)
include_directories(../../resources/include)
include_directories(../../entities/include)
include_directories(../../core/maths/include)
include_directories(../../core/entities/include)
include_directories(../../Physics/include)
include_directories(../../Graphics/2D/include)


find_package(SFML 2.0 REQUIRED system window graphics network audio)
find_package(GLEW)
find_package(GLUT)
find_package(OpenGL)

SET(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${GL_LIBRARY} ${GLU_LIBRARY} ${SFML_LIBRARIES})


target_link_libraries(Simplex StraOptimization)
target_link_libraries(pruebaOpti ${CORELIBS} StraOptimization StraEntity StraResources StraPhysics StraMath StraBase)
