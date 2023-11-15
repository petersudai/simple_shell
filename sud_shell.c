#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

#define MAX_INPUT_SIZE 1024

/**
 * find_builtin - Finds if the command is a built-in command.
 * @cmd: The command to be checked.
 * Return: 1 if built-in, 0 otherwise.
 */
int find_builtin(char *cmd) {
    if (_strcmp(cmd, "exit") == 0 || _strcmp(cmd, "cd") == 0) {
        return 1;
    }
    return 0;
}

/**
 * find_cmd - Finds the command in the PATH.
 * @cmd: The command to be found.
 * Return: The full path of the command if found, NULL otherwise.
 */
char *find_cmd(char *cmd) {
    /* Dummy implementation, replace with actual PATH lookup logic */
    char *path = "/usr/bin/";
    char *full_path = malloc(MAX_INPUT_SIZE);
    if (full_path == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    full_path[0] = '\0';

    _strcat(full_path, path);
    _strcat(full_path, cmd);

    if (access(full_path, X_OK) == 0) {
        return full_path;
    } else {
        free(full_path);
        return NULL;
    }
}

/**
 * is_cmd - Determines if a file is an executable command.
 *
 * @file_path: The path of the file to check.
 * Return: 1 if it is an executable command, 0 otherwise.
 */
int is_cmd(char *file_path)
{
    return access(file_path, X_OK) == 0;
}

/**
 * dup_chars - Duplicates characters in a string.
 *
 * @str: The string to duplicate.
 * Return: The duplicated string.
 */
char *dup_chars(const char *str)
{
    char *duplicate = strdup(str);
    if (duplicate == NULL)
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    return duplicate;
}

/**
 * fork_cmd - Forks a new process to run the command.
 * @cmd: The command to be executed.
 */
void fork_cmd(char *cmd) {
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) 
    {
    char **args = malloc(2 * sizeof(char*));
    
    if (args == NULL)
    {
	    perror("malloc");
	    exit(EXIT_FAILURE);
    }
    args[0] = cmd;
    args[1] = NULL;

    if (execv(cmd, args) == -1)
    {
            perror("execv");
            exit(EXIT_FAILURE);
    }

    free(args);

    } else {
        
        wait(NULL);
    }
}

int main(void) {
    char *input;
    size_t input_size = MAX_INPUT_SIZE;
    ssize_t chars_read;

    while (1) {
        printf("$ ");
        input = malloc(input_size);
        if (input == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        chars_read = getline(&input, &input_size, stdin);
        if (chars_read == -1) {
            if (feof(stdin)) {
                printf("\n");
                break;
            } else {
                perror("getline");
                exit(EXIT_FAILURE);
            }
        }
        input[chars_read - 1] = '\0';

        if (find_builtin(input)) {
            printf("Executing built-in command:%s\n",input);
           
        } else {
            char *cmd_path = find_cmd(input);
            if (cmd_path != NULL) {
                printf("Executing command:%s\n",cmd_path);
                fork_cmd(cmd_path);
                free(cmd_path);
            } else {
                printf("Command not found: %s\n", input);
            }
        }
        free(input);
    }

    return 0;
}
