#ifndef LIST_H
#define LIST_H

/*
* apontador void para uma instancia do TAD que esta presente em um no da lista.
*/
typedef void* Info;

/*
*apontador void para um no de uma lista.
*/
typedef void* Node;

/*
*apontador void para uma instancia de lista.
*/
typedef void* List;

/*
* Pré-Condição: nenhuma.
* Pós-Condição: retornar uma lista vazia.
*/
List createList();

/*
* Pré-Condição: requer uma lista.
* Pós-Condição: retorna a quantidade de nós presentes na lista.
*/
int length(List Li);

/*
* Pré-Condição: requer uma lista e uma referencia para o bloco de memoria que representa a informação do no a ser inserido.
* Pós-Condição: insere um novo nó ao final da lista e retorna uma referencia para ele.
*/
Node insert(List Li, Info info);

/*
* Pré-Condição: requer um lista, uma referencia para o no que sera removido e uma referencia para a funcao que libera a memoria da informacao presente dentro do no. 
* Pós-Condição: se o no for encontrado libera a memoria da informacao do no, libera o no, o desconecta da lista e retorna 1. Se nao, retorna 0.
*/
int removeNode(List Li, Node nodeToRemove, void (*freeTAD)(void*));

/*
* Pré-Condição: requer uma lista vazia, ou, com um ou mais elementos e um apontador Posic para um no da lista.
* Pós-Condição: retorna um apontador para a instancia de um TAD presente no nó apontado por Posic.
*/
Info get(List Li, Node Posic);

/*
* Pré-Condição: requer uma lista não vazia, um ponteiro Posic para um no e um ponteiro chamado Informacao para a instancia de um TAD.
* Pós-Condição: adiciona um no com a Informacao antes do no apontado por Posic, e, retorna uma referencia para o nó criado.
*/
Node insertBefore(List Li, Node Posic, Info Information);

/*
* Pré-Condição: requer uma lista não vazia, um ponteiro Posic para um no e um ponteiro chamado Informacao para a instancia de um TAD.
* Pós-Condição: adiciona um no com a Informacao depois do no apontado por Posic, e, retorna uma referencia para o nó criado.
*/
Node insertAfter(List Li, Node Posic, Info Information);

/*
* Pré-Condição: Requer uma lista com um ou mais nós.
* Pós-Condição: Retorna o endereço do primeiro nó da lista.
*/
Node getFirst(List Li);

/*
* Pré-Condição: Requer uma lista e um ponteiro Posic para um elemento.
* Pós-Condição: Retorna o endereço do elemento posterior ao elemento Posic passado por parâmetro.
*/
Node getNext(List Li, Node Posic);

/*
* Pré-Condição: Requer uma lista com um ou mais nós.
* Pós-Condição: Retorna o endereço do ultimo nó da lista.
*/
Node getLast(List Li);

/*
* Pré-Condição: Requer uma lista e um ponteiro para um elemento.
* Pós-Condição: Retorna o endereço do elemento anterior ao elemento Posic passado por parâmetro.
*/
Node getPrevious(List Li, Node Posic);

/*
* Pré-Condição: requer a referencia para uma lista, a referencia para uma funcao de pegar o id dos elementos (tads) que fazem parte da lista, e o id de um elemento a ser procurado na lista.
* Pós-Condição: percorre a lista e , se encontrado, retorna no com a informacao (tad) que possui o id passado por parametro. Se o elemento nao for encontrado e retonado NULL.
*/
Node searchForElementByIdentifier(List Li, char* (*getElementId)(void*), char* idToSearch);

/*
* Pré-Condição: requer a referencia para uma lista, e uma informacao.
* Pós-Condição: percorre a lista e , se encontrado, retorna no que possua a informacao (tad) passada por parametro. Se o elemento nao for encontrado e retonado NULL.
*/
Node searchForNodeByInfo(List Li, Info info);

/*
* Pré-Condição: requer uma lista com um ou mais nós.
* Pós-Condição: imprimir na saida padrão a informação presente em cada nó da lista especificada. 
*/
void printList(List Li, void (*printInformation)(void*));

/*
Pré-condição: requer uma lista com um ou mais nós.
Pós-condição: cria e retorna um vetor que aponta para as mesmas informacoes que a lista.
*/
Info* listToArray(List Li);

/*
* Pré-Condição: requer uma lista vazia, ou, com um ou mais elementos.
* Pós-Condição: desalocar a memoria usada para a lista e seus nós.
*/
void freeList(List Li, void (*freeTAD)(void*));

/*
* Pré-Condição: requer uma lista vazia, ou, com um ou mais elementos.
* Pós-Condição: desalocar a memoria usada pela lista.
*/
void freeOnlyList(List Li);

#endif