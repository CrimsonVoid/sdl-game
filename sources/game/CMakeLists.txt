find_package(SDL3 CONFIG REQUIRED)

add_executable(game)
target_sources(game
  PRIVATE
    game.cpp error.cpp main.cpp
  PRIVATE
    FILE_SET HEADERS
    BASE_DIRS include/game)
target_link_libraries(game PRIVATE sdlpp::sdlpp SDL3::SDL3)

target_compile_features(game PRIVATE cxx_std_23)
target_compile_options(game PRIVATE
  $<$<COMPILE_LANGUAGE:CXX>:${PROJECT_WARNINGS_CXX}>)
set_target_properties(game PROPERTIES
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF)
