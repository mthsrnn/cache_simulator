#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cachetypes.h"
#include "cacheutils.c"
#include "substitution.c"
#include "cache.c"

int main(int argc, char *argv[])
{
    Cache *cache = ConstroiCache(256,4,1, RANDOM); 
    FILE *arquivo = fopen("bin_100.bin", "rb");
    Endereco endereco;
    uint32_t acessos = 0;

    while( fread( &endereco.endereco, sizeof(uint32_t), 1, arquivo ) ){
        acessos++;
        endereco.endereco = ConverteEndianess(endereco);
        uint32_t tag = EnderecoParaTag(endereco, cache->bits_indice, cache->bits_offset);
        uint32_t indice = EnderecoParaIndice(endereco, cache->bits_indice, cache->bits_offset);

        Resultado_acesso acesso = AcessaCache(indice, tag, cache);

        if (acesso != CACHE_HIT && cache->EscolheVia != NULL ) { /* tratamento de miss */
            uint32_t via = cache->EscolheVia(indice, tag, cache);
            EscreveCache(indice, tag, via, cache);
        }

        switch (acesso) { /* contabilização de miss */
            case CACHE_HIT:
                cache->hits++;
            break;

            case CACHE_MISS_COMPULSORIO:
                cache->missesCompulsorios++;
                cache->memoria->itensArmazenados++;
            break;

            case CACHE_MISS_CAPACIDADE:
                cache->missesCapacidade++;
            break;

            case CACHE_MISS_CONFLITO:
                cache->missesConflito++;
            break;
        }
    }
    
    uint32_t misses = cache->missesCompulsorios + cache->missesCapacidade + cache->missesConflito;

    printf("%u %.4f %.4f, %.2f %.2f %.2f\n", acessos,
           (float) cache->hits / acessos,
           (float) misses / acessos,
           (float) cache->missesCompulsorios / misses,
           (float) cache->missesCapacidade / misses,
           (float) cache->missesConflito / misses );

    return EXIT_SUCCESS;
}
