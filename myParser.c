#include "shell.h"

/**
 * parse_command - Tokenize a command string into an array of strings.
 * @command: The command string to parse.
 *
 * Return: An array of strings representing the parsed tokens.
 */

#define MAX_TOKENS 20
#define MAX_TOKEN_LENGTH 100

char **parse_command(char *command)
{
    char **tokens = (char **)malloc(MAX_TOKENS * sizeof(char *));
    char *token;
    int i = 0;
    
    if (tokens == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(command, " ");

     while (token != NULL && i < MAX_TOKENS - 1)
    {
        tokens[i] = strdup(token);
        if (tokens[i] == NULL)
        {
            perror("strdup");
            exit(EXIT_FAILURE);
        }

        token = strtok(NULL, " ");
        i++;
    }

    tokens[i] = NULL; /* Null-terminate the array */

    return (tokens);
}

/**
 * exec_cmd - Check if a file is an executable command.
 * @cmd: The command to check.
 *
 * Return: 0 if executable, -1 otherwise.
 */
int exec_cmd(char *cmd)
{
    char *path = find_cmd_path(cmd);

    if (path != NULL)
    {
        free(path);
        return 0;
    }

    return -1;
}

/**
 * dupli_char - Duplicate characters.
 * @c: The character to duplicate.
 * @n: The number of times to duplicate.
 *
 * Return: The duplicated string.
 */
char *dupli_char(char c, int n)
{
	int i;
	char *str = (char *)malloc((n + 1) * sizeof(char));
    
	if (str == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < n; i++)
    {
        str[i] = c;
    }

    str[n] = '\0';
    return str;
}

/**
 * find_cmd_path - Find the path of a command in the PATH string.
 * @cmd: The command to find.
 *
 * Return: The full path of the command, or NULL if not found.
 */
char *find_cmd_path(char *cmd)
{
    char *env_path = getenv("PATH");
    char *token = strtok(env_path, ":");

    while (token != NULL)
    {
        char *full_path = (char *)malloc((strlen(token) + strlen(cmd) + 2) * sizeof(char));
        if (full_path == NULL)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }

        strcpy(full_path, token);
        strcat(full_path, "/");
        strcat(full_path, cmd);

        if (access(full_path, X_OK) == 0)
        {
            return full_path;
        }

        free(full_path);
        token = strtok(NULL, ":");
    }

    return NULL;
}
