/******************************************************************************
* File Name: RealTimeClk.c
*
* File Description: This file contains the routines to initialize, Set and Get
*                   Real Time Clock Data 
*
* Modification History: Ver/Rev      CR        ATR         Remarks
*
* Created by:   dskr             21/10/2009
*
* Modified by:  
*
* Compiler/Assembler/Linker: Armcc.Exe V3.1.0.919, Armasm.Exe V3.1.0.919,
*                               ArmLink.Exe V3.1.0.919
*
* Version/Revision: 0.1
*
******************************************************************************/

#include "header.h" 

unsigned int ui_RTCMilliSeconds = ZERO;
unsigned int ui_RTCPrevSecond = ZERO;

/******************************************************************************
*	File Header          RealTimeClk.c
*	Procedure Name :     SpoiRTCInit  
*	Package Name   :     SPOI   
*	Date of creation :   21/10/2009     
*	Created by     :     dskr     	     
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 21/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function initialize the real time clock
*
*	Allocation	  :	   	NIL    
*
*	DR            :     LxCS-DR-20
*						LxCS-DR-21
*						LxCS-DR-22
*						LxCS-DR-23
*						LxCS-DR-24   
*
*	Interfaces	  :		None	
*	Calls                 
*
*	Called by     :     1. main()   
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                           --                    None                  --
*						
*	Global variables :     Type                   Name		         comments
*
*                           --                    None                  --
*					
*	Output variables :	  
*	Local variables  :     Type                   Name		         comments
*
*                           --                    None                  --
*						
*	Global variables :     Type                   Name		         comments
*
*                           --                    None                  --
*
*	Reference	     :     SRS		SDR		SWRS		DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*	Step1:Enable power to RTC
*	Step2:Select typr of oscillator for RTC.
*	Step3:Enable RTC interrupts 
*	Step4:Disable Alarm
*	Step5:Enable Every Second interrupt.
*	Step6:Disable Sub Second interrupt.
*
******************************************************************************/

void SpoiRTCInit(void)
{ 
    PCONP 	 |= RTC_POW_ENABLE;         /* RTC Power Enabled */
    RTC_CCR   = RTC_OSC_SELECT;		    /* RTC Osci.Clock Enabled */
    //RTC_ILR  |= RTC_INT_ENABLE; 		/* RTC Interrupt Enabled */
    //RTC_AMR  |= ALR_MSK_DISABLE;		/* Alarm Mask Register Disabled */
    //RTC_CIIR  = EVR_SEC_INT_ENABLE;  	/* Every Second Interrupt Enabled */
    //RTC_CISS  = SUB_SEC_INT_ENABLE;		/* Sub Second Interrupt Disabled */

	ReadGPSData(GPSPORT);

	//printf("\nRTC Updated In Intialization");

  return;
}	/* End of SpoiRTCInit */

/******************************************************************************
*	File Header          RealTimeClk.c
*	Procedure Name :     SpoiRTCSetDateTime     
*	Package Name   :     SPOI    
*	Date of creation :   21/10/2009    
*	Created by     :     dskr     	     
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 21/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :    This function set the RTC timer value 
*
*	Allocation	  :	   NIL	    
*
*	DR            :    NIL      
*
*	Interfaces	  :		None	
*	Calls                 
*
*	Called by     :     1. main()   
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                 RTCDateTime_t            st_DateTime     Structure Contains 
*                                                          Data to set RTC date
*						                                   and time
*
*	Global variables :     Type                   Name		         comments
*
*                           --                    None                  --
*					
*	Output variables :	  
*	Local variables  :     Type                   Name		         comments
*
*                           --                    None                  --
*						
*	Global variables :     Type                   Name		         comments
*
*                           --                    None                  --
*
*	Reference	     :     SRS		SDR		SWRS		DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*	Step1:Update the RTC date and time
*
******************************************************************************/

short int  SpoiRTCSetDateTime(RTCDateTime_t st_DateTime) 
{
	/* Storing Date and Time in RTC */
    
//		RTC_SEC = st_DateTime.ui_RTCSec;
//    RTC_MIN = st_DateTime.ui_RTCMin;
//    RTC_HOUR = st_DateTime.ui_RTCHour;
//    RTC_DOM = st_DateTime.ui_RTCMday;
//    RTC_MONTH = st_DateTime.ui_RTCMon;
//    RTC_YEAR = st_DateTime.ui_RTCYear;    
	
	RTC_SEC = st_DateTime.ui_RTCSec;
    RTC_MIN = st_DateTime.ui_RTCMin;
    RTC_HOUR = st_DateTime.ui_RTCHour;
    RTC_DOM = st_DateTime.ui_RTCMday;
    RTC_MONTH = st_DateTime.ui_RTCMon;
    RTC_YEAR = st_DateTime.ui_RTCYear;    

	Write_ex_RTC(st_DateTime);

    return 1;
}	/* End of SpoiRTCSetDateTime */

/******************************************************************************
*	File Header          RealTimeClk.c
*	Procedure Name :     SpoiRTCGetDateTime  
*	Package Name   :     SPOI    
*	Date of creation :   21/10/2009      
*	Created by     :     dskr     	    
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 21/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function Get the RTC date and time value
*
*	Allocation	  :	   	NIL    
*
*	DR            :     NIL    
*
*	Interfaces	  :		 None	
*	Calls                 
*
*	Called by     :      1. main()  
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                           --                    None                  --
*						
*	Global variables :     Type                   Name		         comments
*
*                           --                    None                  --
*					
*	Output variables :	  
*	Local variables  :     Type                   Name		         comments
*
*                 RTCDateTime_t       st_LocalDateTime 	    Structure contains
*						                                    RTC data	
*
*	Global variables :     Type                   Name		         comments
*
*                           --                    None                  --
*
*	Reference	     :     SRS		SDR		SWRS		DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*	Step1:Store RTC date and time in st_LocalDateTime structure
*
******************************************************************************/

RTCDateTime_t SpoiRTCGetDateTime(void) 
{
    RTCDateTime_t st_LocalDateTime;
    
    /* Store RTC date and time in st_LocalDateTime structure */

    st_LocalDateTime.ui_RTCSec = RTC_SEC;
    st_LocalDateTime.ui_RTCMin = RTC_MIN;
    st_LocalDateTime.ui_RTCHour = RTC_HOUR;
    st_LocalDateTime.ui_RTCMday = RTC_DOM;
    st_LocalDateTime.ui_RTCMon = RTC_MONTH;
    st_LocalDateTime.ui_RTCYear = RTC_YEAR;

    return (st_LocalDateTime);    
}	/* End of SpoiRTCGetDateTime */
 
 /*****************************************************************************
*	File Header          RealTimeClk.c
*	Procedure Name :     SpoiRTCGETMilliSeconds    
*	Package Name   :     SPOI    
*	Date of creation :   21/10/2009     
*	Created by     :     dskr     	    
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 21/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function set the RTC timer value
*
*	Allocation	  :	   	NIL    
*
*	DR            :     NIL     
*
*	Interfaces	  :		1. SpoiGetSysTICs()	
*	Calls                 
*
*	Called by     :     1. main()  
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                 RTCDateTime_t           st_DateTime       Structure Contains 
*                                                           Data to set RTC 
*						                                    date and time
*
*	Global variables :     Type                   Name		         comments
*
*                           --                    None                  --
*					
*	Output variables :	  
*	Local variables  :     Type                   Name		         comments
*
*                           --                    None                  --
*						
*	Global variables :     Type                   Name		         comments
*
*                           --                    None                  --
*
*	Reference	     :     SRS		SDR		SWRS		DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*	step1: if the present RTC_SEC and RTCPrevSecond are not equal then
*		   set the RTCPrevSecond with RTC_SEC.
*
******************************************************************************/

void SpoiRTCGETMilliSeconds() 
{
	//static unsigned long ul_SysTics;
	/* Storing Date and Time in RTC */

	if (ui_RTCPrevSecond != RTC_SEC)
	{
		ui_RTCMilliSeconds = SpoiGetSysTICs();
		ui_RTCPrevSecond = RTC_SEC;		
	}	
    	
    return;
}	/* End of SpoiRTCSetDateTime */

/******************************************************************************
*	File Header          RealTimeClk.c
*	Procedure Name :     SpoiCycleTime   
*	Package Name   :     SPOI    
*	Date of creation :   05-04-2011     
*	Created by     :      Sravan    
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 05-04-2011 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function is used to set the CycleTimeFlag.
*
*	Allocation	  :	   	NIL    
*
*	DR            :     NIL     
*
*	Interfaces	  :		 None 	
*	Calls                 
*
*	Called by     :     1. main()   
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                         static unsigned int    ui_CycleTimeFlag      --
*						
*	Global variables :     Type                   Name		         comments
*
*                           --                    None                  --
*					
*	Output variables :	  
*	Local variables  :     Type                   Name		         comments
*
*                           --                    None                  --
*						
*	Global variables :     Type                   Name		         comments
*
*                           --                    None                  --
*
*	Reference	     :     SRS		SDR		SWRS		DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*   step1: initialize the CycleTimeFlag to 0.
*	step2: if CycleTimeFlag is 0, IOSET1 is OR with BIT28 and CycleTimeFlag
*		   is set to 1.
*	step3: if CycleTimeFlag is 1, IOCLR1 is OR with BIT28 and CycleTimeFlag
*		   is set to 0.
*
******************************************************************************/
//Modified on 05-04-2011 -- added function -- Sravan

/*void SpoiCycleTime ()
{
	static unsigned int ui_CycleTimeFlag = 0;

	if(ui_CycleTimeFlag == 0)
	{
		IOSET1 |= BIT28;
		ui_CycleTimeFlag = 1;
		//printf("\nFlag = %d --- pin SET--- %d:%d:%d\n",ui_AvgTimeFlag,RTC_HOUR,RTC_MIN,RTC_SEC);
	}

	else if(ui_CycleTimeFlag == 1)
	{
		IOCLR1 |= BIT28;
		ui_CycleTimeFlag = 0;
		//printf("\nFlag = %d --- pin CLR--- %d:%d:%d\n",ui_AvgTimeFlag,RTC_HOUR,RTC_MIN,RTC_SEC);
	}
}*/

/*End Of File*/


