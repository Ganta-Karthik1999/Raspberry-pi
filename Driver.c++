
#includ<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <arpa/inet.h>
int main()
{
    int fd = open("/dev/mem", O_RDWR|O_SYNC);
    if (fd == -1) {
    printf("cannot open driver!\n");
    return -1;
}
uint32_t *gpio = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x3f200000);
*gpio = 1 << 6; // GPIO 2 as output
for (;;)
{
    *(gpio + 7) = (1 << 2); // GPIO 2 ON
    usleep(100000); // 100 ms
    *(gpio + 10) = (1 << 2); // GPIO 2 OFF
    usleep(100000); // 100 ms
}
}