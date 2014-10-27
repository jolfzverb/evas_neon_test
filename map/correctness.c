#include <stdlib.h>
#include <stdio.h>
#include "correct.h"
#include "map.h"

int main(){
  printf("\nMapping correctness test started!\nHope you compiled right version=)\n\n");
  int len = 1000000;
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
  DATA32 c1 = ((rand()&0xffff) << 16) + (rand()&0xffff);
  DATA32 c2 = ((rand()&0xffff) << 16) + (rand()&0xffff);
  for(i = 0; i < len; i++){
    val1[i] = ((rand()&0xffff) << 16) + (rand()&0xffff);
    val2[i] = ((rand()&0xffff) << 16) + (rand()&0xffff);
    val3[i] = ((rand()&0xffff) << 16) + (rand()&0xffff);
    val4[i] = ((rand()&0xffff) << 16) + (rand()&0xffff);
    ru[i] = rand()&0xff;
    rv[i] = rand()&0xff;
    cv[i] = rand()&0xff0000;
    //printf("%x %x %x %x %x\n", p0[i], p1[i], p2[i], p3[i], ax[i]);
    result1[i]=0;
    result2[i]=0;
    result3[i]=0;
  }
  int ret = 0;
  size_t size = sizeof(DATA32);
  c_orig0(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig0(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new0(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 0 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 0 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig1(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig1(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new1(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 1 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 1 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig2(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig2(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new2(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 2 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 2 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig3(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig3(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new3(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 3 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 3 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig4(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig4(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new4(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 4 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 4 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig5(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig5(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new5(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 5 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 5 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig6(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig6(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new6(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 6 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 6 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig7(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig7(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new7(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 7 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 7 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig8(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig8(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new8(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 8 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 8 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig9(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig9(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new9(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 9 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 9 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig10(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig10(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new10(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 10 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 10 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig11(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig11(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new11(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 11 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 11 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig12(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig12(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new12(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 12 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 12 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig13(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig13(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new13(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 13 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 13 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig14(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig14(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new14(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 14 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 14 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");

  c_orig15(val1, val2, val3, val4, rv, ru, result1, len, cv, c1, c2);
  neon_orig15(val1, val2, val3, val4, rv, ru, result2, len, cv, c1, c2);
  neon_new15(val1, val2, val3, val4, rv, ru, result3, len, cv, c1, c2);

  printf("New neon 15 test ... ");
  if(compare(result1,result2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }

  printf("Original neon 15 test ... ");
  if(compare(result1,result3,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
  printf("\n");



  return ret;
}
