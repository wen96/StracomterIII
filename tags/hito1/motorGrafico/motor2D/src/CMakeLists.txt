#Carpeta src MotorGrafico

IF (GLEW_INCLUDE_DIR)
  # Already in cache, be silent
  SET(GLEW_FIND_QUIETLY TRUE)
ENDIF (GLEW_INCLUDE_DIR)

   FIND_PATH( GLEW_INCLUDE_DIR glew.h wglew.h
              PATHS /usr/local/include /usr/include
              PATH_SUFFIXES gl/ GL/ )
   SET( GLEW_NAMES glew GLEW )
   FIND_LIBRARY( GLEW_LIBRARY
                 NAMES ${GLEW_NAMES}
                 PATHS /usr/lib /usr/local/lib )

GET_FILENAME_COMPONENT( GLEW_LIBRARY_DIR ${GLEW_LIBRARY} PATH )

IF (GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
   SET(GLEW_FOUND TRUE)
    SET( GLEW_LIBRARY_DIR ${GLEW_LIBRARY} )
ELSE (GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
   SET( GLEW_FOUND FALSE )
   SET( GLEW_LIBRARY_DIR )
ENDIF (GLEW_INCLUDE_DIR AND GLEW_LIBRARY)

MARK_AS_ADVANCED(
  GLEW_LIBRARY
  GLEW_INCLUDE_DIR
)


#Para poder hacer esto tienes que instalar: libxmu-dev libxi-dev libusb-1.0-0-dev
find_package(GLUT)
find_package(OpenGL)

SET(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${GL_LIBRARY} ${GLU_LIBRARY})

#Creacion del ejecutable
add_executable(motorGrafico test.cc) 
add_executable(OpenGlTest OpenGlTest.cc)

#Lincando librerias para el ejecutable
target_link_libraries(motorGrafico MotorGrafico)
target_link_libraries(motorGrafico Transformacion)
target_link_libraries(motorGrafico ${CORELIBS})

target_link_libraries(OpenGlTest MotorGrafico)
target_link_libraries(OpenGlTest Point)
target_link_libraries(OpenGlTest Polygon)
target_link_libraries(OpenGlTest Transformacion)
target_link_libraries(OpenGlTest ${CORELIBS})

