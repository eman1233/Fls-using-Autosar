#ifndef __MEMIF_TYPES_H__
#define __MEMIF_TYPES_H__

/*************************************************************************************************************/
//Services                :SWS_MemIf_00065
//Name                    :MemIf_JobResultType
//Type                    :Enumeration
//Description             :Denotes the result of the last job.
/************************************************************************************************************/

typedef enum{
	MEMIF_JOB_OK=1,                   //The job has been finished successfully.
	MEMIF_JOB_FAILED,                //The job has not been finished successfully.
	MEMIF_JOB_PENDING,              //The job has not yet been finished
	MEMIF_JOB_CANCELED,            //The job has been canceled.
	MEMIF_BLOCK_INCONSISTENT,     // 1. The requested block is inconsistent, it may
                               //contain corrupted data.
                              // 2. Block is NOT found.
	MEMIF_BLOCK_INVALID,       //The requested block has been marked as invalid,
                            //the requested operation can not be performed.
}MemIf_JobResultType;

/*************************************************************************************************************/
//Services                :SWS_MemIf_00066
//Name                    :MemIf_ModeType
//Type                    :Enumeration
//Description             :Denotes the operation mode of the underlying abstraction modules and device drivers.
/************************************************************************************************************/

typedef enum{
	MEMIF_MODE_SLOW=1,               //The underlying memory abstraction modules and drivers are working in slow mode.
	MEMIF_MODE_FAST,                //The underlying memory abstraction modules and drivers are working in fast mode
}MemIf_ModeType;

/*************************************************************************************************************/
//Services                :SWS_MemIf_00064
//Name                    :MemIf_StatusType
//Type                    :Enumeration
//Description             :Denotes the current status of the underlying abstraction module and device drive.
/************************************************************************************************************/

typedef enum{
	MEMIF_UNINIT=0,                 //The underlying abstraction module or device driver has not been initialized (yet).
  MEMIF_IDLE,                    //The underlying abstraction module or device driver is currently idle.
	MEMIF_BUSY,                   //The underlying abstraction module or device driver is currently busy.
	MEMIF_BUSY_INTERNAL,         //The underlying abstraction module is busy with internal
                              //management operations. The underlying device driver can be busy or idle.
}MemIf_StatusType;
#endif
