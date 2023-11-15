#include "shell.h"

/**
 * is_cmd - Determines if a file is an executable command.
 * @file_path: The path of the file to check.
 * Return: 1 if it is an executable command, 0 otherwise.
 */
int is_cmd(char *file_path) {
    return access(file_path, X_OK) == 0;
}

/**
 * dup_chars - Duplicates characters in a string.
 * @str: The string to duplicate.
 * Return: The duplicated string.
 */
char *dup_chars(const char *str) {
    char *duplicate = _strdup(str);
    if (duplicate == NULL) {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    return duplicate;
}

/**
 * find_path - Finds the command in the PATH.
 * @cmd: The command to be found.
 * Return: The full path of the command if found, NULL otherwise.
 */
char *find_path(char *cmd) {
    
    char *path = "/usr/bin:/bin";
    char *token;
    char *path_copy = dup_chars(path);

    token = strtok(path_copy, ":");
    while (token != NULL) {
        char *full_path = _malloc(_strlen(token) + _strlen(cmd) + 2);
        if (full_path == NULL) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        _strcpy(full_path, token);
        _strcat(full_path, "/");
        _strcat(full_path, cmd);

        if (is_cmd(full_path)) {
            free(path_copy);
            return full_path;
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}
