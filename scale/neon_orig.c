#include <arm_neon.h>
#include "scale.h"

int neon_orig(DATA32* _p0, DATA32* _p1, DATA32* _p2, DATA32* _p3, DATA32* _ax, DATA32 _ay, DATA32* result, int len) {

  int ay = _ay;
  int i;
  DATA32* pbuf = result;
  __asm__ __volatile__(".fpu neon \n\t");;
  __asm__ __volatile__("vdup.16 d12, %[val] \n\t" :: [val] "r" (ay) : "d12");;
  __asm__ __volatile__("vmov.i16 q2, #255 \n\t" ::: "q2");;


  for(i = 0; i < len; i++) {

    DATA32 p0 = *_p0++;
    DATA32 p1 = *_p1++;
    DATA32 p2 = *_p2++;
    DATA32 p3 = *_p3++;
    int ax = *_ax++;
    if (p0 | p1 | p2 | p3) {

      __asm__ __volatile__(".fpu neon \n\t");;
      __asm__ __volatile__("vmov.32 d8[0], %[val] \n\t" :: [val] "r" (p0) : "d8");;
      __asm__ __volatile__("veor q0, q0, q0 \n\t" ::: "q0");;
      __asm__ __volatile__("vmov.32 d9[0], %[val] \n\t" :: [val] "r" (p2) : "d9");;
      __asm__ __volatile__("vmov.32 d10[0], %[val] \n\t" :: [val] "r" (p1) : "d10");;
      __asm__ __volatile__("veor q1, q1, q1 \n\t" ::: "q1");;
      __asm__ __volatile__("vmov.32 d11[0], %[val] \n\t" :: [val] "r" (p3) : "d11");;
      __asm__ __volatile__("vdup.16 q3, %[val] \n\t" :: [val] "r" (ax) : "q3");;
      __asm__ __volatile__("vzip.8 q4, q0 \n\t" ::: "q4" , "q0");;
      __asm__ __volatile__("vzip.8 q5, q1 \n\t" ::: "q5" , "q1");;
      __asm__ __volatile__("vmov d9, d0 \n\t" ::: "d9");;
      __asm__ __volatile__("vmov d11, d2 \n\t" ::: "d11");;
      __asm__ __volatile__(
          "vsub.i16 q5, q5, q4 \n\t"
          "vmul.u16 q5, q5, q3 \n\t"
          "vsri.16 q5, q5, #8 \n\t"
          "vadd.i16 q5, q5, q4 \n\t"
          "vand q4, q5, q2 \n\t" ::: "q5", "q4" );;
      __asm__ __volatile__(
          "vsub.i16 d9, d9, d8 \n\t"
          "vmul.u16 d9, d9, d12 \n\t"
          "vsri.16 d9, d9, #8 \n\t"
          "vadd.i16 d9, d9, d8 \n\t"
          "vand d8, d9, d5 \n\t" ::: "d9", "d8" );;
      __asm__ __volatile__(
          "vqmovn.u16 d8, q4 \n\t"
          "vst1.32 {d8[0]}, [%[p]] \n\t" :: [p] "r" (pbuf) : "d8", "memory");;
      pbuf++;
    }
    else
      *pbuf++ = p0;
  }
	return 0;
}

