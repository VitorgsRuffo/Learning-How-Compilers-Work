#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtable.h"
#include "list.h"


typedef struct hashtable {
    int elementsAmount;
    int size;
    List* info;
    getInfoKey getKey;
}hashtable;


int hashFunction(hashtable* hashT, char *str);

HashTable createHashTable(int tableSize, getInfoKey getKey){

    if(tableSize <= 0 || getKey == NULL)
        return NULL;

    hashtable* hashT = (hashtable*) malloc(sizeof(hashtable));
    if(hashT == NULL)
        return NULL;

    hashT->size = tableSize;
    hashT->elementsAmount = 0;

    hashT->info = (List*) malloc(tableSize * sizeof(List));
    if(hashT->info == NULL){
        free(hashT);
        return NULL;
    }

    for(int i = 0 ; i < tableSize; i++)
        hashT->info[i] = createList(); //same as *((*hashT).info + i) = createList();

    hashT->getKey = getKey;

    return hashT;
}

hashtable* resizeHashTable(hashtable* hashT){

    hashtable* newHashT = createHashTable(hashT->size*2, hashT->getKey);

    for(int i=0; i<hashT->size; i++){

        List currentList = hashT->info[i];

        if(currentList != NULL){

            Node currentNode = getFirst(currentList);
            Info info;

            while(currentNode != NULL){

                info = get(currentList, currentNode);

                insertHashTable((HashTable*) &newHashT, info);

                currentNode = getNext(currentList, currentNode);
            }
        }
    }

    freeHashTable((HashTable) hashT, NULL); //desaloca apenas a hashtable antiga, mantendo as informacoes alocadas.
    return newHashT;
}



int insertHashTable(HashTable* HashT, Info info){

    if(HashT == NULL  || *HashT == NULL || info == NULL)
        return 0;   
        
    hashtable** hashT = (hashtable**) HashT;

    if((**hashT).elementsAmount + 1 >= 0.75 * (**hashT).size){ //se a insercao de mais um elemento causar uma ocupacao de 75% do tamanho da tabela é recomendado aumentar seu tamanho.
        *hashT = resizeHashTable(*hashT);
    }

    char* infoKey = (*((**hashT).getKey))(info);

    int position = hashFunction(*hashT, infoKey);


    insert((**hashT).info[position], info);
    (**hashT).elementsAmount++;

    return 1;
}


int isThereKeyInHashTable(HashTable HashT, char* key){

    if(HashT == NULL || key == NULL)
        return 0;

    hashtable* hashT = (hashtable*) HashT;

    int position = hashFunction(hashT, key);

    List infoList = hashT->info[position];   // same as List infoList = *((*hashT).info + position);

    Node currentNode = getFirst(infoList);
    Info info;
    char* infoKey;

    while(currentNode != NULL){

        info = get(infoList, currentNode);

        infoKey = (*(hashT->getKey))(info);

        if(!strcmp(key, infoKey))
            return 1;

        currentNode = getNext(infoList, currentNode);
    }

    return 0;
}

Info getHashTableInfo(HashTable HashT, char* key){

    if(HashT == NULL || key == NULL)
        return NULL;

    hashtable* hashT = (hashtable*) HashT;

    int position = hashFunction(hashT, key);

    List infoList = hashT->info[position];   //same as List infoList = *((*hashT).info + position);

    Node currentNode = getFirst(infoList);
    Info info;
    char* infoKey;

    while(currentNode != NULL){

        info = get(infoList, currentNode);

        infoKey = (*(hashT->getKey))(info);

        if(!strcmp(key, infoKey))
            return info;

        currentNode = getNext(infoList, currentNode);
    }

    return NULL;
}


int removeHashTableInfo(HashTable HashT, char* key, freeInfo freeFunction){

    if(HashT == NULL || key == NULL)
        return 0;

    hashtable* hashT = (hashtable*) HashT;

    int position = hashFunction(hashT, key);

    List infoList = hashT->info[position];   //same as List infoList = *((*hashT).info + position);

    Node currentNode = getFirst(infoList);
    Info info;
    char* infoKey;

    while(currentNode != NULL){

        info = get(infoList, currentNode);

        infoKey = (*(hashT->getKey))(info);

        if(!strcmp(key, infoKey)){
            removeNode(infoList, currentNode, freeFunction);
            return 1;
        }

        currentNode = getNext(infoList, currentNode);
    }

    return 0;
}


void printHashTable(HashTable HashT, void (*printInformation)(void*)){

    if(HashT == NULL)
        return;

    hashtable* hashT = (hashtable*) HashT;

    printf("HashTable:\n");
    for(int i=0; i<hashT->size; i++){
        printf("[%d]: \n", i);
        printList(hashT->info[i], printInformation);
    }
}


void freeHashTable(HashTable HashT, freeInfo freeFunction){
    if(HashT == NULL)
        return;

    hashtable* hashT = (hashtable*) HashT;

    for(int i = 0; i<hashT->size; i++)
        freeList(hashT->info[i], freeFunction);

    free(hashT->info);
    free(hashT);
}


int hashFunction(hashtable* hashT, char *str){

    if(hashT->size == 0 || str == NULL) return -1;

    unsigned long hash = 5381;
    int c;

    while((c = *str++))
        hash = ((hash << 5) + hash) + c;

    return (hash % hashT->size);
}
