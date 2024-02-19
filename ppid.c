#ifndef _PPID_
#define _PPID_

#include <stdio.h>
#include <unistd.h>

/**
 * main - PPID
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_ppid;

    my_ppid = ppid();
    printf("%u\n", my_ppid);
    return (0);
}

#endif /* _PPID_ */