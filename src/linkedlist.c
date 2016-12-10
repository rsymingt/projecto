
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

Record * createRecord(char *string, char *filename)
{
	Record *record = malloc(sizeof(Record));
	if(!record)
	{
		perror("malloc error");
		exit(1);
	}
	
	record->string = malloc(sizeof(char) * (strlen(string) + 1));
	record->filename = malloc(sizeof(char) * (strlen(filename) + 1));
	
	if(!record->string || !record->filename)
	{
		perror("malloc error");
		exit(1);
	}
	
	strcpy(record->string, string);
	strcpy(record->filename, filename);
	
	record->next = NULL;
	
	return record;
}

Record * addToBack(Record *record, char *string, char *filename)
{
	if(!record)
	{
		record = createRecord(string, filename);
		return record;
	}
	else
	{
		record->next = addToBack(record->next, string, filename);
		return record;
	}
}

Record * removeRecord(Record *record, char *string, char *filename)
{
	if(!record)
	{
		return record;
	}
	else
	{
		if(strcmp(record->string, string) == 0 && strcmp(record->filename, filename) == 0)
		{
			free(record->string);
			free(record);
			record = record->next;
		}
		else
		{
			record->next = removeRecord(record->next, string, filename);
		}
		return record;
	}
}

Record * destroyList(Record *record)
{
	if(!record)
	{
		return record;
	}
	else
	{
		destroyList(record->next);
		free(record->string);
		record->string = NULL;
		free(record->filename);
		record->filename = NULL;
		free(record);
		return (record = NULL);
	}
}

int exists(Record *record, char *string, char *filename)
{
	if(record == NULL)
		return 0;
	else
	{
		if(strcmp(record->string, string) == 0)
			return 1;
		return exists(record->next, string, filename);
	}
}

void printRecords(Record *record, char *filename)
{
	if(!record)
	{
		return;
	}
	else
	{
		if(strcmp(record->filename, filename) != 0)
		{
			filename = record->filename;
			if(filename)
			{
				printf("file location: %s\n", filename);
				for(int i = 0; i < strlen(filename) + 15; printf("_"), i ++);
				printf("\n\n");
			}
		}
		printf("%s\n", record->string);
		printRecords(record->next, filename);
		return;
	}
}

