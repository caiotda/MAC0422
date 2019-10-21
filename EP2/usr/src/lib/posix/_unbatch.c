#include <lib.h>
#include <unistd.h>

PUBLIC int unbatch(int PID) {
	message m;
	m.m1_i1 = PID;
	return(_syscall(PM, UNBATCH, &m));
}
