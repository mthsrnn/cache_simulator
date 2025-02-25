#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "cache.h"

int main(int argc, char *argv[])
{
    
    //conversor de endianess elegante
    
    Endereco bigEndian, littleEndian;
    littleEndian.endereco = (int) 0x1027; //deve ser 0x2710000 em big endian 32b

    bigEndian.endereco = littleEndian.enderecoBytes[0] << 24 |
                         littleEndian.enderecoBytes[1] << 16 |
                         littleEndian.enderecoBytes[2] << 8  |
                         littleEndian.enderecoBytes[3];

    printf("littleEndian: %x\nbigEndian: %x\n",littleEndian.endereco, bigEndian.endereco);
    return EXIT_SUCCESS;
}
