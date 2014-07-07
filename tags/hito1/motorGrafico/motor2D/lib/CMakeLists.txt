#carpeta lib MotorGráfico

#Creacion de libreria
add_library(MotorGrafico MotorGrafico)
add_library(Color Color)
add_library(Transformacion Transformacion)
add_library(Scene Scene)

target_link_libraries(MotorGrafico Point)
target_link_libraries(MotorGrafico Polygon)
target_link_libraries(MotorGrafico Color)
target_link_libraries(Transformacion Matrix)
target_link_libraries(Transformacion Point)
target_link_libraries(Scene EntityManager)
target_link_libraries(Scene Polygon)
target_link_libraries(Scene Entity)
target_link_libraries(Scene MotorGrafico)
target_link_libraries(Scene Transformacion)
