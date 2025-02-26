#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include "cache.h"

int main(int argc, char *argv[])
{

    // cerifica se o número de argumentos está correto

    if (argc != 7) {
        fprintf(stderr, "Uso: %s <nsets> <bsize> <assoc> <substituicao> <flag_saida> <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }
    Substituicao substituicao = converteSubstituicao(argv[4][0]);

    // converte os argumentos para os tipos corretos

    size_t nsets = atoi(argv[1]);
    size_t bsize = atoi(argv[2]);
    size_t assoc = atoi(argv[3]);
    Substituicao substituicao = converteSubstituicao(argv[4][0]);
    bool flag_saida = (atoi(argv[5]) != 1);
    char *arquivo_de_entrada = argv[6];

    // abre o arquivo de entrada

    FILE *arquivo = fopen(arquivo_de_entrada, "rb");
    if (arquivo == NULL) {
        perror("ERRO: Não foi possível abrir o arquivo de entrada.");
        return 1;
    }

    // cria a cache

    Cache *cache = ConstroiCache(nsets, bsize, assoc, substituicao);
    
    //conversor de endianess elegante
    
    Endereco bigEndian, littleEndian;
    littleEndian.endereco = (int) 0x1027; //deve ser 0x2710000 em big endian 32b

    bigEndian.endereco = littleEndian.enderecoBytes[0] << 24 |
                         littleEndian.enderecoBytes[1] << 16 |
                         littleEndian.enderecoBytes[2] << 8  |
                         littleEndian.enderecoBytes[3];

    printf("littleEndian: %x\nbigEndian: %x\n",littleEndian.endereco, bigEndian.endereco);


    fclose(arquivo);
    return EXIT_SUCCESS;
}
