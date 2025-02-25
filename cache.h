#ifndef CACHE_H
#define CACHE_H
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    CACHE_HIT = 0, // o compilador já faria isso automaticamente, mas é bom documentar que 0 significa sucesso.
    CACHE_MISS_COMPULSORIO,
    CACHE_MISS_CONFLITO,
    CACHE_MISS_CAPACIDADE
} Resultado_acesso;

typedef enum {
    LRU,
    FIFO,
    RANDOM
} Substituicao;

typedef union {
    uint8_t  enderecoBytes[4];
    uint32_t endereco;
} Endereco;

typedef struct nodo {
    struct nodo *pAnterior;
    struct nodo *pProx;
    Endereco endereco;
} Nodo;

typedef struct contextoSubstituicao {
    Nodo *pPrimeiro;
    Nodo *pUltimo;
    size_t tamanhoContexto;
    Resultado_acesso (*FuncaoSubstituicao)(Endereco, struct contextoSubstituicao*);
} Contexto_substituicao;

typedef struct {
    uint8_t  *valor;
    uint32_t *tag;
    Contexto_substituicao *contexto;
} CacheMemory;

typedef struct {
    size_t nsets;
    size_t bsize;
    size_t assoc;
    size_t bits_offset;
    size_t bits_indice;
    size_t bits_tag;
    size_t missesCompulsorios;
    size_t missesConflito;
    size_t missesCapacidade;
    CacheMemory *memoria;
} Cache;

Cache* ConstroiCache (size_t nsets, size_t bsize, size_t assoc, Substituicao substituicao);
// Aloca o espaço necessário para a cache e insere seus atributos na estrutura de dados
// Retorna o endereço da cache alocada.

void FreeCache (Cache *cache);
// Libera os espaços alocados dinamicamente para a cache (função de encerramento do programa)

Resultado_acesso AcessaCache (Cache *cache, Endereco endereco);
// Realiza um acesso na cache em um determinado endereco
// Retorna se a escrita foi bem sucedida ou se houve algum tipo de miss.

Resultado_acesso SubstituiFIFO (Endereco endereco, Contexto_substituicao* contexto);
Resultado_acesso SubstituiLRU (Endereco endereco, Contexto_substituicao* contexto);
Resultado_acesso SubstituiRANDOM (Endereco endereco, Contexto_substituicao* contexto);
// As três funções acima operam o contexto de substituição da cache em caso de miss.

#endif // !CACHE_H
