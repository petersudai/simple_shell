#include "shell.h"

/**
 * isExecutable - Determines if file is executable command.
 * @file_path: The path of the file to check
 * Return: 1 if executable command, 0 otherwise.
 */
int isExecutable(char *file_path)
{
	return (access(file_path, X_OK) == 0);
}

/**
 * duplicateString - Duplicates characters in a string.
 * @str: The string to duplicate.
 * Return: The duplicated string.
 */
char *duplicateString(const char *str)
{
	char *duplicate = strdup(str);

	if (duplicate == NULL)
	{
		perror("strdup");
		exit(EXIT_FAILURE);
	}
	return (duplicate);
}

/**
 * findPath - Finds command in the PATH
 * @cmd: comand to be found.
 * Return: The full path of the command if found, NULL otherwise.
 */
char *findPath(char *cmd)
{
	char *path = "/usr/bin:/bin";
	char *token;
	char *pathCopy = duplicateString(path);

	token = strtok(pathCopy, ":");

	while (token != NULL)
	{
		char *fullPath = (char *)malloc(strLength(token) + strLength(cmd) + 2);

		if (fullPath == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		strConcat(fullPath, token);
		strConcat(fullPath, "/");
		strConcat(fullPath, cmd);

		if (isExecutable(fullPath))
		{
			free(pathCopy);
			return (fullPath);
		}
		free(fullPath);
		token = strtok(NULL, ":");
	}
	free(pathCopy);
	return (NULL);
}
