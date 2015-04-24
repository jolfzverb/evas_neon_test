#include <stdlib.h>
#include <stdio.h>
#include "correct.h"
#include "blend.h"

int main(){
  printf("\nScaling correctness test started!\nHope you compiled right version=)\n\n");
  int len = 1000000;
  DATA32 *d0 = malloc(sizeof(DATA32)*len);
  DATA32 *d1 = malloc(sizeof(DATA32)*len);
  DATA32 *d3 = malloc(sizeof(DATA32)*len);
  DATA32 *d4 = malloc(sizeof(DATA32)*len);
#ifdef __arm__
  DATA32 *d2 = malloc(sizeof(DATA32)*len);
  DATA32 *d5 = malloc(sizeof(DATA32)*len);
#endif
  DATA32 *d6 = malloc(sizeof(DATA32)*len);
  DATA32 *d7 = malloc(sizeof(DATA32)*len);
  DATA32 *s = NULL;
  DATA8 *a = NULL;
  int i;
  srand(0);

  DATA32 c = ((rand()&0xffff) << 16) + (rand()&0xffff);
  if(c>>24 == 0)
     c=0;
  DATA32 c1 = ((rand()&0xffff) << 16) + (rand()&0xffff);

  for(i = 0; i < len; i++){
    d0[i] =
    d1[i] =
    d3[i] =
    d4[i] =
#ifdef __arm__
    d2[i] =
    d5[i] =
#endif
    d6[i] =
    d7[i] =
          ((rand()&0xffff) << 16) + (rand()&0xffff);
  }
  //int alpha = (c>>24);
  //c = ((MUL_256(alpha,c))&0xffffff)+(alpha<<24);

  _op_blend_c_dp(s, a, c, d0, len);
  _op_blend_c_dp_neon_intrinsics(s, a, c, d1, len);
#ifdef __arm__
  _op_blend_c_dp_neon_inline(s, a, c, d2, len);
#endif
  _op_blend_rel_c_dp(s, a, c1, d6, len);
  _op_blend_rel_c_dp_neon(s, a, c1, d7, len);
  c = 0;
  _op_blend_c_dp(s, a, c, d3, len);
  _op_blend_c_dp_neon_intrinsics(s, a, c, d4, len);
#ifdef __arm__
  _op_blend_c_dp_neon_inline(s, a, c, d5, len);
#endif

  size_t size = sizeof(DATA32);
  int ret = 0;

  printf("New neon c test ... ");
  if(compare(d0,d1,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("New neon null test ... ");
  if(compare(d3,d4,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

#ifdef __arm__
  printf("Original neon c test ... ");
  if(compare(d0,d2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("Original neon null test ... ");
  if(compare(d3,d5,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
#endif
  printf("rel_c neon test ... ");
  if(compare(d6,d7,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  free(d0);
  free(d1);
#ifdef __arm__
  free(d2);
  free(d5);
#endif
  free(d3);
  free(d4);
  free(d6);
  free(d7);
  return ret;
}
