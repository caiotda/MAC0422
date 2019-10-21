# Relatório EP2 de SO

### Integrantes : 

* Caio Túlio de Deus Andrade ; NUSP : 9797232
* Édio Cerati Neto ; NUSP

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

