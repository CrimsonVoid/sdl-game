find_package(SDL3 CONFIG REQUIRED)

add_executable(game)
target_sources(game
  PRIVATE
    game.cpp error.cpp main.cpp
  PRIVATE
    FILE_SET HEADERS
    BASE_DIRS include/game)
target_link_libraries(game PRIVATE sdlpp::sdlpp SDL3::SDL3)

SET_PROJECT_CXX_PROPERTIES(game)
