#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    printf("%zu\n", sizeof(_Bool));
    printf("%zu\n", sizeof(unsigned char));
    return EXIT_SUCCESS;
}
