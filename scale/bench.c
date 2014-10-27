#include <stdlib.h>
#include <stdio.h>
#include <arm_neon.h>
#include "time.h"
#include "scale.h"

int main(){
  printf("\nScaling benchmark started!\nHope you compiled right version=)\n\n");
  int len = 10000000;
  DATA32 *p0 = malloc(sizeof(DATA32)*len);
  DATA32 *p1 = malloc(sizeof(DATA32)*len);
  DATA32 *p2 = malloc(sizeof(DATA32)*len);
  DATA32 *p3 = malloc(sizeof(DATA32)*len);
  DATA32 *ax = malloc(sizeof(DATA32)*len);
  DATA32 *result1 = malloc(sizeof(DATA32)*len);
  DATA32 *result2 = malloc(sizeof(DATA32)*len);
  DATA32 *result3 = malloc(sizeof(DATA32)*len);
  int i;
  //DATA32 ay = rand()&0xff;
  DATA32 ay = 1234&0xff;
    //printf("%x\n", ay);
  for(i = 0; i < len; i++){
    p0[i] = i;
    p1[i] = i;
    p2[i] = i;
    p3[i] = i;
    ax[i] = i&0xff;
    result1[i]=0;
    result2[i]=0;
    result3[i]=0;
  }
  printf("10000000 pixels by c_orig:\t");
  start();
  c_orig(p0, p1, p2, p3, ax, ay, result1, len);
  stop_n_print();
  printf("10000000 pixels by neon_new:\t");
  start();
  neon_new(p0, p1, p2, p3, ax, ay, result2, len);
  stop_n_print();
  printf("10000000 pixels by neon_orig:\t");
  start();
  neon_orig(p0, p1, p2, p3, ax, ay, result3, len);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i])
      return 1;
  }



  return 0;
}
