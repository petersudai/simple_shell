#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_TOKENS 20 /* Maximum number of tokens in a command */
#define MAX_TOKEN_LENGTH 100 /* Maximum length of a single token */
#define MAX_WAIT_ATTEMPTS 1000 /* Maximum number of attempts to wait for child process */

/* Function prototypes */
void hsh(void);
int myBuiltin(char *command);
char *find_command(char *command);
int execute_command(char **tokens);
char **parse_command(char *command);
int exec_cmd(char *cmd);
char *dupli_char(char c, int n);
char *find_cmd_path(char *cmd);
void exit_shell(void);

#endif /* SHELL_H */
