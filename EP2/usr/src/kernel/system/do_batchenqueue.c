/*###########################################################################*/
#include "../system.h"
#include <minix/endpoint.h>

/*===========================================================================*
 *                                do_batchenqueue                            *
 *===========================================================================*/
int do_batchenqueue(message *m_ptr)
{   
    struct mproc* rp;

    rp = m_ptr_in.m1_i1;
    lock_dequeue(rp);
    rp->p_max_priority = rp->p_priority = BATCH_Q;
    if (! rp->p_rts_flags) lock_enqueue(rp);

    return(OK);
}
/*###########################################################################*/
