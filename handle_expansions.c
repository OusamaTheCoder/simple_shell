#include "shell.h"

/**
 * expandVariables - Expand variables.
 * @data: A pointer to a struct of the program's data.
 *
 * Return: Nothing, but sets errno.
 */
void expandVariables(DataOfProgram *data)
{
	int i, j;
	char line[BUFFER_SIZE] = {0}, expandedLine[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->inputLine == NULL)
		return;
	addToBuffer(line, data->inputLine);
	for (i = 0; line[i]; i++)
		if (line[i] == '#')
			line[i--] = '\0';
		else if (line[i] == '$' && line[i + 1] == '?')
		{
			line[i] = '\0';
			convertLongToString(errno, expandedLine, 10);
			addToBuffer(line, expandedLine);
			addToBuffer(line, data->inputLine + i + 2);
		}
		else if (line[i] == '$' && line[i + 1] == '$')
		{
			line[i] = '\0';
			convertLongToString(getpid(), expandedLine, 10);
			addToBuffer(line, expandedLine);
			addToBuffer(line, data->inputLine + i + 2);
		}
		else if (line[i] == '$' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
			continue;
		else if (line[i] == '$')
		{
			for (j = 1; line[i + j] && line[i + j] != ' '; j++)
				expandedLine[j - 1] = line[i + j];
			temp = getEnvironKey(expandedLine, data);
			line[i] = '\0', expandedLine[0] = '\0';
			addToBuffer(expandedLine, line + i + j);
			temp ? addToBuffer(line, temp) : 1;
			addToBuffer(line, expandedLine);
		}
	if (!compareStrings(data->inputLine, line, 0))
	{
		free(data->inputLine);
		data->inputLine = duplicateString(line);
	}
}

/**
 * expandAlias - Expand aliases.
 * @data: A pointer to a struct of the program's data.
 *
 * Return: Nothing, but sets errno.
 */
void expandAlias(DataOfProgram *data)
{
	int i, j, wasExpanded = 0;
	char line[BUFFER_SIZE] = {0}, expandedLine[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->inputLine == NULL)
		return;

	addToBuffer(line, data->inputLine);

	for (i = 0; line[i]; i++)
	{
		for (j = 0; line[i + j] && line[i + j] != ' '; j++)
			expandedLine[j] = line[i + j];
		expandedLine[j] = '\0';

		temp = getAlias(data, expandedLine);
		if (temp)
		{
			expandedLine[0] = '\0';
			addToBuffer(expandedLine, line + i + j);
			line[i] = '\0';
			addToBuffer(line, temp);
			line[getStringLength(line)] = '\0';
			addToBuffer(line, expandedLine);
			wasExpanded = 1;
		}
		break;
	}
	if (wasExpanded)
	{
		free(data->inputLine);
		data->inputLine = duplicateString(line);
	}
}

/**
 * addToBuffer - Append a string at the end of the buffer.
 * @buffer: Buffer to be filled.
 * @str_to_add: String to be copied into the buffer.
 * Return: Nothing, but sets errno.
 */
int addToBuffer(char *buffer, char *str_to_add)
{
	int length, i;

	length = getStringLength(buffer);
	for (i = 0; str_to_add[i]; i++)
	{
		buffer[length + i] = str_to_add[i];
	}
	buffer[length + i] = '\0';
	return (length + i);
}
