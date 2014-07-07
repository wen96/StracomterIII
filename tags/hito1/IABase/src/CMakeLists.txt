#CMake de src de IABASE
include_directories(../include)
include_directories(../lib)

#add_executable(IA testGrafo.cc)
add_executable(testTri testTri.cc)
add_executable(testGrafico testGrafico.cc)
add_executable(testDelaunay testDelaunay.cc)
add_executable(testGrafo testGrafo.cc)
add_executable(testPathfinder testPathfinder.cc)
add_executable(testAStar testAStar.cc)
add_executable(testExp testExp)
add_executable(testNiceGrafic testNiceGrafic.cc)

#Linkar librerias Necesarias
#target_link_libraries(IA XMLParser)
#target_link_libraries(IA GraphUD)
#target_link_libraries(IA Point)
#target_link_libraries(IA ASNode)
#target_link_libraries(IA Triangulation)
#target_link_libraries(IA NavGraph)
#target_link_libraries(IA Pathfinder)


find_package(SFML 1.6 REQUIRED system window graphics network audio)
find_package(GLEW)
find_package(GLUT)
find_package(OpenGL)

SET(CORELIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARY} ${GL_LIBRARY} ${GLU_LIBRARY} ${SFML_LIBRARIES})


target_link_libraries(testTri Triangulation)
target_link_libraries(testGrafo ASNode NavGraph)

target_link_libraries(testGrafico ${CORELIBS} Polygon MotorGrafico Triangulation Tri TWindow IOControl)
target_link_libraries(testDelaunay ${CORELIBS} Polygon MotorGrafico Triangulation Tri TWindow IOControl Map)
target_link_libraries(testPathfinder ${CORELIBS} Polygon MotorGrafico Triangulation Tri Pathfinder NavGraph TWindow IOControl Map)
target_link_libraries(testAStar Triangulation Tri Pathfinder NavGraph Map)
target_link_libraries(testNiceGrafic ${CORELIBS} Polygon MotorGrafico Triangulation Tri Pathfinder NavGraph TWindow IOControl Map)
target_link_libraries(testExp ${CORELIBS} Polygon MotorGrafico Triangulation Tri Pathfinder NavGraph TWindow IOControl Map)


