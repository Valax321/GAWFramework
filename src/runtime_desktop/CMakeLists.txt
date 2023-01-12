set(Runtime_SRCS
"main.cpp"
)

add_executable(RuntimeDesktop WIN32 ${Runtime_SRCS})
target_include_directories(RuntimeDesktop PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(RuntimeDesktop Game SDL2 SDL2main)
set_target_properties(RuntimeDesktop PROPERTIES
OUTPUT_NAME "${CMAKE_PROJECT_NAME}"
)

if (WIN32)
    set(GAME_APP_ICON "${CMAKE_CURRENT_SOURCE_DIR}/app.ico")
    configure_file(app.rc.in "${CMAKE_CURRENT_BINARY_DIR}/app.rc" @ONLY)
    target_sources(RuntimeDesktop PRIVATE "app.manifest" "${CMAKE_CURRENT_BINARY_DIR}/app.rc")
endif()