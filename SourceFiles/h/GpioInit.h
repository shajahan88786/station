/******************************************************************************
* File Name			: GpioInit.h
*
* Abstract		    : This file contains the declarations for the routines of 
*					  GpioInit.c                                                  
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


#ifndef GPIOINIT_H
#define GPIOINIT_H


#define OK              1
#define FAIL            2




typedef struct
{
    unsigned char uc_CurInputs[20];/*Array of Current Input*/ 
    unsigned char uc_CurOutputs[10];/*Array of Current output*/
    
}LOCOTCASIO_t;

extern LOCOTCASIO_t stIdrvTcas;


/*Initialize GPIO*/
void SpoiGPIOInit(void);
unsigned char getMIESlotNumber(void);
void CheckCrcOnStartup(void);


#endif /* GPIOINIT_H */


/*End Of File*/
