#include "blend.h"
/* blend pixel x mask --> dst */

void
_op_blend_rel_p_mas_dp(DATA32 *s, DATA8 *m, DATA32 c, DATA32 *d, int l) {
   DATA32 *e;
   int alpha;
   UNROLL8_PLD_WHILE(d, l, e,
           {
            c = MUL_SYM(*m, *s);
            alpha = 256 - (c >> 24);
            *d = MUL_SYM(*d >> 24, c) + MUL_256(alpha, *d);
            d++; m++; s++;
           });
}
void
_op_blend_p_mas_dp(DATA32 *s, DATA8 *m, DATA32 c, DATA32 *d, int l) {
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
                             alpha = 256 - (*s >> 24);
                             *d = *s + MUL_256(alpha, *d);
                             break;
                          default:
                             c = MUL_SYM(alpha, *s);
                             alpha = 256 - (c >> 24);
                             *d = c + MUL_256(alpha, *d);
                             break;
                          }
                        m++;  s++;  d++;
                     });
}

void
_op_blend_pas_mas_dp(DATA32 *s, DATA8 *m, DATA32 c, DATA32 *d, int l) {
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
                             alpha = 256 - (*s >> 24);
                             *d = *s + MUL_256(alpha, *d);
                             break;
                          default:
                             c = MUL_SYM(alpha, *s);
                             alpha = 256 - (c >> 24);
                             *d = c + MUL_256(alpha, *d);
                             break;
                          }
                        m++;  s++;  d++;
                     });
}
