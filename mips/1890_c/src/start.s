#include <arch/1890/regdef.h>
#include <arch/1890/bdef.h>

.text
	addu    t8, zero, ra
begin:
	j main
        jr      t8
        nop

