# CMakeList.txt : CMake project for sdl-game, include source and define
# project specific logic here.
#

# Add source to this project's executable.
find_package(SDL3 CONFIG REQUIRED)
add_executable (sdl-game "sdl-game.cpp" "sdl-game.h")
target_link_libraries(sdl-game PRIVATE SDL3::SDL3)

set_property(TARGET sdl-game PROPERTY CXX_STANDARD 23)

# TODO: Add tests and install targets if needed.
