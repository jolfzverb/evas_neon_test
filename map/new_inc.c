#ifdef SMOOTH
{
  DATA32 *d = result;
  int ww = len;
#ifdef COLMUL
#ifndef COLBLACK
  DATA32 c1 = _c1;
#ifndef COLSAME
  DATA32 c2 = _c2;
#endif
#endif
#endif
# ifdef SCALE_USING_NEON
#  ifndef COLBLACK
   uint16x4_t temp_16x4;
   uint16x4_t rv_16x4;
   uint16x4_t val1_16x4;
   uint16x4_t val3_16x4;
   uint16x8_t ru_16x8;
   uint16x8_t val1_val3_16x8;
   uint16x8_t val2_val4_16x8;
   uint16x8_t x255_16x8;
   uint32x2_t res_32x2;
   uint32x2_t val1_val3_32x2;
   uint32x2_t val2_val4_32x2;
   uint8x8_t val1_val3_8x8;
   uint8x8_t val2_val4_8x8;

   x255_16x8 = vdupq_n_u16(0xff);
#   ifdef COLMUL
   uint16x4_t x255_16x4;
   x255_16x4 = vget_low_u16(x255_16x8);
   uint16x4_t c1_16x4;
#    ifdef COLSAME
   uint16x4_t c1_val3_16x4;
   uint16x8_t c1_16x8;
   uint16x8_t c1_val3_16x8;
   uint32x2_t c1_32x2;
   uint8x8_t c1_8x8;
   uint8x8_t c1_val3_8x8;

   c1_32x2 = vset_lane_u32(c1, c1_32x2, 0);
   c1_8x8 = vreinterpret_u8_u32(c1_32x2);
   c1_16x8 = vmovl_u8(c1_8x8);
   c1_16x4 = vget_low_u16(c1_16x8);
#    else
   uint16x4_t c2_16x4;
   uint16x4_t c2_local_16x4;
   uint16x4_t cv_16x4;
   uint16x8_t c1_c2_16x8;
   uint16x8_t c1_val1_16x8;
   uint16x8_t c2_val3_16x8;
   uint16x8_t cv_rv_16x8;
   uint32x2_t c1_c2_32x2;
   uint8x8_t c1_c2_8x8;
   uint8x8_t val3_8x8;
   uint16x8_t val3_16x8;

   c1_c2_32x2 = vset_lane_u32(c1, c1_c2_32x2, 0);
   c1_c2_32x2 = vset_lane_u32(c2, c1_c2_32x2, 1);
   c1_c2_8x8 = vreinterpret_u8_u32(c1_c2_32x2);
   c1_c2_16x8 = vmovl_u8(c1_c2_8x8);
   c1_16x4 = vget_low_u16(c1_c2_16x8);
   c2_16x4 = vget_high_u16(c1_c2_16x8);
#    endif //COLSAME
#   else
   uint8x8_t val3_8x8;
   uint16x8_t val3_16x8;
#   endif //COLMUL
#  endif //COLBLACK
# endif //SCALE_USING_NEON

   while (ww > 0)
     {
# ifdef COLBLACK
        *d = 0xff000000; // col
# else
        DATA32 ru = *_ru++;
        DATA32 rv = *_rv++;
#ifdef COLMUL
#ifndef COLBLACK
#ifndef COLSAME
        DATA32 cv = *_cv++;
#endif
#endif
#endif

        DATA32 val1 = *_val1++;

        DATA32 val2 = *_val2++;

        DATA32 val3 = *_val3++;

        DATA32 val4 = *_val4++;

#  ifdef SCALE_USING_NEON
        if (val1 | val2 | val3 | val4)
          {
             rv_16x4 = vdup_n_u16(rv);
             ru_16x8 = vdupq_n_u16(ru);

             val1_val3_32x2 = vset_lane_u32(val1, val1_val3_32x2, 0);
             val1_val3_32x2 = vset_lane_u32(val3, val1_val3_32x2, 1);
             val2_val4_32x2 = vset_lane_u32(val2, val2_val4_32x2, 0);
             val2_val4_32x2 = vset_lane_u32(val4, val2_val4_32x2, 1);

             val1_val3_8x8 = vreinterpret_u8_u32(val1_val3_32x2);
             val2_val4_8x8 = vreinterpret_u8_u32(val2_val4_32x2);

             val2_val4_16x8 = vmovl_u8(val2_val4_8x8);
             val1_val3_16x8 = vmovl_u8(val1_val3_8x8);

             val2_val4_16x8 = vsubq_u16(val2_val4_16x8, val1_val3_16x8);
             val2_val4_16x8 = vmulq_u16(val2_val4_16x8, ru_16x8);
             val2_val4_16x8 = vshrq_n_u16(val2_val4_16x8, 8);
             val2_val4_16x8 = vaddq_u16(val2_val4_16x8, val1_val3_16x8);
             val2_val4_16x8 = vandq_u16(val2_val4_16x8, x255_16x8);

             val1_16x4 = vget_low_u16(val2_val4_16x8);
             val3_16x4 = vget_high_u16(val2_val4_16x8);
#   ifdef COLMUL
#    ifdef COLSAME

             val3_16x4 = vsub_u16(val3_16x4, val1_16x4);
             val3_16x4 = vmul_u16(val3_16x4, rv_16x4);
             val3_16x4 = vshr_n_u16(val3_16x4, 8);
             val3_16x4 = vadd_u16(val3_16x4, val1_16x4);
             val3_16x4 = vand_u16(val3_16x4, x255_16x4);

             c1_val3_16x4 = vmul_u16(c1_16x4, val3_16x4);
             c1_val3_16x4 = vadd_u16(c1_val3_16x4, x255_16x4);

             c1_val3_16x8 = vcombine_u16(c1_val3_16x4, temp_16x4);

             c1_val3_8x8 = vshrn_n_u16(c1_val3_16x8, 8);
             res_32x2 = vreinterpret_u32_u8(c1_val3_8x8);
#    else
             c1_val1_16x8 = vcombine_u16(c1_16x4, val1_16x4);
             c2_val3_16x8 = vcombine_u16(c2_16x4, val3_16x4);

             cv_16x4 = vdup_n_u16(cv>>16);
             //cv += cd;
             cv_rv_16x8 = vcombine_u16(cv_16x4, rv_16x4);

             c2_val3_16x8 = vsubq_u16(c2_val3_16x8, c1_val1_16x8);
             c2_val3_16x8 = vmulq_u16(c2_val3_16x8, cv_rv_16x8);
             c2_val3_16x8 = vshrq_n_u16(c2_val3_16x8, 8);
             c2_val3_16x8 = vaddq_u16(c2_val3_16x8, c1_val1_16x8);
             c2_val3_16x8 = vandq_u16(c2_val3_16x8, x255_16x8);

             c2_local_16x4 = vget_low_u16(c2_val3_16x8);
             val3_16x4 = vget_high_u16(c2_val3_16x8);

             val3_16x4 = vmul_u16(c2_local_16x4, val3_16x4);
             val3_16x4 = vadd_u16(val3_16x4, x255_16x4);

             val3_16x8 = vcombine_u16(val3_16x4, temp_16x4);

             val3_8x8 = vshrn_n_u16(val3_16x8, 8);
             res_32x2 = vreinterpret_u32_u8(val3_8x8);
#    endif
#   else
             val3_16x4 = vsub_u16(val3_16x4, val1_16x4);
             val3_16x4 = vmul_u16(val3_16x4, rv_16x4);
             val3_16x4 = vshr_n_u16(val3_16x4, 8);
             val3_16x4 = vadd_u16(val3_16x4, val1_16x4);

             val3_16x8 = vcombine_u16(val3_16x4, temp_16x4);

             val3_8x8 = vmovn_u16(val3_16x8);
             res_32x2 = vreinterpret_u32_u8(val3_8x8);
#   endif
             vst1_lane_u32(d, res_32x2, 0);
          }
        else
          *d = val1;
#  else
        val1 = INTERP_256(ru, val2, val1);
        val3 = INTERP_256(ru, val4, val3);
        val1 = INTERP_256(rv, val3, val1); // col
#   ifdef COLMUL
#    ifdef COLSAME
        *d = MUL4_SYM(c1, val1);
#    else
        val2 = INTERP_256((cv >> 16), c2, c1); // col
        *d   = MUL4_SYM(val2, val1); // col
        //cv += cd; // col
#    endif
#   else
        *d   = val1;
#   endif
#  endif
//        u += ud;
//        v += vd;
# endif //COLBLACK
        d++;
        ww--;
     }
}
#else
{
  DATA32 *d = result;
  int ww = len;
#ifdef COLMUL
#ifndef COLBLACK
  DATA32 c1 = _c1;
#ifndef COLSAME
  DATA32 c2 = _c2;
#endif
#endif
#endif
# ifdef SCALE_USING_NEON
#  ifndef COLBLACK
#   ifdef COLMUL
   uint16x4_t x255_16x4;
   uint16x4_t temp_16x4;
   uint16x8_t cval_16x8;
   uint32x2_t res_32x2;
   uint8x8_t cval_8x8;
   uint16x4_t c1_16x4;
   uint16x4_t cval_16x4;
   uint16x4_t val1_16x4;
   uint32x2_t val1_32x2;
   uint8x8_t val1_8x8;

   x255_16x4 = vdup_n_u16(0xff);
#    ifdef COLSAME
   uint16x8_t c1_16x8;
   uint16x8_t val1_16x8;
   uint32x2_t c1_32x2;
   uint8x8_t c1_8x8;

   c1_32x2 = vset_lane_u32(c1, c1_32x2, 0);

   c1_8x8 = vreinterpret_u8_u32(c1_32x2);
   c1_16x8 = vmovl_u8(c1_8x8);

   c1_16x4 = vget_low_u16(c1_16x8);
#    else
   uint16x4_t c2_16x4;
   uint16x4_t c2_c1_16x4;
   uint16x4_t c2_c1_local_16x4;
   uint16x4_t cv_16x4;
   uint16x8_t c1_c2_16x8;
   uint16x8_t val1_16x8;
   uint32x2_t c1_c2_32x2;
   uint8x8_t c1_c2_8x8;

   c1_c2_32x2 = vset_lane_u32(c1, c1_c2_32x2, 0);
   c1_c2_32x2 = vset_lane_u32(c2, c1_c2_32x2, 1);

   c1_c2_8x8 = vreinterpret_u8_u32(c1_c2_32x2);
   c1_c2_16x8 = vmovl_u8(c1_c2_8x8);

   c1_16x4 = vget_low_u16(c1_c2_16x8);
   c2_16x4 = vget_high_u16(c1_c2_16x8);

   c2_c1_16x4 = vsub_u16(c2_16x4, c1_16x4);
#    endif
#   endif
#  endif
# endif

   while (ww > 0)
     {
# ifndef SCALE_USING_NEON
#  ifdef COLMUL
#   ifndef COLBLACK
        DATA32 val1;
#    ifdef COLSAME
#    else
        DATA32 cval; // col
#    endif
#   endif
#  endif
# endif

# ifdef COLBLACK
        *d = 0xff000000; // col
# else
#ifdef COLMUL
#ifndef COLBLACK
#ifndef COLSAME
        DATA32 cv = *_cv++;
#endif
#endif
#endif
        DATA32 * s = _val1++;
#  ifdef COLMUL
#   ifdef SCALE_USING_NEON
#    ifdef COLSAME
        val1_32x2 = vset_lane_u32(*s, val1_32x2, 0);
        val1_8x8 = vreinterpret_u8_u32(val1_32x2);
        val1_16x8 = vmovl_u8(val1_8x8);
        val1_16x4 = vget_low_u16(val1_16x8);
        cval_16x4 = c1_16x4;
#    else
        cv_16x4 = vdup_n_u16(cv>>16);
//        cv += cd; // col

        c2_c1_local_16x4 = vmul_u16(c2_c1_16x4, cv_16x4);
        c2_c1_local_16x4 = vshr_n_u16(c2_c1_local_16x4, 8);
        c2_c1_local_16x4 = vadd_u16(c2_c1_local_16x4, c1_16x4);
        cval_16x4 = vand_u16(c2_c1_local_16x4, x255_16x4);
        val1_32x2 = vset_lane_u32(*s, val1_32x2, 0);
        val1_8x8 = vreinterpret_u8_u32(val1_32x2);
        val1_16x8 = vmovl_u8(val1_8x8);
        val1_16x4 = vget_low_u16(val1_16x8);
#    endif
        cval_16x4 = vmul_u16(cval_16x4, val1_16x4);
        cval_16x4 = vadd_u16(cval_16x4, x255_16x4);

        cval_16x8 = vcombine_u16(cval_16x4, temp_16x4);

        cval_8x8 = vshrn_n_u16(cval_16x8, 8);
        res_32x2 = vreinterpret_u32_u8(cval_8x8);

        vst1_lane_u32(d, res_32x2, 0);
#   else
        val1 = *s; // col
#    ifdef COLSAME
        *d = MUL4_SYM(c1, val1);
#    else
        cval = INTERP_256((cv >> 16), c2, c1); // col
        *d = MUL4_SYM(cval, val1);
//        cv += cd; // col              
#    endif
#   endif
#  else
        *d = *s;
#  endif
//        u += ud;
//        v += vd;
# endif
        d++;
        ww--;
     }
}
#endif
