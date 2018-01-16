#include "gen.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "cyclicBuf.h"


int main() 
  {
	uint64_t current = 0;
    uint64_t prev_seed = -1;

    int shared_fdescr = shm_open("shared_place", O_RDONLY, 0);
    if (shared_fdescr == -1) 
	{
      perror("Can't open file");
      return shared_fdescr;
    }

    struct cyclic_buf* mem = mmap(NULL, sizeof(struct cyclic_buf), PROT_READ, MAP_SHARED, shared_fdescr, 0);
      
    if (mem == MAP_FAILED) 
	{
      perror("don't have mmap");
      return -1;
    }

  
  printf("starting on position: %ld\n", current);

  bool seed_check = false;

  while (1) 
  {
  
    if (mem->place == current) 
	{
      sleep(1);
      continue;
    }
    
    if(mem->place >= current + 5000)
	{
      break;
    }
    
    int64_t current_seed = verify((void*)mem->buff[current].arr);
    
    if (current_seed == -1 || (prev_seed + 1 != current_seed && seed_check == true)
    {
      break;
    }
    
    prev_seed = current_seed;
    
    printf("%ld -> %ld\n", current, current_seed);
    current++;
  }
  
  return 0;
}
