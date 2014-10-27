#include <stdlib.h>
#include <stdio.h>
#include <arm_neon.h>
#include "time.h"
#include "blend.h"

int main(){
  printf("\nScaling benchmark started!\nHope you compiled right version=)\n\n");
  int len = 10000000;
  srand(0);

  DATA32 *d0 = malloc(sizeof(DATA32)*len);
  DATA32 *d1 = malloc(sizeof(DATA32)*len);
#ifdef __arm__
  DATA32 *d2 = malloc(sizeof(DATA32)*len);
#endif
  DATA32 *d3 = malloc(sizeof(DATA32)*len);
  DATA32 *d4 = malloc(sizeof(DATA32)*len);
  DATA32 *d5 = malloc(sizeof(DATA32)*len);
  DATA32 *d6 = malloc(sizeof(DATA32)*len);
  DATA32 *d7 = malloc(sizeof(DATA32)*len);
  DATA32 *d8 = malloc(sizeof(DATA32)*len);
  DATA32 *d9 = malloc(sizeof(DATA32)*len);
  DATA32 *d10 = malloc(sizeof(DATA32)*len);
  DATA32 *d11 = malloc(sizeof(DATA32)*len);
  DATA32 *d12 = malloc(sizeof(DATA32)*len);
  DATA32 *d13 = malloc(sizeof(DATA32)*len);
  DATA32 *d14 = malloc(sizeof(DATA32)*len);
  DATA8 *m = malloc(sizeof(DATA8)*len);
  DATA32 *s = malloc(sizeof(DATA32)*len);
  DATA32 c = ((rand()&0xffff) << 16) + (rand()&0xffff);
  int i;

  for(i = 0; i < len; i++){
    d0[i] =
    d1[i] =
    d3[i] =
    d4[i] =
    d5[i] =
    d6[i] =
    d7[i] =
    d8[i] =
    d9[i] =
    d10[i] =
    d11[i] =
    d12[i] =
    d13[i] =
    d14[i] =
    s[i] =
#ifdef __arm__
    d2[i] =
#endif
          i+c;
    m[i] = i&0xff;
  }

  printf("10000000 pixels by _op_blend_p_c_dp:\t");
  start();
  _op_blend_p_c_dp(s, m, c, d0, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_p_c_dp_neon_intrinsics:\t");
  start();
  _op_blend_p_c_dp_neon_intrinsics(s, m, c, d1, len);
  stop_n_print();

#ifdef __arm__
  printf("10000000 pixels by _op_blend_p_c_dp_neon_inline:\t");
  start();
  _op_blend_p_c_dp_neon_inline(s, m, c, d2, len);
  stop_n_print();
#endif

  printf("10000000 pixels by _op_blend_pan_c_dp:\t");
  start();
  _op_blend_pan_c_dp(s, m, c, d3, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_pan_c_dp_neon:\t");
  start();
  _op_blend_pan_c_dp_neon(s, m, c, d4, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_p_can_dp:\t");
  start();
  _op_blend_p_can_dp(s, m, c, d5, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_p_can_dp_neon:\t");
  start();
  _op_blend_p_can_dp_neon(s, m, c, d6, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_pan_can_dp:\t");
  start();
  _op_blend_pan_can_dp(s, m, c, d7, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_pan_can_dp_neon:\t");
  start();
  _op_blend_pan_can_dp_neon(s, m, c, d8, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_p_caa_dp:\t");
  start();
  _op_blend_p_caa_dp(s, m, c, d9, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_p_caa_dp_neon:\t");
  start();
  _op_blend_p_caa_dp_neon(s, m, c, d10, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_pan_caa_dp:\t");
  start();
  _op_blend_pan_caa_dp(s, m, c, d11, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_pan_caa_dp_neon:\t");
  start();
  _op_blend_pan_caa_dp_neon(s, m, c, d12, len);
  stop_n_print();

  c = 0;

  printf("10000000 pixels by _op_blend_pan_c_dp with NULL c:\t");
  start();
  _op_blend_pan_c_dp(s, m, c, d13, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_pan_c_dp_neon with NULL c:\t");
  start();
  _op_blend_pan_c_dp_neon(s, m, c, d14, len);
  stop_n_print();

  for(i = 0; i < len; i++){
    if(
#ifdef __arm__
          (d2[i]!=d0[i]) ||
#endif
          (d3[i]!=d4[i]) ||
          (d5[i]!=d6[i]) ||
          (d7[i]!=d8[i]) ||
          (d9[i]!=d10[i]) ||
          (d11[i]!=d12[i]) ||
          (d13[i]!=d14[i]) ||
          (d1[i]!=d0[i])
      )
      return 1;
  }
  return 0;
}
