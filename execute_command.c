#include "shell.h"

/**
 * execute - Execute a command with its entire path variables.
 * @data: A pointer to the program's data. 
 * Return: If success returns zero; otherwise, return -1.
 */
int executeCommand(DataOfProgram *data)
{
	int retval = 0, status;
	pid_t processID;

	retval = listBuiltins(data);
	if (retval != -1)
		return (retval);

	retval = findProgram(data);
	if (retval)
	{
		return (retval);
	}
	else
	{
		processID = fork();
		if (processID == -1)
		{
			perror(data->commandName);
			exit(EXIT_FAILURE);
		}
		if (processID == 0)
		{
			retval = execve(data->tokenArray[0], data->tokenArray, data->env);
			if (retval == -1)
				perror(data->commandName), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&status);
			if (WIFEXITED(status))
				errno = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				errno = 128 + WTERMSIG(status);
		}
	}
	return (0);
}
