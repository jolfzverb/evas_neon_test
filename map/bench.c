#include <stdlib.h>
#include <stdio.h>
#include <arm_neon.h>
#include "time.h"
#include "map.h"

int main(){
  printf("\nMapping benchmark started!\nHope you compiled right version=)\n\n");
  int len = 10000000;
  DATA32 *val1 = malloc(sizeof(DATA32)*len);
  DATA32 *val2 = malloc(sizeof(DATA32)*len);
  DATA32 *val3 = malloc(sizeof(DATA32)*len);
  DATA32 *val4 = malloc(sizeof(DATA32)*len);
  DATA32 *ru = malloc(sizeof(DATA32)*len);
  DATA32 *rv = malloc(sizeof(DATA32)*len);
  DATA32 *cv = malloc(sizeof(DATA32)*len);
  DATA32 *result1 = malloc(sizeof(DATA32)*len);
  DATA32 *result2 = malloc(sizeof(DATA32)*len);
  DATA32 *result3 = malloc(sizeof(DATA32)*len);
  int i;
  srand(0);
  DATA32 c1 = 0x21fe01da;
  DATA32 c2 = 0x15ab995d;
  for(i = 0; i < len; i++){
    val1[i] = i;
    val2[i] = i;
    val3[i] = i;
    val4[i] = i;
    ru[i] = i&0xff;
    rv[i] = i&0xff;
    cv[i] = i&0xff0000;
    //printf("%x %x %x %x %x\n", p0[i], p1[i], p2[i], p3[i], ax[i]);
    result1[i]=0;
    result2[i]=0;
    result3[i]=0;
  }

  int ret = 0;
  printf("10000000 pixels by c_orig0:\t");
  start();
  c_orig0(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new0:\t");
  start();
  neon_new0(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig0:\t");
  start();
  neon_orig0(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig1:\t");
  start();
  c_orig1(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new1:\t");
  start();
  neon_new1(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig1:\t");
  start();
  neon_orig1(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig2:\t");
  start();
  c_orig2(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new2:\t");
  start();
  neon_new2(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig2:\t");
  start();
  neon_orig2(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig3:\t");
  start();
  c_orig3(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new3:\t");
  start();
  neon_new3(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig3:\t");
  start();
  neon_orig3(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig4:\t");
  start();
  c_orig4(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new4:\t");
  start();
  neon_new4(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig4:\t");
  start();
  neon_orig4(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig5:\t");
  start();
  c_orig5(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new5:\t");
  start();
  neon_new5(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig5:\t");
  start();
  neon_orig5(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig6:\t");
  start();
  c_orig6(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new6:\t");
  start();
  neon_new6(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig6:\t");
  start();
  neon_orig6(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig7:\t");
  start();
  c_orig7(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new7:\t");
  start();
  neon_new7(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig7:\t");
  start();
  neon_orig7(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig8:\t");
  start();
  c_orig8(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new8:\t");
  start();
  neon_new8(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig8:\t");
  start();
  neon_orig8(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig9:\t");
  start();
  c_orig9(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new9:\t");
  start();
  neon_new9(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig9:\t");
  start();
  neon_orig9(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig10:\t");
  start();
  c_orig10(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new10:\t");
  start();
  neon_new10(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig10:\t");
  start();
  neon_orig10(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig11:\t");
  start();
  c_orig11(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new11:\t");
  start();
  neon_new11(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig11:\t");
  start();
  neon_orig11(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig12:\t");
  start();
  c_orig12(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new12:\t");
  start();
  neon_new12(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig12:\t");
  start();
  neon_orig12(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig13:\t");
  start();
  c_orig13(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new13:\t");
  start();
  neon_new13(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig13:\t");
  start();
  neon_orig13(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig14:\t");
  start();
  c_orig14(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new14:\t");
  start();
  neon_new14(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig14:\t");
  start();
  neon_orig14(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");

  printf("10000000 pixels by c_orig15:\t");
  start();
  c_orig15(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_new15:\t");
  start();
  neon_new15(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);
  stop_n_print();
  printf("10000000 pixels by neon_orig15:\t");
  start();
  neon_orig15(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  stop_n_print();
  for(i = 0; i < len; i++){
    if(result2[i]!=result1[i] || result3[i]!=result1[i])
      ret = 1;
  }
  printf("\n");


  free(val1);
  free(val2);
  free(val3);
  free(val4);
  free(ru);
  free(rv);
  free(cv);
  free(result1);
  free(result2);
  free(result3);
  return ret;
}
