set(Game_SOURCES
"gaw_framework.h"
"${CMAKE_CURRENT_SOURCE_DIR}/include/gaw_config.h"

"gamestate/game_state_machine.h"
"gamestate/game_state_machine.c"

"game_init.c"
)

configure_file(gaw_config.h.in "${CMAKE_CURRENT_SOURCE_DIR}/include/gaw_config.h" @ONLY)

add_library(Game STATIC ${Game_SOURCES})
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/include")
if (NOT EMSCRIPTEN)
    target_link_libraries(Game SDL2)
endif()