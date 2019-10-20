/*###########################################################################*/
#include "../system.h"
#include <minix/endpoint.h>

/*===========================================================================*
 *                                do_batchenqueue                            *
 *===========================================================================*/
int do_batchenqueue(message *m_ptr)
{   
    register struct proc *rp;

    lock_dequeue(rp);
    rp->p_max_priority = rp->p_priority = new_q;
    if (! rp->p_rts_flags) lock_enqueue(rp);

    return(OK);
}
/*###########################################################################*/
