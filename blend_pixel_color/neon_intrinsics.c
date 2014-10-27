#include "blend.h"

#define BUILD_NEON_INTRINSICS
#define static
#define _op_blend_p_c_dp_neon _op_blend_p_c_dp_neon_intrinsics
#include "op_blend_pixel_color_neon.c"
#undef _op_blend_p_c_dp_neon
