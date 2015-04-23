#include "blend.h"
/* blend pixel x color --> dst */



void
_op_blend_p_c_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c, DATA32 *d, int l) {
   DATA32 *e;
   int alpha;
   UNROLL8_PLD_WHILE(d, l, e,
                     {
                        DATA32 sc = MUL4_SYM(c, *s);
                        alpha = 256 - (sc >> 24);
                        *d = sc + MUL_256(alpha, *d);
                        d++;
                        s++;
                     });
}

void
_op_blend_pan_c_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c, DATA32 *d, int l) {
   DATA32 *e;
   int alpha = 256 - (c >> 24);
   UNROLL8_PLD_WHILE(d, l, e,
                     {
                        *d = ((c & 0xff000000) + MUL3_SYM(c, *s)) + MUL_256(alpha, *d);
                        d++;
                        s++;
                     });
}

void
_op_blend_p_can_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c, DATA32 *d, int l) {
   DATA32 *e;
   int alpha;
   UNROLL8_PLD_WHILE(d, l, e,
                     {
                        alpha = 256 - (*s >> 24);
                        *d = ((*s & 0xff000000) + MUL3_SYM(c, *s)) + MUL_256(alpha, *d);
                        d++;
                        s++;
                     });
}

void
_op_blend_pan_can_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c, DATA32 *d, int l) {
   DATA32 *e;
   UNROLL8_PLD_WHILE(d, l, e,
                     {
                        *d++ = 0xff000000 + MUL3_SYM(c, *s);
                        s++;
                     });
}

void
_op_blend_p_caa_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c, DATA32 *d, int l) {
   DATA32 *e;
   int alpha;
   c = 1 + (c & 0xff);
   UNROLL8_PLD_WHILE(d, l, e,
                     {
                        DATA32 sc = MUL_256(c, *s);
                        alpha = 256 - (sc >> 24);
                        *d = sc + MUL_256(alpha, *d);
                        d++;
                        s++;
                     });
}

void
_op_blend_pan_caa_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c, DATA32 *d, int l) {
   DATA32 *e;
   c = 1 + (c & 0xff);
   UNROLL8_PLD_WHILE(d, l, e,
                     {
                        *d = INTERP_256(c, *s, *d);
                        d++;
                        s++;
                     });
}

void
_op_blend_rel_p_c_dp(DATA32 *s, DATA8 *m EINA_UNUSED, DATA32 c, DATA32 *d, int l) {
   DATA32 *e;
   int alpha;
   UNROLL8_PLD_WHILE(d, l, e,
                     {
                        DATA32 sc = MUL4_SYM(c, *s);
                        alpha = 256 - (sc >> 24);
                        *d = MUL_SYM(*d >> 24, sc) + MUL_256(alpha, *d);
                        d++;
                        s++;
                     });
}
