#ifndef H_CACHETYPES
#define H_CACHETYPES

#define MALLOC_NULL_CHECK(ponteiro, mensagem) \
do { \
    if ((ponteiro) == NULL) { \
        errno = ENOMEM; \
        perror((mensagem)); \
        exit(EXIT_FAILURE); \
    } \
} while(0)

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
    uint32_t via;
} Nodo;

typedef struct contextoSubstituicao {
    Nodo *pPrimeiro;
    Nodo *pUltimo;
} Contexto_substituicao;

typedef struct {
    uint8_t  *valor;
    uint32_t *tag;
    uint32_t itensArmazenados;
} Memoria_cache;

typedef struct cache {
    uint32_t seed;
    uint32_t nsets;
    uint32_t bsize;
    uint32_t assoc;
    uint32_t bits_offset;
    uint32_t bits_indice;
    uint32_t bits_tag;
    uint32_t missesCompulsorios;
    uint32_t missesConflito;
    uint32_t missesCapacidade;
    uint32_t hits;
    Memoria_cache *memoria;
    Contexto_substituicao *contexto;
    // OperaContexto: deve operar o contexto de substituição (se existir) e retornar a VIA da cache em que deve
    // ocorrer a substituição.
    uint32_t (*EscolheVia)(uint32_t, struct cache *);
} Cache;

#endif /* ifndef H_CACHETYPES */

