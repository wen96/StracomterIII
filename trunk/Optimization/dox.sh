if [ $# = 0 ]; then
	echo "Crear Doxygen: ./dox.sh c"
	echo "Ejecutar: ./construir.sh r"
else
	case $1 in
		"c" )
			doxygen -g Doxydoc
			echo "Modifica el archivo Doxydoc"
			echo "	-Añade los directorios "include lib src" al INPUT - línea 601 -"
			echo "	-INPUT			=	include lib src" 
			;;
		"r" )
			doxygen Doxydoc 2> doxygen.log >/dev/null
			echo "Log de errores: doxygen.log"
			cat doxygen.log
			;;
		"d" )
			rm -R -f html latex doxygen.log Doxydoc.bak
			;;
		* )
			echo "Crear Doxygen: ./dox.sh c"
			echo "Ejecutar: ./dox.sh r"
			echo "Borrar: ./dox.sh d"
			
			;;
	esac
fi