#include "blend.h"
/* blend pixel --> dst */

void
_op_blend_p_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c EINA_UNUSED, DATA32 *d, int l) {
   DATA32 *e;
   int alpha;
   UNROLL8_PLD_WHILE(d, l, e,
                     {
                        alpha = 256 - (*s >> 24);
                        *d = *s++ + MUL_256(alpha, *d);
                        d++;
                     });
}

void
_op_blend_pas_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c EINA_UNUSED, DATA32 *d, int l) {
   DATA32 *e;
   int alpha;
   UNROLL8_PLD_WHILE(d, l, e,
                     {
                        switch (*s & 0xff000000)
                          {
                          case 0:
                             break;
                          case 0xff000000:
                             *d = *s;
                             break;
                          default:
                             alpha = 256 - (*s >> 24);
                             *d = *s + MUL_256(alpha, *d);
                             break;
                          }
                        s++;  d++;
                     });
}
