#include "cache.h"
#include "cacheUtils.h"
#include <stdio.h>

#define MALLOC_NULL_CHECK(ponteiro, mensagem) \
    do { \
        if ((ponteiro) == NULL) { \
            perror((mensagem)); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)


Cache* ConstroiCache (size_t nsets, size_t bsize, size_t assoc, Substituicao substituicao) {
    Cache *cache = malloc(sizeof(Cache));
    MALLOC_NULL_CHECK(cache, "ERRO: Nao foi possivel alocar memória para a cache.");
    
    cache->nsets = nsets;
    cache->bsize = bsize;
    cache->assoc = assoc;
    cache-> bits_offset = fast_log2(bsize);
    cache-> bits_indice = fast_log2(nsets);
    cache-> bits_tag = 32 - cache->bits_offset - cache->bits_indice;
    cache-> missesCompulsorios = 0;
    cache-> missesConflito = 0;
    cache-> missesCapacidade = 0;

    cache->memoria->tag = (uint32_t*) calloc(cache->nsets * cache->assoc, sizeof(uint32_t));
    MALLOC_NULL_CHECK(cache->memoria->tag, "ERRO: Não foi possível alocar memória para a cache.");
    cache->memoria->valor = (uint8_t*) calloc(cache->nsets * cache->assoc, sizeof(uint8_t));
    MALLOC_NULL_CHECK(cache->memoria->valor, "ERRO: Não foi possível alocar memória para a cache.");

    if (nsets == 1) {
        cache->memoria->contexto = NULL;
    } else {
        cache->memoria->contexto = (Contexto_substituicao*) malloc(sizeof(Contexto_substituicao));
        MALLOC_NULL_CHECK(cache->memoria->contexto, "ERRO: Não foi possível alocar memória para o contexto de substituição da cache.");

        switch (substituicao) {
            case LRU:
                cache->memoria->contexto->FuncaoSubstituicao = &SubstituiLRU; 
                break;

            case FIFO:
                cache->memoria->contexto->FuncaoSubstituicao = &SubstituiFIFO;
                break;
        
            case RANDOM:
                cache->memoria->contexto->FuncaoSubstituicao = &SubstituiRANDOM;
                break;
        }
    }

    return cache;
}

Resultado_acesso SubstituiFIFO (Endereco endereco, Contexto_substituicao* contexto);
Resultado_acesso SubstituiLRU (Endereco endereco, Contexto_substituicao* contexto);
Resultado_acesso SubstituiRANDOM (Endereco endereco, Contexto_substituicao* contexto);

