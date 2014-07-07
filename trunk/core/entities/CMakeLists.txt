project(StraEnt)

###################################
# Opciones del compilador - Debug #
###################################
# Esto deberia manejarse mediante un flag (para activar o desactivar)
add_definitions(-g -Wall)

##############################
# INCLUDES y LIBS "globales" #
##############################
set(INCDIRS 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
        
set(LIBDIRS
    ${CMAKE_CURRENT_BINARY_DIR}/lib
)

include_directories(${INCDIRS})
                    
link_directories(${LIBDIRS})

##############################
# Compilacion de los modulos #
##############################
add_subdirectory(lib)
add_subdirectory(src)

