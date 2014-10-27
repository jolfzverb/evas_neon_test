#include "blend.h"
/* blend color --> dst */
#ifdef __arm__
#define _op_blend_p_dp_neon _op_blend_p_dp_neon_inline_fixed
#define _op_blend_pas_dp_neon _op_blend_pas_dp_neon_inline_fixed
#define static
#define asm __asm__
#include "op_blend_pixel_neon.c"
#undef _op_blend_p_dp_neon
#undef _op_blend_pas_dp_neon
#endif
