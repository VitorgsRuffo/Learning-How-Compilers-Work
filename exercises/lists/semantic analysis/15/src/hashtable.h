#ifndef HASH_TABLE
#define HASH_TABLE

#define HASH_TABLE_INITIAL_SIZE 29

typedef void* HashTable;
typedef void* Info;
typedef char* InfoKey;

typedef void (*freeInfo)(Info); 
typedef InfoKey (*getInfoKey)(Info);

/*
*/

/*
    Pré condição: recebe o tamanho da tabela hash (deve ser maior que 0).
    Pós condição: cria uma tabela hash com tamanho "tableSize" e retorna a referencia dessa tabela criada. Se a criacao falhar retorna NULL.
*/
HashTable createHashTable(int tableSize, getInfoKey getKey);

/*
    Pré condição: requer uma instancia de tabela hash e a informacao a ser inserida. A chave dessa informacao nao deve ja estar presente na tabela.
    Pós condição: insere o dado "info" na tabela e retorna 1. Se a insercao falhar retorna 0.
*/
int insertHashTable(HashTable* HashT, Info info);

/*
    Pré condição: requer uma instancia de tabela hash e uma chave.
    Pós condição: retorna 1 se houver uma informacao na tabela cuja chave é igual a chave passada. Se nao, retorna 0.
*/
int isThereKeyInHashTable(HashTable HashT, char* key);


/*
    Pré condição: requer uma instancia de tabela hash e uma chave.
    Pós condição: retorna a informacao da tabela, se existente, cuja chave é a chave passada por parametro. Se nao, retorna NULL.
*/
Info getHashTableInfo(HashTable HashT, char* key);


/*
    Pré condição: requer uma instancia de tabela hash e uma chave.  A passagem de uma funcao de desalocar informacao e opcional.
    Pós condição: remove a informacao, cuja chave foi passada por parametro, da tabela. Se uma funcao de desalocar for passada, a informacao tambem e desalocada.
                  Se a remocao for bem sucedida retorna 1. Se nao retorna 0.
*/
int removeHashTableInfo(HashTable HashT, char* key, freeInfo freeFunction);


/*
    Pré condição: requer uma instancia de tabela hash e para função de print do tad.
    Pós condição: percorre a tabela printando seus elementos.
*/
void printHashTable(HashTable HashT, void (*printInformation)(void*));


/*
    Pré condição: requer uma instancia de tabela hash. A passagem de uma funcao de desalocar informacao e opcional.
    Pós condição: desaloca a memoria usada pela tabela. Se uma funcao de desalocar for passada, as informacoes tambem sao desalocadas.
*/
void freeHashTable(HashTable HashT, freeInfo freeFunction);

#endif