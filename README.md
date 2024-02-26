# simple_shell
This is my repo for 0x16. C - Simple Shell

Executing the individual files: <br/>
Install gcc:
`sudo apt install gcc`

Main entry point:
`gcc -o prompt prompt.c`
`./prompt`

Get process ID:
`gcc -o mypid pid.c`
`./mypid`

Get parent process ID:
`gcc -o ppid ppid.c`
`./ppid`

Determine whether a function is builtin or external
`gcc -o execute_args execute_args.c builtin.c`
`./execute_args`

Executing a program:
`gcc -o exec exec.c`
`./exec`

Print the current environment variables:
`gcc -o env-environ env-environ.c`
`./env-environ`

Print the current environment variables of the current process:
`gcc -o printenv env-main.c`
`./printenv`

Create a new child process
`gcc -o fork fork.c`
`./fork`

Simple fork a child process and then immediately waits for it
`gcc -o wait wait.c`
`./wait`

Take a filename as a command-line argument and print various pieces of information about the file
`gcc -o stat stat.c`
`./stat`
Usage:
`./stat <filename>`

Read stream:
``

Shell program: <br />
interactive mode:
`hsh main.c shell.c`

non-interactive mode:
`hsh main.c shell.c test_ls_2`