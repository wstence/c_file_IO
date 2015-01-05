#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>

#define COUNT 20

main(int argc, char *argv[]) 
{
  int i, j, n, fd;
  struct stat s1;
  char buf[COUNT];

  for (i= 0; i < argc; i++)
    printf("[%d] %s\n", i, argv[i]);
  if (argc != 2)
  {
    fprintf(stderr, "usage: fileio <filename>\n");
    exit(-1);
  }
  fd = open(argv[1], O_RDWR);
  if (fd == -1)
  {
   /*printf("error: %d\n", errno);*/
     perror("file open error");
     exit(-1);
  }
  if (fstat(fd, &s1) == -1)  
  {
    perror("file open error");
    exit(-1);
  }
  printf("Size: %u\n", (unsigned)s1.st_size);
  printf("file descriptor: %d\n", fd);  

  printf("file contents: ");
  while ((n = read(fd, buf, COUNT)) != 0)
  {
    if (n == -1) 
    {
      perror("file error");
      exit(-1);
    }
    for (j = 0; j < n; j++)
      printf("%c", buf[j]); 
  } 
  printf("\n");
}
