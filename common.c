#include "common.h"

/*
 * File: common.c
 * Auth: Steve Murimi
 */

/* Implement the display_menu function 2 */

void int_to_string(char *str, int num) {
	int i = 0;
	int temp = num;
	int len = 0;
	int j;

	/* Calculate the length of the integer */
	while (temp != 0) {
		temp /= 10;
		len++;
	}

	/* Handle the case when the number is negative */
	if (num < 0) {
		str[i++] = '-';
		num = -num;
	}

	/* Convert the integer to a string in reverse order */
	for (j = i + len - 1; j >= i; j--) {
		str[j] = (num % 10) + '0';
		num /= 10;
	}

	/* Null-terminate the string */
	str[i + len] = '\0';
}