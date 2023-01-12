cmake_minimum_required(VERSION 3.20)

set(CMAKE_MODULE_PATH "src/cmake")
project(GameFramework VERSION 1.0.0 LANGUAGES C CXX)
set(CMAKE_C_STANDARD_REQUIRED 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)

# Passed to emcc for referencing game files
set(GAME_DATA_PATH "${CMAKE_SOURCE_DIR}/data/build")

if (EMSCRIPTEN)
    include(ProjectEmscriptenConfig)
else()
    include(ProjectDesktopConfig)
endif()

add_subdirectory(src/game)
if (EMSCRIPTEN)
    add_subdirectory(src/runtime_web)
else()
    add_subdirectory(src/runtime_desktop)
endif()