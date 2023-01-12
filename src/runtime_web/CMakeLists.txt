set(Runtime_SOURCES
"main.c"
)

configure_file(index.html "${CMAKE_BINARY_DIR}/bin/index.html" @ONLY)

add_executable(RuntimeWeb ${Runtime_SOURCES})
target_include_directories(RuntimeWeb PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(RuntimeWeb Game)
set_target_properties(RuntimeWeb PROPERTIES
OUTPUT_NAME "${CMAKE_PROJECT_NAME}"
)