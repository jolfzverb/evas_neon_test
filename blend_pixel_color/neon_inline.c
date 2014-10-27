#include "blend.h"
/* blend color --> dst */
#ifdef __arm__
#define _op_blend_p_c_dp_neon _op_blend_p_c_dp_neon_inline
#define static
#define asm __asm__
#include "op_blend_pixel_color_neon.c"
#undef _op_blend_p_c_dp_neon
#endif
