#include "Fls.h"
#include "Fls_MemMap.h"
/* Enable all interrupts */
__attribute__((naked)) void irq_Enable(void)
{
	__asm(" CPSIE I");
	__asm(" BX LR") ;
}

/* Disable all interrupts */

__attribute__((naked)) void irq_Disable(void)
{
    __asm(" CPSID I");
    __asm(" BX LR") ;
}