#include "shell.h"

/**
 * freeRecurrentData - Free the fields needed for each loop.
 * @data: Struct of the program's data.
 * 
 * Return: Nothing.
 */
void freeRecurrentData(DataOfProgram *data)
{
	if (data->tokenArray)
		freePointerArray(data->tokenArray);
	if (data->inputLine)
		free(data->inputLine);
	if (data->commandName)
		free(data->commandName);

	data->inputLine = NULL;
	data->commandName = NULL;
	data->tokenArray = NULL;
}

/**
 * freeAllData - Free all fields of the data.
 * @data: Struct of the program's data.
 * 
 * Return: Nothing.
 */
void freeAllData(DataOfProgram *data)
{
	if (data->fileDescriptor != 0)
	{
		if (close(data->fileDescriptor))
			perror(data->programName);
	}
	freeRecurrentData(data);
	freePointerArray(data->env);
	freePointerArray(data->aliasList);
}

/**
 * freePointerArray - Frees each pointer of an array of pointers,
 * and the array itself.
 * @array: Array of pointers.
 * 
 * Return: Nothing.
 */
void freePointerArray(char **array)
{
	int i;

	if (array != NULL)
	{
		for (i = 0; array[i]; i++)
			free(array[i]);

		free(array);
		array = NULL;
	}
}
