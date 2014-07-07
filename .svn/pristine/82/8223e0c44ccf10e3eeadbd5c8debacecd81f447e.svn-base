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
			make
			;;
		"cln" )
			rm -Rf build/
			;;
		"Demo" )
			./build/core/src/Stracomter
			;;
		"AStar" )
			./build/IABase/src/testNiceGrafic $2
			;;
		"Navigation" )
			./build/IABase/src/testPathfinder $2
			;;
		"Triangulation" )
			./build/IABase/src/testDelaunay $2
			;;
		"Simplex" )
			./build/motorOptimizacion/src/Simplex
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

