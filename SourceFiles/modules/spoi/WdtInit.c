/******************************************************************************
* File Name: WdtInit.c
*
* File Description: This file contains the routines to initialize and reload
*                   the watchdog timer 
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

/******************************************************************************
*	File Header          WdtInit.c
*	Procedure Name :     SpoiWDTInit     
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
*	Abstract      :     This function initialize the watchdog timer
*
*	Allocation	  :	   	NIL    
*
*	DR            :     LxCS-DR-15
*						LxCS-DR-16
*						LxCS-DR-17
*						LxCS-DR-18
*						LxCS-DR-19    
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
*	step1 : Select RTC Clock for Watchdog
*	step2 : Set WDT mode
*	step3 : Initialize WDT timeout value
*	step4 : Clear Watchdog Software Interrrupt
*	step5 : Reload the Watchdog Value
*
******************************************************************************/

void SpoiWDTInit()
{
	WDCLKSEL = WDT_CLOCK_SEL;	/* Selecting RTC Clock for Watchdog */
	WDMOD    = WDT_MODE;		/* WDEN - 1, WDRESET - 1,after timeout reset */
	WDTC	 = WATCHDOGTIMEOUT;	/* Initializing timeout value */
	VICSoftIntClr = CLR_WDT_INT;/* Clear Watchdog Software Interrrupt */
	WDFEED   = FEED_SEQ1;		/* Reloading the Watchdog Value */
	WDFEED   = FEED_SEQ2;		/* Reloading the Watchdog Value */
}	/* End of SpoiWDTInit */

/******************************************************************************
*	File Header           WdtInit.c
*	Procedure Name :      SpoiWDTReload   
*	Package Name   :      SPOI   
*	Date of creation :    21/10/2009    
*	Created by     :      dskr     	    
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 21/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function reloads the watchdog timer
*
*	Allocation	  :	   	NIL    
*
*	DR            :     NIL    
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
*	Reference	     :      SRS		SDR		SWRS		DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*	step1 : Clear Watchdog Software Interrrupt
*	step2 : Reload the Watchdog Value
*
******************************************************************************/

void SpoiWDTReload()
{
	 VICSoftIntClr = CLR_WDT_INT;  	/* Clear Watchdog Software Interrrupt */
	 WDFEED   = FEED_SEQ1;			/* Reloading the Watchdog Value */
 	 WDFEED   = FEED_SEQ2;			/* Reloading the Watchdog Value */ 
}	/* End of SpoiWDTReload */


/******************************************************************************
*	File Header          Communication.c
*	Procedure Name :     CommWatchDogStrobe     
*	Package Name   :     Communication Module    
*	Date of creation :   30/10/2009     
*	Created by     :     dskr     	   
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 30/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function sends watchdog strobe signal.
*
*	Allocation	  :	   	 NIL   
*
*	DR            :      LxCS-DR-7   
*
*	Interfaces	  :		SpoiElapsTICs()	
*	Calls               SpoiGetSysTICs()
*                       
*	Called by     :     main()   
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                      static uint32_t       sui_WatchDogSetTime        --
*                      static uint32_t       sui_WatchDogClrTime        -- 
*                    static unsigned char    suc_WatchDogFlag           --
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
*	Reference	     :    SRS		SDR		SWRS		DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*	Step1:Generate watchdog strobe signal set and reset P4.24 at 
*         regular intervals
*
******************************************************************************/

void CommWatchDogStrobe()
{
	static uint32_t sui_WatchDogSetTime = ZERO;    /* To set */
    static uint32_t sui_WatchDogClrTime = ZERO;    /* To clear */
    static unsigned char suc_WatchDogFlag = ZERO;  /* Flag to set or reset */
		
	/* For watchdog strobe signal set and reset at regular intervals */
    IODIR0 |= WATCHDOG_STROBE_PIN;

    if ((SpoiElapsTICs(sui_WatchDogClrTime) > (WDT_CHANGE_OVER))
		&&(suc_WatchDogFlag == CLEAR))
	{
		
        /* Setting P4.24 */

        IOSET0 |= WATCHDOG_STROBE_PIN;		

		sui_WatchDogSetTime = SpoiGetSysTICs();
		suc_WatchDogFlag = SET;

	}
	if ((SpoiElapsTICs(sui_WatchDogSetTime) > (WDT_CHANGE_OVER))
		&&(suc_WatchDogFlag == SET))
	{
		/* Clearing P4.24 */
        
        IOCLR0 |= WATCHDOG_STROBE_PIN;
			
		sui_WatchDogClrTime = SpoiGetSysTICs();
		suc_WatchDogFlag = CLEAR;
	}		
}   /* End of CommWatchDogStrobe() */

/*End Of File*/
