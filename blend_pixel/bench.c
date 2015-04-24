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
  DATA32 *d8 = malloc(sizeof(DATA32)*len);
  DATA32 *d9 = malloc(sizeof(DATA32)*len);
  DATA32 *d10 = malloc(sizeof(DATA32)*len);
  DATA32 *d11 = malloc(sizeof(DATA32)*len);
  DATA32 *s = malloc(sizeof(DATA32)*len);
  DATA32 *s1 = malloc(sizeof(DATA32)*len);
  DATA8 *a = NULL;
  int i;

  srand(0);
  DATA32 c = ((rand()&0xffff) << 16) + (rand()&0xffff);
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
    s[i] = i+c;
    if(!(s[i]>>24))
       s[i] = 0;
  }

  printf("10000000 pixels by _op_blend_p_dp:\t");
  start();
  _op_blend_p_dp(s, a, c, d0, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_pas_dp:\t");
  start();
  _op_blend_pas_dp(s, a, c, d1, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_p_dp_neon_intrinsics:\t");
  start();
  _op_blend_p_dp_neon_intrinsics(s, a, c, d2, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_pas_dp_neon_intrinsics:\t");
  start();
  _op_blend_pas_dp_neon_intrinsics(s, a, c, d3, len);
  stop_n_print();

#ifdef __arm__
  printf("10000000 pixels by _op_blend_p_dp_neon_inline_orig:\t");
  start();
  _op_blend_p_dp_neon_inline_orig(s, a, c, d4, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_pas_dp_neon_inline_orig:\t");
  start();
  _op_blend_pas_dp_neon_inline_orig(s, a, c, d5, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_p_dp_neon_inline_fixed:\t");
  start();
  _op_blend_p_dp_neon_inline_fixed(s, a, c, d6, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_pas_dp_neon_inline_fixed:\t");
  start();
  _op_blend_pas_dp_neon_inline_fixed(s, a, c, d7, len);
  stop_n_print();
#endif
  printf("10000000 pixels by _op_blend_rel_p_dp:\t");
  start();
  _op_blend_rel_p_dp(s1, a, c, d8, len);
  stop_n_print();
  printf("10000000 pixels by _op_blend_rel_p_dp_neon:\t");
  start();
  _op_blend_rel_p_dp_neon(s1, a, c, d9, len);
  stop_n_print();
  printf("10000000 pixels by _op_blend_rel_pan_dp:\t");
  start();
  _op_blend_rel_pan_dp(s1, a, c, d10, len);
  stop_n_print();
  printf("10000000 pixels by _op_blend_rel_pan_dp_neon:\t");
  start();
  _op_blend_rel_pan_dp_neon(s1, a, c, d11, len);
  stop_n_print();

  int ret = 0;
  for(i = 0; i < len; i++){
    if(
#ifdef __arm__
          ( d0[i] != d4[i] ) ||
          ( d1[i] != d5[i] ) ||
          ( d0[i] != d6[i] ) ||
          ( d1[i] != d7[i] ) ||
#endif
          ( d0[i] != d2[i] ) ||
          ( d8[i] != d9[i] ) ||
          ( d10[i] != d11[i] ) ||
          ( d1[i] != d3[i] )
      )
      ret = 1;
  }
  free(d0);
  free(d1);
  free(d2);
  free(d3);
#ifdef __arm__
  free(d4);
  free(d5);
  free(d6);
  free(d7);
#endif
  free(d8);
  free(d9);
  free(d10);
  free(d11);
  free(s);
  free(s1);
  return ret;
}
