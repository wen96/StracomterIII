if [ $# = 0 ]; then
	mkdir build 2>/dev/null
	cd build
	cmake .. >/dev/null
else
	case $1 in
		"mathGraph" )
			./build/core/maths/src/testGraph
			;;
		"com" )
			cd build
			make $2
			;;
		"cln" )
			for file in $(find build/ -maxdepth 1 -type d | grep -v -e "build/$" -e "3rdParty"); do
				rm -R $file; 
			done
			;;
		"reset" )
			rm -Rf build/
			;;
		"Demo" )
			./build/core/src/Stracomter
			;;
		"AStar" )
			./build/AI/src/testNiceGrafic $2
			;;
		"Navigation" )
			./build/AI/src/testPathfinder $2
			;;
		"Triangulation" )
			./build/AI/src/testDelaunay $2
			;;
		"Simplex" )
			./build/Optimization/src/Simplex
			;;
		"Model" )
                        ./build/Graphics/src/ModelLoader $2
                        ;;

		* )
			echo "Construir make: ./construir.sh"
			echo "Compilar: ./construir.sh com"
			echo "Limpiar: ./construir.sh cln"
			echo "Demo del juego: ./construir.sh Demo"
			echo "Altoritmo AStar: ./construir.sh AStar"
			echo "Grafo de navegacion: ./construir.sh Navigation"
			echo "Test de triangulacion: ./construir.sh Triangulation"
			echo "Algritmo simplex: ./construir.sh Simplex"
			;;
	esac
fi

