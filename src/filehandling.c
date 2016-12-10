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

#include "filehandling.h"
#include "commands.h"

Tree * readFiles(Tree *tree, char *dirName)
{
	DIR *dp = opendir(dirName);
	struct dirent *ep;
	
	if(dp)
	{
		while((ep = readdir(dp)))
		{
			if(*ep->d_name != '.')
			{
				printf("%s\n", ep->d_name);
				if(strstr(ep->d_name, "."))
				{
					char *dir = malloc(sizeof(char) * (strlen(dirName) + strlen(ep->d_name) + 1));
					if(!dir)
					{
						perror("malloc error\n");
						exit(1);
					}
					strcpy(dir, dirName);
					strcat(dir, "/");
					strcat(dir, ep->d_name);
					printf("dir:%s\n", dir);
					tree = readFile(tree, dir);
					free(dir);
				}
				else
				{
					char *dir = malloc(sizeof(char) * (strlen(dirName) + strlen(ep->d_name) + 1));
					if(!dir)
					{
						perror("malloc error");
						exit(1);
					}
					strcpy(dir, dirName);
					strcat(dir, "/");
					strcat(dir, ep->d_name);
					tree = readFiles(tree, dir);
					free(dir);
				}
			}
		}
		
	(void) closedir(dp);
	}
	
	return tree;
}

Tree * readFile(Tree *tree, char *filename)
{
	printf("filename:%s\n", filename);
	FILE *f = fopen(filename, "rb");
	if(f)
	{
		fseek(f, 0, SEEK_END);
		long fsize = ftell(f);
		fseek(f, 0, SEEK_SET);  //same as rewind(f);

		char *file = malloc(fsize + 1);
		
		if(!file)
		{
			perror("malloc error");
			exit(1);
		}
		
		fread(file, fsize, 1, f);
		
		char *para = file;
		int lineSize = 0;
		
		//printf("%s\n", file);
		
		if(!file)
			printf("WTF\n");

		for (int i = 0; i < strlen(file); i ++)
		{
			//printf("%d\n", file[i]);
			if (file[i] == '\n')
		        {
		        	if(lineSize == 0)
		        	{
		        		char temp = file[i];
		        		file[i] = '\0';
		        		//printf("START%sEND\n", para);
		        		
		        		//creates keys for given paragraph
		        		tree = makeKeys(tree, para);
		        		
		        		file[i] = temp;
		        		para = file + i;
		        	}
		        	else if (i == strlen(file)-1)
		        	{
		        		//printf("START%sEND\n", para);
		        		
		        		//creates keys for given last paragraph
		        		tree = makeKeys(tree, para);
		        	}
		        	lineSize = 0;
		        }
		        
		        else if (file[i] != '\r' && file[i] != '\n')
		        
		        {
		        	lineSize ++;
		   	}
		}
		
		free(file);
		fclose(f);
	}
	else
	{
		printf("file not found\n");
	}
	
	return tree;
}
		
