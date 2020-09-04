#ifndef __FLS_CFG_H__
#define __FLS_CFG_H__
#include "Fee_Cbk.h"
#include "Memif_Types.h"
#define STD_ON 0X01
#define STD_OFF 0X00
#define FlsBlankCheckApi             STD_ON
#define FlsCancelApi                 STD_ON
#define FlsCompareApi                STD_ON
#define FlsDevErrorDetect            STD_ON
#define FlsJobErrorNotificationApi   STD_ON
#define FlsGetStatusApi              STD_ON
#define FlsGetJobResultApi           STD_ON
#define FlsSetModeApi                STD_ON
#define FlsTimeoutSupervisionEnabled STD_ON
#define FlsEraseVerificationEnabled  STD_ON

#endif
