/*
 * Ryan Symington
 * 11/28/16
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#include "commands.h"
#include "filehandling.h"
#include "avl.h"

Tree *runCommands(Tree *tree, char *command, char *currentDirectory)
{
	//lists list of commands
	if(equals(command, "help"))
	{
		printf("Here is a list of commands...\n");
		printf("_______________________________\n");
		//list of commands
		printf("_______________________________\n");
	}
	
	//goes back a directory
	else if(equals(command, "cd.."))
	{
		char *found = strrchr(currentDirectory, '/');
			if(found)
				*found = '\0';
	}
	
	//moves to given directory if exists
	else if(equals(command, "cd"))
	{
		char *dir = strtok(NULL, " ");
		if(dir)
		{
			DIR *dp; 
			
			char *directory = getDir(currentDirectory, strlen(dir) + 2);
			strcat(directory, "/");
			strcat(directory, dir);
			
			//printf("%s\n", directory);
			
			dp = opendir (directory);
			
			free(directory);

			if (dp != NULL)
			{
				char *tok = strtok(dir, "/");
				if(tok && *tok != '.')
				{
					strcat(currentDirectory, "/");
					strcat(currentDirectory, tok);
				}
				(void) closedir(dp);
			}
			else
				printf("directory not found!\n\n");
		}
		
	}
	
	//lists directories and files in current directory
	else if(equals(command, "ls"))
	{
		DIR *dp;
		struct dirent *ep; 
		
		char *dir = getDir(currentDirectory, 0);
		
		printf("dir:%s\n", dir);
		
		dp = opendir (dir);
		
		free(dir);

		if (dp != NULL)
		{
			printf("\n");
			while ((ep = readdir(dp)))
				if(*(ep->d_name) != '.')
					puts (ep->d_name);
			printf("\n");
			(void) closedir (dp);
		}
		else
			perror ("Couldn't open the directory");
		
	}
	
	//makes a directory
	else if(equals(command, "mkdir"))
	{
		char *tok = strtok(NULL, " ");
		if(tok)
		{
			struct stat st;
			
			char *dir = getDir(currentDirectory, strlen(tok) + 1);
			strcat(dir, "/");
			strcat(dir, tok);
			
			if(stat(dir, &st) == -1)
			{
				mkdir(dir, 0700);
			}
			
			free(dir);
		}
	}
	
	//removes directory
	else if(equals(command, "rmdir"))
	{
		char *tok = strtok(NULL, " ");
		if(tok)
		{
			struct stat st;
			
			char *dir = getDir(currentDirectory, strlen(tok) + 1);
			strcat(dir, "/");
			strcat(dir, tok);
			
			if(stat(dir, &st) != -1)
				rmdir(dir);
			
			free(dir);
		}
	}
	
	//prints given input
	else if(equals(command, "print"))
	{
		char *tok = strtok(NULL, " ");
		if(tok)
		{
			if(equals(tok, "tree"))
			{
				if(tree)
					printTree(tree->root);
			}
		}
	}
	
	//search for terms seperated by spaces
	else if(equals(command, "search"))
	{
		char *search = strtok(NULL, "");
		if(search)
		{
			printf("searching for matching terms...\n\n");
			Record *list = searchTerms(tree->root, search);
			if(list)
			{
				printRecords(list);
				free(list);
			}
			else
			{
				printf("no_matching_terms\n");
			}
		}
	}
	
	//create tree out of given file
	else if(equals(command, "create"))
	{
		char *tok = strtok(NULL, " ");
		if(tok)
		{
			{
				char *found = strpbrk(tok, "\r\n");
				if(found)
				{
					*found = '\0';
					//printf("found");
				}
			}
				
			DIR *dp;
			struct dirent *ep; 
			
			char *dir = getDir(currentDirectory, strlen(tok) + 2);
			
			if(!dir)
			{
				perror("malloc error");
				exit(1);
			}
			
			dp = opendir (dir);
			
			int found;

			if (dp != NULL)
			{
				printf("\n");
				while ((ep = readdir(dp)))
				{
					if(*ep->d_name != '.' && equals(ep->d_name, tok))
					{
						strcat(dir, "/");
						strcat(dir, ep->d_name);
						found = 1;
					}
				}
				(void) closedir (dp);
				
				if(found == 1)
				{
					if(strstr(tok, "."))
					{
						printf("pass");
						tree = readFile(tree, dir);
					}
					else
						tree = readFiles(tree, dir);
				}
			}
			else
				perror ("Couldn't open the directory");
			free(dir);
		}
	}
	
	//inserts given key
	else if(equals(command, "insert"))
	{
		char *tok;
		while((tok = strtok(NULL, " ")))
		{
			tree->root = insert(tree->root, tok);
		}
	}
	
	//removes given key
	else if(equals(command, "remove"))
	{
		char *tok = strtok(NULL, " ");
		if(tok)
		{
			tree->root = removeNode(tree->root, tok);
		}
	}
	
	//testing block
	else if(equals(command, "destroy"))
	{
		char *tok = strtok(NULL, " ");
		if(tok)
		{
			if(equals(tok, "tree"))
			{
				tree = destroyTree(tree);
			}
		}
	}
	
	//if doesn't match any command print unknown command
	else
	{
		printf("unknown command\n");
	}
	
	return tree;
}

int equals(char *string, char *check)
{
	if(strcmp(string, check) == 0)
		return 1;
	else
		return 0;
}

char * getDir(char *currentDirectory, int extra)
{
	char *dir = malloc(sizeof(char) * (strlen(currentDirectory-2) + extra));
	strcpy(dir, "./");
	strcat(dir, currentDirectory + 4);
	return dir;
}
