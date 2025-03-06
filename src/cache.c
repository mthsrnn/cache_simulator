#include "cachetypes.h"

Cache* ConstroiCache (uint32_t nsets, uint32_t bsize, uint32_t assoc, Substituicao substituicao) {
    Cache *cache = malloc(sizeof(Cache));
    MALLOC_NULL_CHECK(cache, "ERRO: Nao foi possivel alocar memória para a cache.");
    
    cache->nsets = nsets; 
    cache->bsize = bsize;
    cache->assoc = assoc;
    cache->bits_offset = FastLog2(bsize); 
    cache->bits_indice = FastLog2(nsets);
    cache->bits_tag = 32 - (cache->bits_offset) - (cache->bits_indice);
    cache->missesCompulsorios = 0;
    cache->missesConflito = 0;
    cache->missesCapacidade = 0;
    cache->hits= 0;

    cache->memoria = malloc(sizeof(Memoria_cache));

    cache->memoria->tag = (uint32_t*) calloc(nsets * assoc, sizeof(uint32_t));
    MALLOC_NULL_CHECK(cache->memoria->tag, "ERRO: Não foi possível alocar memória para a cache.");
    cache->memoria->valor = (uint8_t*) calloc(nsets * assoc, sizeof(uint8_t));
    MALLOC_NULL_CHECK(cache->memoria->valor, "ERRO: Não foi possível alocar memória para a cache.");

    cache->memoria->itensArmazenados = 0;

    if (assoc == 1) {
        cache->contexto = NULL;
        cache->EscolheVia = &SubstituiDIRETO;
    } else {

        switch (substituicao) {
            case FIFO:
                cache->contexto = malloc(nsets * sizeof(Contexto_substituicao));
                MALLOC_NULL_CHECK(cache->contexto, "ERRO: Não foi possível alocar contexto de substituição");
                cache->EscolheVia = &SubstituiFIFO;
                break;
                
            case LRU:
                cache->contexto = malloc(nsets * sizeof(Contexto_substituicao));
                MALLOC_NULL_CHECK(cache->contexto, "ERRO: Não foi possível alocar contexto de substituição");
                cache->EscolheVia = &SubstituiLRU;
                break;

            case RANDOM:
                cache->contexto = NULL;
                cache->EscolheVia = &SubstituiRANDOM;
                break;

            default:
                cache->contexto = NULL;
                cache->EscolheVia = NULL;
                break;
        }

        if (cache->contexto != NULL) {
            for (uint32_t i = 0; i < nsets; i++) {
                cache->contexto[i].pPrimeiro = NULL;
                cache->contexto[i].pUltimo = NULL;

                for (uint32_t j = 0; j < assoc; j++) {
                    Nodo *nodo = (Nodo*) malloc(sizeof(Nodo));
                    MALLOC_NULL_CHECK(nodo, "ERRO: Não foi possível alocar um nodo para o contexto de substituição.");

                    nodo->pAnterior = NULL;
                    nodo->pProx = NULL;

                    if (cache->contexto[i].pPrimeiro == NULL) {
                        cache->contexto[i].pPrimeiro = nodo;
                        cache->contexto[i].pUltimo = nodo;
                    } else {
                        cache->contexto[i].pPrimeiro = nodo;
                        cache->contexto[i].pUltimo->pProx = nodo;
                        cache->contexto[i].pUltimo= nodo;
                    } 
                }

            }
        }

    }
    return cache;
}

Resultado_acesso AcessaCache (uint32_t indice, uint32_t tag, Cache *cache) {
    for (uint32_t i = 0; i < cache->assoc; i++) {
        if ( cache->memoria->valor[indice * cache->assoc + i] && (cache->memoria->tag[indice * cache->assoc + i] == tag) ) {
            return CACHE_HIT;
        }
    }

    for (uint32_t i = 0; i < cache->assoc; i++) {
        if ( !cache->memoria->valor[indice * cache->assoc + i] ) {
            return CACHE_MISS_COMPULSORIO;
        }
    }

    if (cache->memoria->itensArmazenados == (cache->nsets * cache->assoc)) {
        return CACHE_MISS_CAPACIDADE;
}

    cache->missesConflito++;
    return CACHE_MISS_CONFLITO;
}

void EscreveCache (uint32_t indice, uint32_t tag, uint32_t via, Cache *cache) {
    cache->memoria->tag[indice * (cache->assoc) + via] = tag;
    cache->memoria->valor[indice * (cache->assoc) + via] = 1U;
}
