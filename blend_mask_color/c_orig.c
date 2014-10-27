#include "blend.h"
/* blend color -> dst */

void
_op_blend_mas_c_dp(DATA32 *s EINA_UNUSED, DATA8 *m, DATA32 c, DATA32 *d, int l) {
   DATA32 *e;
   int alpha = 256 - (c >> 24);
   UNROLL8_PLD_WHILE(d, l, e,
                     {
                        DATA32 a = *m;
                        switch(a)
                          {
                          case 0:
                             break;
                          case 255:
                             *d = c + MUL_256(alpha, *d);
                             break;
                          default:
                               {
                                  DATA32 mc = MUL_SYM(a, c);
                                  a = 256 - (mc >> 24);
                                  *d = mc + MUL_256(a, *d);
                               }
                             break;
                          }
                        m++;  d++;
                     });
}

void
_op_blend_mas_can_dp(DATA32 *s EINA_UNUSED, DATA8 *m, DATA32 c, DATA32 *d, int l) {
   DATA32 *e;
   int alpha;
   UNROLL8_PLD_WHILE(d, l, e,
                     {
                        alpha = *m;
                        switch(alpha)
                          {
                          case 0:
                             break;
                          case 255:
                             *d = c;
                             break;
                          default:
                             alpha++;
                             *d = INTERP_256(alpha, c, *d);
                             break;
                          }
                        m++;  d++;
                     });
}
