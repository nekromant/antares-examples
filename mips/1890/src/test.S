#include <arch/1890/regdef.h>
#include <arch/1890/bdef.h>

.text
	addu    k0, zero, ra
begin:
	jal start
	nop
        jr  k0
        nop

