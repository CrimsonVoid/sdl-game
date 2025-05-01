find_package(SDL3 CONFIG REQUIRED)

add_executable(game "game.cpp" "error.cpp" "main.cpp")
target_link_libraries(game PRIVATE sdlpp::sdlpp SDL3::SDL3)
target_include_directories(game PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/game")

target_compile_features(game PRIVATE cxx_std_23)
set_target_properties(game PROPERTIES
	CMAKE_CXX_STANDARD_REQUIRED ON
	CMAKE_CXX_EXTENSIONS OFF)

target_compile_options(game PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/W4>
  $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra -pedantic>
  $<$<CXX_COMPILER_ID:Clang>:-Wall -Wextra -pedantic>
  $<$<CXX_COMPILER_ID:AppleClang>:-Wall -Wextra -pedantic>
)
