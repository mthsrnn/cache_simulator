# Simulador de caches

Simulador de memórias cache apresentado à disciplina de Arquitetura e Organização de Computadores 2.

# Instruções de compilação

Deve compilar em qualquer máquina com um compilador C. O progrma não possui dependências além das bibliotecas padrão `ISO C`.

Compiladores testados:
`clang`,
`gcc 13 (Linux)`,
`zig cc`,
`gcc 6 (Windows - MinGW)`.

Em todos os casos, o programa compila com (usando `gcc` como exemplo):

`gcc src/main.c -o cache_simulator`

# Uso

```c
./cache_simulator <nsets> <bsize> <assoc> <substituição> <flag_saida> arquivo_de_entrada
```

Certifique-se que o caminho para o arquivo `arquivo_de_entrada` está correto.

# O bit "`flag_saida`"
Utilizamos como seletor de funcionamento do algoritmo de substituição `RANDOM`:

`0`: As substituições são aleatórias e diferentes para cada execução do programa.
`1`: As substuições são aleatórias, mas sempre as mesmas para uma determinada configuração.
