#include "../../servers/inc.h" /* import do server : check */
#include <timers.h>
#include <ibm/interrupt.h>
#include <minix/endpoint.h>
#include "../../kernel/const.h" /* imports do kernel : check */
#include "../../kernel/config.h"
#include "../../kernel/debug.h"
#include "../../kernel/type.h"
#include "../../kernel/proc.h"
#include "../../kernel/ipc.h"

int get_free_memory(struct pm_mem_info *pmi)
{
  int h;
  int total_bytes = 0;

  for(h = 0; h < _NR_HOLES; h++) {
    if(pmi->pmi_holes[h].h_base && pmi->pmi_holes[h].h_len) { // se a base for maior que zero, assim como o comprimento do buraco
      int bytes;
      bytes = pmi->pmi_holes[h].h_len << CLICK_SHIFT;
          /* converte clicks pra bytes. Click shift vale 12, então multiplica por 2^12 */
      total_bytes += bytes; 
    }
  }

  return total_bytes;
}

void get_table() {
  register struct proc *rp;
  static struct pm_mem_info pmi;
  static struct proc *oldrp = proc;

  int r, n = 0;
  int free_mem;

  if(getsysinfo(PM_PROC_NR, SI_MEM_ALLOC, &pmi) != OK) {                  
    printf("Falha ao obter a lista de lacunas.\n");              
    return; 
  } 

  /* First obtain a fresh copy of the current process table. */
  if ((r = sys_getproctab(proc)) != OK) {
    report("IS","warning: couldn't get copy of process table", r);
    return;
  }
  printf("\n ---PID--- \t ---inicio--- \t ---fim--- \n");
  for(rp = oldrp; rp < END_PROC_ADDR; rp++) {
    printf("%3d\t%4x\t%4x\n",
    proc_nr(rp),
    rp->p_memmap[T].mem_phys,
    rp->p_memmap[S].mem_phys + rp->p_memmap[S].mem_len
    );
  }

  free_mem = get_free_memory(&pmi);

  printf("Memoria livre : %d kb\n", free_mem/1024);

}
