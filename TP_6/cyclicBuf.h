#ifndef _ARR
#define _ARR
#define _SIZE 4096

#include <stdint.h>

struct chunk {
  volatile int array[SIZE];
};

struct cyclic_buf {

  volatile uint64_t place;
  
  volatile struct chunk_t buff[5000];
};

#endif
