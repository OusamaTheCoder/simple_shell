#include "shell.h"

/**
 * displayEnv - Shows the environment where the shell runs.
 * @data: Struct for the program's data.
 * 
 * Return: Zero if success, or another number if declared in the arguments.
 */
int displayEnv(DataOfProgram *data)
{
	int i;
	char copyName[50] = {'\0'};
	char *cpVar = NULL;

	/* If there are no arguments. */
	if (data->tokenArray[1] == NULL)
		printEnv(data);
	else
	{
		for (i = 0; data->tokenArray[1][i]; i++)
		{
			/* Checks if there exists a '=' character. */
			if (data->tokenArray[1][i] == '=')
			{
				/*
				Checks if there exists a variable with the same name
				and temporarily changes its value.
				*/
				cpVar = duplicateString(getEnvironKey(copyName, data));
				if (cpVar != NULL)
					setEnvKey(copyName, data->tokenArray[1] + i + 1, data);

				/* Print the environment. */
				printEnv(data);
				if (getEnvironKey(copyName, data) == NULL)
				{
					/* Print the variable if it does not exist in the environment. */
					printString(data->tokenArray[1]);
					printString("\n");
				}
				else
				{
					/* Returns the old value of the variable. */
					setEnvKey(copyName, cpVar, data);
					free(cpVar);
				}
				return (0);
			}
			copyName[i] = data->tokenArray[1][i];
		}
		errno = 2;
		perror(data->commandName);
		errno = 127;
	}
	return (0);
}

/**
 * setEnvVariable - ...
 * @data: Struct for the program's data.
 * 
 * Return: Zero if success, or another number if declared in the arguments.
 */
int setEnvVariable(DataOfProgram *data)
{
	if (data->tokenArray[1] == NULL || data->tokenArray[2] == NULL)
		return (0);
	if (data->tokenArray[3] != NULL)
	{
		errno = E2BIG;
		perror(data->commandName);
		return (5);
	}

	setEnvKey(data->tokenArray[1], data->tokenArray[2], data);

	return (0);
}

/**
 * unsetEnvVariable - ...
 * @data: Struct for the program's data.
 * 
 * Return: ...
 */
int unsetEnvVariable(DataOfProgram *data)
{
	if (data->tokenArray[1] == NULL)
		return (0);
	if (data->tokenArray[2] != NULL)
	{
		errno = E2BIG;
		perror(data->commandName);
		return (5);
	}
	removeEnvKey(data->tokenArray[1], data);

	return (0);
}
