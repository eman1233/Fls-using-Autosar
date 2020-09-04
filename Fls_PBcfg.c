#include "Fls.h"
#include "Fls_Cbk.h"
#include "Fls_MemMap.h"
static Fls_ConfigType Config={
	.FlsJobEndNotification=Fee_JobEndNotification,
	.FlsJobErrorNotification=Fee_JobErrorNotification
};
