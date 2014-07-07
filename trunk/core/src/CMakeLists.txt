add_executable(Stracomter Stracomter)
target_link_libraries(Stracomter StraCore sfml-graphics StraEnt)

add_executable(Editor mapEditor)
target_link_libraries(Editor StraCore sfml-graphics sfml-system StraEnt)

#add_executable(generic testGeneric)
#target_link_libraries(generic StraCore sfml-graphics sfml-system StraEnt)

#add_executable(anim testAnimation)
#target_link_libraries(anim StraCore sfml-graphics sfml-system StraEnt)

#add_executable(Menus testMenus)
#target_link_libraries(Menus StraCore sfml-graphics sfml-system StraEnt)

add_executable(Movimiento testMov)
target_link_libraries(Movimiento StraCore StraGraphics StraEnt)

add_executable(RadioB testRadioB)
target_link_libraries(RadioB StraCore sfml-graphics sfml-system StraEnt)

#add_executable(Shaders testShaders)
#target_link_libraries(Shaders StraCore StraGraphics StraEnt)

#add_executable(TPB tTPB)
#target_link_libraries(TPB StraCore StraGraphics StraEnt)

#add_executable(tstatus testStatus)
#target_link_libraries(tstatus StraCore StraEnt)
