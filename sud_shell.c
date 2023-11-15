#include "shell.h"

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
 * forkCommand - Forks new process to run the command.
 * @cmd: command to be executed
 * @args: command line argument
 */
void forkCommand(char *cmd, char **args)
{
	pid_t childPid;
	int inputFile, outputFile;
	char *env[2];

	if (cmd == NULL || args == NULL)
	{
		printf("Error: NULL command or arguments\n");
		exit(EXIT_FAILURE);
	}

	childPid = fork();
	if (childPid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (childPid == 0)
	{
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
		env[0] = "PATH=/bin:/usr/bin";
		env[1] = NULL;

		if (execve(cmd, args, env) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
	else
	    wait(NULL);
}
