#CMake para la compilacion de src de CORE
include_directories(${stracomter_SOURCE_DIR}/core/include)
include_directories(${stracomter_SOURCE_DIR}/core/lib)
include_directories(${stracomter_SOURCE_DIR}/core/maths/include)
include_directories(${stracomter_SOURCE_DIR}/core/maths/lib)

#Para poder hacer esto tienes que instalar: libxmu-dev libxi-dev libusb-1.0-0-dev
find_package(GLUT)
find_package(OpenGL)
#find_package(GL)
#find_package(GLU)




find_package(SFML 1.6 REQUIRED system window graphics network audio)
find_package(GLEW)

SET(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${GL_LIBRARY} ${GLU_LIBRARY} ${SFML_LIBRARIES})


add_executable(Stracomter test.cc)
add_executable(testEntity testEntity.cc)
add_executable(testResource testResource.cc)
add_executable(testWindow testWindow.cc)
add_executable(testMap testMap.cc)

target_link_libraries(testResource ResourceManager)

target_link_libraries(testWindow ${CORELIBS})
target_link_libraries(testWindow TWindow)

target_link_libraries(testMap Map)
target_link_libraries(testMap Node)
target_link_libraries(testMap GraphUD)

target_link_libraries(testEntity EntityManager)

target_link_libraries(Stracomter ${CORELIBS})
target_link_libraries(Stracomter Aplication)
