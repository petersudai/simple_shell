#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

#define MAX_INPUT_SIZE 1024

/* String Prototypes from strings.c */
int strLength(char *s);
int strCompare(char *s1, char *s2);
char *strConcat(char *dest, char *src);
void strFree(char *str);
char *strDuplicate(const char *str);

/* sud_shell.c and sud_shell2.c */
int isBuiltin(char *cmd);
char *findCommandPath(char *cmd);
void handleInputRedirection(void);
void handleOutputRedirection(void);
void execute_Command(char *cmd, char **args);
void forkNewProcess(char *cmd, char **args);
void forkCommand(char *cmd, char **args);


/* parser.c function prototypes */
int isExecutable(char *file_path);
char *duplicateString(const char *str);
char *findPath(char *cmd);

/* tokenizer.c */
char **tokenizeInput(char *input);
void freeArgs(char **args);

/* Function prototypes from shell.c */
void processInput(char *input);

/* Function prototypes from command_execution.c */
void executeCommand(char *input, int background);

/* Function prototypes from input_handler.c */
char *getCommand(void);

#endif /* SHELL_H */

