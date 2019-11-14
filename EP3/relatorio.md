# MAC0422 - EP03

## Integrantes

* Caio Túlio de Deus Andrade - NUSP 9797232
* Édio Cerati Neto - NUSP 9762678

## Estrutura dos arquivos modificados no MINIX

* `usr`
  * `include`
    * `minix`
      * **callnr.h**
  * `local`
    * `src`
      * **memorymap.c**
    * `Bin`
      * **memorymap**
  * `src`
    * `include`
      * `minix`
        * **callnr.h**
    * `lib`
      * `posix`
        * **_memalloc.c**
    * `servers`
      * `pm`
        * **alloc.c**
        * **glo.h**
        * **misc.c**
      * **proto.h**
        * **table.c**
  
* Esses foram os arquivos com modificações para este exercício programa, a imagem enviada contém mais modificações referentes às fases anteriores

## Modificações

* **callnr.h**: definição da chamada de sistema MEMALLOC
* **memorymap.c**: implementação do utilitário que imprime o mapa da memória conforme a segunda parte do enunciado
* **memorymap**: binário obtido pela compilação do arquivo memorymap.c
* **_memalloc.c**: relativo à implementação da chamada de sistema, que invoca o PM, passando por mensagem parâmetros como o tipo de alocação de memória a ser executado (**0** para first fit e **1** para worst fit) e o id do usuário que invocou tal chamada de sistema
* **alloc.c**: apenas a função `alloc_mem` foi modificada. Agora, ela checa a variável global `worst_fit` para decidir entre executar esta política em caso que valha **1** ou a política de first fit quando `worst_fit` vale **0**
* **glo.h**: declaração da variável global `worst_fit`
* **misc.c**: criação da função `do_memalloc` que implementa a respectiva chamada de sistema para mudança da política de alocação de memória (apenas se o root foi quem chamou)
* **proto.h**: declaração do protótipo de `do_memalloc`
* **table.c**: definição da syscall `do_memalloc` 

## Teste e instruções de usos

* A primeira parte do enunciado *Política de Alocação* foi testada com o arquivo `/usr/src/teste_memalloc.c`, onde modificamos o parâmetro entre as duas políticas que ele deveria implementar e para se certificar disso, incluímos `printf` temporários nos respectivos casos do `if` na função `alloc_mem` em `alloc.c`

  * Por mais que isso poluía a saída do MINIX no terminal com prints constantes, serviu para certificar de que a chamada agia como esperado
  * Para garantir que apenas o root é capaz de chamar essa função, criamos outro usuário no MINIX e ao tentar executar o arquivo acima, respondeu negativamente, como esperado

* A segunda parte do enunciado *Mapa de memória* foi implementada conforme requisitado no utilitário `memorymap`que se encontra em `/usr/local/src`

  * Para compilá-lo, basta o comando:
    * `cc memorymap.c -o memorymap -w -lcurses -D_MINIX -D_POSIX_SOURCE`

  * Executando este utilitário a saída se dá conforme a especificação e comparando com a saída do `top` encontra-se correta, mostrando todos os processos ativos