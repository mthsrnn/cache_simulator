#ifndef CACHE_H
#define CACHE_H
#include <stdlib.h>
#include <stdint.h>

typedef enum {
    CACHE_HIT = 0, // o compilador já faria isso automaticamente, mas é bom documentar que 0 significa sucesso.
    CACHE_MISS_COMPULSORIO,
    CACHE_MISS_CONFLITO,
    CACHE_MISS_CAPACIDADE
} Resultado_escrita;

typedef enum {
    LRU,
    FIFO,
    RANDOM
} Substituicao;

typedef union {
    uint8_t  enderecoBytes[4];
    uint32_t endereco;
} Endereco;

typedef struct {
    uint8_t  *valor;
    uint32_t *tag;
} CacheMemory;

typedef struct {
    size_t nsets;
    size_t bsize;
    size_t assoc;
    Substituicao substituicao;
    CacheMemory memoria;
} Cache;

Cache* ConstroiCache (size_t nsets, size_t bsize, size_t assoc, Substituicao substituicao);
// Aloca o espaço necessário para a cache e insere seus atributos na estrutura de dados
// Retorna o endereço da cache alocada.

void FreeCache (Cache *cache);
// Libera os espaços alocados dinamicamente para a cache (função de encerramento do programa)

Resultado_escrita EscreveCache (Cache *cache, Endereco endereco);
// Realiza uma escrita na cache em um determinado endereco
// Retorna se a escrita foi bem sucedida ou se houve algum tipo de miss.

#endif // !CACHE_H
