#include "shell.h"

/**
 * processInput - handles user inputs
 * @input: user inputs
 */

void processInput(char *input)
{
	int background = 0;

	if (strCompare(input, "exit") == 0)
	{
		printf("Exiting the Shell!\n");
		exit(EXIT_SUCCESS);
	}
	if (input[strLength(input) - 2] == '&')
	{
		background = 1;
		input[strLength(input) - 2] = '\0';
	}
	if (isBuiltin(input))
	{
		printf("Executing built-in command: %s\n", input);
	}
	else
	{
		executeCommand(input, background);
	}
}
