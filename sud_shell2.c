#include "shell.h"

/**
 * forkNewProcess - forks new process to run the command
 *
 * @cmd: command to execute
 * @args: arguments for command
 */
void forkNewProcess(char *cmd, char **args)
{
	pid_t childPid = fork();

	if (childPid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (childPid == 0)
	{
		handleInputRedirection();
		handleOutputRedirection();
		execute_Command(cmd, args);
	}
	else
		wait(NULL);
}

/**
 * forkCommand - Forks new process to run the command.
 * @cmd: command to be executed
 * @args: command line argument
 */
void forkCommand(char *cmd, char **args)
{
	if (cmd == NULL || args == NULL)
	{
		printf("Error: NULL command or arguments\n");
		exit(EXIT_FAILURE);
	}
	forkNewProcess(cmd, args);
}
