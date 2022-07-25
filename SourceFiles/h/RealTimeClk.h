/******************************************************************************
* File Name			: RealtimeClk.h
*
* Abstract		    : This file contains the declarations for the routines of 
*					  RealtimeClk.c                                                  
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


#ifndef REALTIMECLK_H 
#define REALTIMECLK_H 

#define RTC_POW_ENABLE          0x0200
#define RTC_OSC_SELECT          0x11
#define RTC_INT_ENABLE          0x01
#define ALR_MSK_DISABLE         0xFF
#define EVR_SEC_INT_ENABLE      0x01
#define SUB_SEC_INT_ENABLE		0x87 
#define SUB_SEC_INT_DISABLE     0x00 


/* Structure for RTC Date and Time */
typedef struct 
{
    unsigned int ui_SDMMilliSec; /* SDM Milliseconds received */      
    unsigned int ui_RTCSec;     /* Second value - [0,59] */
    unsigned int ui_RTCMin;     /* Minute value - [0,59] */
    unsigned int ui_RTCHour;    /* Hour value - [0,23] */
    unsigned int ui_RTCMday;    /* Day of the month value - [1,31] */
    unsigned int ui_RTCMon;     /* Month value - [1,12] */
    unsigned int ui_RTCYear;    /* Year value - [0,4095] */
} RTCDateTime_t;

extern unsigned int ui_RTCMilliSeconds;
extern unsigned int ui_RTCPrevSecond;

/* Function used for RTC initialization */
void SpoiRTCInit( void );
/* Function used for setting date and time of RTC */
short int SpoiRTCSetDateTime( RTCDateTime_t );
/* Function used for getting date and time of RTC */
RTCDateTime_t SpoiRTCGetDateTime( void );

void SpoiRTCGETMilliSeconds(void);
void SpoiCycleTime(void);               //Modified on 05/04/11 --added SpoiCycleTime()

#endif /* REALTIMECLK_H */ 

/*End Of File*/
