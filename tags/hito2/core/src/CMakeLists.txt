add_executable(Stracomter Stracomter)
target_link_libraries(Stracomter StraCore sfml-graphics)

add_executable(Editor mapEditor)
target_link_libraries(Editor StraCore sfml-graphics sfml-system)

add_executable(Menus testMenus)
target_link_libraries(Menus StraCore sfml-graphics sfml-system)

add_executable(Movimiento testMov)
target_link_libraries(Movimiento StraCore StraGraphics)
