#include "shell.h"

/**
 * tokenizeData - Separates the string using a designated delimiter.
 * @data: A pointer to the program's data.
 * 
 * Return: An array of the different parts of the string.
 */
void tokenizeData(DataOfProgram *data)
{
	char *delimiter = " \t";
	int i, j, dirCounter  = 2, length;

	length = getStringLength(data->inputLine);
	if (length)
	{
		if (data->inputLine[length - 1] == '\n')
			data->inputLine[length - 1] = '\0';
	}

	for (i = 0; data->inputLine[i]; i++)
	{
		for (j = 0; delimiter[j]; j++)
		{
			if (data->inputLine[i] == delimiter[j])
				dirCounter ++;
		}
	}

	data->tokenArray = malloc(dirCounter  * sizeof(char *));
	if (data->tokenArray == NULL)
	{
		perror(data->programName);
		exit(errno);
	}
	i = 0;
	data->tokenArray[i] = duplicateString(customStrtok(data->inputLine, delimiter));
	data->commandName = duplicateString(data->tokenArray[0]);
	while (data->tokenArray[i++])
	{
		data->tokenArray[i] = duplicateString(customStrtok(NULL, delimiter));
	}
}
