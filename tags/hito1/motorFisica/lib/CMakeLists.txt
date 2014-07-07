#carpeta lib MOTOR FISICA
include_directories(../include)
include_directories(../../core/maths/include)

#Creacion de libreria
add_library(Box Box)
add_library(World World)
add_library(Body Body)
add_library(Force Force)
add_library(BodyData BodyData)

#enlace de la libreria Box2D con la libreria Box (-lBox2D)
target_link_libraries(Box Box2D)
target_link_libraries(Body World)
target_link_libraries(Body Box)
target_link_libraries(Body Box2D)
target_link_libraries(Body Force)
target_link_libraries(World Box2D)
target_link_libraries(World Box)
target_link_libraries(World Point)
target_link_libraries(World Polygon)
target_link_libraries(Force Box2D)
target_link_libraries(BodyData Box2D)
target_link_libraries(BodyData Force)
target_link_libraries(BodyData Box)

