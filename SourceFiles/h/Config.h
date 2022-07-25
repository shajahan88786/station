/******************************************************************************
* File Name			: Config.h
*
* Abstract		    : This file contains the declarations for the routines of 
*					  Config.c                                                  
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


#include "Macros.h"

#ifndef CONFIG_H
#define CONFIG_H

/*ECM to perform normal Opeartion*/
#define RUN_MODE            1
/*ECM to perform only Conifguration Opeartion*/
#define CONFIG_MODE			2

#define EQUAL               1
#define NOTEQUAL            0

/*Battery Backup Address where the config data is stored*/
#define BATTERY_BACKUP_RAM  0xE0084000

#define ONE					1
#define TWO					2
#define THREE				3
#define FOUR				4
#define FIVE				5
#define EIGHT				8
#define FIFTEEN				15
#define SIXTEEN				16
#define FIFTY				50
#define TWO_HUNDREAD		200
#define TWO_FIFTY_SIX       256

#define ONE_BYTE			8
#define TWO_BYTE			16

#ifdef LPM_CONFIG_CHECK_WITH_SDM
	extern unsigned char uc_ConfigData[LPM_CONFIG_BYTES+1];
#endif /*#ifdef LPM_CONFIG_CHECK_WITH_SDM*/

/*Function to find LxCS operating mode*/
unsigned char Cmgt_OpModeSelect(void);

#ifdef CONFIG_STORE_BATT_BACKUP
/*Function to Write config data to RAM*/
unsigned char Cmgt_WriteConfig(unsigned char *, unsigned int );
/*Function to validate battery backup RAM data*/
unsigned char Cmgt_ReadAndValidateConfig(void);
#endif /*#ifdef CONFIG_STORE_BATT_BACKUP*/

/*Function to assign config data to data sructure */
void Cmgt_AssignConfig(unsigned char * ,unsigned char);
//void Cmgt_SetConfig(unsigned char * puc_Config);
int Cmgt_SetConfig(void);
#ifdef DEFAULT_CONFIGURATION
	void CmgtAssignDefaultConfigData(void);
#endif /*#ifdef DEFAULT_CONFIGURATION*/


#endif /* CONFIG_H */

/*End Of File*/

