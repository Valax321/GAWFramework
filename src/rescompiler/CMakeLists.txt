set(rescompiler_SRCS
"main.cpp"
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")

add_executable(rescompiler ${rescompiler_SRCS})
target_include_directories(rescompiler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rescompiler Game lz4_static)