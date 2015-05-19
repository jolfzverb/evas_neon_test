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
#endif
  DATA32 *d6 = malloc(sizeof(DATA32)*len);
  DATA32 *d7 = malloc(sizeof(DATA32)*len);
  DATA8 *m = malloc(sizeof(DATA8)*len);
  DATA32 *s = NULL;
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
#endif
    d6[i] =
    d7[i] =
          i+c;
    m[i] = i&0xff;
  }

  //int alpha = (c>>24);
  //c = ((MUL_256(alpha,c))&0xffffff)+(alpha<<24);

  printf("10000000 pixels by _op_blend_mas_c_dp:\t");
  start();
  _op_blend_mas_c_dp(s, m, c, d0, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_mas_can_dp:\t");
  start();
  _op_blend_mas_can_dp(s, m, c, d1, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_mas_c_dp_neon_intrinsics:\t");
  start();
  _op_blend_mas_c_dp_neon_intrinsics(s, m, c, d2, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_mas_can_dp_neon_intrinsics:\t");
  start();
  _op_blend_mas_can_dp_neon_intrinsics(s, m, c, d3, len);
  stop_n_print();

#ifdef __arm__
  printf("10000000 pixels by _op_blend_mas_c_dp_neon_inline:\t");
  start();
  _op_blend_mas_c_dp_neon_inline(s, m, c, d4, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_mas_can_dp_neon_inline:\t");
  start();
  _op_blend_mas_can_dp_neon_inline(s, m, c, d5, len);
  stop_n_print();
#endif
  printf("10000000 pixels by _op_blend_rel_mas_c_dp:\t");
  start();
  _op_blend_rel_mas_c_dp(s, m, c, d6, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_rel_mas_c_dp_neon:\t");
  start();
  _op_blend_rel_mas_c_dp_neon(s, m, c, d7, len);
  stop_n_print();

  int ret = 0;
  for(i = 0; i < len; i++){
    if(
#ifdef __arm__
          (d4[i]!=d0[i]) ||
          (d5[i]!=d1[i]) ||
#endif
          (d6[i]!=d7[i]) ||
          (d3[i]!=d1[i]) ||
          (d2[i]!=d0[i])
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
#endif
  free(d6);
  free(d7);
  free(m);
  return ret;
}
