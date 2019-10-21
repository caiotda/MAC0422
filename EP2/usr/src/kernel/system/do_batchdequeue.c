#include "../system.h"
#include <minix/endpoint.h>

/*===========================================================================*
 *                                do_batchdequeue                            *
 *===========================================================================*/
int do_batchdequeue(message *m_ptr)
{
    register struct proc *rp;
    int proc_num;

    proc_num = m_ptr->m1_i1;

    rp = proc_addr(proc_num);
    lock_dequeue(rp);
    rp->p_priority = USER_Q;
    lock_enqueue(rp);

    return(OK);
}
/*###########################################################################*/
