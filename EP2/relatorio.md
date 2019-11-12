# Relatório EP2 de SO

### Integrantes : 

* Caio Túlio de Deus Andrade ; NUSP : 9797232
* Édio Cerati Neto ; NUSP : 9762678

***

### Sumário dos arquivos modificados

* usr
  * include
    * minix
      * callnr.h :  Define chamadas de sistema BATCH e UNBATCH.
  * src
    * include
      * minix
        * callnr.h : Define chamadas de sistema BATCH e UNBATCH.
        * com.h : define o ID das kernell calls SYS_BATCHENQUEUE e SYS_BATCHDEQUEUE.
        * syslib.h : define o protótipo das kernell calls sys_batchenqueue e sys_batchdequeue.
      * kernel
        * system
          * do_batchdequeue : define a função do_batchdequeue.
          * do_batchenqueue: define a função do_batchenqueue.
          * Makefile: incluimos os novos arquivos para serem compilados.
        * proc.c : modificamos a função sched.
        * proc.h: definimos o número de filas totais(**17**), o ID da IDLE-Q(**16**), da MIN_USER_Q (**14**) e incluimos a BATCH_Q (**15**) entre IDLE_Q e MIN_USER_Q.
        * system.c: mapeia o ID da kernell call para a função correspondente.
        * system.h:  define o prototipo das funções da kernell call.
      * lib
        * posix
          * _batch.c : define handler da syscall BATCH.
          * _unbatch.c: define handler da syscall UNBATCH.
          * Makefile.in: Modificamos o makefile para incluir os arquivos novos.
        * syslib
          * sys_batchdequeue: handler da taskcall SYS_BATCHDEQUEUE.
          * sys_batchenqueue: handler da taskcall SYS_BATCHENQUEUE.
          * Makefile.in: Modificamos o makefile para incluir os arquivos novos.
      * servers
        * pm
          * misc.c :  criamos as funções do_batch e do_unbatch que recebem o PID do processo por mensagem e repassar para o kernel.
          * proto.h: inclui o protótipo das funções criadas em misc.c.
          * table.c: mapeia as funções do_batch e do_unbatch definidas em misc.c para IDs de chamadas de sistema.

***



### Resumo das atividades efetuadas

* Primeiramente implementamos as chamadas de sistema batch e unbatch. Começamos por aí porque queríamos comunicar o espaço de usuário com os servidores primeiro.
* Os handlers _batch e _unbatch recebem o PID do processo que deverá ser colocado na BATCH_Q (Ou retirado da BATCH_Q)via parametro.
* Os handlers então fazem uma chamada de sistema para as funções do_batch e do_unbatch, dentro do servidor gerenciador de processos. Estas, recebem o PID do processo que deverá ser movido via mensagem, desempacotam o PID e obtemos o número do processo na tabela de processos. Evocamos então os handlers sys_batchenqueue e sys_batchdequeue para fazerem a chamada de kernel. Também passamos, via mensagem, o número do processo na tabela de mensagem.
* Os handlers apenas fazem a kernell call, repassando a mensagem.
* Dentro do kernell : 
  * A função do_batchenqueue obtem o ponteiro para o processo identificado por proc_num (obtido via mensagem) e faz um lock dequeue, isto é, remove o processo da fila aonde estava e trava a função dequeue, evitando condições de corrida.
  * Então, modificamos a prioridade maxima desse processo para ser BATCH_Q, evitando que o processo rodando fique com prioridades mais altas (a prioridade dele não sera abaixada pelo sched, por exemplo, porque ele está acima da fila maxima de processos de usuario, então o processo fica estacionário na fila BATCH_Q). Tambem definimos a prioridade do processo como BATCH_Q. Por fim, chamamos a função lock_enqueue, que fuciona de forma similar a lock_dequeue com a diferença que essa chama a função enqueue, posicionando o processo na fila BATCH_Q.
  * A função do_batchdequeue é muito parecida com do_batchenqueue, com a diferença que, nesta função, a prioridade do processo é definida como USER_Q, fazendo que o processo volte a ser escalonado livremente pelo sistema operacional
* Se tudo estiver ok, o processo retorna com sucesso.
* Importante ressaltar que fixamos que o processo colocado ou removido da BATCH deverá ser filho do processo que fez a chamada
  * Fizemos isso comparando o PID do processo rodando do_batch e do_unbatch com o PID do processo pai do PID recebido por parametro.

### Testando

	* Para testar as rotinas de batch e unbatch, criamos um arquivo "Loop" (armazenado em /usr/src) que cria um loop infinito. Fazemos um batch com esse processo, e observamos que ele vai para a fila 15. Posteriormente, rodamos um unbatch no processo e ele volta para a fila 14. 