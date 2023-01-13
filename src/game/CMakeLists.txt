set(Game_SOURCES
"gaw_framework.h"
"${CMAKE_CURRENT_BINARY_DIR}/include/gaw_config.h"

"gamestate/game_state_machine.h"
"gamestate/game_state_machine.c"

"mathlib/vector.h"

"game_init.c"
)

configure_file(gaw_config.h.in "${CMAKE_CURRENT_BINARY_DIR}/include/gaw_config.h" @ONLY)

add_library(Game STATIC ${Game_SOURCES})
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_BINARY_DIR}/include")
target_link_libraries(Game PRIVATE vectorial)
if (NOT EMSCRIPTEN)
    target_link_libraries(Game PUBLIC SDL2)
endif()