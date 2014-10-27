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
  DATA32 *s = malloc(sizeof(DATA32)*len);
  DATA8 *a = NULL;
  int i;
  srand(0);
  DATA32 ay = ((rand()&0xffff) << 16) + (rand()&0xffff);
    //printf("%x\n", ay);
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
          ((rand()&0xffff) << 16) + (rand()&0xffff);
    s[i] = ((rand()&0xffff) << 16) + (rand()&0xffff);
    if(!(s[i]>>24))
       s[i] = 0;
  }
  _op_blend_p_dp(s, a, ay, d0, len);
  _op_blend_pas_dp(s, a, ay, d1, len);

  _op_blend_p_dp_neon_intrinsics(s, a, ay, d2, len);
  _op_blend_pas_dp_neon_intrinsics(s, a, ay, d3, len);

#ifdef __arm__
  _op_blend_p_dp_neon_inline_orig(s, a, ay, d4, len);
  _op_blend_pas_dp_neon_inline_orig(s, a, ay, d5, len);

  _op_blend_p_dp_neon_inline_fixed(s, a, ay, d6, len);
  _op_blend_pas_dp_neon_inline_fixed(s, a, ay, d7, len);
#endif

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


  return ret;
}
