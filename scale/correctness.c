#include <stdlib.h>
#include <stdio.h>
#include "correct.h"
#include "scale.h"

int main(){
  printf("\nScaling correctness test started!\nHope you compiled right version=)\n\n"); int len = 1000000;
  DATA32 *p0 = malloc(sizeof(DATA32)*len);
  DATA32 *p1 = malloc(sizeof(DATA32)*len);
  DATA32 *p2 = malloc(sizeof(DATA32)*len);
  DATA32 *p3 = malloc(sizeof(DATA32)*len);
  DATA32 *ax = malloc(sizeof(DATA32)*len);
  DATA32 *result1 = malloc(sizeof(DATA32)*len);
  DATA32 *result2 = malloc(sizeof(DATA32)*len);
  DATA32 *result3 = malloc(sizeof(DATA32)*len);
  int i;
  srand(0);
  DATA32 ay = rand()&0xff;
    //printf("%x\n", ay);
  for(i = 0; i < len; i++){
    p0[i] = ((rand()&0xffff) << 16) + (rand()&0xffff);
    p1[i] = ((rand()&0xffff) << 16) + (rand()&0xffff);
    p2[i] = ((rand()&0xffff) << 16) + (rand()&0xffff);
    p3[i] = ((rand()&0xffff) << 16) + (rand()&0xffff);
    ax[i] = rand()&0xff;
    result1[i]=0;
    result2[i]=0;
    result3[i]=0;
  }
  c_orig(p0, p1, p2, p3, ax, ay, result1, len);
  neon_new(p0, p1, p2, p3, ax, ay, result2, len);
  neon_orig(p0, p1, p2, p3, ax, ay, result3, len);
  printf("New neon test ... ");

  size_t size = sizeof(DATA32);
  int ret = 0;
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }



  return ret;
}
