#include "blend.h"

#define BUILD_NEON_INTRINSICS
#define static
#define _op_blend_p_dp_neon _op_blend_p_dp_neon_intrinsics
#define _op_blend_pas_dp_neon _op_blend_pas_dp_neon_intrinsics
#include "op_blend_pixel_neon.c"
#undef _op_blend_p_dp_neon
#undef _op_blend_pas_dp_neon
