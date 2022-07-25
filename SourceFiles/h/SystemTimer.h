/******************************************************************************
* File Name			: SystemTimer.h
*
* Abstract		    : This file contains the declarations for the routines of 
*					  SystemTimer.c                                                  
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


#ifndef SYSTEMTIMER_H
#define SYSTEMTIMER_H

#include <stdint.h>
#include "LPC23xx.h"
#include "sys_config.h"


#define T0_PCLK_DIV     14400 /* To obtain 1000 tics per second */
//#define T0_PCLK_DIV     12000 /* To obtain 1000 tics per second */

#define sysTICSperMIN   (PCLK  / T0_PCLK_DIV)
#define sysTICSperSEC   (sysTICSperMIN / 4)

#define TIMER0_PCONP 	0x00000002	/* For Timer 0 */
#define TIMER1_PCONP    0x00000004/* For Timer 1*/
#define  TIMER2_PCONP   0x00400000  /*For  Timer2*/
#define   TIMER3_PCONP  0x00800000	/*FOr timeer3*/
/* Macros for different time slots */

#define ONE_MS          (uint32_t)((  1e-3 * sysTICSperSEC) + .5)
#define TWO_MS          (uint32_t)((  2e-3 * sysTICSperSEC) + .5)
#define FIVE_MS         (uint32_t)((  5e-3 * sysTICSperSEC) + .5)
#define TEN_MS          (uint32_t)(( 10e-3 * sysTICSperSEC) + .5)
#define TWENTY_MS       (uint32_t)(( 20e-3 * sysTICSperSEC) + .5)
#define THIRTY_MS       (uint32_t)(( 30e-3 * sysTICSperSEC) + .5)
#define FIFTY_MS        (uint32_t)(( 50e-3 * sysTICSperSEC) + .5)
#define HUNDRED_MS      (uint32_t)((100e-3 * sysTICSperSEC) + .5)
#define ONE_FIFTY_MS    (uint32_t)((150e-3 * sysTICSperSEC) + .5)
#define QUARTER_SEC     (uint32_t)((250e-3 * sysTICSperSEC) + .5)
#define HALF_SEC        (uint32_t)((500e-3 * sysTICSperSEC) + .5)
#define ONE_SEC         (uint32_t)(( 1.0   * sysTICSperSEC) + .5)
#define TWO_SEC         (uint32_t)(( 2.0   * sysTICSperSEC) + .5)
#define FIVE_SEC        (uint32_t)(( 5.0   * sysTICSperSEC) + .5)
#define SIX_SEC        (uint32_t)(( 6.0   * sysTICSperSEC) + .5)
#define EIGHT_SEC       (uint32_t)(( 8.0   * sysTICSperSEC) + .5)
#define NINE_SEC        (uint32_t)(( 9.0   * sysTICSperSEC) + .5)
#define TEN_SEC         (uint32_t)((10.0   * sysTICSperSEC) + .5)
#define TWENTY_SEC      (uint32_t)((20.0   * sysTICSperSEC) + .5)
#define ONE_MIN         (uint32_t)((60.0   * sysTICSperSEC) + .5)
#define THREE_MIN       (uint32_t)((180.0  * sysTICSperSEC) + .5)
#define FOUR_MIN        (uint32_t)((240.0  * sysTICSperSEC) + .5)


#define TIMEOUT_FLBLFB   (uint32_t)(15*HUNDRED_MS)
#define TIMEOUT_TCI_OCC  (uint32_t)(2*HUNDRED_MS)
#define TIMEOUT_TCI_CLR  (uint32_t)(2*HUNDRED_MS)

#define TIMEOUT_PB_DELAY (uint32_t)(2*HUNDRED_MS)   

/* Initialize System Timer */
void SpoiSysTimeInit(void);
/* Process System TICS */
uint32_t SpoiGetSysTICs(void);
/* Process Elapsed System TICS */
uint32_t SpoiElapsTICs(uint32_t startTime);
/* Pause the System  */
void SpoiPause(uint32_t ui_Duration);

extern uint32_t ui_CycleTime;

#endif /* SYSTEMTIMER_H */

/*End Of File*/

