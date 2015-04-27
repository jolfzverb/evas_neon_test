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
          ((rand()&0xffff) << 16) + (rand()&0xffff);
    m[i] = rand()&0xff;
  }

  _op_blend_mas_c_dp(s, m, c, d0, len);
  _op_blend_mas_can_dp(s, m, c, d1, len);
  _op_blend_mas_c_dp_neon_intrinsics(s, m, c, d2, len);
  _op_blend_mas_can_dp_neon_intrinsics(s, m, c, d3, len);
#ifdef __arm__
  _op_blend_mas_c_dp_neon_inline(s, m, c, d4, len);
  _op_blend_mas_can_dp_neon_inline(s, m, c, d5, len);
#endif
  _op_blend_rel_mas_c_dp(s, m, c, d6, len);
  _op_blend_rel_mas_c_dp_neon(s, m, c, d7, len);

  size_t size = sizeof(DATA32);
  int ret = 0;

  printf("c intrinsics test ... ");
  if(compare(d0,d2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("can intrinsics test ... ");
  if(compare(d1,d3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

#ifdef __arm__
  printf("c inline test ... ");
  if(compare(d0,d4,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("can inline test ... ");
  if(compare(d1,d5,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
#endif
  printf("rel_mas_c intrinsics test ... ");
  if(compare(d6,d7,size,len)) {
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
#endif
  free(d6);
  free(d7);
  free(m);
  return ret;
}
