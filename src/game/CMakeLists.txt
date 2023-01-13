set(Game_SOURCES
"gaw_framework.h"
"${CMAKE_CURRENT_BINARY_DIR}/include/gaw_config.h"

"filesystem/file_container.h"
"filesystem/file_container.c"
"filesystem/resource_image.h"
"filesystem/resource_image.c"

"gamestate/game_state_machine.h"
"gamestate/game_state_machine.c"

"graphics/graphics.h"
"graphics/graphics.c"
"graphics/rlgl.c"

"math/raymath.c"

"menu/menu_state.h"
"menu/menu_state.c"

"game_init.c"
)

configure_file(gaw_config.h.in "${CMAKE_CURRENT_BINARY_DIR}/include/gaw_config.h" @ONLY)

add_library(Game STATIC ${Game_SOURCES})
target_include_directories(Game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} "${CMAKE_CURRENT_BINARY_DIR}/include")
target_link_libraries(Game PRIVATE raylib glad lz4_static)
if (NOT EMSCRIPTEN)
    target_link_libraries(Game PUBLIC SDL2)
endif()