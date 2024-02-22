#ifndef _WAIT_
#define _WAIT_

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
* wait - fork & wait
*
* Return: Always 0.
*/
int shell_wait(void)
{
pid_t child_pid;
int status;

child_pid = fork();
if (child_pid == -1)
{
perror("Error:");
return (1);
}
if (child_pid == 0)
{
printf("Wait for me, wait for me\n");
sleep(3);
}
else
{
wait(&status);
printf("Oh, it's all better now\n");
}
return (0);
}

#endif /* _WAIT_ */