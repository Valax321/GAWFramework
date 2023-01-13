set(raylib_SRCS
"raymath.h"
"rlgl.h"
)

add_library(raylib INTERFACE ${raylib_SRCS})
target_include_directories(raylib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})