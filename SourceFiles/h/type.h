/******************************************************************************
* File Name			: type.h
*
* Abstract		    : This file contains the declarations for the routines of 
*					  type.c                                                  
* Date of creation  :       21/10/2009 
* Date of Modification :               
* Created by        :        dskr
* Modification history :
* +--------------------------------------------------------------------------+
* |   Revision  |      SPR        |  AR    |    DATE	|     Remarks	     |
* |-------------|-----------------|--------|------------|--------------------|
* |    1.0		| Initial Release |        |		    |                    |
* +--------------------------------------------------------------------------+
*
* Compiler/Assembler/Linker: Armcc.exe V3.1.0.919, Armasm.exe V3.1.0.919,
*                               ArmLink.exe V3.1.0.919                   
******************************************************************************/

#ifndef __TYPE_H__
#define __TYPE_H__

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

#define SWAP(x) (x & 0xFF),((x >> 8) & 0xFF)

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef unsigned int   BOOL;

typedef unsigned char  UCHAR;
typedef unsigned short USHORT;
typedef unsigned long  ULONG;
typedef unsigned short UWORD;

#endif  /* __TYPE_H__ */


/*End Of File*/

