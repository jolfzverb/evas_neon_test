#include "time.h"
#include <stdio.h>
#include <sys/time.h>

//only one timer per program=)
struct timeval old;


void start(){
  gettimeofday(&old, NULL);
  //start timer
}

void stop_n_print(){
  struct timeval new;
  gettimeofday(&new, NULL);
  int time = (new.tv_sec-old.tv_sec)*1000000 +(new.tv_usec-old.tv_usec);
  printf("%d usec\n",time);
}

