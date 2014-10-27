#define BUILD_NEON
#define EINA_UNUSED
typedef unsigned int DATA32;
typedef unsigned char DATA8;
#include "evas_blend_ops.h"
#include "evas_common_private.h"

void _op_blend_p_c_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c EINA_UNUSED, DATA32 *d, int l);
void _op_blend_p_c_dp_neon_intrinsics(DATA32 *s, DATA8 *m, DATA32 c, DATA32 *d, int l);
#ifdef __arm__
void _op_blend_p_c_dp_neon_inline(DATA32 *s, DATA8 *m, DATA32 c, DATA32 *d, int l);
#endif
void _op_blend_pan_c_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c EINA_UNUSED, DATA32 *d, int l);
void _op_blend_pan_c_dp_neon(DATA32 *s, DATA8 *m, DATA32 c, DATA32 *d, int l);
void _op_blend_p_can_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c EINA_UNUSED, DATA32 *d, int l);
void _op_blend_p_can_dp_neon(DATA32 *s, DATA8 *m, DATA32 c, DATA32 *d, int l);
void _op_blend_pan_can_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c EINA_UNUSED, DATA32 *d, int l);
void _op_blend_pan_can_dp_neon(DATA32 *s, DATA8 *m, DATA32 c, DATA32 *d, int l);
void _op_blend_p_caa_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c EINA_UNUSED, DATA32 *d, int l);
void _op_blend_p_caa_dp_neon(DATA32 *s, DATA8 *m, DATA32 c, DATA32 *d, int l);
void _op_blend_pan_caa_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c EINA_UNUSED, DATA32 *d, int l);
void _op_blend_pan_caa_dp_neon(DATA32 *s, DATA8 *m, DATA32 c, DATA32 *d, int l);
