#include "syslib.h"

int sys_batchenqueue(unsigned flags, endpoint_t proc_ep)
{
        message m;

        return(_kernel_call(SYS_BATCHENQUEUE, &m));
}