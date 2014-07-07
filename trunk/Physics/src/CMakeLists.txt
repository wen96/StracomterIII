#Carpeta src Motor de fisica

include_directories(../lib)
include_directories(../include)
include_directories(../../core/maths/include)
include_directories(../../core/base/include)
include_directories(../../box2d/86)
include_directories(../../box2d/64)

#Creacion del ejecutable
add_executable(motorFisica test.cc)

find_package(SFML 2.0 REQUIRED system window graphics network audio)
find_package(GLEW)
find_package(GLUT)
find_package(OpenGL)

SET(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${GL_LIBRARY} ${GLU_LIBRARY} ${SFML_LIBRARIES})

#Lincando librerias para el ejecutable
target_link_libraries(motorFisica ${CORELIBS} StraPhysics StraBase Stra2DGraphics)
