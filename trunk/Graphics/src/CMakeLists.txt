add_executable(ModelLoader modelLoader)
target_link_libraries(ModelLoader StraGraphics StraEnt StraCore)

add_executable(TextureLoader textureLoader)
target_link_libraries(TextureLoader StraGraphics StraEnt StraCore)

add_executable(Loader loader)
target_link_libraries(Loader StraGraphics StraEnt StraCore)

add_executable(Animation animation)
target_link_libraries(Animation StraGraphics StraEnt StraCore)
