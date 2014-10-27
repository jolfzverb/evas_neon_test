#include "blend.h"

#define BUILD_NEON_INTRINSICS
#define static
#define _op_blend_mas_c_dp_neon _op_blend_mas_c_dp_neon_intrinsics
#define _op_blend_mas_can_dp_neon _op_blend_mas_can_dp_neon_intrinsics
#include "op_blend_mask_color_neon.c"
#undef _op_blend_mas_c_dp_neon
#undef _op_blend_mas_can_dp_neon
