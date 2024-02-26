#ifndef BUILTIN_1_C
#define BUILTIN_1_C

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

// Custom function to convert an integer to a string
void int_to_string(char *str, int num) {
    int i = 0;
    while (num != 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }
    str[i] = '\0';

    // Reverse the string
    int start = 0, end = i - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}


#endif /* BUILTIN_1_C */