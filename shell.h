#ifndef MAIN_SHELL_H
#define MAIN_SHELL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>

/******************** MACROS *********************/

/*
 * Include header file containing macros related to messages, help, and prompt.
 * This file defines macros for prompt messages,
 * unused attribute, buffer size, and help messages.
 */
#include "shell_macros.h"

/******************** MACROS *********************/

/****************** STRUCTURES *******************/

/**
 * struct info - Structure holding program data
 * @programName: Name of the executable
 * @inputLine: Pointer to input obtained using getLine
 * @commandName: Pointer to the first user-typed command
 * @execCounter: Number of executeCommandd commands
 * @fileDescriptor: File descriptor for command input
 * @tokenArray: Pointer to an array of tokenized input
 * @env: Copy of environment variables (environ)
 * @aliasList: Array of pointers to aliases
 */
typedef struct info
{
	char *programName;
	char *inputLine;
	char *commandName;
	int execCounter;
	int fileDescriptor;
	char **tokenArray;
	char **env;
	char **aliasList;
} DataOfProgram;

/**
 * struct builtins - Structure defining built-in,
 * commands and their associated functions.
 * @builtin: The name of the built-in command.
 * @function: The function pointer to the associated built-in function.
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(DataOfProgram *data);
} builtins;

/************************* STRUCTURES *******************************/

/*========================  main_shell.c  ========================*/
/**
 * initializeData - Initializes the struct with the program's information.
 * @data: Pointer to the structure holding program data.
 * @arc: Number of values received from the command line.
 * @argv: Array of arguments passed to the program execution.
 * @env: Environ passed to the program execution.
 */
void initializeData(DataOfProgram *data, int arc, char *argv[], char **env);

/**
 * executeSisifo - Initiates an infinite loop displaying the prompt.
 * @prompt: Prompt to be printed.
 * @data: Pointer to the structure holding program data.
 */
void executeSisifo(char *prompt, DataOfProgram *data);

/**
 * handleCtrl_C - Handles the Ctrl+C signal,
 * by printing the prompt in a new line.
 * @UNUSED: Option of the prototype (unused).
 */
void handleCtrl_C(int opr UNUSED);
/*========================  main_shell.c  ========================*/


/*========================  getline_helper.c  ========================*/
/**
 * getLine - Reads one line from the standard input.
 * @data: Pointer to the structure holding program data.
 * Return: The number of bytes read.
 */
int getLine(DataOfProgram *data);

/**
 * checkLogicOperators - Checks and splits each line for logical,
 * operators if they exist.
 * @commandArray: Array of commands.
 * @i: Index in the commandArray to be checked.
 * @operatorsArray: Array of logical operators for each previous command.
 * Return: The index of the last command in the commandArray.
 */
int checkLogicOperators(char *commandArray[], int i, char operatorsArray[]);
/*========================  getline_helper.c  ========================*/


/*======================== handle_expansions.c ========================*/
/**
 * expandVariables - Expands variables.
 * @data: Pointer to the structure holding program data.
 */
void expandVariables(DataOfProgram *data);

/**
 * expandAlias - Expands aliases.
 * @data: Pointer to the structure holding program data.
 */
void expandAlias(DataOfProgram *data);

/**
 * addToBuffer - Appends the string to the end of the buffer.
 * @buffer: Buffer to be filled.
 * @str_to_add: String to be added to the buffer.
 * Return: 0 on success, or an error code.
 */
int addToBuffer(char *buffer, char *str_to_add);
/*======================== handle_expansions.c ========================*/


/*======================== custom_strtok.c ========================*/
/**
 * tokenizeData - Separates the string into tokens,
 * using a designated delimiter.
 * @data: Pointer to the structure holding program data.
 */
void tokenizeData(DataOfProgram *data);

/**
 * customStrtok - Creates a pointer to a part of a string.
 * @line: Pointer to the string to be tokenized.
 * @delim: String containing delimiter characters.
 * Return: Pointer to the next token in the string.
 */
char *customStrtok(char *line, char *delim);
/*======================== custom_strtok.c ========================*/


/*======================== execute_command.c ========================*/
/**
 * executeCommand - Executes a command with its full path.
 * @data: Pointer to the program's data structure.
 * This function takes a command from the data structure, finds its full path,
 * and executes it. It returns 0 on success or -1 on failure.
 *
 * Return: 0 on success, -1 on failure.
 */
int executeCommand(DataOfProgram *data);
/*======================== execute_command.c ========================*/


/*======================== list_builtins.c ========================*/
/**
 * listBuiltins - Execute a builtin command if it matches.
 * @data: Pointer to the program's data structure.
 * This function iterates through the list of builtins, checks if the entered
 * command matches any of them, and executes the corresponding function. If
 * there is a match, it returns the return value of the executed function;
 * otherwise, it returns -1.
 *
 * Return: Return value of the executed builtin function or -1 if no match.
 */
int listBuiltins(DataOfProgram *data);
/*======================== list_builtins.c ========================*/


/*======================== search_in_path.c ========================*/
/**
 * tokenizePath - Tokenize the PATH variable into an array of directories.
 * @data: Pointer to the program's data structure.
 * This function takes the PATH variable from the environment, tokenizes it
 * using ':' as the delimiter, and returns an array of strings representing
 * each directory in the PATH.
 *
 * Return: An array of strings containing directories in the PATH.
 */
char **tokenizePath(DataOfProgram *data);

/**
 * findProgram - Search for a program in the directories listed in the PATH.
 * @data: Pointer to the program's data structure.
 * This function searches for the specified program in the directories listed
 * in the PATH variable. If the program is found, it updates the command's
 * full path in the data structure.
 *
 * Return: 0 if the program is found, an error code otherwise.
 */
int findProgram(DataOfProgram *data);
/*======================== search_in_path.c ========================*/


/************** HELPERS FOR MEMORY MANAGEMENT **************/

/*======================== free_helpers.c ========================*/

/* Frees the memory for directories */
void freePointerArray(char **directoryIndex);

/* Free the fields needed each loop */
void freeRecurrentData(DataOfProgram *data);

/* Free all field of the data */
void freeAllData(DataOfProgram *data);
/*======================== free_helpers.c ========================*/

/************** BUILTINS **************/

/*======================== more_builtins.c ========================*/
/**
 * exitShell - Exit the shell with the specified status.
 * @data: Pointer to the program's data structure.
 * This function exits the shell with the specified status. If no status is
 * provided, it uses the status of the last executed command.
 *
 * Return: 0 if successful, -1 if an error occurs.
 */
int exitShell(DataOfProgram *data);

/**
 * changeDirectory - Change the current working directory.
 * @data: Pointer to the program's data structure.
 * This function changes the current working directory based on the provided
 * arguments. If no argument is given, it changes to the home directory.
 * If the argument is "-", it changes to the previous working directory.
 *
 * Return: 0 if successful, -1 if an error occurs.
 */
int changeDirectory(DataOfProgram *data);

/**
 * setWorkingDirectory - Set the working directory to the specified path.
 * @data: Pointer to the program's data structure.
 * @newDirectory: New working directory path.
 * This function sets the working directory to the specified path.
 *
 * Return: 0 if successful, -1 if an error occurs.
 */
int setWorkingDirectory(DataOfProgram *data, char *newDirectory);

/**
 * displayHelp - Display help information for the shell built-ins.
 * @data: Pointer to the program's data structure.
 * This function displays help information for the built-in commands.
 *
 * Return: 0 if successful, -1 if an error occurs.
 */
int displayHelp(DataOfProgram *data);

/**
 * handleAlias - Add, remove, or show aliases.
 * @data: Pointer to the program's data structure.
 * This function handles the manipulation and display of aliases.
 *
 * Return: 0 if successful, -1 if an error occurs.
 */
int handleAlias(DataOfProgram *data);
/*======================== more_builtins.c ========================*/


/*====================== env_builtins.c =============================*/
/**
 * displayEnv - Display the current environment variables.
 * @data: Pointer to the program's data structure.
 * This function prints the current environment variables.
 *
 * Return: 0 if successful, -1 if an error occurs.
 */
int displayEnv(DataOfProgram *data);

/**
 * setEnvVariable - Create or override an environment variable.
 * @data: Pointer to the program's data structure.
 * This function creates or overrides an environment variable with the provided
 * key-value pair.
 *
 * Return: 0 if successful, -1 if an error occurs.
 */
int setEnvVariable(DataOfProgram *data);

/**
 * unsetEnvVariable - Delete an environment variable.
 * @data: Pointer to the program's data structure.
 * This function deletes the specified environment variable.
 *
 * Return: 0 if successful, -1 if an error occurs.
 */
int unsetEnvVariable(DataOfProgram *data);
/*====================== env_builtins.c =============================*/

/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/

/*======================== manage_env.c ========================*/
/**
 * getEnvironKey - Get the value of an environment variable.
 * @name: The name of the environment variable.
 * @data: Pointer to the program's data structure.
 * This function returns the value of the specified environment variable.
 *
 * Return: A pointer to the value of the variable or NULL if it doesn't exist.
 */
char *getEnvironKey(char *name, DataOfProgram *data);

/**
 * setEnvKey - Overwrite the value of the environment variable.
 * @key: The name of the environment variable.
 * @value: The new value for the environment variable.
 * @data: Pointer to the program's data structure.
 * This function overwrites the value of the specified environment variable
 * or creates it if it does not exist.
 *
 * Return: 1 if the parameters are NULL,
 * 2 if there is an error, or 0 if successful.
 */
int setEnvKey(char *key, char *value, DataOfProgram *data);

/**
 * removeEnvKey - Remove a key from the environment.
 * @key: The name of the environment variable to be removed.
 * @data: Pointer to the program's data structure.
 * This function removes the specified environment variable.
 *
 * Return: 1 if the key was removed, 0 if the key does not exist.
 */
int removeEnvKey(char *key, DataOfProgram *data);

/**
 * printEnv - Print the current environment.
 * @data: Pointer to the program's data structure.
 * This function prints the current environment variables.
 */
void printEnv(DataOfProgram *data);
/*======================== manage_env.c ========================*/

/******************************* HELPERS *******************************/

/*========================== print_helpers.c ========================*/
/**
 * printString - Writes a string to the standard output.
 * @string: Pointer to the array of characters.
 * This function writes the specified string to the standard output.
 *
 * Return: The number of bytes written,
 * or -1 on error with errno set appropriately.
 */
int printString(char *string);

/**
 * printErrorString - Writes a string to the standard error.
 * @string: Pointer to the array of characters.
 * This function writes the specified string to the standard error.
 *
 * Return: The number of bytes written,
 * or -1 on error with errno set appropriately.
 */
int printErrorString(char *string);

/**
 * printErrorMessage - Writes an error message to the standard error.
 * @errorCode: The error code to be printed.
 * @data: Pointer to the program's data structure.
 * This function writes an error message associated with the given error code,
 * to the standard error.
 *
 * Return: The number of bytes written,
 * or -1 on error with errno set appropriately.
 */
int printErrorMessage(int errorCode, DataOfProgram *data);
/*========================== print_helpers.c ========================*/


/*======================== string_helpers.c ========================*/
/**
 * getStringLength - Returns the length of a string.
 * @string: Pointer to the string.
 * This function calculates and returns the length of the specified string.
 *
 * Return: Length of the string.
 */
int getStringLength(char *string);

/**
 * duplicateString - Duplicates a string.
 * @string: String to be duplicated.
 * This function creates a new string that is a duplicate,
 * of the specified string.
 *
 * Return: Pointer to the duplicated string.
 */
char *duplicateString(char *string);

/**
 * compareStrings - Compares two strings.
 * @frtString: First string (or the shorter one).
 * @scdString: Second string (or the longer one).
 * @number: Number of characters to be compared (0 for infinite).
 * This function compares two strings up to the specified number of characters.
 *
 * Return: 1 if the strings are equal, 0 if different.
 */
int compareStrings(char *frtString, char *scdString, int number);

/**
 * concatenateStrings - Concatenates two strings.
 * @frtString: First string.
 * @scdString: Second string.
 * This function concatenates two strings and returns,
 * a pointer to the resulting string.
 *
 * Return: Pointer to the concatenated string.
 */
char *concatenateStrings(char *frtString, char *scdString);

/**
 * reverseString - Reverses a string in-place.
 * @string: Pointer to the string.
 * This function reverses the order of characters in the specified string.
 *
 * Return: None.
 */
void reverseString(char *string);
/*======================== string_helpers.c ========================*/


/*======================== number_helpers.c ========================*/
/**
 * convertLongToString - Converts a long number to a string.
 * @number: Number to be converted.
 * @string: Buffer to save the number as a string.
 * @base: Base to convert the number.
 * This function converts the specified long number to a string representation
 * using the specified base and stores it in the provided buffer.
 *
 * Return: None.
 */
void convertLongToString(long number, char *string, int base);

/**
 * parseInt - Converts a string to an integer.
 * @s: Pointer to the string.
 * This function converts the specified string to an integer.
 *
 * Return: The integer representation of the string.
 */
int parseInt(char *s);

/**
 * countCharacters - Counts the occurrences of a character in a string.
 * @string: Pointer to the string.
 * @character: String with characters to be counted.
 * This function counts the occurrences of the specified,
 * characters in the given string.
 *
 * Return: The count of occurrences.
 */
int countCharacters(char *string, char *character);
/*======================== number_helpers.c ========================*/


/*======================= manage_alias.c ========================*/
/**
 * printAlias - Prints the list of aliases or the value of a specific alias.
 * @data: Pointer to the program's data.
 * @alias: Name of the alias to be printed (NULL for the entire list).
 * This function prints either the list of all aliases,
 * or the value of a specific alias
 * if the 'alias' parameter is provided.
 *
 * Return: 0 on success, or an error code if the alias is not found.
 */
int printAlias(DataOfProgram *data, char *alias);

/**
 * getAlias - Gets the value of a specific alias.
 * @data: Pointer to the program's data.
 * @alias: Name of the alias to retrieve.
 * This function retrieves the value of the specified alias.
 *
 * Return: A pointer to the alias value, or NULL if the alias is not found.
 */
char *getAlias(DataOfProgram *data, char *alias);

/**
 * setAlias - Adds or overrides an alias.
 * @aliaString: Alias string in the form (name='value').
 * @data: Pointer to the program's data.
 * This function adds a new alias or overrides,
 * an existing one based on the provided string.
 *
 * Return: 0 on success, or an error code if there is an issue with the input.
 */
int setAlias(char *aliaString, DataOfProgram *data);
/*======================= manage_alias.c ========================*/

#endif /* MAIN_SHELL_H */
