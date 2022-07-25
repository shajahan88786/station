/******************************************************************************
* File Name			: Main.h
*
* Abstract		    : This file contains the declarations for the routines of 
*					  Main.c                                                  
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


#ifndef MAIN_H
#define MAIN_H

//#define ISP_PORT						0		/* UART0 for ISP */
//#define GPSPORT							1		/* UART 1 for GPS */
//#define RXPORT							2		/* UART 2 for RX */
//#define TXPORT							3		/* UART 3 for TX */

#define ISP_PORT						0		/* UART0 for ISP */
#define TXPORT 							1		/* UART 1 for TX  */
#define GPSPORT 						2		/* UART 2 for GPS  */
#define RXPORT							3		/* UART 3 for RX*/
#define FLASH_BASE_ADDR  0x00000020
#define CRC_BASE_ADDR    0x0007D000

#define WATCHDOG			/* For Enabling watchdog utility */
//#undef WATCHDOG			/* For Disabling watchdog utility */


#ifdef RT_AGENT
 #include "RT_Agent.h"
 #define init_comm      RTA_Init
 #define getkey         RTA_TermGetChar
#else
 #define init_comm      init_serial
#endif	/* RT_AGENT */

/* Initialize Serial port */
extern void init_serial (void);
/*Get the Character from UART*/
extern int  getkey (void);
/*Send the Character to UART*/
extern int sendchar (int);

void SendingCrcValue(void);
extern unsigned char ucHealthReplayASCII[400];

#endif /* MAIN_H */




/*End Of File*/

