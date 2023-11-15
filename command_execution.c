#include "shell.h"

/**
 * executeCommand - handles commands inputeed and executes them
 * @input: user inputs
 * @background: the background processes
 */

void executeCommand(char *input, int background)
{
	char *cmdPath = strDuplicate(findCommandPath(input));
	char **args;

	if (cmdPath != NULL)
	{
		printf("Executing command: %s\n", cmdPath);
		args = tokenizeInput(input);

		forkCommand(cmdPath, args);
		if (!background)
			wait(NULL);

		freeArgs(args);
		free(cmdPath);
	}
	else
		printf("Command not found: %s\n", input);
}
