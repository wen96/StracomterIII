########################
# Proyecto CandyMath   #
########################
project(StraMath)

add_definitions(-g -Wall)

##############################################
# Indicamos los directorios de INCLUDE y LIB #
##############################################

set(INCDIRS 
    ${PROJECT_SOURCE_DIR}/include
    )        
                    
set(LIBDIRS 
    ${PROJECT_BINARY_DIR}/lib
    )                    

include_directories(${INCDIRS})
link_directories(${LIBDIRS})

################################################
# Compilacion de la libreria matematica (todo) #
################################################
add_subdirectory(lib)

