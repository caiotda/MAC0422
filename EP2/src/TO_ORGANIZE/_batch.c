#include <lib.h>
#include <unistd.h>

PUBLIC int batch(int PID) {
	message m;
	return (_syscall(MM, BATCH, &m));
}
