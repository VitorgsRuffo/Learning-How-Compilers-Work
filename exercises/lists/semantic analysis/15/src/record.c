#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "record.h"

typedef struct {
    char* id;
    char type[10];
}record;

Record newRecord(char* id, char* type){
    record* rec = (record*) malloc(sizeof(record));
    if(rec == NULL) return NULL;
    rec->id = id;
    strcpy(rec->type, type);
    return rec;
}

char* getRecordId(Record Rec){
    record* rec = (record*) Rec;
    return rec->id;
}

char* getRecordType(Record Rec){
    record* rec = (record*) Rec;
    return rec->type;
}

void printRecord(Record Rec){
    record* rec = (record*) Rec;
    printf("record: %s %s.\n", rec->type, rec->id);
}

void freeRecord(Record T){
    record* rec = (record*) T;
    free(rec->id);
    free(rec);
}