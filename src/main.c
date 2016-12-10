/*
 * Ryan Symington
 * 11/28/16
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "avl.h"
#include "commands.h"
#include "filehandling.h"

void getInput(char *input, char *currentDirectory);

int main(int argc, char *args[])
{
	Tree *tree = init();
	
	char input[255];
	char currentDirectory[255] = "root";
	char *command;
	
	while(1){
		getInput(input, currentDirectory);
		
		if(equals(input, "q"))
			break;
		
		if((command = strtok(input, " ")))
		{
			tree = runCommands(tree, command, currentDirectory);
		}
	}
	
	tree = destroyTree(tree);
	free(tree);
}

void getInput(char *input, char *currentDirectory)
{
	printf("%s>", currentDirectory);
	fgets(input, 255, stdin);
	char *found = strstr(input, "\n");
	if(found)
		*found = '\0';
	return;
}
