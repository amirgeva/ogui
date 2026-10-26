cmake_minimum_required(VERSION 3.16)

include_directories(../../include)
IF (MSVC)
add_definitions( "/wd4005 /wd4996 /nologo" )
ENDIF(MSVC)
add_definitions("-DROOTDIR=\"${CMAKE_SOURCE_DIR}\"")
add_library(demo mainmenu.cpp table.cpp imagemap.cpp buttons.cpp)
target_link_libraries(demo ogui)
