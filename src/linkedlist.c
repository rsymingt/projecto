
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

Record * createRecord(char *string)
{
	Record *record = malloc(sizeof(Record));
	if(!record)
	{
		perror("malloc error");
		exit(1);
	}
	
	record->string = malloc(sizeof(char) * (strlen(string) + 1));
	
	if(!record->string)
	{
		perror("malloc error");
		exit(1);
	}
	
	strcpy(record->string, string);
	
	record->next = NULL;
	
	return record;
}

Record * addToBack(Record *record, char *string)
{
	if(!record)
	{
		record = createRecord(string);
		return record;
	}
	else
	{
		record->next = addToBack(record->next, string);
		return record;
	}
}

Record * removeRecord(Record *record, char *string)
{
	if(!record)
	{
		return record;
	}
	else
	{
		if(strcmp(record->string, string) == 0)
		{
			free(record->string);
			free(record);
			record = record->next;
		}
		else
		{
			record->next = removeRecord(record->next, string);
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
		free(record);
		return (record = NULL);
	}
}

int exists(Record *record, char *string)
{
	if(record == NULL)
		return 0;
	else
	{
		if(strcmp(record->string, string) == 0)
			return 1;
		return exists(record->next, string);
	}
}

void printRecords(Record *record)
{
	if(!record)
	{
		return;
	}
	else
	{
		printf("%s\n", record->string);
		printRecords(record->next);
		return;
	}
}

