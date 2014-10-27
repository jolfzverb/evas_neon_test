#include "blend.h"
/* blend color --> dst */
#ifdef __arm__
#define _op_blend_mas_c_dp_neon _op_blend_mas_c_dp_neon_inline
#define _op_blend_mas_can_dp_neon _op_blend_mas_can_dp_neon_inline
#define static
#define asm __asm__
#include "op_blend_mask_color_neon.c"
#undef _op_blend_mas_c_dp_neon
#undef _op_blend_mas_can_dp_neon
#endif
