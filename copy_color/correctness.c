#include <stdlib.h>
#include <stdio.h>
#include "correct.h"
#include "copy.h"

int main(){
  printf("\nScaling correctness test started!\nHope you compiled right version=)\n\n");
  int len = 1000000;
  DATA32 *d0 = malloc(sizeof(DATA32)*len);
#ifdef __arm__
  DATA32 *d1 = malloc(sizeof(DATA32)*len);
#endif
  DATA32 *d2 = malloc(sizeof(DATA32)*len);
  DATA32 *s = malloc(sizeof(DATA32)*len);
  DATA8 *m = malloc(sizeof(DATA8)*len);

  int i;
  srand(0);

  DATA32 c = ((rand()&0xffff) << 16) + (rand()&0xffff);

  for(i = 0; i < len; i++){
    d0[i] =
          ((rand()&0xffff) << 16) + (rand()&0xffff);
#ifdef __arm__
    d1[i] =
          ((rand()&0xffff) << 16) + (rand()&0xffff);
#endif
    d2[i] =
          ((rand()&0xffff) << 16) + (rand()&0xffff);
  }

  _op_copy_c_dp(s, m, c, d0, len);
  _op_copy_c_dp_neon_intrinsics(s, m, c, d2, len);
#ifdef __arm__
  _op_copy_c_dp_neon_inline(s, m, c, d1, len);
#endif

  size_t size = sizeof(DATA32);
  int ret = 0;

  printf("New neon c test ... ");
  if(compare(d0,d2,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
#ifdef __arm__
  printf("Original neon c test ... ");
  if(compare(d0,d1,size,len)) {
    printf("fail\n");
    ret = 1;
  } else {
    printf("ok\n");
  }
#endif

  free(d0);
#ifdef __arm__
  free(d1);
#endif
  free(d2);
  free(s);
  free(m);
  return ret;
}
