#include <stdio.h>
uint32_t ConverteEndianess(Endereco enderecoEntrada) {
    Endereco enderecoConvertido;

    enderecoConvertido.endereco = enderecoEntrada.enderecoBytes[0] << 24 |
                                  enderecoEntrada.enderecoBytes[1] << 16 |
                                  enderecoEntrada.enderecoBytes[2] << 8  |
                                  enderecoEntrada.enderecoBytes[3];

    return enderecoConvertido.endereco;
}

uint32_t FastLog2 (uint32_t entrada) {
    if (entrada < 2)
        return 0;

    return 1 + FastLog2(entrada >> 1);
}

uint32_t FastRandomUint32 (uint32_t * seed, uint32_t limite) {
    // utilizando xorshift
    uint32_t seedLocal = *seed;
    seedLocal = seedLocal ^ seedLocal << 13;
    seedLocal = seedLocal ^ seedLocal >> 17;
    seedLocal = seedLocal ^ seedLocal << 5;
    *seed = seedLocal;
    return (*seed % (limite));
}

uint32_t EnderecoParaTag (Endereco endereco, uint32_t bits_indice, uint32_t bits_offset) {
    return endereco.endereco >> (bits_indice + bits_offset);
}

uint32_t EnderecoParaIndice (Endereco endereco, uint32_t bits_indice, uint32_t bits_offset) {
    return (endereco.endereco >> bits_offset) & ((1U << bits_indice) - 1);
}
