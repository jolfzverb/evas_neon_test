#ifdef __arm__
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
   FPU_NEON;
   VMOV_I2R_NEON(q2, #255);
#  ifdef COLMUL
#   ifndef COLBLACK
   // this part can be done here as c1 and c2 are constants in the cycle
   FPU_NEON;
   VMOV_M2R_NEON(d18, c1);
   VEOR_NEON(q8);
#    ifndef COLSAME
   VMOV_M2R_NEON(d19, c2);
#    endif
   VZIP_NEON(q9, q8);
#    ifndef COLSAME
   VMOV_R2R_NEON(d19, d16);
#    endif
   // here we have c1 and c2 spread through q9 register
#   endif
#  endif
# endif //SCALE_USING_NEON

   while (ww > 0)
     {
# ifdef COLBLACK
        *d = 0xff000000; // col
# else
        DATA32 ru = *_ru++;
        DATA32 rv = *_rv++;
#ifdef COLMUL
        DATA32 cv = *_cv++;
#endif

        DATA32 val1 = *_val1++;

        DATA32 val2 = *_val2++;

        DATA32 val3 = *_val3++;

        DATA32 val4 = *_val4++;

#  ifdef SCALE_USING_NEON
        // not sure if we need this condition, but it doesn't affect the result
        if (val1 | val2 | val3 | val4)
          {
            FPU_NEON;
#   ifdef COLMUL
            // initialize alpha for interpolation of c1 and c2
            VDUP_NEON(d15, cv >> 16);
            // copy c1 and c2 as algorithm will overwrite it
            VMOV_R2R_NEON(q6, q9);
//            cv += cd; // col
#   endif
            VMOV_M2R_NEON(d8, val1);
            VEOR_NEON(q0);
            VMOV_M2R_NEON(d9, val3);
            VMOV_M2R_NEON(d10, val2);
            VEOR_NEON(q1);
            VMOV_M2R_NEON(d11, val4);
            VDUP_NEON(q3, ru);
            VDUP_NEON(d14, rv);
            VZIP_NEON(q4, q0);
            VZIP_NEON(q5, q1);
            VMOV_R2R_NEON(d9, d0);
            VMOV_R2R_NEON(d11, d2);
            // by this point we have all required data in right registers
            // interpolate val1,val2 and val3,val4
            INTERP_256_NEON(q3, q5, q4, q2);
#   ifdef COLMUL
#    ifdef COLSAME
            INTERP_256_NEON(d14, d9, d8, d4);
#    else
            /* move result of val3,val4 interpolation (and c1 if COLMUL is
               defined) for next step */
            VSWP_NEON(d9, d12);
            /* second stage of interpolation, also here c1 and c2 are
               interpolated */
            INTERP_256_NEON(q7, q6, q4, q2);
#    endif
#   else
            INTERP_256_NEON(d14, d9, d8, d4);
#   endif
#   ifdef COLMUL
#    ifdef COLSAME
            MUL4_SYM_NEON(d8, d12, d4);
#    else
            MUL4_SYM_NEON(d8, d9, d4); // do required multiplication
#    endif
#   endif
            VMOV_R2M_NEON(q4, d8, d); // save result to d
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
//        cv += cd; // col
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
#  ifdef COLMUL
#   ifndef COLBLACK
#    ifdef COLSAME
   FPU_NEON;
   VMOV_I2R_NEON(q2, #255);
   VMOV_M2R_NEON(d10, c1);
   VEOR_NEON(d0);
   VZIP_NEON(d10, d0);
#    else
   // c1 and c2 are constants inside the cycle
   FPU_NEON;
   VMOV_I2R_NEON(q2, #255);
   VMOV_M2R_NEON(d10, c1);
   VEOR_NEON(q0);
   VMOV_M2R_NEON(d11, c2);
   VZIP_NEON(q5, q0);
   VMOV_R2R_NEON(d11, d0);
#    endif
#   endif
#  endif
# endif

   while (ww > 0)
     {
# ifdef COLMUL
#  ifndef COLBLACK
        DATA32 val1;
#   ifdef COLSAME
#   else
        DATA32 cval; // col
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
        val1 = *s; // col
#   ifdef COLSAME
#    ifdef SCALE_USING_NEON
        VMOV_M2R_NEON(d1, val1);
        VEOR_NEON(d0);
        VZIP_NEON(d1, d0);
        VMOV_R2R_NEON(d0, d10);
        MUL4_SYM_NEON(d0, d1, d4)
        VMOV_R2M_NEON(q0, d0, d);
#    else
        *d = MUL4_SYM(c1, val1);
#    endif
#   else
/* XXX: this neon is broken! :( FIXME
#    ifdef SCALE_USING_NEON
        FPU_NEON;
        VMOV_M2R_NEON(d12, val1);
        VMOV_R2R_NEON(q4, q5);
        VEOR_NEON(q1);
        VDUP_NEON(d15, cv >> 16);
        VZIP_NEON(q6, q1);
        INTERP_256_NEON(d15, d9, d8, d4); // interpolate c1 and c2
        MUL4_SYM_NEON(d8, d12, d4); // multiply
        VMOV_R2M_NEON(q4, d8, d); // save result
#    else
 */
        cval = INTERP_256((cv >> 16), c2, c1); // col
        *d = MUL4_SYM(cval, val1);
//        cv += cd; // col
/*
#    endif
 */
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
#endif
