/************             N L C N T            ***********/
/********** Steeve Johan Otoka Eyota, August 2021 ********/
/*
  This program accepts two command line arguments.
  The first is either the word 'reading' or 'mapping' or any leading substring.
  The second is the string argument of the function my_cnt

  After opening the file, the program calls the proper version my_cnt,
  which counts the number of non new line characters, then prins it 
*/

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>

void show_usage(char *name)
{
  printf("USAGE: %s reading|mapping filename\n", name);
  exit(1);
}

int main(int argc, char **argv)
{
  int i;
  char *s;
  void *handle;
  int (*my_cnt)(char *);

  if (argc != 3)
    show_usage(argv[0]);

  // Reading command line arguments
  if (strncmp(argv[1], "mapping", 1) == 0)
  {
    handle = dlopen("./mapping.so", RTLD_LAZY);
  }
  else if (strncmp(argv[1], "reading", 1) == 0)
  {
    handle = dlopen("./reading.so", RTLD_LAZY);
  }
  else
  {
    fprintf(stderr, "Error: unknown file type: %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  if (!handle)
  {
    // fail to load the library
    fprintf(stderr, "%s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  dlerror(); // clear any existing error

  // dlsym invoke with proper argument
  *(void **)(&my_cnt) = dlsym(handle, "my_cnt");
  if (!my_cnt)
  {
    fprintf(stderr, "Error: %s\n", dlerror());
    dlclose(handle);
    return EXIT_FAILURE;
  }

  // print the result
  printf("%d\n", my_cnt(argv[2]));

  dlclose(handle);

  exit(0);
}