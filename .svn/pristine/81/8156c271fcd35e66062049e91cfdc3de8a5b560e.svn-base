# FTGL CMake build file
cmake_minimum_required(VERSION 2.6)
#project (FTGL)

set(FTGL_src
        FTBuffer.cpp
        FTCharmap.cpp
        FTContour.cpp
        FTFace.cpp
        FTGlyphContainer.cpp
        FTLibrary.cpp
        FTPoint.cpp
        FTSize.cpp
        FTVectoriser.cpp
        FTFont/FTBitmapFont.cpp
        FTFont/FTBufferFont.cpp
        FTFont/FTExtrudeFont.cpp
        FTFont/FTFont.cpp
        FTFont/FTFontGlue.cpp
        FTFont/FTOutlineFont.cpp
        FTFont/FTPixmapFont.cpp
        FTFont/FTPolygonFont.cpp
        FTFont/FTTextureFont.cpp
        FTGlyph/FTBitmapGlyph.cpp
        FTGlyph/FTBufferGlyph.cpp
        FTGlyph/FTExtrudeGlyph.cpp
        FTGlyph/FTGlyph.cpp
        FTGlyph/FTGlyphGlue.cpp
        FTGlyph/FTOutlineGlyph.cpp
        FTGlyph/FTPixmapGlyph.cpp
        FTGlyph/FTPolygonGlyph.cpp
        FTGlyph/FTTextureGlyph.cpp
        FTLayout/FTLayout.cpp
        FTLayout/FTLayoutGlue.cpp
        FTLayout/FTSimpleLayout.cpp
)

include_directories(${FREETYPE_INCLUDE_DIRS})

message(${FREETYPE_INCLUDE_DIRS})	

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/FTGL)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/FTFont)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/FTGlyph)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/FTLayout)

add_library(FTGL ${FTGL_src})
#set_target_properties(FTGL PROPERTIES
#        COMPILE_DEFINITIONS "_LIB")

target_link_libraries(FTGL
     ${FREETYPE_LIBRARIES}
     ${OPENGL_gl_LIBRARY}
     ${OPENGL_glu_LIBRARY}
)
