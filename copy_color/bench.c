#include <stdlib.h>
#include <stdio.h>
#include <arm_neon.h>
#include "time.h"
#include "copy.h"

int main(){
  printf("\nScaling benchmark started!\nHope you compiled right version=)\n\n");
  int len = 10000000;
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
#ifdef __arm__
    d1[i] =
#endif
    d2[i] =
          i+c;
  }

  printf("10000000 pixels by _op_copy_c_dp:\t");
  start();
  _op_copy_c_dp(s, m, c, d0, len);
  stop_n_print();
  printf("10000000 pixels by _op_copy_c_dp_neon_intrinsics:\t");
  start();
  _op_copy_c_dp_neon_intrinsics(s, m, c, d2, len);
  stop_n_print();
#ifdef __arm__
  printf("10000000 pixels by _op_copy_c_dp_neon_inline:\t");
  start();
  _op_copy_c_dp_neon_inline(s, m, c, d1, len);
  stop_n_print();
#endif

  int ret = 0;
  for(i = 0; i < len; i++){
    if(
#ifdef __arm__
          (d1[i]!=d0[i]) ||
#endif
          (d0[i]!=d2[i])
      )
      ret = 1;
  }
  free(d0);
#ifdef __arm__
  free(d1);
#endif
  free(d2);
  free(s);
  free(m);
  return ret;
}
