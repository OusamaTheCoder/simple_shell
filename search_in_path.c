#include "shell.h"

int checkFileExists(char *fullPath);

/**
 * findProgram - Find a program in the path.
 * @data: A pointer to the program's data. 
 * Return: 0 if success, error code otherwise.
 */
int findProgram(DataOfProgram *data)
{
	int i = 0, returnCode = 0;
	char **directoryIndex;

	if (!data->commandName)
		return (2);

	if (data->commandName[0] == '/' || data->commandName[0] == '.')
		return (checkFileExists(data->commandName));

	free(data->tokenArray[0]);
	data->tokenArray[0] = concatenateStrings(duplicateString("/"),
			data->commandName);
	if (!data->tokenArray[0])
		return (2);

	directoryIndex = tokenizePath(data);

	if (!directoryIndex || !directoryIndex[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; directoryIndex[i]; i++)
	{
		directoryIndex[i] = concatenateStrings
			(directoryIndex[i], data->tokenArray[0]);
		returnCode = (checkFileExists(directoryIndex[i]));
		if (returnCode == 0 || returnCode == 126)
		{
			errno = 0;
			free(data->tokenArray[0]);
			data->tokenArray[0] = duplicateString(directoryIndex[i]);
			freePointerArray(directoryIndex);
			return (returnCode);
		}
	}
	free(data->tokenArray[0]);
	data->tokenArray[0] = NULL;
	freePointerArray(directoryIndex);
	return (returnCode);
}

/**
 * tokenizePath - Tokenize the path into directories.
 * @data: A pointer to the program's data.
 * Return: Array of path directories.
 */
char **tokenizePath(DataOfProgram *data)
{
	int i = 0;
	int directoryCounter = 2;
	char **tokenArray = NULL;
	char *PATH;

	PATH = getEnvironKey("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = duplicateString(PATH);

	for (i = 0; PATH[i]; i++)
	{
		if (PATH[i] == ':')
			directoryCounter++;
	}

	tokenArray = malloc(sizeof(char *) * directoryCounter);

	i = 0;
	tokenArray[i] = duplicateString(customStrtok(PATH, ":"));
	while (tokenArray[i++])
	{
		tokenArray[i] = duplicateString(customStrtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokenArray);

}

/**
 * checkFileExists - Checks if a file exists, is not a directory, and has
 * execution permissions for permissions.
 * @fullPath: Pointer to the full file name. 
 * Return: 0 on success, or an error code if it exists.
 */
int checkFileExists(char *fullPath)
{
	struct stat significantBit;

	if (stat(fullPath, &significantBit) != -1)
	{
		if (S_ISDIR(significantBit.st_mode) ||  access(fullPath, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
