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
          ((rand()&0xffff) << 16) + (rand()&0xffff);
    m[i] = rand()&0xff;
  }
  //int alpha = (c>>24);
  //c = ((MUL_256(alpha,c))&0xffffff)+(alpha<<24);

  _op_blend_mas_c_dp(s, m, c, d0, len);
  _op_blend_mas_can_dp(s, m, c, d1, len);
  _op_blend_mas_c_dp_neon_intrinsics(s, m, c, d2, len);
  _op_blend_mas_can_dp_neon_intrinsics(s, m, c, d3, len);
#ifdef __arm__
  _op_blend_mas_c_dp_neon_inline(s, m, c, d4, len);
  _op_blend_mas_can_dp_neon_inline(s, m, c, d5, len);
#endif

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
  for(i = 0; i < 1000; i++)
     if(d1[i]!=d3[i])
        printf("%x %x %x %x %d\n",d1[i], d3[i], c, m[i], i);

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

  free(d0);
  free(d1);
  free(d2);
  free(d3);
#ifdef __arm__
  free(d4);
  free(d5);
#endif
  free(m);
  return ret;
}
