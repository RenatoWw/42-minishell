*This project has been created as part of the 42 curriculum by dapinhei and ranhaia-.*

## Description

**Minishell** is a project that aims to create a simple shell, mimicking the behavior of the Bash shell. The goal is to learn about process creation and synchronization using the C programming language, specifically diving deep into file descriptors, pipes, redirections, and signal handling.

This shell is capable of parsing user input, executing commands, managing environment variables, and handling pipelines and redirections, providing a functional command-line interface.

## Instructions

### Prerequisites
To run this project, you need a C compiler (`cc` or `gcc`), `make`, and the **Readline** library installed on your system.

On Linux (Ubuntu/Debian):
```bash
sudo apt-get install libreadline-dev
```
### Compilation
Clone the repository and compile the project using the Makefile:

```bash
git clone <repository_url> minishell
cd minishell
make
```
Execution
To start the shell, simply run the executable:

```bash
./minishell
```

You can now type commands just like in bash:

```bash
minishell$ ls -la
minishell$ grep "something" < file.txt | wc -l > result.txt
minishell$ export MY_VAR="Hello World"
minishell$ echo $MY_VAR
```

To exit the shell, type exit or press Ctrl+D.

### Features

This Minishell implements the following features:

Prompt: Displays a prompt waiting for a new command.

Command History: Working history (up/down arrows).

System Executables: Searches and launches executables based on the PATH variable or relative/absolute paths.

Single quotes prevent interpretation of metacharacters.

Double quotes inhibit all metacharacters except $.

Redirections:

`<` Redirect input.

`>` Redirect output.

`<<` Heredoc (reads input until a delimiter).

`>>` Redirect output in append mode.

Pipes (`|`): Connects the output of one command to the input of the next.

Environment Variables: Expands variables starting with `$`, including the exit status `$?`.

Signals:

`Ctrl+C`: Displays a new prompt on a new line.

`Ctrl+D`: Exits the shell.

`Ctrl+\`: Does nothing (in interactive mode).

### Builtins:

`echo (with -n option)`

`cd (with relative or absolute paths)`

`pwd`

`export`

`unset`

`env`

`exit`

## Resources
### References
[GNU Bash Manual](https://www.gnu.org/software/bash/manual/) - The reference for behavior.

[GNU Readline Library](https://tiswww.case.edu/php/chet/readline/rltop.html) - Documentation for input handling.

### AI Usage
Artificial Intelligence tools (specifically Gemini/ChatGPT models) were used in this project for the following tasks:

Debugging Memory Leaks: AI was used to analyze Valgrind logs and identify "still reachable" memory leaks in child processes (handling fork memory duplication) and specific leaks in the environment expansion logic.

Signal Handling Logic: AI assisted in understanding the difference between signal handling in the parent process versus child processes (blocking SIGINT/SIGQUIT during waitpid to prevent double prompts).


Exit Codes: Consultation on correct Bash behavior for exit codes in pipelines and syntax errors.

Note: All code logic was implemented and understood by the students; AI served as a pair programmer for debugging and explaining complex system call behaviors.