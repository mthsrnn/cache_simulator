#include "cacheUtils.h"

Endereco converteEndianess(Endereco enderecoEntrada) {
    Endereco enderecoConvertido;

    enderecoConvertido.endereco = enderecoEntrada.enderecoBytes[0] << 24 |
                                  enderecoEntrada.enderecoBytes[1] << 16 |
                                  enderecoEntrada.enderecoBytes[2] << 8  |
                                  enderecoEntrada.enderecoBytes[3];

    return enderecoConvertido;
}
