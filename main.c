#include "shell.h"

/**
 * main - Entry point of the program
 * @argc: the number of arguments
 * @argv: the array of arguments
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int i, j;
	char **tokens;

	if (argc > 1)
	{
		for (i = 1; i < argc; i++)
		{
			tokens = parse_command(argv[i]);
			execute_command(tokens);

			for (j = 0; tokens[j] != NULL; j++)
				free(tokens[j]);
			free(tokens);
		}
	}
	else
		hsh();

	return (0);
}
