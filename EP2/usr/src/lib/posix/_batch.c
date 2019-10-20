#include <lib.h>
#include <unistd.h>

PUBLIC int batch(int PID) {
	message m;
	m.m1_i1 = PID;
	
	return (_syscall(MM, BATCH, &m));
}
