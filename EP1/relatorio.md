# MAC0422 - Relatório EP01

### Caio Túlio de Deus Andrade - NUSP 9797232

### Édio Cerati Neto - NUSP 9762678

* Implementamos a nossa Shell inicialmente lendo a entrada de um comando do usuário (lida até o `\n` inserido pela tecla Enter de confirmação) com o uso da função `fgets()`
* Após isso, o input do usuário é parseado com o auxílio da função `strtok()` dentro da função auxiliar `get_input()`
* Um array de strings (`args`) é montado a partir da input parseada, que será passado como parâmetro quando necessário para a função de execução
  * Observação: conforme uma resposta de um dos monitores no Paca, vimos que não seria necessário considerar passagem de parâmetros para os programas em `rode` e `rodeveja`, mas dado que já havíamos implementado e funcionava a contento, mantemos essa funcionalidade
* `protegepracaramba` funciona como esperado, dando proteção `000` ao arquivo passado como parâmetro utilizando as chamadas de sistemas: `chmod()` (altera a proteção do arquivo), `waitpid()` (para fazer com que o processo pai aguarde a finalização da execução do filho em questão) e `fork()` para criar um novo processo filho
* `liberageral` funciona como esperado, dando proteção `777` ao arquivo passado como parâmetro utilizando as chamadas de sistemas: `chmod()` (altera a proteção do arquivo), `waitpid()` (para fazer com que o processo pai aguarde a finalização da execução do filho em questão) e `fork()` para criar um novo processo filho
* O comando `rodeveja` funciona como esperado, usando a chamada de sistema `fork()` para criar um novo processo filho. Depois, o processo pai aguarda o fim da execução do processo filho com a chamada de sistema `waitpid()`, imprimindo em seguida o código de saída do processo filho
  * O processo filho executa a chamada de sistema `execve()` com o path do programa a ser executado, bem como seus argumentos. Se a execução foi bem sucedida, o processo filho se encerra automaticamente pela chamada, caso contrário, executa a chamada de sistema `exit()` com o código retornado pela execução falha em `execve()`
* O comando `rode` funciona como esperado, usando a chamada de sistema `fork()` para criar um novo processo filho. Depois o pai apenas executa um `continue` para prosseguir a execução da shell normalmente, enquanto seu filho faz o trabalho em segundo plano
  * O processo filho tem sua entrada padrão fechada com a chamada de sistema `close()` para garantir que a shell monopolize o teclado e depois executa o programa passado como argumento através da chamada `execve()`
  * Havia um bug em que o processo filho se tornava um processo zumbi, mas este foi corrigido com a implementação atual
* Caso o comando passado não seja um dos quatro esperados, a shell devolve que o comando não foi reconhecido e volte a imprimir o prompt e aguardar pelo próximo comando
* Por fim, a memória alocada é desalocada com `free()`