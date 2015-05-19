#include "copy.h"

#define BUILD_NEON_INTRINSICS
#define static
#define _op_copy_c_dp_neon _op_copy_c_dp_neon_intrinsics
#include "op_copy_color_neon.c"
#undef _op_copy_c_dp_neon
