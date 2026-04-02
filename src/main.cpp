#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  FILE *fptr;
  char temp[1024];

  fptr = fopen("test", "r");

  while (fgets(temp, 1024, fptr))
    printf("%s", temp);

  return 0;
}
