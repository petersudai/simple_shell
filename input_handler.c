#include "shell.h"

/**
 * getCommand - Reads a command from  user.
 *
 * Return: command entered by user.
 */
char *getCommand(void)
{
	char *input;
	size_t input_size = MAX_INPUT_SIZE;
	ssize_t chars_read;

	printf("$ ");
	input = (char *)malloc(input_size);
	if (input == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	chars_read = getline(&input, &input_size, stdin);
	if (chars_read == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}
	input[chars_read - 1] = '\0';
	return (input);
}
