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
  DATA8 *m = malloc(sizeof(DATA8)*len);
  DATA32 *s = NULL;
  int i;
  srand(0);

//  DATA8 a = rand()&0xff;
//  DATA8 r = rand()&0xff;
//  DATA8 g = rand()&0xff;
//  DATA8 b = rand()&0xff;
//  if((a<r)||(a<g)||(a<b)){
//     r = r/2;
//     g = g/2;
//     b = b/2;
//  }
//  while((a<r)||(a<g)||(a<b)){
//     a++;
//  }
  DATA32 c = ((rand()&0xffff) << 16) + (rand()&0xffff);
  //DATA32 c = (a<<24)+(r<<16)+(g<<8)+b;

  for(i = 0; i < len; i++){
    d0[i] =
    d1[i] =
    d2[i] =
    d3[i] =
#ifdef __arm__
    d4[i] =
    d5[i] =
#endif
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

  for(i = 0; i < len; i++){
    if(
#ifdef __arm__
          (d4[i]!=d0[i]) ||
          (d5[i]!=d1[i]) ||
#endif
          (d3[i]!=d1[i]) ||
          (d2[i]!=d0[i])
      )
      return 1;
  }
  return 0;
}
