/*
* A generic abstract data type. It can be used when testing other ADTs implementations.
*/ 

#ifndef REC_H
#define REC_H

typedef void* Record;
Record newRecord(char* id, char* type);
char* getRecordId(Record Rec);
char* getRecordType(Record Rec);
void printRecord(Record Rec);
void freeRecord(Record T);

#endif