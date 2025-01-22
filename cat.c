#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  void* file;
  if (argc == 1)
    file = fopen("/proc/self/fd/0", "r");
  else
    file = fopen(argv[1], "r");

  char character;
  while (fread(&character, sizeof(char), 1, file) == 1)
    printf("%c", character);
}
