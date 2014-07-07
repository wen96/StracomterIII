#! /bin/bash

if [ $# = 1 ]; then
	case $1 in
		"OPT" )
			sed 's/^#add_subdirectory(core\/maths)/add_subdirectory(core\/maths)/' -i CMakeLists.txt
			sed 's/^add_subdirectory(motorFisica)/#add_subdirectory(motorFisica)/' -i CMakeLists.txt
			sed 's/^add_subdirectory(core)/#add_subdirectory(core)/' -i CMakeLists.txt
			sed 's/^add_subdirectory(motorGrafico)/#add_subdirectory(motorGrafico)/' -i CMakeLists.txt
			sed 's/^#add_subdirectory(motorOptimizacion)/add_subdirectory(motorOptimizacion)/' -i CMakeLists.txt
			sed 's/^add_subdirectory(IABase)/#add_subdirectory(IABase)/' -i CMakeLists.txt
			;;
		"ALL" )
			sed 's/^#add_subdirectory(core\/maths)/add_subdirectory(core\/maths)/' -i CMakeLists.txt
			sed 's/^#add_subdirectory(motorFisica)/add_subdirectory(motorFisica)/' -i CMakeLists.txt
			sed 's/^#add_subdirectory(core)/add_subdirectory(core)/' -i CMakeLists.txt
			sed 's/^#add_subdirectory(motorGrafico)/add_subdirectory(motorGrafico)/' -i CMakeLists.txt
			sed 's/^#add_subdirectory(motorOptimizacion)/add_subdirectory(motorOptimizacion)/' -i CMakeLists.txt
			sed 's/^#add_subdirectory(IABase)/add_subdirectory(IABase)/' -i CMakeLists.txt
			;;
		"GRA" )
			sed 's/^#add_subdirectory(core\/maths)/add_subdirectory(core\/maths)/' -i CMakeLists.txt
			sed 's/^add_subdirectory(motorFisica)/#add_subdirectory(motorFisica)/' -i CMakeLists.txt
			sed 's/^#add_subdirectory(core)/add_subdirectory(core)/' -i CMakeLists.txt
			sed 's/^#add_subdirectory(motorGrafico)/add_subdirectory(motorGrafico)/' -i CMakeLists.txt
			sed 's/^add_subdirectory(motorOptimizacion)/#add_subdirectory(motorOptimizacion)/' -i CMakeLists.txt
			sed 's/^add_subdirectory(IABase)/#add_subdirectory(IABase)/' -i CMakeLists.txt
			;;
		"IA" )
			sed 's/^#add_subdirectory(core\/maths)/add_subdirectory(core\/maths)/' -i CMakeLists.txt
			sed 's/^#add_subdirectory(motorFisica)/add_subdirectory(motorFisica)/' -i CMakeLists.txt
			sed 's/^#add_subdirectory(core)/add_subdirectory(core)/' -i CMakeLists.txt
			sed 's/^#add_subdirectory(motorGrafico)/add_subdirectory(motorGrafico)/' -i CMakeLists.txt
			sed 's/^add_subdirectory(motorOptimizacion)/#add_subdirectory(motorOptimizacion)/' -i CMakeLists.txt
			sed 's/^#add_subdirectory(IABase)/add_subdirectory(IABase)/' -i CMakeLists.txt
			;;
	esac
fi