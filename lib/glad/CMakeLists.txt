set(glad_SRCS
"include/glad/glad.h"
"include/KHR/khrplatform.h"
"src/glad.c"
)

add_library(glad STATIC ${glad_SRCS})
target_include_directories(glad PUBLIC "include")