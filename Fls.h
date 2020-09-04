#ifndef __FLS_H__
#define __FLS_H__
#include "Spi.h"
#include "Fls_Cfg.h"
#include "Std_Types.h"

//Container for general parameters of the flash driver. These parameters are always pre-compile
typedef struct{
	uint8 FlsAcLoadOnJobStart;
	int FlsBaseAddress;
	uint8 FlsDriverIndex;
	uint16 FlsTotalSize;
	int FlsUseInterrupts;
}FlsGeneral;

//Container for runtime configuration parameters of the flash driver.Implementation Type: Fls_ConfigType.
typedef struct{
	uint32 FlsAcErase;
	uint32 FlsAcWrite;
	float FlsCallCycle;
	MemIf_ModeType ModeType;
	void (*FlsJobEndNotification)(void);
	void (*FlsJobErrorNotification)(void);
	uint32 FlsMaxReadFastMode;
	uint32 FlsMaxReadNormalMode;
	uint32 FlsMaxWriteFastMode;
	uint32 FlsMaxWriteNormalMode;
	uint32 FlsProtection;
}Fls_ConfigType;

typedef uint32 Fls_AddressType;
typedef uint32 Fls_LengthType;
//This container is present for external Flash drivers only. Internal Flash
//drivers do not use the parameter listed in this container, hence its
//multiplicity is 0 for internal drivers
typedef struct{
	SpiSequence FlsSpiReference;
}FlsExternalDriver;

//Configuration description of a flashable sector.
typedef struct{
	uint16 FlsNumberOfSectors;
	Fls_LengthType  FlsPageSize;
	Fls_LengthType  FlsSectorSize;
	Fls_AddressType FlsSectorStartaddress;
}FlsSector;

typedef enum{
	NO_JOB=0,
	READ_JOB,
	WRITE_JOB,
	ERASE_JOB,
	COMPARE_JOB,
	VERIFICATION_JOB,
}JOB_PENDING_TYPE;


void Fls_Init(const Fls_ConfigType* ConfigPtr);
Std_ReturnType Fls_Erase(Fls_AddressType TargetAddress,Fls_LengthType Length);
Std_ReturnType Fls_Write(Fls_AddressType TargetAddress,const uint8* SourceAddressPtr,Fls_LengthType Length);
void Fls_Cancel(void);
MemIf_StatusType Fls_GetStatus(void);
MemIf_JobResultType Fls_GetJobResult(void);
Std_ReturnType Fls_Read(Fls_AddressType SourceAddress,uint8* TargetAddressPtr,Fls_LengthType Length);
Std_ReturnType Fls_Compare(Fls_AddressType SourceAddress,const uint8* TargetAddressPtr,Fls_LengthType Length);
void Fls_SetMode(MemIf_ModeType Mode);
void Fls_GetVersionInfo(Std_VersionInfoType* VersioninfoPtr);
Std_ReturnType Fls_BlankCheck(Fls_AddressType TargetAddress,Fls_LengthType Length);


typedef uint8 API;
#define Fls_Init_API                   ((API)0X00)
#define Fls_Erase_API                  ((API)0X01)
#define Fls_Write_API                  ((API)0X02)
#define Fls_Cancel_API                 ((API)0X03)
#define Fls_GetStatus_API              ((API)0X04)
#define Fls_GetJobResult_API           ((API)0X05)
#define Fls_Read_API                   ((API)0X07)
#define Fls_Compare_API                ((API)0X08)
#define Fls_SetMode_API                ((API)0X09)
#define Fls_GetVersionInfo_API         ((API)0X10)
#define Fls_BlankCheck_API             ((API)0X0A)
#define Fls_MainFunction_API           ((API)0X06)

typedef uint8  Development;
#define FLS_E_PARAM_CONFIG              ((Development)0x01)
#define FLS_E_PARAM_ADDRESS             ((Development)0x02)
#define FLS_E_PARAM_LENGTH              ((Development)0x03)
#define FLS_E_PARAM_DATA                ((Development)0x04)
#define FLS_E_UNINIT                    ((Development)0x05)
#define FLS_E_BUSY                      ((Development)0x06)
#define FLS_E_PARAM_POINTER             ((Development)0x0A)

typedef uint8 RunTime_error;
#define FLS_E_VERIFY_ERASE_FAILED       ((RunTime_error)0X07)
#define FLS_E_VERIFY_WRITE_FAILED       ((RunTime_error)0X08)
#define FLS_E_TIMEOUT                   ((RunTime_error)0X09)

typedef uint8 Transient_Faults;
#define FLS_E_ERASE_FAILED              ((Transient_Faults)0X01)
#define FLS_E_WRITE_FAILED              ((Transient_Faults)0X02)
#define FLS_E_READ_FAILED               ((Transient_Faults)0X03)
#define FLS_E_COMPARE_FAILED            ((Transient_Faults)0X04)
#define FLS_E_UNEXPECTED_FLASH_ID       ((Transient_Faults)0X05)     
#define FlashID                         92
#define instanceID                      (0U) 
	
void irq_Enable(void);
void irq_Disable(void);
#endif
