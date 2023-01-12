set(Runtime_SRCS
"main.cpp"
)

add_executable(RuntimeDesktop WIN32 ${Runtime_SRCS})
target_include_directories(RuntimeDesktop PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(RuntimeDesktop Game SDL2 SDL2main)
set_target_properties(RuntimeDesktop PROPERTIES
OUTPUT_NAME "${CMAKE_PROJECT_NAME}"
)