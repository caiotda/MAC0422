#include <lib.h>
#include <unistd.h>

PUBLIC int memalloc(int type) {
	message m;
	m.m1_i1 = type;
	m.m1_i2 = geteuid();
	
	return (_syscall(MM, MEMALLOC, &m));
}
