#CMake para el src sound

add_executable(blank testBlank)
target_link_libraries(blank sfml-audio StraAudio StraCore StraEnt)

add_executable(abstr testAbstraction)
target_link_libraries(abstr sfml-audio StraAudio StraCore StraEnt)

add_executable(spa testSpacialization)
target_link_libraries(spa sfml-audio StraAudio StraCore StraEnt)