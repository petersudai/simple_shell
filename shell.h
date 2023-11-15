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
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strcat(char *dest, char *src);

/* sud_shell.c */
int find_builtin(char *cmd);
char *find_cmd(char *cmd);
void fork_cmd(char *cmd);

/* parser.c function prototypes */
int is_cmd(char *file_path);
char *dup_chars(const char *str);
char *find_path(char *cmd)
void *malloc(size_t size);

#endif /* SHELL_H */

