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
  DATA32 *d2 = malloc(sizeof(DATA32)*len);
  DATA32 *d3 = malloc(sizeof(DATA32)*len);
  DATA32 *d4 = malloc(sizeof(DATA32)*len);
  DATA32 *d5 = malloc(sizeof(DATA32)*len);
  DATA32 *d6 = malloc(sizeof(DATA32)*len);
  DATA32 *d7 = malloc(sizeof(DATA32)*len);
  DATA8 *m = malloc(sizeof(DATA8)*len);
  DATA8 *m0 = malloc(sizeof(DATA8)*len);
  DATA8 *m1 = malloc(sizeof(DATA8)*len);
  DATA32 *s = malloc(sizeof(DATA32)*len);
  DATA32 c = ((rand()&0xffff) << 16) + (rand()&0xffff);

  int i;
  for(i = 0; i < len; i++){
    d0[i] =
    d1[i] =
    d2[i] =
    d3[i] =
    d4[i] =
    d5[i] =
    d6[i] =
    d7[i] =
          ((rand()&0xffff) << 16) + (rand()&0xffff);
    s[i] = ((rand()&0xffff) << 16) + (rand()&0xffff);
    m[i] = rand()&0xff;
    m0[i] = 0x0;
    m1[i] = 0xff;
  }

  _op_blend_p_mas_dp(s, m, c, d0, len);
  _op_blend_p_mas_dp_neon(s, m, c, d1, len);

  _op_blend_pas_mas_dp(s, m, c, d2, len);
  _op_blend_pas_mas_dp_neon(s, m, c, d3, len);

  _op_blend_pas_mas_dp(s, m0, c, d4, len);
  _op_blend_pas_mas_dp_neon(s, m0, c, d5, len);

  _op_blend_pas_mas_dp(s, m1, c, d6, len);
  _op_blend_pas_mas_dp_neon(s, m1, c, d7, len);

  size_t size = sizeof(DATA32);
  int ret = 0;

  printf("p random test ... ");
  if(compare(d0,d1,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("pas random test ... ");
  if(compare(d2,d3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("pas nul test ... ");
  if(compare(d4,d5,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("pas ff test ... ");
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
  free(d4);
  free(d5);
  free(d6);
  free(d7);
  free(m);
  free(m0);
  free(m1);
  free(s);
  return ret;
}
