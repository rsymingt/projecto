
#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

typedef struct record
{
	char *string;
	char *filename;
	struct record *next;
}Record;

Record * createRecord(char *string, char *filename);

Record * addToBack(Record *record, char *string, char *filename);

Record * removeRecord(Record *record, char *string, char *filename);

Record * destroyList(Record *record);

int exists(Record *record, char *string, char *filename);

void printRecords(Record *record, char *filename);

#endif

