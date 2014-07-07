project(StraGraphics)

#####################################
# INCLUDES y LIBS                   #
#####################################
set(INCDIRS 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
        
set(LIBDIRS
    ${CMAKE_CURRENT_BINARY_DIR}/lib
)

include_directories(${INCDIRS})
                    
link_directories(${LIBDIRS})

##############################
# Compilacion de la libreria #
##############################
add_subdirectory(lib)

######################################
# Compilacion de utilidades/ejemplos #
######################################
add_subdirectory(src)
