#include "cachetypes.h"
##include "cacheutils.c"

uint32_t SubstituiFIFO (uint32_t indice, uint32_t tag, Cache *cache) {
    return CACHE_HIT;
}
uint32_t SubstituiLRU (uint32_t indice, uint32_t tag, Cache *cache) {
    return CACHE_HIT;
}
uint32_t SubstituiRANDOM (uint32_t indice, uint32_t tag, Cache *cache) {
    return ;
}

uint32_t SubstituiDIRETO (uint32_t indice, uint32_t tag, Cache *cache) {
    // escreve sempre na via 0
    return 0U;
}
