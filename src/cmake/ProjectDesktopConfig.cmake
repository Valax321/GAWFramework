message(STATUS "Configuring project for desktop build")

# Only need to add SDL from source on desktop
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/SDL2")