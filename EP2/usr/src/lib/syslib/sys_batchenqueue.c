#include "syslib.h"

int sys_batchenqueue(message *msgptr)
{
        return(_taskcall(SYSTASK, SYS_BATCHENQUEUE, msgptr));
}