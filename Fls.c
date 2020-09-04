#include "Fls.h"
#include "Fls_MemMap.h"
#include "SchM_Fls.h"
#include "Det.h"
#include "Fls_Cbk.h"
#define NULL ((void*)0)
extern MemIf_StatusType StatusType;
extern MemIf_JobResultType JobResultType;
extern MemIf_ModeType ModeType;
extern JOB_PENDING_TYPE PENDING_TYPE; 

void Fee_JobErrorNotification(void){
	extern Faild Fa;
  Fa|=(Read_job_failed|Write_job_failed|Erase_job_failed|Compare_job_failed);
	extern Aborted Ab;
	Ab|=(Read_job_aborted|Write_job_aborted|Erase_job_aborted|Compare_job_aborted);

	
	
}
void Fls_Init(const Fls_ConfigType* ConfigPtr){
	StatusType=MEMIF_IDLE;
	JobResultType=MEMIF_JOB_OK;
	ModeType=MEMIF_MODE_FAST;
	PENDING_TYPE=NO_JOB;
	static uint32 num_byte;
	#if (FlsDevErrorDetect==STD_ON)
	  if(NULL==ConfigPtr)
			Det_ReportError(FlashID,instanceID,Fls_Init_API,FLS_E_UNINIT);
		if(StatusType!=MEMIF_IDLE)
			Det_ReportError(FlashID,instanceID,Fls_Init_API,FLS_E_BUSY);
		if((num_byte>ConfigPtr->FlsMaxReadFastMode)||(num_byte>ConfigPtr->FlsMaxWriteFastMode))
				Det_ReportError(FlashID,instanceID,Fls_Init_API,FLS_E_PARAM_CONFIG);
	#endif
}

Std_ReturnType Fls_Erase(Fls_AddressType TargetAddress,Fls_LengthType Length){
	static FlsSector *Sector;
	static Std_ReturnType status;
	static uint32 FlsBaseAddress;
	PENDING_TYPE=ERASE_JOB;
	StatusType=MEMIF_BUSY;
	JobResultType=MEMIF_JOB_PENDING;
	status=E_OK;
	while(Length%Sector->FlsSectorSize){
		Length++;
	}
	#if (FlsDevErrorDetect==STD_ON)
	  if(((FlsBaseAddress+TargetAddress)%Sector->FlsSectorSize!=0)||(TargetAddress>(Sector->FlsSectorSize*Sector->FlsNumberOfSectors)-1)){
			Det_ReportError(FlashID,instanceID,Fls_Erase_API,FLS_E_PARAM_ADDRESS);
			status=E_NOT_OK;
		}
		if((Length>0)||((TargetAddress+Length)>Sector->FlsSectorSize)||(Length>(Sector->FlsSectorSize*Sector->FlsNumberOfSectors) - TargetAddress)){
			Det_ReportError(FlashID,instanceID,Fls_Erase_API,FLS_E_PARAM_LENGTH);
			status=E_NOT_OK;
		}
		if(StatusType==MEMIF_UNINIT){
			Det_ReportError(FlashID,instanceID,Fls_Erase_API, FLS_E_UNINIT);
			status=E_NOT_OK;
		}
		if(StatusType==MEMIF_BUSY){
			Det_ReportError(FlashID,instanceID,Fls_Erase_API, FLS_E_BUSY);
			status=E_NOT_OK;
		}

	#endif
	return status;
}

Std_ReturnType Fls_Write(Fls_AddressType TargetAddress,const uint8* SourceAddressPtr,Fls_LengthType Length){
	static FlsSector *Sector;
	static Std_ReturnType status;
	static uint32 FlsBaseAddress;
	PENDING_TYPE=WRITE_JOB;
	StatusType=MEMIF_BUSY;
	JobResultType=MEMIF_JOB_PENDING;
	//FlsBaseAddress + (TargetAddress*Length)==(uint8*)SourceAddressPtr;
	status=E_OK;
	#if (FlsDevErrorDetect==STD_ON)
	  if(((FlsBaseAddress+TargetAddress)%Sector->FlsSectorSize!=0)||(TargetAddress>(Sector->FlsSectorSize*Sector->FlsNumberOfSectors)-1)){
			Det_ReportError(FlashID,instanceID,Fls_Write_API,FLS_E_PARAM_ADDRESS);
			status=E_NOT_OK;
		}
		if((Length>0)||((TargetAddress+Length)>Sector->FlsSectorSize)||(Length>(Sector->FlsSectorSize*Sector->FlsNumberOfSectors) - TargetAddress)){
			Det_ReportError(FlashID,instanceID,Fls_Write_API,FLS_E_PARAM_LENGTH);
			status=E_NOT_OK;
		}
		if(StatusType==MEMIF_UNINIT){
			Det_ReportError(FlashID,instanceID,Fls_Write_API, FLS_E_UNINIT);
			status=E_NOT_OK;
		}
		if(StatusType==MEMIF_BUSY){
			Det_ReportError(FlashID,instanceID,Fls_Write_API, FLS_E_BUSY);
			status=E_NOT_OK;
		}
	  if(NULL==SourceAddressPtr)
			Det_ReportError(FlashID,instanceID,Fls_Write_API, FLS_E_PARAM_DATA);
	#endif
	return status;
}
#if (FlsCancelApi==STD_ON)
void Fls_Cancel(void){
	StatusType=MEMIF_IDLE;
	static Fls_ConfigType* ConfigPtr;
	if(JobResultType==MEMIF_JOB_PENDING)
		JobResultType=MEMIF_JOB_CANCELED;
	#if (FlsJobErrorNotificationApi==STD_ON)
		ConfigPtr->FlsJobErrorNotification();
	#endif
	#if (FlsDevErrorDetect==STD_ON)
	  if(StatusType==MEMIF_UNINIT)
			Det_ReportError(FlashID,instanceID,Fls_Cancel_API, FLS_E_UNINIT);
	#endif
}
#endif

#if (FlsGetStatusApi==STD_ON)
MemIf_StatusType Fls_GetStatus(void){
	#if (FlsDevErrorDetect==STD_ON)
	  if(StatusType==MEMIF_UNINIT)
			Det_ReportError(FlashID,instanceID,Fls_Cancel_API, FLS_E_UNINIT);
	#endif
	return StatusType;
}
#endif

#if (FlsGetJobResultApi==STD_ON)
MemIf_JobResultType Fls_GetJobResult(void){
	#if (FlsDevErrorDetect==STD_ON)
	  if(StatusType==MEMIF_UNINIT){
			Det_ReportError(FlashID,instanceID,Fls_GetJobResult_API, FLS_E_UNINIT);
			JobResultType= MEMIF_JOB_FAILED;
		}
			
	#endif
	
	return JobResultType;
}
#endif

Std_ReturnType Fls_Read(Fls_AddressType SourceAddress,uint8* TargetAddressPtr,Fls_LengthType Length){
	static FlsSector *Sector;
	static Std_ReturnType status;
	static uint32 FlsBaseAddress;
	PENDING_TYPE=READ_JOB;
	StatusType=MEMIF_BUSY;
	JobResultType=MEMIF_JOB_PENDING;
	status=E_OK;
		#if (FlsDevErrorDetect==STD_ON)
	  if(((FlsBaseAddress+SourceAddress)%Sector->FlsSectorSize!=0)||(SourceAddress>(Sector->FlsSectorSize*Sector->FlsNumberOfSectors)-1)){
			Det_ReportError(FlashID,instanceID,Fls_Read_API,FLS_E_PARAM_ADDRESS);
			status=E_NOT_OK;
		}
		if((Length>0)||((SourceAddress+Length)>Sector->FlsSectorSize)||(Length>(Sector->FlsSectorSize*Sector->FlsNumberOfSectors) - SourceAddress)){
			Det_ReportError(FlashID,instanceID,Fls_Read_API,FLS_E_PARAM_LENGTH);
			status=E_NOT_OK;
		}
		if(StatusType==MEMIF_UNINIT){
			Det_ReportError(FlashID,instanceID,Fls_Read_API, FLS_E_UNINIT);
			status=E_NOT_OK;
		}
		if(StatusType==MEMIF_BUSY){
			Det_ReportError(FlashID,instanceID,Fls_Read_API, FLS_E_BUSY);
			status=E_NOT_OK;
		}
	  if(NULL== TargetAddressPtr)
			Det_ReportError(FlashID,instanceID,Fls_Read_API, FLS_E_PARAM_DATA);
	#endif
	return status;
}
#if (FlsCompareApi==STD_ON)
Std_ReturnType Fls_Compare(Fls_AddressType SourceAddress,const uint8* TargetAddressPtr,Fls_LengthType Length){
	static FlsSector *Sector;
	static Std_ReturnType status;
	static uint32 FlsBaseAddress;
	PENDING_TYPE=READ_JOB;
	StatusType=MEMIF_BUSY;
	JobResultType=MEMIF_JOB_PENDING;
	status=E_OK;
		#if (FlsDevErrorDetect==STD_ON)
	  if(((FlsBaseAddress+SourceAddress)%Sector->FlsSectorSize!=0)||(SourceAddress>(Sector->FlsSectorSize*Sector->FlsNumberOfSectors)-1)){
			Det_ReportError(FlashID,instanceID,Fls_Compare_API,FLS_E_PARAM_ADDRESS);
			status=E_NOT_OK;
		}
		if((Length>0)||((SourceAddress+Length)>Sector->FlsSectorSize)||(Length>(Sector->FlsSectorSize*Sector->FlsNumberOfSectors) - SourceAddress)){
			Det_ReportError(FlashID,instanceID,Fls_Compare_API,FLS_E_PARAM_LENGTH);
			status=E_NOT_OK;
		}
		if(StatusType==MEMIF_UNINIT){
			Det_ReportError(FlashID,instanceID,Fls_Compare_API, FLS_E_UNINIT);
			status=E_NOT_OK;
		}
		if(StatusType==MEMIF_BUSY){
			Det_ReportError(FlashID,instanceID,Fls_Compare_API, FLS_E_BUSY);
			status=E_NOT_OK;
		}
	  if(NULL== TargetAddressPtr)
			Det_ReportError(FlashID,instanceID,Fls_Compare_API, FLS_E_PARAM_DATA);
	#endif
	return status;
}
#endif

#if (FlsSetModeApi==STD_ON)
void Fls_SetMode(MemIf_ModeType Mode){
	#if (FlsDevErrorDetect==STD_ON)
	  if(StatusType==MEMIF_BUSY)
			Det_ReportError(FlashID,instanceID,Fls_SetMode_API, FLS_E_BUSY);
	#endif
}
#endif

void Fls_GetVersionInfo(Std_VersionInfoType* VersioninfoPtr){
	#if (FlsDevErrorDetect==STD_ON)
	  if(NULL==VersioninfoPtr)
			Det_ReportError(FlashID,instanceID,Fls_GetVersionInfo_API,FLS_E_PARAM_POINTER);	
	#endif
	VersioninfoPtr->InstanceID=instanceID;
	VersioninfoPtr->vendorID=FlashID;
}


#if (FlsBlankCheckApi==STD_ON)
Std_ReturnType Fls_BlankCheck(Fls_AddressType TargetAddress,Fls_LengthType Length){
	static Std_ReturnType status;
	static FlsSector *Sector;
	static uint32 FlsBaseAddress;
	JobResultType=MEMIF_JOB_PENDING;
	StatusType=MEMIF_BUSY;
	PENDING_TYPE=VERIFICATION_JOB;
	status=E_OK;
	#if (FlsDevErrorDetect==STD_ON)
	  if(((FlsBaseAddress+TargetAddress)%Sector->FlsSectorSize!=0)||(TargetAddress>(Sector->FlsSectorSize*Sector->FlsNumberOfSectors)-1)){
			Det_ReportError(FlashID,instanceID,Fls_BlankCheck_API,FLS_E_PARAM_ADDRESS);
			status=E_NOT_OK;
		}
		if((Length>0)||((TargetAddress+Length)>Sector->FlsSectorSize)||(Length>(Sector->FlsSectorSize*Sector->FlsNumberOfSectors) - TargetAddress)){
			Det_ReportError(FlashID,instanceID,Fls_BlankCheck_API,FLS_E_PARAM_LENGTH);
			status=E_NOT_OK;
		}
		if(StatusType==MEMIF_UNINIT){
			Det_ReportError(FlashID,instanceID,Fls_BlankCheck_API, FLS_E_UNINIT);
			status=E_NOT_OK;
		}
		if(StatusType==MEMIF_BUSY){
			Det_ReportError(FlashID,instanceID,Fls_BlankCheck_API, FLS_E_BUSY);
			status=E_NOT_OK;
		}

	#endif
	return status;
}
#endif

