#include "shell.h"

/**
 * main - main shell function
 *
 * Return: void
 */

int main(void)
{
	char *input;

	while (1)
	{
		input = getCommand();
		processInput(input);
		free(input);
	}

	return (0);
}
