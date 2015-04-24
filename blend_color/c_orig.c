#include "blend.h"
/* blend color -> dst */

void
_op_blend_rel_c_dp(DATA32 *s EINA_UNUSED, DATA8 *m EINA_UNUSED, DATA32 c, DATA32 *d, int l) {
   DATA32 *e;
   int alpha = 256 - (c >> 24);
   UNROLL8_PLD_WHILE(d, l, e,
                     {
                        *d = MUL_SYM(*d >> 24, c) + MUL_256(alpha, *d);
                        d++;
                     });
}
void
_op_blend_c_dp(DATA32 *s EINA_UNUSED, DATA8 *m EINA_UNUSED, DATA32 c, DATA32 *d, int l) {
    DATA32 *e, a = 256 - (c >> 24);
    UNROLL8_PLD_WHILE(d, l, e,
                      {
                         *d = c + MUL_256(a, *d);
                         d++;
                      });
}
