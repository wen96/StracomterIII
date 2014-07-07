if(NOT(GLOBAL_BUILD))
cmake_minimum_required(VERSION 2.6)

project(Box2D)
endif(NOT(GLOBAL_BUILD))

option(BOX2D_INSTALL "Install Box2D libs, includes, and CMake scripts" OFF)
option(BOX2D_INSTALL_DOC "Install Box2D documentation" OFF)
option(BOX2D_BUILD_SHARED "Build Box2D shared libraries" ON)
option(BOX2D_BUILD_STATIC "Build Box2D static libraries" OFF)

set(BOX2D_VERSION 2.1.0)

# The Box2D library.
add_subdirectory(Box2D)

if(BOX2D_INSTALL_DOC)
  install(DIRECTORY Documentation DESTINATION share/doc/Box2D PATTERN ".svn" EXCLUDE)
endif(BOX2D_INSTALL_DOC)