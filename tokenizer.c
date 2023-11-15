#include "shell.h"

#define MAX_ARGS 100

/**
 * tokenizeInput - Tokenizes the input string.
 * @input: The input string to tokenize.
 *
 * Return: An array of strings containing the tokens.
 */

char **tokenizeInput(char *input)
{
	int i;
	char **args;
	char *token;
	args = malloc(MAX_ARGS * sizeof(char *));
	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	i = 0;
	token = strtok(input, " ");
	while (token != NULL)
	{
		args[i] = strDuplicate(token);
		if (args[i] == NULL)
		{
			perror("strDuplicate");
			exit(EXIT_FAILURE);
		}
		i++;

		if (i >= MAX_ARGS)
		{
			printf("Too many arguments\n");
			exit(EXIT_FAILURE);
		}

		token = strtok(NULL, " ");
	}
	args[i] = NULL;
	return (args);
}

/**
 * freeArgs - frees the memory allocated for arguments tokenized
 * @args: array of string to free
 */

void freeArgs(char **args)
{
	int i;
	for (i = 0; args[i] != NULL; i++)
		strFree(args[i]);
	free(args);
}
