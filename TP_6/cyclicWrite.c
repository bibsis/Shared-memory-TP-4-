#include "gen.h"
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "cyclicBuf.h"

int main() 
  {
    int shared_fdescr = shm_open("shared_buffer", O_CREAT | O_RDWR, S_IRWXU);
    if (shared_fdescr == -1)
    {
      perror("Can't open the file");
      return -1;
    }

    int r;
    r = ftruncate(shared_fdescr, sizeof(struct cyclic_buf));
    if (r != 0)
    {
      perror("Can't truncate the file");
      return r;
    }

    struct cyclic_buf* mem = mmap(NULL, sizeof(struct cyclic_buf), PROT_READ | PROT_WRITE, MAP_SHARED, shared_fdescr, 0);
    if (mem == NULL)
    {
      perror("don't have mmap");
      return -1;
    }

    mem->place = 0;
    uint32_t seed = 0;
    while (1) 
	{
      generate((void*)mem->buff[mem->place].arr, seed);
      seed++;
      mem->place++;
   
    }
  return 0;
}
