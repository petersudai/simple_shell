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

/* String Prototypes from strings.c */
int strLength(char *s);
int strCompare(char *s1, char *s2);
char *strConcat(char *dest, char *src);

/* sud_shell.c */
int isBuiltin(char *cmd);
char *findCommandPath(char *cmd);
void forkCommand(char *cmd, char **args);

/* parser.c function prototypes */
int isExecutable(char *file_path);
char *duplicateString(const char *str);
char *findPath(char *cmd);

#endif /* SHELL_H */

