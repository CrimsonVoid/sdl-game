find_package(SDL3 CONFIG REQUIRED)

add_library(sdlpp)
add_library(sdlpp::sdlpp ALIAS sdlpp)
target_sources(sdlpp
  PRIVATE
    sdlpp.cpp
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include
  PRIVATE
    FILE_SET internal
    TYPE HEADERS
    BASE_DIRS include/sdlpp)
target_link_libraries(sdlpp INTERFACE SDL3::SDL3)

SET_PROJECT_CXX_PROPERTIES(sdlpp)
