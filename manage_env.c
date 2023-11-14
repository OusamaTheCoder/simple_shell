#include "shell.h"

/**
 * getEnvironKey - Gets the value of an environment variable.
 * @key: The environment variable of interest.
 * @data: Struct of the program's data.
 * 
 * Return: A pointer to the value of the variable or NULL if it doesn't exist.
 */

char *getEnvironKey(char *key, DataOfProgram *data)
{
	int i, keyLen = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	keyLen = getStringLength(key);

	for (i = 0; data->env[i]; i++)
	{
		if (compareStrings(key, data->env[i], keyLen) &&
		 data->env[i][keyLen] == '=')
		{
			return (data->env[i] + keyLen + 1);
		}
	}
	return (NULL);
}

/**
 * setEnvKey - Overwrite the value of the environment variable
 * or create it if it does not exist.
 * @key: Name of the variable to set.
 * @value: New value.
 * @data: Struct of the program's data.
 * 
 * Return: 1 if the parameters are NULL, 2 if there is an error, or 0 if success.
 */
int setEnvKey(char *key, char *value, DataOfProgram *data)
{
	int i, keyLen = 0, is_new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	keyLen = getStringLength(key);

	for (i = 0; data->env[i]; i++)
	{
		if (compareStrings(key, data->env[i], keyLen) &&
		 data->env[i][keyLen] == '=')
		{
			is_new_key = 0;
			free(data->env[i]);
			break;
		}
	}
	data->env[i] = concatenateStrings(duplicateString(key), "=");
	data->env[i] = concatenateStrings(data->env[i], value);

	if (is_new_key)
	{
		/*
		If the variable is new, it is created at the end of the actual list,
		and we needto put the NULL value in the next position.
		*/
		data->env[i + 1] = NULL;
	}
	return (0);
}

/**
 * removeEnvKey - Remove a key from the environment.
 * @key: The key to remove.
 * @data: The structure of the program's data.
 * 
 * Return: 1 if the key was removed, 0 if the key does not exist.
 */
int removeEnvKey(char *key, DataOfProgram *data)
{
	int i, keyLen = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	keyLen = getStringLength(key);

	for (i = 0; data->env[i]; i++)
	{
		if (compareStrings(key, data->env[i], keyLen) &&
		 data->env[i][keyLen] == '=')
		{
			free(data->env[i]);

			i++;
			for (; data->env[i]; i++)
			{
				data->env[i - 1] = data->env[i];
			}
			data->env[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * printEnv - Prints the current environment.
 * @data: Struct for the program's data.
 * 
 * Return: Nothing.
 */
void printEnv(DataOfProgram *data)
{
	int j;

	for (j = 0; data->env[j]; j++)
	{
		printString(data->env[j]);
		printString("\n");
	}
}
