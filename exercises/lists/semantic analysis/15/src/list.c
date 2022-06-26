#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

typedef struct node {
    struct node *previous;
    Info info;
    struct node *next;
}node;

typedef struct list {
    node *first;
    node *last;
}list;


List createList(){
    list *li = (list*) malloc(sizeof(list));

    if(li == NULL)
        return NULL;
    

    li->first = NULL;
    li->last = NULL;
    return li;
}


int length(List Li){
    if(Li == NULL)
        return -1;
    
    list *li = (list*) Li;
    if(li->first == NULL){
        return 0;
    }else{
        node *NODE = li->first;
        int nodeAmount = 0;
        while(NODE != NULL){
            nodeAmount++;
            NODE = NODE->next;
        }
        return nodeAmount;
    }
}


Node insert(List Li, Info info){
    if(Li == NULL || info == NULL )
        return NULL;
        
    list *li = (list*) Li;

    node *NODE = (node*) malloc(sizeof(node));
    NODE->info = info;

    if(li->first == NULL){ //lista vazia
        li->first = NODE;
        NODE->previous = NULL;
    }else{
        NODE->previous = li->last;
        NODE->previous->next = NODE;
    }
    li->last = NODE;
    NODE->next = NULL;

    return NODE;
}

int removeNode(List Li, Node nodeToRemove, void (*freeTAD)(void*)){
    if(Li == NULL || nodeToRemove == NULL)
        return 0;
        
    list *li = (list*) Li;
    node *NODE = li->first;

    while(NODE != NULL){

        if(NODE == nodeToRemove){

            if(freeTAD != NULL)
              (*freeTAD)(NODE->info);

            if(NODE->previous == NULL){ //remocao no inicio
                li->first = NODE->next;

                if(li->first != NULL) //if (lista resultante tem mais de um elemento) 
                  li->first->previous = NULL; 

            }else if(NODE->next == NULL){ //remocao no final
                li->last = NODE->previous;
                li->last->next = NULL;

            }else{ //remocao no meio
                NODE->previous->next = NODE->next;
                NODE->next->previous = NODE->previous;
            }
           
            free(NODE);
            return 1; //no encontrado e removido.
        }
        NODE = NODE->next;
    }
    
    return 0; //no nao encontrado.
}

Info get(List Li, Node Posic){ 
    if(Li == NULL || Posic == NULL)
        return NULL;

    node *NODE = (node*) Posic;
    return NODE->info;
}

Node insertBefore(List Li, Node Posic, Info Information){
    if(Li == NULL || Posic == NULL || Information == NULL)
        return NULL;

    list *li = (list*) Li;
    node *NODE = (node*) Posic;
    
    node *previousNODE = (node*) malloc(sizeof(node));
    previousNODE->info = Information;

    if(NODE->previous == NULL){
        previousNODE->previous = NULL;
        previousNODE->next = NODE;

        li->first = previousNODE;
        NODE->previous = previousNODE;
    }else{
        previousNODE->next = NODE;
        previousNODE->previous = NODE->previous; 

        previousNODE->previous->next = previousNODE;
        NODE->previous = previousNODE;
    }

    return previousNODE;
}

Node insertAfter(List Li, Node Posic, Info Information){   
    
    if(Li == NULL || Posic == NULL || Information == NULL)
        return NULL;
        
    list *li = (list*) Li;
    node *NODE = (node*) Posic;

    node *afterNODE = (node*) malloc(sizeof(node));
    afterNODE->info = Information;

    if(NODE->next == NULL){
        afterNODE->next = NULL;
        afterNODE->previous = NODE;

        NODE->next = afterNODE;
        li->last = afterNODE;
    }else{
        afterNODE->next = NODE->next;
        afterNODE->previous = NODE;

        NODE->next->previous = afterNODE;
        NODE->next = afterNODE;
    }

    return afterNODE;
}

Node getFirst(List Li){
    if(Li == NULL || length(Li) == 0)
        return NULL;
    
    list *li = (list*) Li;
    return li->first;
}

Node getNext(List Li, Node Posic){
    if(Li == NULL || Posic == NULL)
        return NULL;

    node *NODE = (node*) Posic;
    return NODE->next;
}

Node getLast(List Li){
    if(Li == NULL || length(Li) == 0)
        return NULL;

    list *li = (list*) Li;
    return li->last;
}

Node getPrevious(List Li, Node Posic){ 
    if(Li == NULL || Posic == NULL)
        return NULL;

    node *NODE = (node*) Posic;
    return NODE->previous;
}

Node searchForElementByIdentifier(List Li, char* (*getElementId)(void*), char* idToSearch){
    if(Li == NULL)
        return NULL;

    char elementId[30];
    Info elementInformation;
    Node NODE;
    List elementsList = (list*) Li;
    
    NODE = getFirst(elementsList);
    
    while (NODE != NULL){
        elementInformation = get(elementsList, NODE);
        strcpy(elementId, (*getElementId)(elementInformation));
        
        if(!strcmp(elementId, idToSearch))
            return NODE;    
        else
            NODE = getNext(elementsList, NODE);               
    }

    return NULL;
}

Node searchForNodeByInfo(List Li, Info info){
    if(Li == NULL || info == NULL)
        return NULL;

    List li = (list*) Li;
    Info currentInfo;
    Node currentNode;
    
    currentNode = getFirst(li);
    
    while (currentNode != NULL){

        currentInfo = get(li, currentNode);
        
        if(currentInfo == info)
            return currentNode;    
        else
            currentNode = getNext(li, currentNode);               
    }

    return NULL;
}

void printList(List Li, void (*printInformation)(void*)){
    if(Li == NULL)
        return;
    
    list *li = (list*) Li;
    if(li->first == NULL)
        return;
    
    node *NODE = li->first; 
    while(NODE != NULL){
        (*printInformation)(NODE->info);
        NODE = NODE->next;
    }
}


Info* listToArray(List Li){
    if(Li == NULL) return NULL;

    int listLength = length(Li);
    if(listLength == 0) return NULL;

    Info* array = (Info*) malloc(listLength*sizeof(Info));
    if(array == NULL) return NULL;
    int i = 0;

    node* currentNode = getFirst(Li);

    while(currentNode != NULL){
        array[i] = get(Li, currentNode);
        currentNode = getNext(Li, currentNode);
        i++;
    }
    
    return array;
}

void freeList(List Li, void (*freeTAD)(void*)){
    if(Li == NULL)
        return;

    list *li = (list*) Li;
    
    if(li->first != NULL){
        node *NODE = li->first;
        node *helperNODE = NODE->next;
        while(1){
            if(freeTAD != NULL)
                (*freeTAD)(NODE->info);
            
            free(NODE);
            NODE = helperNODE;
            if(NODE == NULL){
                break;
            }
            helperNODE = helperNODE->next;
        }
    }

    li->first = NULL; li->last = NULL;
    free(li);
}