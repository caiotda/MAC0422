#include "../system.h"
#include <minix/endpoint.h>

/*===========================================================================*
 *                                do_batchenqueue                            *
 *===========================================================================*/
int do_batchenqueue(message *m_ptr)
{
    register struct proc *rp;
    int proc_num;

    proc_num = m_ptr->m1_i1;

    rp = proc_addr(proc_num);
    lock_dequeue(rp);
    rp->p_max_priority = rp->p_priority = BATCH_Q;
    if (! rp->p_rts_flags) lock_enqueue(rp);

    kprintf("Teste da batchenqueue funcinou");
    return(OK);
}
/*###########################################################################*/
