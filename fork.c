#ifndef _FORK_
#define _FORK_

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

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
        printf("My pid is %u\n", my_pid);

    if (pid == -1)
    {
        perror("Error:");
        return (1);
    }

    elif (pid == 0)
    {
        printf("After fork:\n");
        my_pid = getpid();
            printf("My pid is %u\n", my_pid);
    }
    else
    {
        int status;
        wait(&status); /* Ensure parent waits for child to finish before exiting */
        if (WIFEXITED(status))
        {
            printf("Parent process finished\n");
        }
    }

    return 0;
}

#endif /* _FORK_ */
