#ifndef CACHEUTILS_H
#define CACHEUTILS_H
#include <stdlib.h>
#include "cache.h"

#define MALLOC_NULL_CHECK(ponteiro, mensagem) \
    do { \
        if ((ponteiro) == NULL) { \
            perror((mensagem)); \
            exit(EXIT_FAILURE); \
        } \
    } while(0)

size_t fast_log2 (size_t entrada);
// Calcula log2 de um número o mais rápido que der
// [TODO] implementar essa função utilizando uma lookup table, não tem muitos valores possíveis para esse log2

Endereco converteEndianess(Endereco endereco);
// Recebe um endereço em bigEndian e transforma em littleEndian, e vice-versa.

#endif // !CACHEUTILS_H
