# 0x16. C - Simple Shell
`C` `Group project` `Syscall`

## Description:

[![printf.jpg](https://i.ibb.co/Kz8mLRm/printf.png)](https://ibb.co/yBxVYGV)

The Simple Shell project is a lightweight command-line interface designed to send formatted output to stdout. This educational project was crafted by students from cohort `19`, namely `Ousama` and `Fatima`. The heart of the shell lies in the custom `_printf()` function, meticulously developed for the purpose of learning and understanding the intricacies of shell programming.

## Resources
### Read or watch:

- [Unix shell](https://en.wikipedia.org/wiki/Unix_shell)
- [Thompson shell](https://en.wikipedia.org/wiki/Thompson_shell)
- [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson)
- **Everything you need to know to start coding your own shell** concept page

### man or help:

- `sh` (Run sh as well)

## List of allowed functions and system calls

- access (man 2 access)
- chdir (man 2 chdir)
- close (man 2 close)
- closedir (man 3 closedir)
- execve (man 2 execve)
- exit (man 3 exit)
- _exit (man 2 _exit)
- fflush (man 3 fflush)
- fork (man 2 fork)
- free (man 3 free)
- getcwd (man 3 getcwd)
- getline (man 3 getline)
- getpid (man 2 getpid)
- isatty (man 3 isatty)
- kill (man 2 kill)
- malloc (man 3 malloc)
- open (man 2 open)
- opendir (man 3 opendir)
- perror (man 3 perror)
- read (man 2 read)
- readdir (man 3 readdir)
- signal (man 2 signal)
- stat (__xstat) (man 2 stat)
- lstat (__lxstat) (man 2 lstat)
- fstat (__fxstat) (man 2 fstat)
- strtok (man 3 strtok)
- wait (man 2 wait)
- waitpid (man 2 waitpid)
- wait3 (man 2 wait3)
- wait4 (man 2 wait4)
- write (man 2 write)

---

# Files in the Repository

| Name                   | Information                                          | Relevant Files                          |
|------------------------|------------------------------------------------------|-----------------------------------------|
| getline_helper.c       | Contains the `_getline` function for reading lines. | getline_helper.c                        |
| list_builtins.c        | Handles the list of built-in commands.               | list_builtins.c                        |
| execute_command.c      | Executes a given command.                            | execute_command.c                      |
| free_helpers.c         | Handles the freeing of allocated memory.             | helpers_free.c                         |
| string_helpers.c       | Provides utility functions for string operations.   | helpers_string.c                       |
| main_shell.c           | The main file for the shell program.                 | shell.c                                |
| tokenize_string.c      | Tokenizes strings based on delimiters.               | tokenize.c                             |
| manage_alias.c         | Manages aliases in the shell.                        | alias_management.c                     |
| more_builtins.c        | Additional built-in commands.                        | builtins_more.c                        |
| handle_expansions.c    | Deals with variable expansions.                      | expansions.c                           |
| number_helpers.c       | Helper functions for numeric operations.             | helpers_numbers.c                      |
| shell_macros.h         | Macros used in the shell program.                    | macros.h                               |
| env_builtins.c         | Built-in commands related to environment variables. | builtins_env.c                         |
| manage_env.c           | Manages the environment variables.                   | env_management.c                      |
| search_in_path.c       | Searches for a program in the PATH.                   | find_in_path.c                         |
| print_helpers.c        | Helper functions for printing.                       | helpers_print.c                        |
| custom_strtok.c        | Custom string tokenization.                          | strtok.c                               |

---

## Compilation

Your shell will be compiled this way:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o simple_shell
```

## Testing

### Your shell should work like this in interactive mode:

```bash
$ ./simple_shell
($) /bin/ls
simple_shell main.c shell.c
($)
($) exit
$
```

### But also in non-interactive mode:

```bash
$ echo "/bin/ls" | ./simple_shell
simple_shell main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./simple_shell
simple_shell main.c shell.c test_ls_2
simple_shell main.c shell.c test_ls_2
$
```
---
# Disclaimer
If you happen to use this repo, we scored `??%`
### Authors &copy;

- [Fatima El Asri](https://github.com/fatimaelasri01)
- [Ousama Oujaber](https://github.com/OusamaTheCoder)
---
