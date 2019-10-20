#include "syslib.h"

int sys_batchenqueue(int proc)
{
        message m;

        return(_taskcall(SYSTASK, SYS_BATCHENQUEUE, &m));
}