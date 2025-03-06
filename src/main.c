#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "cachetypes.h"
#include "cacheutils.c"
#include "cache.c"
#include "substitution.c"

int main(int argc, char *argv[])
{
    Cache *cache = ConstroiCache(256,4,1, RANDOM); 
    FILE *arquivo = fopen("bin_1000.bin", "rb");
    Endereco endereco;

    while( fread( &endereco.endereco, sizeof(uint32_t), 1, arquivo ) ){
        endereco.endereco = ConverteEndianess(endereco);
        uint32_t tag = EndercoParaTag(endereco, cache->bits_indice, cache->bits_offset);
        uint32_t indice = EndercoParaIndice(endereco, cache->bits_indice, cache->bits_offset);

        Resultado_acesso acesso = AcessaCache(indice, tag, cache);

        if (acesso != CACHE_HIT) { /* tratamento de miss */
            cache->TrataMiss(indice, tag, cache);
        }

        switch (acesso) { /* contabilização de miss */
            case CACHE_HIT:
                cache->hits++;
            break;

            case CACHE_MISS_COMPULSORIO:
                cache->missesCompulsorios++;
            break;

            case CACHE_MISS_CAPACIDADE:
                cache->missesCapacidade++;
            break;

            case CACHE_MISS_CONFLITO:
                cache->missesConflito++;
            break;
        }
    }


    return EXIT_SUCCESS;
}
