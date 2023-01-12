message(STATUS "Configuring project for desktop build")

set(GAME_BUILD_FOR_DESKTOP ON)

# Only need to add SDL from source on desktop
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/SDL2")
target_include_directories(SDL2 PUBLIC "${CMAKE_SOURCE_DIR}/lib/SDL2/include")
target_include_directories(SDL2-static PUBLIC "${CMAKE_SOURCE_DIR}/lib/SDL2/include")
target_include_directories(SDL2main PUBLIC "${CMAKE_SOURCE_DIR}/lib/SDL2/include")