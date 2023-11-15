#include "shell.h"
#include <unistd.h>

#define MAX_INPUT_SIZE 1024

/**
 * isBuiltin - Finds if command is a built-in
 * @cmd: command to be checked.
 * Return: 1 if built-in, 0 otherwise.
 */
int isBuiltin(char *cmd)
{
	if (strCompare(cmd, "exit") == 0 || strCompare(cmd, "cd") == 0)
	{
		return (1);
	}
	return (0);
}

/**
 * findCommandPath - Finds command in the PATH
 * @cmd: command to be found
 * Return: full path of command if found, NULL otherwise.
 */
char *findCommandPath(char *cmd)
{
	char *path = "/usr/bin/";
	char *fullPath;

	fullPath = (char *)malloc(MAX_INPUT_SIZE);

	if (fullPath == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	fullPath[0] = '\0';

	strConcat(fullPath, path);
	strConcat(fullPath, cmd);

	if (access(fullPath, X_OK) == 0)
		return (fullPath);
	free(fullPath);
	return (NULL);
}

/**
 * handleInputRedirection - handles input redirection for child process
 */
void handleInputRedirection(void)
{
	int inputFile;

	inputFile = open("input.txt", O_RDONLY);
	if (inputFile != -1)
	{
		if (dup2(inputFile, STDIN_FILENO) == -1)
		{
			perror("dup2 input");
			exit(EXIT_FAILURE);
		}
		close(inputFile);
	}
}

/**
 * handleOutputRedirection - Handles output redirection for the child process
 */
void handleOutputRedirection(void)
{
	int outputFile;

	outputFile = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outputFile != -1)
	{
		if (dup2(outputFile, STDOUT_FILENO) == -1)
		{
			perror("dup2 output");
			exit(EXIT_FAILURE);
		}
		close(outputFile);
	}
}

/**
 * execute_Command - Executes the command in the child process
 *
 * @cmd: command to execute
 * @args: arguments for command
 */
void execute_Command(char *cmd, char **args)
{
	char *env[2];

	env[0] = "PATH=/usr/bin";
	env[1] = NULL;
	if (execve(cmd, args, env) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
}
