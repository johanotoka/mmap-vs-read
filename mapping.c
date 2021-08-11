/***********************************************************************/
/*** Author: Steeve Johan Otoka Eyota                                ***/
/*** Description: Counting non new line characters using mmap        ***/
/***                         August 2021                             ***/
/***********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

int my_cnt(char *f)
{
    // count the number of characters in the file excluding the new lines
    // mmaping the file to memory

    int i;
    int count = 0;
    char *addr;
    int fd;
    struct stat sb;
    size_t length;

    // open file
    fd = open(f, O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "Error: open\n");
        exit(EXIT_FAILURE);
    }

    // get file size
    if (fstat(fd, &sb) == -1)
    {
        fprintf(stderr, "Error: fstat\n");
        exit(EXIT_FAILURE);
    }
    length = sb.st_size;

    // mapping
    addr = mmap(0, length, PROT_READ, MAP_SHARED, fd, 0);

    if (addr == MAP_FAILED)
    {
        perror("mmap failed\n");
    }

    // count number of characters
    for (i = 0; i < length; i++)
    {
        if (addr[i] != '\n')
        {
            count++;
        }
    }

    // unmapping
    if (munmap(addr, length) != 0)
    {
        perror("munmap failed\n");
    }

    return count;
}