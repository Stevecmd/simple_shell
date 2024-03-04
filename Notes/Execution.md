# Stages
- Pre-processor
- Compile
- Assembly
- Linking
- Loading
- Execution

## Pre-processor
In the code below, these parts are interpreted by the pre-processor.
```c
#ifndef __EXECUTE_COMMANDS__
#define __EXECUTE_COMMANDS__

#include "shell.h"
#include <stdio.h>
```

This section processes all the lines with `#` with the appropriate values.
It then makes it available for the compiler.

## Assembly file
Once the pre-processor fetches the files and the program has no issue. <br />
An `Assembly` file will be generated from the code. <br />
It usually has the extension `.asm`.
An `Assembler` will then convert the code into `object code` eg `myprogram.obj`. <br />

## Linking
Next the `Linker` will link all the object code into one file and link it with `system libraries`. <br />
System libraries contains definitions of various pre-defined functions. <br />
After this an executable file will be generated with the extension `.exe`.

## Loading
Before execution the program has to be loaded into memory ie `RAM`. <br />
If there are no errors, the program will run from the `main` function.
