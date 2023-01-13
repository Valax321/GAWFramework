set(vectorial_SRCS
"include/vectorial/config.h"
"include/vectorial/mat4f.h"
"include/vectorial/simd2f_common.h"
"include/vectorial/simd2f_neon.h"
"include/vectorial/simd2f.h"
"include/vectorial/simd4f_common.h"
"include/vectorial/simd4f_gnu.h"
"include/vectorial/simd4f_neon.h"
"include/vectorial/simd4f_scalar.h"
"include/vectorial/simd4f_sse.h"
"include/vectorial/simd4f.h"
"include/vectorial/simd4x4f_gnu.h"
"include/vectorial/simd4x4f_neon.h"
"include/vectorial/simd4x4f_scalar.h"
"include/vectorial/simd4x4f_sse.h"
"include/vectorial/simd4x4f.h"
"include/vectorial/vec_convert.h"
"include/vectorial/vec2f.h"
"include/vectorial/vec3f.h"
"include/vectorial/vec4f.h"
"include/vectorial/vectorial.h"
)

add_library(vectorial INTERFACE ${vectorial_SRCS})
target_include_directories(vectorial INTERFACE "include")