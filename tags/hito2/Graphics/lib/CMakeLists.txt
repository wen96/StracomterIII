#carpeta lib MotorGráfico

file(GLOB graphics_src "*.cc")

add_library(StraGraphics ${graphics_src})

target_link_libraries(StraGraphics ${OPENGL_LIBRARY} ${SFML_LIBRARIES})
target_link_libraries(StraGraphics FTGL StraMath)
