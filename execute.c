#include "shell.h"

/**
 * execute_command - execute an external command
 * @tokens: array of strings representing the command and its arguments
 * Return: 0 success, -1 fail
 */

int execute_command(char **tokens)
{
	pid_t pid;

	if (myBuiltin(tokens[0]) == 0)
		return (0);

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execute_child(tokens);
	}
	else
	{
		int status;

		handle_parent(pid, &status);
	}
	return (0);
}

/**
 * execute_child - function to handle execution in the child process
 * @tokens: array of strings representing the command and its arguments
 */

void execute_child(char **tokens)
{
	char *path = find_command(tokens[0]);

	if (path != NULL)
	{
		if (execve(path, tokens, NULL) == -1)
		{
			perror("execve");
			fprintf(stderr, "Error executing command: %s\n", tokens[0]);
			free(path);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fprintf(stderr, "Command not found: %s\n", tokens[0]);
		exit(EXIT_FAILURE);
	}
}

/**
 * handle_parent - function to handle execution in the parent process
 * @pid: process ID of the child process
 * @status: pointer to the status of the child process
 */

void handle_parent(pid_t pid, int *status)
{
	int attempts = 0;
	pid_t wpid;

	while ((wpid = waitpid(pid, status, WUNTRACED)) > 0
			&& attempts < MAX_WAIT_ATTEMPTS)
	{
		if (WIFEXITED(*status) || WIFSIGNALED(*status))
			break;
		attempts++;
	}
	if (attempts >= MAX_WAIT_ATTEMPTS)
	{
		fprintf(stderr, "Error waiting for child process to exit\n");
		kill(pid, SIGKILL);
		exit(EXIT_FAILURE);
	}
}
