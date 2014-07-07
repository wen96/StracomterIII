#Carpeta src Motor de fisica

include_directories(../lib)
include_directories(../include)
include_directories(../../core/maths/include)

#Creacion del ejecutable
add_executable(motorFisica test.cc)

find_package(SFML 1.6 REQUIRED system window graphics network audio)
find_package(GLEW)
find_package(GLUT)
find_package(OpenGL)

SET(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${GL_LIBRARY} ${GLU_LIBRARY} ${SFML_LIBRARIES})

#Lincando librerias para el ejecutable
target_link_libraries(motorFisica Box2D)
target_link_libraries(motorFisica Box)
target_link_libraries(motorFisica World)
target_link_libraries(motorFisica Body)
target_link_libraries(motorFisica BodyData)
target_link_libraries(motorFisica Force)
target_link_libraries(motorFisica IOControl)
target_link_libraries(motorFisica TWindow)
target_link_libraries(motorFisica MotorGrafico)
target_link_libraries(motorFisica Transformacion)
target_link_libraries(motorFisica ${CORELIBS})
