# Resources
[Unix Shell](https://en.wikipedia.org/wiki/Unix_shell) <br />
[Thompson Shell](https://en.wikipedia.org/wiki/Thompson_shell) <br />
[Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson) <br />

## simple_shell
This is my repo for 0x16. C - Simple Shell

### General
    - Who designed and implemented the original Unix operating system
    - Who wrote the first version of the UNIX shell
    - Who invented the B programming language (the direct predecessor to the C programming language)
    - Who is Ken Thompson
    - How does a shell work
    - What is a pid and a ppid
    - How to manipulate the environment of the current process
    - What is the difference between a function and a system call
    - How to create processes
    - What are the three prototypes of main
    - How does the shell use the PATH to find the programs
    - How to execute another program with the execve system call
    - How to suspend the execution of a process until one of its children terminates
    - What is EOF / “end-of-file”?

## Requirements
- Allowed editors: vi, vim, emacs
- All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
- All your files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- Use system calls only when you need to (why?)
- Write a README with the description of your project
- You should have an AUTHORS file at the root of your repository, listing all individuals having contributed content to the repository.

### Output

    Unless specified otherwise, your program must have the exact same output as `sh (/bin/sh)` as well as the exact same error output.
    The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]` (See below)

Example of error with `sh`:
```sh
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
```
Same error with your program `hsh`:
```sh
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
```
### List of allowed functions and system calls
```txt
    access
    chdir 
    close 
    closedir 
    execve 
    exit 
    _exit 
    fflush 
    fork 
    free
    getcwd 
    getline 
    getpid 
    isatty 
    kill 
    malloc
    open 
    opendir 
    perror 
    read 
    readdir 
    signal 
    stat 
    lstat 
    fstat 
    strtok 
    wait 
    waitpid 
    wait3 
    wait4 
    write 
```

### Compilation

Your shell will be compiled this way:

`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`

### Testing

Your shell should work like this in interactive mode:
```sh
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
```
But also in non-interactive mode:
```sh
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
```

##Tasks
0. Betty would be proud <br />
Write a beautiful code that passes the Betty checks

1. Simple shell 0.1 <br />
Write a UNIX command line interpreter.

    Usage: `simple_shell`

Your Shell should:

    Display a prompt and wait for the user to type a command. A command line always ends with a new line. <br />
    The prompt is displayed again each time a command has been executed. <br />
    The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features. <br />
    The command lines are made only of one word. No arguments will be passed to programs. <br />
    If an executable cannot be found, print an error message and display the prompt again. <br />
    Handle errors. <br />
    You have to handle the “end of file” condition `(Ctrl+D)` <br />

You don’t have to:

    use the `PATH`
    implement built-ins
    handle special characters:` ", ', `, \, *, &, #`
    be able to move the cursor
    handle commands with arguments

`execve` will be the core part of your Shell, don’t forget to pass the environ to it…

```sh
julien@ubuntu:~/shell$ ./shell 
#cisfun$ ls
./shell: No such file or directory
#cisfun$ /bin/ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell.c  stat.c         wait
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     stat test_scripting.sh  wait.c
#cisfun$ /bin/ls -l
./shell: No such file or directory
#cisfun$ ^[[D^[[D^[[D
./shell: No such file or directory
#cisfun$ ^[[C^[[C^[[C^[[C
./shell: No such file or directory
#cisfun$ exit
./shell: No such file or directory
#cisfun$ ^C
julien@ubuntu:~/shell$ echo "/bin/ls" | ./shell
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell.c  stat.c         wait
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     stat test_scripting.sh  wait.c
```
3. Simple shell 0.3 <br />
Simple shell 0.2 +

-  Handle the `PATH`
- `fork` must not be called if the command doesn’t exist
```sh
julien@ubuntu:~/shell$ ./shell_0.3
:) /bin/ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell_0.3  stat    test_scripting.sh  wait.c
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     shell.c    stat.c  wait
:) ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell_0.3  stat    test_scripting.sh  wait.c
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     shell.c    stat.c  wait
:) ls -l /tmp 
total 20
-rw------- 1 julien julien    0 Dec  5 12:09 config-err-aAMZrR
drwx------ 3 root   root   4096 Dec  5 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-colord.service-V7DUzr
drwx------ 3 root   root   4096 Dec  5 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-rtkit-daemon.service-ANGvoV
drwx------ 3 root   root   4096 Dec  5 12:07 systemd-private-062a0eca7f2a44349733e78cb4abdff4-systemd-timesyncd.service-CdXUtH
-rw-rw-r-- 1 julien julien    0 Dec  5 12:09 unity_support_test.0
:) ^C
julien@ubuntu:~/shell$ 
```
4. Simple shell 0.4 <br />
Simple shell 0.3 +

    Implement the `exit` built-in, that exits the shell
    Usage: `exit`
    You don’t have to handle any argument to the built-in `exit`

5. Simple shell 1.0 <br />
Simple shell 0.4 +

- Implement the `env` built-in, that prints the current environment.
```sh
julien@ubuntu:~/shell$ ./simple_shell
$ env
USER=julien
LANGUAGE=en_US
SESSION=ubuntu
COMPIZ_CONFIG_PROFILE=ubuntu
SHLVL=1
HOME=/home/julien
C_IS=Fun_:)
DESKTOP_SESSION=ubuntu
LOGNAME=julien
TERM=xterm-256color
PATH=/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DISPLAY=:0
$ exit
julien@ubuntu:~/shell$ 
```
6. Simple shell 0.1.1 <br />
Simple shell 0.1 +

- Write your own getline function
- Use a buffer to read many chars at once and call the least possible the read system call
- You will need to use static variables
- You are not allowed to use getline

You don’t have to:

- be able to move the cursor

7. Simple shell 0.2.1 <br />
Simple shell 0.2 +

- You are not allowed to use `strtok`

8. Simple shell 0.4.1 <br />
Simple shell 0.4 +

- handle arguments for the built-in `exit`
- Usage: `exit status`, where status is an integer used to `exit` the shell.

```sh
julien@ubuntu:~/shell$ ./shell_0.4.1
$ exit 98
julien@ubuntu:~/shell$ echo $?
98
julien@ubuntu:~/shell$ 
```

9. setenv, unsetenv <br />
Simple shell 1.0 +

Implement the setenv and unsetenv builtin commands

1. setenv
- Initialize a new environment variable, or modify an existing one
- Command syntax: setenv VARIABLE VALUE
- Should print something on stderr on failure
2. unsetenv
- Remove an environment variable
- Command syntax: unsetenv VARIABLE
- Should print something on stderr on failure

10. cd <br />
Simple shell 1.0 + <br />

Implement the builtin command `cd`:

    Changes the current directory of the process.
    Command syntax: `cd [DIRECTORY]`
    If no argument is given to `cd` the command must be interpreted like `cd $HOME`
    You have to handle the command cd -
    You have to update the environment variable `PWD` when you change directory

`man chdir, man getcwd`

11. ; 
Handle the commands separator `;`: <br />
```sh
alex@~$ ls /var ; ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn ; ls /var
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /var ; ls /hbtn
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
alex@~$ ls /var ; ls /hbtn ; ls /var ; ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
```

12. && and || <br />
Handle the `&&` and `||` shell logical operators.
```sh
alex@~$ ls /var && ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn && ls /var
ls: cannot access /hbtn: No such file or directory
alex@~$ ls /var && ls /var && ls /var && ls /hbtn
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
alex@~$ ls /var && ls /var && ls /var && ls /hbtn && ls /hbtn
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
alex@~$
alex@~$ ls /var || ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn || ls /var
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn || ls /hbtn || ls /hbtn || ls /var
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn || ls /hbtn || ls /hbtn || ls /var || ls /var
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$
```

13. alias 

- Implement the `alias` builtin command
- Usage: `alias [name[='value'] ...]`
    1. `alias`: Prints a list of all aliases, one per line, in the form `name='value'`
    2. `alias name [name2 ...]`: Prints the aliases `name`, `name2`, etc 1 per line, in the form `name='value'`
    3. `alias name='value' [...]`: Defines an alias for each name whose value is given. If name is already an alias, replaces its value with `value`

14. Variables 

- Handle variables replacement
- Handle the `$?` variable
- Handle the `$$` variable

```sh
julien@ubuntu:~/shell$ ./hsh
$ ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  snap  spool  tmp
$ echo $?
0
$ echo $$
5104
$ echo $PATH
/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
$ exit 
julien@ubuntu:~/shell$ 
```
15. Comments <br />
Handle comments `(#)`
```sh
julien@ubuntu:~/shell$ sh
$ echo $$ # ls -la
5114
$ exit
julien@ubuntu:~/shell$ 
```

16. File as input 

- Usage: `simple_shell [filename]`
- Your shell can take a file as a command line argument
- The file contains all the commands that your shell should run before exiting
- The file should contain one command per line
- In this mode, the shell should not print a prompt and should not read from `stdin`


Executing the individual files: <br/>
Install gcc:
`sudo apt install gcc`

Main entry point: <br />
`gcc -o prompt prompt.c`
`./prompt`

Get process ID: <br />
`gcc -o mypid pid.c`
`./mypid`

Get parent process ID: <br />
`gcc -o ppid ppid.c`
`./ppid`

Determine whether a function is builtin or external: <br />
`gcc -o execute_args execute_args.c builtin.c`
`./execute_args`

Executing a program: <br />
`gcc -o exec exec.c`
`./exec`

Print the current environment variables: <br />
`gcc -o env-environ env-environ.c`
`./env-environ`

Print the current environment variables of the current process: <br />
`gcc -o printenv env-main.c`
`./printenv`

Create a new child process: <br />
`gcc -o fork fork.c`
`./fork`

Simple fork a child process and then immediately waits for it:<br />
`gcc -o wait wait.c`
`./wait`

Take a filename as a command-line argument and print various pieces of information about the file: <br />
`gcc -o stat stat.c`
`./stat`
Usage:<br />
`./stat <filename>`

Read stream:
``

Shell program: <br />
interactive mode:
`hsh main.c shell.c`

non-interactive mode:<br />
`hsh main.c shell.c test_ls_2`