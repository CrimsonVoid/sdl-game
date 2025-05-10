find_package(SDL3 CONFIG REQUIRED)

# if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
#   add_library(sdlpp "sdlpp.cpp")
#   set(SDLPP_LINK_TYPE PRIVATE)
#   set_target_properties(sdlpp PROPERTIES
# 	  CMAKE_CXX_EXTENSIONS OFF)
# else() 
#   add_library(sdlpp INTERFACE)
#   set(SDLPP_LINK_TYPE INTERFACE)
# endif()

# target_link_libraries(sdlpp ${SDLPP_LINK_TYPE} SDL3::SDL3)
# target_compile_features(sdlpp ${SDLPP_LINK_TYPE} cxx_std_23)
# target_include_directories(sdlpp INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
# target_include_directories(sdlpp PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include/sdlpp")

add_library(sdlpp)
target_sources(sdlpp
  PRIVATE
    sdlpp.cpp
  PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include
  PRIVATE
    FILE_SET internal
    TYPE HEADERS
    BASE_DIRS include/sdlpp
)

target_link_libraries(sdlpp PUBLIC SDL3::SDL3)
target_compile_features(sdlpp PRIVATE cxx_std_23)

add_library(sdlpp::sdlpp ALIAS sdlpp)
