#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

//TODO: make syscalls manually instead of using glibc
//      to make binary size smaller

int main(int argc, char* argv[]) {
  DIR* dir_ptr;
  if (argc == 1)
    dir_ptr = opendir(".");
  else
    dir_ptr = opendir(argv[1]);
  
  struct dirent* file_dirent;
  while ((file_dirent = readdir(dir_ptr)) != NULL) {
    if (file_dirent->d_name[0] == '.') continue;
    printf("%s  ", file_dirent->d_name);
  }
  printf("\n");
}
