#include <lib.h>
#include <unistd.h>

PUBLIC int unbatch(void) {
	message m;
	return(_syscall(PM, UNBATCH, &m));
}
