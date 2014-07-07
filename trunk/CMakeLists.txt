#CMake para la compilacion de StracomterIII

#Comprobacion de version de cmake
cmake_minimum_required(VERSION 2.6)

#########################
# Flags para el proyecto#
#########################

# Flag para compilar la Box2D o usar la instalada. ON la compilara  
set(BOX2D ON)

# Flag para compilar los programas de test (DEBUG)
set(TEST_DEBUG ON)

##########################
# Deteccion de librerias #
##########################

# Deteccion (obligatoria) de OpenGL
find_package(OpenGL REQUIRED) 

find_package(Freetype REQUIRED)
#message(${FREETYPE_INCLUDE_DIRS})

find_package(GLUT)

# Deteccion de la SFML
#find_package(SFML) #Seria recomendable saber la version

##############################################
# Compilación de librerías externas al juego #
##############################################

add_subdirectory(3rdParty/SFML)
set(SFML_HS ${PROJECT_SOURCE_DIR}/3rdParty/SFML/include)  
set(SFML_LIBS ${PROJECT_BIN_DIR}/3rdParty/SFML)  

set(SFML_LIBRARIES sfml-window sfml-graphics sfml-system sfml-audio)

# Compilacion de la Box2D (discrimina entre si esta instalada o no, segun el flag)
if(BOX2D)
    add_subdirectory(3rdParty/Box2D)
endif(BOX2D)

# FTGL, GPC y TinyXML
add_subdirectory(3rdParty/GPC)
add_subdirectory(3rdParty/FTGL)
add_subdirectory(3rdParty/tinyXML)
add_subdirectory(3rdParty/WankelParticles)

#####################################
# INCLUDES y LIBS externos al juego #
#####################################

set(INCDIRS 
        ${SFML_HS}
        ${GLUT_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/3rdParty/Box2D
        ${FREETYPE_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/core/include
        ${PROJECT_SOURCE_DIR}/core/entities/include
        ${PROJECT_SOURCE_DIR}/3rdParty/FTGL
        ${PROJECT_SOURCE_DIR}/3rdParty/GPC
        ${PROJECT_SOURCE_DIR}/3rdParty/tinyXML
		${PROJECT_SOURCE_DIR}/3rdParty/FTGL
		${PROJECT_SOURCE_DIR}/3rdParty/WankelParticles/include
		${PROJECT_SOURCE_DIR}/sound/include
        ${PROJECT_SOURCE_DIR}/Math/include
        ${PROJECT_SOURCE_DIR}/Graphics/include
        ${PROJECT_SOURCE_DIR}/AI/include
	    ${PROJECT_SOURCE_DIR}/Optimization/include
	    ${PROJECT_SOURCE_DIR}/Physics/include		
        )
        
set(LIBDIRS
    ${SFML_LIBS}
    ${GLU_LIBRARY}
    ${GLUT_LIBRARY}
    ${GL_LIBRARY}
    ${PROJECT_BINARY_DIR}/3rdParty/Box2D/Box2D
    ${PROJECT_BINARY_DIR}/3rdParty/GPC
    ${PROJECT_BINARY_DIR}/3rdParty/tinyXML
    ${PROJECT_BINARY_DIR}/3rdParty/WankelParticles/lib
    ${PROJECT_BINARY_DIR}/Math/lib
    ${PROJECT_BINARY_DIR}/Graphics/lib
    ${PROJECT_BINARY_DIR}/sound/lib
    ${PROJECT_BINARY_DIR}/AI/lib
    ${PROJECT_BINARY_DIR}/Optimization/lib
    ${PROJECT_BINARY_DIR}/Physics/lib
)

include_directories(${INCDIRS})
                    
link_directories(${LIBDIRS})

################################
# Rutas a los recursos		   #
################################

add_definitions(-DRESOURCESROOT="${CMAKE_CURRENT_SOURCE_DIR}/Graphics/Resources/")

add_definitions(-Wall -g)

################################
# Compilacion de nuestras libs #
################################

add_subdirectory(core/entities)

add_subdirectory(Math)
add_subdirectory(Graphics)
add_subdirectory(AI)
add_subdirectory(Optimization)
add_subdirectory(Physics)
add_subdirectory(sound)

#########################
# Compilacion del juego #
#########################

add_subdirectory(core)
