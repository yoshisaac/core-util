#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// TODO: Make syscalls manually. In assembly ideally. Make the binary smaller.

#define STDIN 0
#define STDOUT 1

unsigned int parse_program_name(char* command, char* name) {
  unsigned int i = 0;
  while (*(command+i) != ' ' && *(command+i) != '\0') {
    name[i] = command[i];
    i++;
  }
  name[i] = '\0';
  return i;
}

void parse_program_args(char* command, unsigned int offset, char* args) {
  unsigned int i = 0;
  while (*(command+offset+1+i) != '\0') {
    if (*(command+offset+1+i) != ' ') *(args+i) = *(command+offset+1+i);
    i++;
  }
  *(args+i) = '\0';
  if (*(args) == '\0') args = NULL;
}

//https://github.com/nir9/welcome/blob/master/lnx/very-minimal-shell/shell.c
int main() {
  char command[255];
  char program[255];
  char* program_arg[3];

  program_arg[0] = program;
  //program_arg[1];
  program_arg[2] = NULL;

  for (;;) {
    write(STDOUT, "$> ", 2);
    int length = read(STDIN, command, 255);
    
    command[length - 1] = '\0'; // /bin/ls\n -> /bin/ls\0
   
    unsigned int name_length = parse_program_name(command, program);

    program_arg[1] = malloc(255);
    parse_program_args(command, name_length, program_arg[1]);

    for (unsigned int i = 0; *(program_arg+i) != NULL;++i) {
      if (*(*(program_arg+i)) == '\0') {
	*(program_arg+i) = NULL;
	continue;
      }
    }

    //debug arguments
    /* char isArg = 0; */
    /* for (unsigned int i = 0; *(program_arg+i) != NULL;++i) { */
    /*   if (*(*(program_arg+i)) == '\0') { */
    /* 	*(program_arg+i) = NULL; */
    /* 	continue; */
    /*   } */
    /*   isArg = 0; */
    /*   printf("%d: ", i); */
    /*   for (unsigned int h = 0; *(*(program_arg+i)+h) != '\0'; ++h) { */
    /* 	isArg = 1; */
    /* 	printf("%c", *(*(program_arg+i)+h)); */
    /*   } */
    /*   if (isArg) */
    /* 	printf("\n"); */
    /* } */
    /* printf("\n"); */
    
    pid_t fork_result = fork();
    if (fork_result == 0) {
      execve(program, program_arg, 0);
      break;
    } else {
      siginfo_t info;
      waitid(P_ALL, 0, &info, WEXITED);
    }

    //clean up
    free(program_arg[1]);
    program_arg[1] = NULL;

    for (unsigned i = 0; i < 255; ++i) {
      program[i] = '\0';
    }

    for (unsigned i = 0; i < 255; ++i) {
      command[i] = '\0';
    }
        
    
  }

  return 0;
}
