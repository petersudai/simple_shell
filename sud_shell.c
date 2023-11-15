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

	childPid = fork();
	if (childPid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (childPid == 0)
	{
		if (execv(cmd, args) == -1)
		{
			perror("execv");
			exit(EXIT_FAILURE);
		}
	}
	else
	    wait(NULL);
}

/**
 * main - entry point
 *
 * Return: void
 */

int main(void)
{
	char *input;
	size_t inputSize = MAX_INPUT_SIZE;
	ssize_t charsRead;
	int background;

	while (1)
	{
		printf("$ ");
		input = (char *)malloc(inputSize);
		if (input == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		charsRead = getline(&input, &inputSize, stdin);
		if (charsRead == -1)
		{
			if (feof(stdin))
			{
				printf("\n");
				break;
			}
			else
			{
				perror("getline");
				exit(EXIT_FAILURE);
			}
		}
		input[charsRead - 1] = '\0';

		if (strCompare(input, "exit") == 0)
		{
			printf("Exitng the Shell!\n");
			free(input);
			exit(EXIT_SUCCESS);
		}

		background = 0;
		if (input[charsRead - 2] == '&')
		{
			background = 1;
			input[charsRead -2] = '\0';
		}

		if (isBuiltin(input))
		{
			printf("Executing built-in command:%s\n", input);
		}
		else
		{
			char *cmdPath = findCommandPath(input);
			char **args;

			if (cmdPath != NULL)
			{
				printf("Executing command:%s\n", cmdPath);
				args = (char **)malloc(2 * sizeof(char *));
				if (args == NULL)
				{
					perror("malloc");
					exit(EXIT_FAILURE);
				}
				args[0] = cmdPath;
				args[1] = NULL;

				forkCommand(cmdPath, args);

				if (!background)
					wait(NULL);
				free(args);
				free(cmdPath);
			}
			else
			{
				printf("Command not found: %s\n", input);
			}
		}
		free(input);
	}
	return (0);
}
