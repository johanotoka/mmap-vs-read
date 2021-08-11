/***********************************************************************/
/*** Author: Steeve Johan Otoka Eyota                                ***/
/*** Description: Counting non new line characters using read        ***/
/***                         August 2021                             ***/
/***********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int my_cnt(char *f)
{
    // count the number of characters in the file excluding the new lines
    // reading multiple pagesize chuncks and counting the new-lines in them

    int i;
    int count = 0;
    int fd;
    size_t num_of_bytes;

    // open file
    fd = open(f, O_RDONLY);
    if (fd == -1)
    {
        fprintf(stderr, "Error: open\n");
        exit(EXIT_FAILURE);
    }

    // get page size
    size_t page_size = sysconf(_SC_PAGE_SIZE);
    if (page_size == -1)
    {
        perror("sysconf failed\n");
    }

    // allocate a buffer of size page_size
    char *buffer = malloc(page_size * sizeof(char));

    while ((num_of_bytes = read(fd, buffer, page_size)) != 0)
    {
        for (i = 0; i < num_of_bytes; i++)
        {
            if (buffer[i] != '\n')
            {
                count++;
            }
        }
    }

    free(buffer);

    return count;
}