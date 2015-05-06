#include <stdio.h>
#include "correct.h"
int compare(void * _a, void * _b, size_t size, int count){
  switch(size){
    case 1:
      {
        char * a = (char*)_a;
        char * b = (char*)_b;
        int i;
        for (i = 0; i < count; i++){
          if(*a++!=*b++) return 1;
        }
        return 0;
      }
    case 4:
      {
        unsigned int * a = (unsigned int *) _a;
        unsigned int * b = (unsigned int *) _b;
        int i;
        for (i = 0; i < count; i++){
          if(*a++!=*b++) return 1;
        }
        return 0;
      }
    default:
      printf("NOT IMPLEMENTED!\n");
  }
  return 0;
}
