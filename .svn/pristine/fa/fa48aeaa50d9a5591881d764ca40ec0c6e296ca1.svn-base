############################
# Proyecto WankelParticles #
############################
project(WankelParticles)

add_definitions(-g -Wall)

##############################################
# Indicamos los directorios de INCLUDE y LIB #
##############################################

set(INCDIRS 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/soil
    )        
                    
set(LIBDIRS 
    ${PROJECT_BINARY_DIR}/lib
    ${PROJECT_BINARY_DIR}/soil
    )                    

include_directories(${INCDIRS})
link_directories(${LIBDIRS})

################################################
# Compilacion de la libreria matematica (todo) #
################################################
add_subdirectory(lib)
add_subdirectory(soil)

