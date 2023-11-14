#include "shell.h"

/**
 * listBuiltins - Search for a match and execute the associated builtin.
 * @data: Struct for the program's data.
 * 
 * Return: Returns the return of the executed function if there is a match,
 * otherwise returns -1.
 */

int listBuiltins(DataOfProgram *data)
{
	int index_;
	builtins options[] = {
		{"exit", exitShell},
		{"help", displayHelp},
		{"cd", changeDirectory},
		{"alias", handleAlias},
		{"env", displayEnv},
		{"setenv", setEnvVariable},
		{"unsetenv", unsetEnvVariable},
		{NULL, NULL}
	};

	for (index_ = 0; options[index_].builtin != NULL; index_++)
	{

		if (compareStrings(options[index_].builtin, data->commandName, 0))
		{
			return (options[index_].function(data));
		}

	}
	return (-1);
}
