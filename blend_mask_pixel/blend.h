#define BUILD_NEON
#define EINA_UNUSED
typedef unsigned int DATA32;
typedef unsigned char DATA8;
#include "evas_blend_ops.h"
#include "evas_common_private.h"

void _op_blend_p_mas_dp(DATA32 *s, DATA8 *m, DATA32 c, DATA32 *d, int l);
void _op_blend_p_mas_dp_neon(DATA32 *s, DATA8 *m, DATA32 c, DATA32 *d, int l);
void _op_blend_pas_mas_dp(DATA32 *s, DATA8 *m, DATA32 c, DATA32 *d, int l);
void _op_blend_pas_mas_dp_neon(DATA32 *s, DATA8 *m, DATA32 c, DATA32 *d, int l);
