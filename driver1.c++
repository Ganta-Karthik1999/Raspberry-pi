#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
int fd = open("/dev/mem", O_RDONLY);
if (fd == -1) {
printf("cannot open driver!\n");
return -1;
}
void *base = mmap(NULL, 4096, PROT_READ, MAP_SHARED, fd, 0x3f003000);

unsigned int lastLo = 0;
for (;;)
{
unsigned int hi = *((unsigned int*)base + 2);
unsigned int lo = *((unsigned int*)base + 1);
printf("%u %u -> %u\n", hi, lo, lo - lastLo);
lastLo = lo;
usleep(1000000);
}
}


