cmake_minimum_required(VERSION 3.20)

project(GameFramework VERSION 1.0.0 LANGUAGES C CXX)
set(CMAKE_C_STANDARD_REQUIRED 11)
set(CMAKE_CXX_STANDARD_REQUIRED 11)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/src/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

# Passed to emcc for referencing game files
set(GAME_DATA_PATH "${CMAKE_SOURCE_DIR}/data/build")
set(GAME_DISPLAY_NAME "Game-a-week")
set(GAME_DEVELOPER "WHAT DO WE CALL OURSELVES")
set(GAME_COPYRIGHT "Copyright blah blah blah")

add_subdirectory(lib/vectorial)

if (EMSCRIPTEN)
    include(ProjectEmscriptenConfig)
else()
    include(ProjectDesktopConfig)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    string(REPLACE "/GR" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fvisibility=hidden")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-rtti -fno-exceptions")
else()
    message(FATAL_ERROR "Unknown CXX compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

message(STATUS "C Flags: ${CMAKE_C_FLAGS}")
message(STATUS "CXX Flags: ${CMAKE_CXX_FLAGS}")

add_subdirectory(src/game)
if (EMSCRIPTEN)
    add_subdirectory(src/runtime_web)
else()
    add_subdirectory(src/runtime_desktop)
endif()