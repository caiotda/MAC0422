#define _MINIX 1
#define _POSIX_SOURCE 1

#include <stdio.h>
#include <pwd.h>
#include <curses.h>
#include <timers.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <termcap.h>
#include <termios.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/ioc_tty.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>

#include <minix/ipc.h>
#include <minix/config.h>
#include <minix/type.h>
#include <minix/const.h>

#include "/usr/src/servers/is/inc.h"
#include "/usr/src/servers/pm/mproc.h"
#include "/usr/src/kernel/const.h"
#include "/usr/src/kernel/proc.h"


#define  TC_BUFFER  1024        /* Size of termcap(3) buffer    */
#define  TC_STRINGS  200        /* Enough room for cm,cl,so,se  */


int get_free_memory(struct pm_mem_info *pmi)
{
  int h;
  int total_bytes = 0;

  for(h = 0; h < _NR_HOLES; h++) {
    if(pmi->pmi_holes[h].h_base && pmi->pmi_holes[h].h_len) {
      int bytes;
      bytes = pmi->pmi_holes[h].h_len << CLICK_SHIFT;
          /* converte clicks pra bytes. Click shift vale 12, então multiplica por 2^12 */
      total_bytes += bytes; 
    }
  }

  return total_bytes;
}

void get_table() {
  /*register struct proc *rp;*/
  static struct pm_mem_info pmi;
  /* static struct proc *oldrp = proc; */
  struct mproc mp[NR_PROCS];
  struct mproc *mp_current;

  int i;
  int free_mem;

  if(getsysinfo(PM_PROC_NR, SI_MEM_ALLOC, &pmi) != OK) {                  
    printf("Falha ao obter a lista de lacunas.\n");              
    return; 
  } 

/*  if ((r = sys_getproctab(proc)) != OK) {
    report("IS","warning: couldn't get copy of process table", r);
    return;
  }
*/
  if(getsysinfo(PM_PROC_NR, SI_PROC_TAB, mp) != OK) {
    printf("Falha ao obter a lista de processos.\n");
    return;
  }

  printf("\nPID\tStart\tEnd\n");
  /*for(rp = oldrp; rp < END_PROC_ADDR; rp++) {*/
  for(i = 0; i < NR_PROCS; i++) {
    mp_current = &mp[i];
    if(mp_current->mp_pid != 0 || i == 0){
	    
      printf("%4d\t%4x\t%4x\n",
      mp_current->mp_pid,
      mp_current->mp_seg[T].mem_phys,
      mp_current->mp_seg[S].mem_phys + mp_current->mp_seg[S].mem_len);
    }
  }

  free_mem = get_free_memory(&pmi);

  printf("Memoria livre : %d kb\n", free_mem/1024);

}

int main(int argc, char* argv[]) {
  get_table();
  return 0;
}
