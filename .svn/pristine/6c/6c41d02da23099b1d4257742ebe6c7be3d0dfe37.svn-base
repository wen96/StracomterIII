#! /bin/bash

if [ $# = 1 ]; then
	case $1 in
		"BASE-UBU" )
			sudo apt-get install g++ cmake make
			;;
		"BASE-ARCH" )
			sudo pacman -S g++ cmake make
			;;
		"UBU" )
			sudo apt-get install freeglut3 freeglut3-dev libglew1.5 libglew1.5-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx libgl1-mesa-dev libxrandr-dev libfreetype6-dev libjpeg8-dev libopenal-dev libsndfile1-dev libxmu-dev libxi-dev
			sudo ln -s /usr/include/freetype2/freetype /usr/include/freetype
			;;
		"ARCH" )
			sudo pacman -S freeglut3 freeglut3-dev libglew1.5 libglew1.5-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx libgl1-mesa-dev libxrandr-dev libfreetype6-dev libjpeg8-dev libopenal-dev libsndfile1-dev libxmu-dev libxi-dev
			sudo ln -s /usr/include/freetype2/freetype /usr/include/freetype
			;;
	esac
			
			
fi
