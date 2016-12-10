/*
 * Ryan Symington
 * 11/28/16
*/

#ifndef __COMMANDS_H__
#define __COMMANDS_H__

#include "avl.h"

Tree * runCommands(Tree *tree, char *command, char *currentDirectory);

int equals(char *string, char *check);

char * getDir(char *currentDirectory, int extra);

#endif
