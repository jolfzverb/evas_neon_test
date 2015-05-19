#include "copy.h"
/* copy color --> dst */
#ifdef __arm__
#define _op_copy_c_dp_neon _op_copy_c_dp_neon_inline
#define static
#define asm __asm__
#include "op_copy_color_neon.c"
#undef _op_copy_c_dp_neon
#endif
