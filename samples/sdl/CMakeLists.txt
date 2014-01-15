cmake_minimum_required(VERSION 2.8)
include_directories(../../include)
IF(MSVC)
add_definitions( "/wd4005 /wd4996 /nologo" )
ENDIF(MSVC)

INCLUDE(${CMAKE_ROOT}/Modules/FindSDL.cmake)
include_directories(${SDL_INCLUDE_DIR})

IF(CMAKE_COMPILER_IS_GNUCXX)
add_definitions("-std=c++11")
ENDIF(CMAKE_COMPILER_IS_GNUCXX)

add_executable(sdl main.cpp)
target_link_libraries(sdl image ogui ${SDL_LIBRARY} ${SDLMAIN_LIBRARY})
