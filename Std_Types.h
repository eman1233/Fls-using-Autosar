#ifndef __STD_TYPES_H__
#define __STD_TYPES_H__

#include "Platform_Types.h"
#include "Compiler.h"

#define E_OK      0x01
#define E_NOT_OK  0x00

typedef uint8 Std_ReturnType;

typedef struct{
uint16 vendorID;
uint16 moduleID;
uint8  InstanceID;
uint8  sw_major_version;
uint8  sw_minor_version;
uint8  sw_patch_version;
} Std_VersionInfoType;


#endif
