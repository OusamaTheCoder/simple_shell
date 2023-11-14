#include "shell.h"

/**
 * getLine - Reads one line from the prompt.
 * @data: Struct for the program's data.
 *
 * Return: Number of bytes read.
 */
int getLine(DataOfProgram *data)
{
	char buff[BUFFER_SIZE] = {'\0'};
	static char *commandArray[10] = {NULL};
	static char operatorsArray[10] = {'\0'};
	ssize_t bytesRead, i = 0;

	/*
	Check if there are no more commands in the array,
	and also check for logical operators.
	*/
	if (!commandArray[0] || (operatorsArray[0] == '&' && errno != 0) ||
		(operatorsArray[0] == '|' && errno == 0))
	{

		/* Free the memory allocated in the array if it exists. */
		for (i = 0; commandArray[i]; i++)
		{
			free(commandArray[i]);
			commandArray[i] = NULL;
		}

		/* Read from the file descriptor into the buffer. */
		bytesRead = read(data->fileDescriptor, &buff, BUFFER_SIZE - 1);
		if (bytesRead == 0)
			return (-1);

		/* Split lines on '\n' or ';'. */
		i = 0;
		do {
			commandArray[i] = duplicateString(customStrtok(i ? NULL : buff, "\n;"));
			/* Check and split for && and || operators. */
			i = checkLogicOperators(commandArray, i, operatorsArray);
		} while (commandArray[i++]);
	}

	/* Obtain the next command (command 0) and remove it from the array. */
	data->inputLine = commandArray[0];
	for (i = 0; commandArray[i]; i++)
	{
		commandArray[i] = commandArray[i + 1];
		operatorsArray[i] = operatorsArray[i + 1];
	}

	return (getStringLength(data->inputLine));
}

/**
 * checkAndSplitLogicOperators - Check and split for && and || operators.
 * @commandArray: Array of commands.
 * @currentIndex: Index in the commandArray to be checked.
 * @operatorsArray: Array of logical operators for each previous command.
 *
 * Return: Index of the last command in the commandArray.
 */
int checkLogicOperators(char *commandArray[], int i, char operatorsArray[])
{
	char *temp = NULL;
	int j;

	/* Check for the '&' character in the command line. */
	for (j = 0; commandArray[i] != NULL  && commandArray[i][j]; j++)
	{
		if (commandArray[i][j] == '&' && commandArray[i][j + 1] == '&')
		{
			/* Split the line when the '&&' characters are found. */
			temp = commandArray[i];
			commandArray[i][j] = '\0';
			commandArray[i] = duplicateString(commandArray[i]);
			commandArray[i + 1] = duplicateString(temp + j + 2);
			i++;
			operatorsArray[i] = '&';
			free(temp);
			j = 0;
		}
		if (commandArray[i][j] == '|' && commandArray[i][j + 1] == '|')
		{
			/* Split the line when the '||' characters are found. */
			temp = commandArray[i];
			commandArray[i][j] = '\0';
			commandArray[i] = duplicateString(commandArray[i]);
			commandArray[i + 1] = duplicateString(temp + j + 2);
			i++;
			operatorsArray[i] = '|';
			free(temp);
			j = 0;
		}
	}
	return (i);
}
