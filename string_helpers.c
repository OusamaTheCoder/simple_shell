#include "shell.h"

/**
 * getStringLength - Returns the length of a string.
 * @string: Pointer to the string.
 * 
 * Return: Length of the string.
 */
int getStringLength(char *string)
{
	int length = 0;

	if (string == NULL)
		return (0);

	while (string[length++] != '\0')
	{
	}
	return (--length);
}

/**
 * duplicateString - Duplicates a string.
 * @string: String to be copied.
 * 
 * Return: Pointer to the duplicated array.
 */
char *duplicateString(char *string)
{
	char *multipResult;
	int length, i;

	if (string == NULL)
		return (NULL);

	length = getStringLength(string) + 1;

	multipResult = malloc(sizeof(char) * length);

	if (multipResult == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < length ; i++)
	{
		multipResult[i] = string[i];
	}

	return (multipResult);
}

/**
 * compareStrings - Compare two strings.
 * @frtString: String one, or the shorter.
 * @scdString: String two, or the longer.
 * @number: Number of characters to be compared, 0 for infinite.
 * 
 * Return: 1 if the strings are equal, 0 if the strings are different.
 */
int compareStrings(char *frtString, char *scdString, int number)
{
	int index_;

	if (frtString == NULL && scdString == NULL)
		return (1);

	if (frtString == NULL || scdString == NULL)
		return (0);

	if (number == 0) /* infinite longitud */
	{
		if (getStringLength(frtString) != getStringLength(scdString))
			return (0);
		for (index_ = 0; frtString[index_]; index_++)
		{
			if (frtString[index_] != scdString[index_])
				return (0);
		}
		return (1);
	}
	else
	{
		for (index_ = 0; index_ < number ; index_++)
		{
			if (frtString[index_] != scdString[index_])
			return (0);
		}
		return (1);
	}
}

/**
 * concatenateStrings - Concatenates two strings.
 * @frtString: First string to be concatenated.
 * @scdString: Second string to be concatenated.
 * 
 * Return: Pointer to the concatenated array.
 */
char *concatenateStrings(char *frtString, char *scdString)
{
	char *multipResult;
	int frtLength = 0, scdLength = 0;

	if (frtString == NULL)
		frtString = "";
	frtLength = getStringLength(frtString);

	if (scdString == NULL)
		scdString = "";
	scdLength = getStringLength(scdString);

	multipResult = malloc(sizeof(char) * (frtLength + scdLength + 1));
	if (multipResult == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	for (frtLength = 0; frtString[frtLength] != '\0'; frtLength++)
		multipResult[frtLength] = frtString[frtLength];
	free(frtString);

	for (scdLength = 0; scdString[scdLength] != '\0'; scdLength++)
	{
		multipResult[frtLength] = scdString[scdLength];
		frtLength++;
	}

	multipResult[frtLength] = '\0';
	return (multipResult);
}


/**
 * reverseString - Reverses a string.
 * @string: Pointer to the string.
 * 
 * Return: Void.
 */
void reverseString(char *string)
{

	int i = 0, length = getStringLength(string) - 1;
	char hold;

	while (i < length)
	{
		hold = string[i];
		string[i++] = string[length];
		string[length--] = hold;
	}
}
