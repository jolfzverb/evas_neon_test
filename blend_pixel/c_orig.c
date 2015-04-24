#include "blend.h"
/* blend pixel --> dst */

void
_op_blend_rel_p_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c, DATA32 *d, int l) {
   DATA32 *e;
   int alpha;
   UNROLL8_PLD_WHILE(d, l, e,
                     {
                        alpha = 256 - (*s >> 24);
                        c = 1 + (*d >> 24);
                        *d = MUL_256(c, *s) + MUL_256(alpha, *d);
                        d++;
                        s++;
                     });
}

void
_op_blend_rel_pan_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c, DATA32 *d, int l) {
   DATA32 *e;
   UNROLL8_PLD_WHILE(d, l, e,
                     {
                        c = 1 + (*d >> 24);
                        *d++ = MUL_256(c, *s);
                        s++;
                     });
}

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
