#include <stdlib.h>
#include <stdio.h>
#include <arm_neon.h>
#include "time.h"
#include "blend.h"

int main(){
  printf("\nScaling benchmark started!\nHope you compiled right version=)\n\n");
  int len = 10000000;
  DATA32 *d0 = malloc(sizeof(DATA32)*len);
  DATA32 *d1 = malloc(sizeof(DATA32)*len);
  DATA32 *d2 = malloc(sizeof(DATA32)*len);
  DATA32 *d3 = malloc(sizeof(DATA32)*len);
#ifdef __arm__
  DATA32 *d4 = malloc(sizeof(DATA32)*len);
  DATA32 *d5 = malloc(sizeof(DATA32)*len);
  DATA32 *d6 = malloc(sizeof(DATA32)*len);
  DATA32 *d7 = malloc(sizeof(DATA32)*len);
#endif
  DATA32 *s = malloc(sizeof(DATA32)*len);
  DATA8 *a = NULL;
  int i;

  srand(0);
  DATA32 ay = ((rand()&0xffff) << 16) + (rand()&0xffff);
  for(i = 0; i < len; i++){
    d0[i] =
    d1[i] =
    d2[i] =
    d3[i] =
#ifdef __arm__
    d4[i] =
    d5[i] =
    d6[i] =
    d7[i] =
#endif
    s[i] = i+ay;
    if(!(s[i]>>24))
       s[i] = 0;
  }

  printf("10000000 pixels by _op_blend_p_dp:\t");
  start();
  _op_blend_p_dp(s, a, ay, d0, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_pas_dp:\t");
  start();
  _op_blend_pas_dp(s, a, ay, d1, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_p_dp_neon_intrinsics:\t");
  start();
  _op_blend_p_dp_neon_intrinsics(s, a, ay, d2, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_pas_dp_neon_intrinsics:\t");
  start();
  _op_blend_pas_dp_neon_intrinsics(s, a, ay, d3, len);
  stop_n_print();

#ifdef __arm__
  printf("10000000 pixels by _op_blend_p_dp_neon_inline_orig:\t");
  start();
  _op_blend_p_dp_neon_inline_orig(s, a, ay, d4, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_pas_dp_neon_inline_orig:\t");
  start();
  _op_blend_pas_dp_neon_inline_orig(s, a, ay, d5, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_p_dp_neon_inline_fixed:\t");
  start();
  _op_blend_p_dp_neon_inline_fixed(s, a, ay, d6, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_pas_dp_neon_inline_fixed:\t");
  start();
  _op_blend_pas_dp_neon_inline_fixed(s, a, ay, d7, len);
  stop_n_print();
#endif

  for(i = 0; i < len; i++){
    if(
#ifdef __arm__
          ( d0[i] != d4[i] ) ||
          ( d1[i] != d5[i] ) ||
          ( d0[i] != d6[i] ) ||
          ( d1[i] != d7[i] ) ||
#endif
          ( d0[i] != d2[i] ) ||
          ( d1[i] != d3[i] )
      )
      return 1;
  }
  return 0;
}
