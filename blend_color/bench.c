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
  DATA32 *d3 = malloc(sizeof(DATA32)*len);
  DATA32 *d4 = malloc(sizeof(DATA32)*len);
#ifdef __arm__
  DATA32 *d2 = malloc(sizeof(DATA32)*len);
  DATA32 *d5 = malloc(sizeof(DATA32)*len);
#endif
  DATA32 *s = NULL;
  DATA8 *a = NULL;
  int i;
  srand(0);

  DATA32 c = ((rand()&0xffff) << 16) + (rand()&0xffff);
  if(c>>24 == 0)
     c=0;

  for(i = 0; i < len; i++){
    d0[i] =
    d1[i] =
    d3[i] =
    d4[i] =
#ifdef __arm__
    d2[i] =
    d5[i] =
#endif
          i+c;
  }

  printf("10000000 pixels by _op_blend_c_dp:\t");
  start();
  _op_blend_c_dp(s, a, c, d0, len);
  stop_n_print();
  printf("10000000 pixels by _op_blend_c_dp_neon_intrinsics:\t");
  start();
  _op_blend_c_dp_neon_intrinsics(s, a, c, d1, len);
  stop_n_print();
#ifdef __arm__
  printf("10000000 pixels by _op_blend_c_dp_neon_inline:\t");
  start();
  _op_blend_c_dp_neon_inline(s, a, c, d2, len);
  stop_n_print();
#endif
  c = 0;
  printf("10000000 pixels by _op_blend_c_dp with null alpha:\t");
  start();
  _op_blend_c_dp(s, a, c, d3, len);
  stop_n_print();
  printf("10000000 pixels by _op_blend_c_dp_neon_intrinsics with null alpha:\t");
  start();
  _op_blend_c_dp_neon_intrinsics(s, a, c, d4, len);
  stop_n_print();
#ifdef __arm__
  printf("10000000 pixels by _op_blend_c_dp_neon_inline with null alpha:\t");
  start();
  _op_blend_c_dp_neon_inline(s, a, c, d5, len);
  stop_n_print();
#endif

  for(i = 0; i < len; i++){
    if(
#ifdef __arm__
          (d2[i]!=d0[i]) ||
          (d3[i]!=d5[i]) ||
#endif
          (d3[i]!=d4[i]) ||
          (d0[i]!=d1[i])
      )
      return 1;
  }
  return 0;
}
