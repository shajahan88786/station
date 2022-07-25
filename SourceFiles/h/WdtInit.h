/******************************************************************************
* File Name			: WdtInit.h
*
* Abstract		    : This file contains the declarations for the routines of 
*					  WdtInit.c                                                  
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

#ifndef WDTINIT_H
#define WDTINIT_H

/* Initializing timeout value */
//#define WATCHDOGTIMEOUT 0xFFF
#define WATCHDOGTIMEOUT 0xFFFF
/* Selecting RTC Clock for Watchdog */
#define WDT_CLOCK_SEL	0x02
/* WDEN - 1, WDRESET - 1,after timeout reset */
#define WDT_MODE		0x03
/* Clear Watchdog Software Interrrupt */
#define CLR_WDT_INT		0x01
/* Reloading the Watchdog Value */
#define FEED_SEQ1		0xAA
/* Reloading the Watchdog Value */
#define FEED_SEQ2		0x55


#define WATCHDOG_STROBE_PIN   0x1000000       /* P4.24 for Watchdog Strobe */

#define WDT_CHANGE_OVER       (THIRTY_MS)		/*Change Over Duration*/
//#define WDT_CHANGE_OVER					FIVE_SEC
/* Process Initialization of Watch Dog TImer */
void SpoiWDTInit(void);
/*Reload Watch Dog Timer with Reload Values*/
void SpoiWDTReload(void);
void CommWatchDogStrobe(void);

#endif /* WDTINIT_H */


/*End Of File*/

