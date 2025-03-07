#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#include "cachetypes.h"
#include "cacheutils.c"
#include "substitution.c"
#include "cache.c"

int main(int argc, char *argv[])
{
    if (argc < 6) {
        errno = EINVAL;
        perror("ENTRADA");
        exit(EXIT_FAILURE);
    }

    uint32_t nsets = atoi(argv[1]);
    uint32_t bsize = atoi(argv[2]);
    uint32_t assoc = atoi(argv[3]);
    Substituicao substituicao;

    switch (*argv[4]) {
        case 'L':
            substituicao = LRU;
        break;

        case 'R':
            substituicao = RANDOM;
        break;

        case 'F':
            substituicao = FIFO;
        break;
            
        default:
            errno = EINVAL;
            perror(argv[4]);
            exit(EXIT_FAILURE);
        break;
    }

    Cache *cache = ConstroiCache(nsets, bsize, assoc, substituicao); 
    FILE *arquivo = fopen(argv[6], "rb");

    if (arquivo == NULL) {
        perror("ARQUIVO");
        exit(EXIT_FAILURE);
    }

    // sem planos melhores para a flag de saída, usamos para determinar estocasticidade
    // 0 -> aleatorio internamente, diferente em cada execução (maomenos)
    // 1 -> aleatorio internamente, determinístico
    if (*argv[5] == '0') {
        // tecnica de estocasticidade: "time XOR salt" (tempo do sistema ^ o endereço de uma variável no stack)
        cache->seed = (uint32_t) time(NULL) ^ (uint32_t) (uintptr_t) &nsets;
        //printf("seed: %u\n", cache->seed);
    }

    Endereco endereco;
    uint32_t acessos, misses;

    while( fread( &endereco.endereco, sizeof(uint32_t), 1, arquivo ) ){
        endereco.endereco = ConverteEndianess(endereco);
        uint32_t tag = EnderecoParaTag(endereco, cache->bits_indice, cache->bits_offset);
        uint32_t indice = EnderecoParaIndice(endereco, cache->bits_indice, cache->bits_offset);

        Resultado_acesso acesso = AcessaCache(indice, tag, cache);

        if ( acesso != CACHE_HIT && cache->EscolheVia != NULL ) { /* tratamento de miss */
            uint32_t via = cache->EscolheVia(indice, cache);
            EscreveCache(indice, via, tag, cache);
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
    
    misses = cache->missesCompulsorios + cache->missesCapacidade + cache->missesConflito;
    acessos = cache->hits + misses;

    printf("%u %.4f %.4f, %.2f %.2f %.2f\n", acessos,
           (float) cache->hits / acessos,
           (float) misses / acessos,
           (float) cache->missesCompulsorios / misses,
           (float) cache->missesCapacidade / misses,
           (float) cache->missesConflito / misses );

    return EXIT_SUCCESS;
}
