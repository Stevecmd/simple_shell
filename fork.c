#ifndef _FORK_
#define _FORK_

#include <stdio.h>
#include <unistd.h>

/**
 * main - fork example
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;
    pid_t pid;

    my_pid = getpid();

    printf("Before fork:\n");
    pid = fork();
    printf("My pid is %u\n", pid);

    if(pid == -1)
    {
        perror("Error:");
        return (1);
    }

    if(pid == 0)
    {
        printf("After fork:\n");
        my_pid = getpid();
        printf("My pid is %u\n", my_pid);
    }

    return 0;
    }

#endif /* _FORK_ */