#include <stdlib.h>
#include <stdio.h>
#include "correct.h"
#include "blend.h"

int main(){
  printf("\nScaling correctness test started!\nHope you compiled right version=)\n\n");
  int len = 1000000;
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
  DATA32 *d15 = malloc(sizeof(DATA32)*len);
  DATA32 *d16 = malloc(sizeof(DATA32)*len);
  DATA8 *m = malloc(sizeof(DATA8)*len);
  DATA32 *s = malloc(sizeof(DATA32)*len);
  DATA32 c = ((rand()&0xffff) << 16) + (rand()&0xffff);
  int i;

  for(i = 0; i < len; i++){
    d0[i] =
    d1[i] =
#ifdef __arm__
    d2[i] =
#endif
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
    d15[i] =
    d16[i] =
          ((rand()&0xffff) << 16) + (rand()&0xffff);
    s[i] = ((rand()&0xffff) << 16) + (rand()&0xffff);
    m[i] = rand()&0xff;
  }

  _op_blend_p_c_dp(s, m, c, d0, len);
  _op_blend_p_c_dp_neon_intrinsics(s, m, c, d1, len);
#ifdef __arm__
  _op_blend_p_c_dp_neon_inline(s, m, c, d2, len);
#endif
  _op_blend_pan_c_dp(s, m, c, d3, len);
  _op_blend_pan_c_dp_neon(s, m, c, d4, len);
  _op_blend_p_can_dp(s, m, c, d5, len);
  _op_blend_p_can_dp_neon(s, m, c, d6, len);
  _op_blend_pan_can_dp(s, m, c, d7, len);
  _op_blend_pan_can_dp_neon(s, m, c, d8, len);
  _op_blend_p_caa_dp(s, m, c, d9, len);
  _op_blend_p_caa_dp_neon(s, m, c, d10, len);
  _op_blend_pan_caa_dp(s, m, c, d11, len);
  _op_blend_pan_caa_dp_neon(s, m, c, d12, len);

  _op_blend_rel_p_c_dp(s, m, c, d15, len);
  _op_blend_rel_p_c_dp_neon(s, m, c, d16, len);

  c = 0;
  _op_blend_pan_c_dp(s, m, c, d13, len);
  _op_blend_pan_c_dp_neon(s, m, c, d14, len);

  size_t size = sizeof(DATA32);
  int ret = 0;

  printf("p_c intrinsics test ... ");
  if(compare(d0,d1,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

#ifdef __arm__
  printf("p_c inline test ... ");
  if(compare(d0,d2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
#endif
  printf("pan_c intrinsics test ... ");
  if(compare(d3,d4,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("p_can intrinsics test ... ");
  if(compare(d5,d6,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("pan_can intrinsics test ... ");
  if(compare(d7,d8,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("p_caa intrinsics test ... ");
  if(compare(d9,d10,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("pan_caa intrinsics test ... ");
  if(compare(d11,d12,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("pan_c intrinsics NULL c test ... ");
  if(compare(d13,d14,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("rel_p_c intrinsics c test ... ");
  if(compare(d15,d16,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  return ret;
}
