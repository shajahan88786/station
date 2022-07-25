/******************************************************************************
*
* $RCSfile: $
* $Revision: $
*
* This module provides information about the project configuration
* Copyright 2004, R O SoftWare
* No guarantees, warrantees, or promises, implied or otherwise.
* May be used for hobby or commercial purposes provided copyright
* notice remains intact.
*
*****************************************************************************/
 
 /* modified by Martin Thomas */
 
// 5/2007 mt: adapted to LPC23xx/24xx 
 
#ifndef SYS_CONFIG_H__
#define SYS_CONFIG_H__

#include "LPC23xx.h"
#include "LPC_UTIL_DEFS.h"


#define WDOG()

// PLL setup values are computed within the LPC include file
// It relies upon the following defines
// PLL input is the XTAL at FOSC
// FCCO is FOSC * PLL_MUL * 2 / PLL_DIV
// 
#define FOSC                (12000000)  // Master Oscillator Freq.
#define PLL_MUL             (12)        // PLL Multiplier
#define PLL_DIV             (1)         // PLL Divider
#define CCLK_DIV            (5)         // PLL out -> CPU clock divider
#define CCLK                ( FCCO / CCLK_DIV ) // CPU Clock Freq.

// Pheripheral Bus Speed Divider
#define PBSD                1           // MUST BE 1, 2, or 4
#define PCLK                (CCLK / PBSD) // Pheripheal Bus Clock Freq.

// Do some value range testing
// TODO: check minimum for LPC23xx/24xx
#if ((FOSC < 10000000) || (FOSC > 25000000))
#error Fosc out of range (10MHz-25MHz)
#error correct and recompile
#endif

#if ((CCLK < 10000000) || (CCLK > 72000000))
// TODO: check minimum for LPC23xx/24xx
#error cclk out of range (10MHz-72MHz)
#error correct PLL_MUL and recompile
#endif

// "The resulting frequency must be in the range of 275 MHz to
// 550 MHz." (Manual p. 36)
#if ((FCCO < 275000000) || (FCCO > 550000000))
#error Fcco out of range (275MHz-550MHz)
#error internal algorithm error
#endif

#if ((PBSD != 1) && (PBSD != 2) && (PBSD != 4))
#error Pheripheal Bus Speed Divider (PBSD) illegal value (1, 2, or 4)
#endif

#endif


/*End of file*/

