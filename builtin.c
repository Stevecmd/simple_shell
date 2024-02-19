#include "shell.h"

#define ERROR_NULL_PARAM -1
#define ERROR_ILLEGAL_NUMBER -2
#define ERROR_CD_FAILURE -3
#define NUM_CMDS 3

#define ERROR_MSG_NULL_PARAM "NULL parameter passed"
#define ERROR_MSG_ILLEGAL_NUMBER "Illegal number: "
#define ERROR_MSG_CD_FAILURE "Failed to change directory"

/**
 * _myexit - exits the shell
 * @commandInfo: Structure containing potential arguments.
 * Return: exits with a given exit status
 *         (0) if commandInfo->argv[0] != "exit"
 */
int _myexit(info_t *commandInfo) {
    if (!commandInfo)
        return ERROR_NULL_PARAM;

    if (commandInfo->argv[1]) {
        int exitCode = _erratoi(commandInfo->argv[1]);
        if (exitCode == -1) {
            commandInfo->status = 2;
            print_error(commandInfo, ERROR_MSG_ILLEGAL_NUMBER);
            _eputs(commandInfo->argv[1]);
            _eputchar('\n');
            return ERROR_ILLEGAL_NUMBER;
        }
        commandInfo->err_num = exitCode;
        return exitCode;
    }
    commandInfo->err_num = -1;
    return 0;
}

/**
 * _mycd - Changes the current working directory of the process
 * 
 * This function implements the built-in 'cd' command to change the current
 * working directory. It checks for arguments, gets the directory to change
 * to from environment variables or arguments, and calls chdir(). On success,
 * it updates the PWD and OLDPWD environment variables.
 * 
 * @commandInfo: Pointer to info_t struct containing command details

 * Return: Returns 0 on success, -1 on failure
 */
int _mycd(info_t *commandInfo) {
    if (!commandInfo)
        return ERROR_NULL_PARAM;

    char *dir;
    char buffer[1024];
    char *currentDir = getcwd(buffer, 1024);

    if (!currentDir) {
        _puts("TODO: >>getcwd failure emsg here<<\n");
        return ERROR_CD_FAILURE;
    }

    if (!commandInfo->argv[1]) {
        dir = _getenv(commandInfo, "HOME=");
        if (!dir)
            dir = _getenv(commandInfo, "PWD=");
    } else if (_strcmp(commandInfo->argv[1], "-") == 0) {
        dir = _getenv(commandInfo, "OLDPWD=");
        if (!dir) {
            _puts(currentDir);
            _putchar('\n');
            return 1;
        }
    } else {
        dir = commandInfo->argv[1];
    }

    if (chdir(dir) == -1) {
        print_error(commandInfo, "can't cd to ");
        _eputs(commandInfo->argv[1]);
        _eputchar('\n');
        return ERROR_CD_FAILURE;
    }

    _setenv(commandInfo, "OLDPWD", _getenv(commandInfo, "PWD="));
    _setenv(commandInfo, "PWD", getcwd(buffer, 1024));
    return 0;
}

/**
 * _help - displays help information
 * @commandInfo: Structure containing potential arguments.
 * Return: Always returns 0
 */
typedef struct {
  char* command;
  char* description;
} Command;

Command commands[] = {
  {
    .command = "exit",
    .description = "Exit the shell"
  },
  {
    .command = "cd", 
    .description = "Change directory"
  },
  {
    .command = "help", 
    .description = "Display Help"
  },
};

const char* descriptions[NUM_CMDS] = {
  "Exit the shell",
  "Change directory", 
  "Display this help"
};

int _help(info_t* commandInfo) {

  if(!ValidateCommandInfo(commandInfo))
    return HandleError(INVALID_PARAMS);  

  for(int i = 0; i < NUM_CMDS; i++) {
    printf("%s - %s\n", commands[i], descriptions[i]);
  }

  return SUCCESS;

}

/**
 * main - my sample test cases
 * @commandInfo: Structure containing potential arguments.
 * Return: Always returns 0
 */
int main() {
    info_t commandInfo;
    commandInfo.argv[0] = "exit";
    commandInfo.argv[1] = "1";
    _myexit(&commandInfo);

    commandInfo.argv[0] = "cd";
    commandInfo.argv[1] = NULL;
    _mycd(&commandInfo);

    commandInfo.argv[0] = "help";
    _help(&commandInfo);

    return 0;
}