#include <stdlib.h>
#include <stdio.h>
#include <arm_neon.h>
#include "time.h"
#include "blend.h"

int main(){
  printf("\nScaling benchmark started!\nHope you compiled right version=)\n\n");
  int len = 10000000;
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
    s[i] =
          i+c;
    m[i] = i&0xff;
    m0[i] = 0x0;
    m1[i] = 0xff;
  }


  printf("10000000 pixels by _op_blend_p_mas_dp:\t");
  start();
  _op_blend_p_mas_dp(s, m, c, d0, len);
  stop_n_print();

  printf("10000000 pixels by _op_blend_p_mas_dp_neon:\t");
  start();
  _op_blend_p_mas_dp_neon(s, m, c, d1, len);
  stop_n_print();

  printf("10000000 pixels, random m, by _op_blend_pas_mas_dp:\t");
  start();
  _op_blend_pas_mas_dp(s, m, c, d2, len);
  stop_n_print();

  printf("10000000 pixels, random m, by _op_blend_pas_mas_dp_neon:\t");
  start();
  _op_blend_pas_mas_dp_neon(s, m, c, d3, len);
  stop_n_print();

  printf("10000000 pixels, nul m, by _op_blend_pas_mas_dp:\t");
  start();
  _op_blend_pas_mas_dp(s, m0, c, d4, len);
  stop_n_print();

  printf("10000000 pixels, nul m, by _op_blend_pas_mas_dp_neon:\t");
  start();
  _op_blend_pas_mas_dp_neon(s, m0, c, d5, len);
  stop_n_print();

  printf("10000000 pixels, ff m, by _op_blend_pas_mas_dp:\t");
  start();
  _op_blend_pas_mas_dp(s, m1, c, d6, len);
  stop_n_print();

  printf("10000000 pixels, ff m, by _op_blend_pas_mas_dp_neon:\t");
  start();
  _op_blend_pas_mas_dp_neon(s, m1, c, d7, len);
  stop_n_print();

  for(i = 0; i < len; i++){
    if(
          (d1[i]!=d0[i]) ||
          (d4[i]!=d5[i]) ||
          (d6[i]!=d7[i]) ||
          (d3[i]!=d2[i])
      )
      return 1;
  }
  return 0;
}
