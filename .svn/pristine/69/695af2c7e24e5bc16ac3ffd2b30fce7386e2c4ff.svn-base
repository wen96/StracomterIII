########################
# Proyecto Stracomter capulllo #
########################
project(Stracomter)

###################################
# Opciones del compilador - Debug #
###################################
# Esto deberia manejarse mediante un flag (para activar o desactivar)
add_definitions(-g -Wall)

##############################
# INCLUDES y LIBS "globales" #
##############################

set(CMAKE_DIR_ACTUAL "${PROJECT_SOURCE_DIR}")

set(INCDIRS 
    ${CMAKE_DIR_ACTUAL}/include
    )        
                    
set(LIBDIRS 
    ${CMAKE_DIR_ACTUAL}/lib
    )                    

# Indicamos las carpetas del include
include_directories(${INCDIRS})

# Indicamos las carpetas de las lib
link_directories(${LIBDIRS})

##############################
# Compilacion de los modulos #
##############################
add_subdirectory(lib)
add_subdirectory(src)

