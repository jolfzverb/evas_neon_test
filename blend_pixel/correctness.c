#include <stdlib.h>
#include <stdio.h>
#include "correct.h"
#include "blend.h"

int main(){
  printf("\nScaling correctness test started!\nHope you compiled right version=)\n\n");
  int len = 1000000;
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
    d8[i] =
    d9[i] =
    d10[i] =
    d11[i] =
          ((rand()&0xffff) << 16) + (rand()&0xffff);
    s[i] = ((rand()&0xffff) << 16) + (rand()&0xffff);
    if(!(s[i]>>24))
       s[i] = 0;
    s1[i] = ((rand()&0xffff) << 16) + (rand()&0xffff);
  }
  _op_blend_p_dp(s, a, c, d0, len);
  _op_blend_pas_dp(s, a, c, d1, len);

  _op_blend_p_dp_neon_intrinsics(s, a, c, d2, len);
  _op_blend_pas_dp_neon_intrinsics(s, a, c, d3, len);

#ifdef __arm__
  _op_blend_p_dp_neon_inline_orig(s, a, c, d4, len);
  _op_blend_pas_dp_neon_inline_orig(s, a, c, d5, len);

  _op_blend_p_dp_neon_inline_fixed(s, a, c, d6, len);
  _op_blend_pas_dp_neon_inline_fixed(s, a, c, d7, len);
#endif

  _op_blend_rel_p_dp(s1, a, c, d8, len);
  _op_blend_rel_p_dp_neon(s1, a, c, d9, len);

  _op_blend_rel_pan_dp(s1, a, c, d10, len);
  _op_blend_rel_pan_dp_neon(s1, a, c, d11, len);

  size_t size = sizeof(DATA32);
  int ret = 0;

  printf("Intrinsics p test ... ");
  if(compare(d0,d2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("Intrinsics pas test ... ");
  if(compare(d1,d3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

#ifdef __arm__
  printf("Inline orig p test ... ");
  if(compare(d0,d4,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("Inline orig pas test ... ");
  if(compare(d1,d5,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Inline fixed p test ... ");
  if(compare(d0,d6,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("Inline fixed pas test ... ");
  if(compare(d1,d7,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
#endif
  printf("rel_p test ... ");
  if(compare(d8,d9,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("rel_pan test ... ");
  if(compare(d10,d11,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
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
