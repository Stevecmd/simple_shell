# C Programming
## Structure of a C program.
- Documentation section
This is the section just above a function that details the <br />
functions input, output and actual code. <br />
For example:
```c
/**
 * is_delimiter - Checks if a character is a delimiter.
 * @character: The character to be checked.
 * @delimiter_set: A string containing delimiter characters.
 *
 * This function iterates through the given string
 * of delimiter characters and checks if the provided character
 * matches any of them. If a match is found, it returns 1,
 * indicating that the character is a delimiter.
 * If no match is found, it returns 0, indicating that
 * the character is not a delimiter.
 *
 * Return: 1 if the character is a delimiter, 0 otherwise.
 */
int is_delimiter(char character, char *delimiter_set)
{
	while (*delimiter_set)
	{
		if (*delimiter_set++ == character)
			return (1);
	}
	return (0);
}
```

- Link Section
This section lists out the dependencies needed for the code to work. <br />
For example: <br />
```c
#include "shell.h"
#include "stdio.h"
```
The `.h` extension means that it is a header file.
You can also include predefined packages such as `standard-input-output`:
```c
#include <stdio.h>
```
So to use `string-length` in `strlen` you should include the string library.
```c
#include "string.h"
```

- Definition section
It defines the constants in the program. eg:
```c
#define Max 100
```
So that you can use the value in multiple sections but only <br />
define it once.

- Global declaration section
Similar to the `definition` section but instead of defining the value <br />
within the scope of a function, it is now available throughout the program.

- Main
This is a compulsory section, can only be declared once in every program.

- Sub program section
Generally appears after the `main` section. <br />
Here you can define additional functions.