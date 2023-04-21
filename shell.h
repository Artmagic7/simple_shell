#ifndef _SIMPLE_SHELL_H_
#define _SIMPLE_SHELL_H_

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* Global Variables */
extern char **environ;

/* Prototypes */
int execute_command(char **args);
int check_for_builtin(char **args);
char **parse_input(char *input);
void free_memory(char **args);

#endif /* _SIMPLE_SHELL_H_ */
