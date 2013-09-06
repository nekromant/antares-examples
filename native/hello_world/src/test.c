#include <stdio.h>
#include <arch/antares.h> 


char msg[] = 
	"This example demonstrates the ability to compile\n"
	"host software with Antares. You can use 'run' deployment method \n"
	"to actually run it. Do not rely on this much though - it's mostly here\n"
	"for testing on the host PC and not real world (tm) applications.\n"
	"If you are looking for something to build host applications, check out\n"
	"CMAKE, autotools or scons.\n\n\n"
	;

int main() {
	printf("Hello world!\n");
	printf(msg);
	return 0;
}
