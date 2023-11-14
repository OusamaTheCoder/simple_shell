#ifndef HELPERS_H
#define HELPERS_H

/* Define the prompt message */
#define PROMPT_MSG "FA.OU $ "

/* Define a macro for unused variables */
#define UNUSED __attribute__((unused))

/* Define the buffer size */
#define BUFFER_SIZE 1024

/*=============Define help messages for built-in commands=============*/

#define HELP_CD_MSG "cd=\n"\
"cd:\tcd [dir]\n\n"\
"	Alter the current working directory of the shell.\n\n"\
"	If the cd command is used without providing any arguments, it will be interpreted as follows:\n"\
"	as cd $HOME.\n"\
"	If the argument is - (cd -), the command will be interpreted:\n"\
"	as cd $OLDPWD.\n\n"

#define HELP_EXIT_MSG "exit=\n"\
"exit:\texit [STATUS]\n\n"\
"	Exit of the simple_shell.\n\n"\
"	Quits the shell with an exit status of N. If N is not provided, the exit status\n"\
"	will be that of the last executed command.\n\n"

#define HELP_ENV_MSG "env=\n"\
"env:\tenv \n\n"\
"	Print environment.\n\n"\
"	The env command prints a comprehensive list of environment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"\
"setenv:\tsetenv VARIABLE VALUE\n\n"\
"	Change or add an environment variable.\n\n"\
"	Initialize a new environment variable or modify an existing one.\n"\
"	If there is an incorrect number of arguments, an error message is printed.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"\
"unsetenv:\tunsetenv VARIABLE\n\n"\
"	The unsetenv function deletes one variable from the environment.\n\n"\
"	When there is an incorrect number of arguments, an error message is printed.\n\n"

#define HELP_MSG "help=\n"\
"help:\thelp [BUILTIN_NAME]\n\n"\
"	Display information about builtin commands.\n\n"\
"	Summary of builtin commands. If BUILTIN_NAME is specified, provides detailed help on commands matching BUILTIN_NAME.\n"\
"   If not, the list of help topics is printed.\n"\
"	Arguments:\n\n"\
"	BUILTIN_NAME specifying a help topic.\n\n"\
"	cd\t[dir]\n"\
"	exit\t[status]\n"\
"	env\n"\
"	setenv\t[variable value]\n"\
"	unset\t[variable]\n"\
"	help\t[built_name]\n\n"


#endif
