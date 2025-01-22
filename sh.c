#include <unistd.h>
#include <sys/wait.h>

#define stdin 0
#define stdout 1

int real_waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options, void*);

unsigned int strlen(char* string) {
  unsigned int i = 0;
  while (*(string+i)!='\0')++i;
  return i;
}

void print(char* string) {
  write(stdout, string, strlen(string));
}

unsigned int parse_program_name(char* command, char* name) {
  unsigned int i = 0;
  while (*(command+i) != ' ' && *(command+i) != '\0') {
    name[i] = command[i];
    i++;
  }
  name[i] = '\0';
  return i;
}

void parse_program_args(char* command, unsigned int offset, char* args[]) {
  unsigned int i = 0;
  unsigned int h = 0;
  unsigned int args_i = 0;
  while (*(command+offset+i) != '\0') {
    if (*(command+offset+i) == ' ') {
      h = 0;
      args_i++;
    }
    (*(args+args_i))[h] = *(command+offset+i);
    i++;
    h++;
  }
}

//https://github.com/nir9/welcome/blob/master/lnx/very-minimal-shell/shell.c
int main() {
  char command[255];
  for (;;) {
    write(stdout, "# ", 2);
    int count = read(stdin, command, 255);
    
    command[count - 1] = '\0'; // /bin/ls\n -> /bin/ls\0
   
    char program[255];
    unsigned int name_count = parse_program_name(command, program);

    char* program_args[255];
    program_args[0] = malloc(255);
    program_args[1] = malloc(255);
    parse_program_args(command, name_count, program_args);

    /*
    for (int i = 0; **())
    */
    pid_t fork_result = fork();
    if (fork_result == 0) {
      execve(program, 0, 0);
      break;
    } else {
      siginfo_t info;
      real_waitid(P_ALL, 0, &info, WEXITED, 0);
    }

    for (unsigned i = 0; i < 255; ++i) {
      program[i] = '\0';
    }
    
  }

  _exit(0);
}
