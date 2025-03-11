# Simulador de caches

Simulador de memórias cache apresentado à disciplina de Arquitetura e Organização de Computadores 2.

# Instruções de compilação

Deve compilar em qualquer máquina, aliás em qualquer compilador C.

Foi testado com:
`clang`
`gcc 13 (Linux)`
`zig cc`
`gcc 6 (Windows - MinGW)`

Em todos os casos, o programa compila com (usando `gcc` como exemplo):
`gcc src/main.c -o cache_simulator`

# Uso

`./cache_simulator <nsets> <bsize> <assoc> <substituição> <flag_saida> arquivo_de_entrada`

Certifique-se que o caminho para o arquivo `arquivo_de_entrada` está correto.

# O bit "`flag_saida`"

Utilizamos como seletor de funcionamento do algoritmo de substituição `RANDOM`, a fim de possibilitar tipos de testes distintos:

Em `1`, o programa utiliza uma seed inicial fixa: isso significa que as substituições realizadas serão sempre as mesmas (ainda assim, aleatórias) para uma determinada configuração, e os resultados também serão o mesmo. Pode ser interessante para validar o funcionamento do programa em si (por isso tornamos default).
Em `0`, o programa tenta gerar uma nova seed em cada execução do programa, permitindo resultados diferentes para uma mesma configuração. Para situações reais de `benchmark`, essa situação pode ser a mais adequada.
