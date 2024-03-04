Define constants early so that the program has access to them during <br />
pre-processing rather than at compile time.
```c
# define PI 3.14
```
Types:
- Numeric constants
This has: <br/>
a) Integer
Contains decimal values. (,  and )
1. Decimal (base 10): - 0 - 9
2. Octet (base 8): - 0 - 7
3. Hexadecimal (base 16): (0 - 9) and (a - f)
```txt
a: 10,
b: 11,
c: 12,
d: 13,
e: 14,
f: 15
```

Examples: <br />
`05` is an octet constant. They always start with `0` on the left side. <br/>
`0X` or `Ox` is for hexadecimal digits. <br/>
b. Floating / Real constants <br/>
This has: 
1) Character constants
```txt
'a': 97 - 'A': 65
'b': 98 - 'A': 66
and so on ...
```
They full representation of character constants is:
```txt
A-Z : 65 - 90,
a-z : 97 - 122,
0-9 : 48 - 57,
Special characters are contained in:
0-47,
58-64,
91-96
```
1. Single character constants
This is a single character eg 'a'.
2. String constants
This is a sequence of characters enclosed in double quotes eg: <br/>
"a" is a string because of the double quotes.  <br/>
"abc" is also a string.

Examples:
The code below will print the decimal value of 'a' ie '97':
```c
print("%d", a)
```
The code below will print the character value of '97' ie 'a':
```c
print("%c", a)
```
When getting the length of a string, assume '+1' because the <br/>
compiler adds a null character constant to mark the end. eg <br/>
"string" will be "string\o" and have 6 characters. <br/>

## Declaring constants
Its done using the `const` keyword eg:
`const int a: 3,` <br/>
const values cannot be changed. <br/>

Declaration can also be done by defining them above the `main` function <br/>
using capital letters eg:
```c
# define PI 3.14
```
