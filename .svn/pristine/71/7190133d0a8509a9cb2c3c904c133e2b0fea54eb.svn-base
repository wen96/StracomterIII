#CMake para lib de IABASE

set(CMAKE_BUILD_TYPE Debug)

include_directories(../include)
include_directories(../../core/maths/include)

#Añadir Librerias
#add_library(XMLParser XMLParser)
add_library(ASNode ASNode)
add_library(Triangulation Triangulation)
add_library(Pathfinder Pathfinder)
add_library(NavGraph NavGraph)
add_library(Tri Tri)

#Linkar librerias necesarias
#target_link_libraries(XMLParser GraphUD)
target_link_libraries(ASNode Node)
target_link_libraries(NavGraph ASNode)
target_link_libraries(NavGraph Point)
target_link_libraries(Triangulation Point)
target_link_libraries(Triangulation Node)
target_link_libraries(Pathfinder GraphUD)
target_link_libraries(Pathfinder NavGraph)
target_link_libraries(Pathfinder World)
target_link_libraries(Pathfinder Polygon)
target_link_libraries(Pathfinder Body)
target_link_libraries(Pathfinder BodyData)
target_link_libraries(Pathfinder Triangulation)
target_link_libraries(Pathfinder Map)
target_link_libraries(Tri Point)
target_link_libraries(Tri Matrix)
target_link_libraries(Triangulation Tri)
