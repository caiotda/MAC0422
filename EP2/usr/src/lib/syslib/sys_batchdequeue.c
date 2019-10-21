#include "syslib.h"

int sys_batchdequeue(message *msgptr)
{
        return(_taskcall(SYSTASK, SYS_BATCHDEQUEUE, msgptr));
}