cmake_minimum_required (VERSION 3.30)

include("cmake/vars.cmake")

project("sdl-game")

add_subdirectory("sources/sdlpp")
add_subdirectory("sources/game")
