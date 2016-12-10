
#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

typedef struct record
{
	char *string;
	struct record *next;
}Record;

Record * createRecord(char *string);

Record * addToBack(Record *record, char *string);

Record * removeRecord(Record *record, char *string);

Record * destroyList(Record *record);

int exists(Record *record, char *string);

void printRecords(Record *record);

#endif

