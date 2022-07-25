/******************************************************************************
* File Name: SystemTimer.c
*
* File Description: This file contains the routines to initialize system Timer 
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

uint32_t ui_CycleTime = 0;

/******************************************************************************
*	File Header          SystemTimer.c
*	Procedure Name :     SpoiSysTimeInit   
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
*	Abstract      :     This function initialize Timer 0 for system timer.
*
*	Allocation	  :	   	NIL    
*
*	DR            :     LxCS-DR-25
*						LxCS-DR-26
*						LxCS-DR-27
*						LxCS-DR-28
*						LxCS-DR-29
*						LxCS-DR-30
*						LxCS-DR-31
*						LxCS-DR-32
*						LxCS-DR-33
*						LxCS-DR-34
*						LxCS-DR-35   
*
*	Interfaces	  :		None	
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
*	Step1:Enable the Power for Timer 0
*	Strp2:Reset timer 0
*	Step3:Set the prescale divider
*	Step4:Disable Capture Contol registers
*	Step5:Disable External Match register
*	Step6:Disable Match Control registers
*	Step7:Enable timer 0
*
******************************************************************************/

void SpoiSysTimeInit(void)
{
	PCONP 	|= TIMER0_PCONP;        /* To enable the Power for Timer 0 */

	T0TCR = TxTCR_Counter_Reset;    /* Reset & disable timercounter 0 */

	T0PR = T0_PCLK_DIV - 1;         /* Set the prescale divider */

	T0CCR = ZERO;                   /* Disable Capture Contol registers */
	T0EMR = ZERO;                   /* Disable External Match register */
	T0MCR = ZERO;                   /* Disable Match Control registers */

	T0TCR = TxTCR_Counter_Enable;   /* Enable timer 0 */


	/******************************************************************************/
	  PCONP 	|= TIMER1_PCONP;   /*To Enable the power for Timer1*/ 

	  T1TCR	=  TxTCR_Counter_Reset;	  /* Reset and disable timer counter1*/
	  T1PR=14400-1;

    T1CCR = ZERO;                   /* Disable Capture Contol registers */
	T1EMR = ZERO;                   /* Disable External Match register */
	T1MCR = ZERO;                   /* Disable Match Control registers */


	  T1TCR = TxTCR_Counter_Enable; 

	 /********************************************************************************/
			  PCONP 	|= TIMER2_PCONP;   /*To Enable the power for Timer1*/ 

	  T2TCR	=  TxTCR_Counter_Reset;	  /* Reset and disable timer counter1*/
	  T2PR=14400-1;

    T2CCR = ZERO;                   /* Disable Capture Contol registers */
	T2EMR = ZERO;                   /* Disable External Match register */
	T2MCR = ZERO;                   /* Disable Match Control registers */


	  T2TCR = TxTCR_Counter_Enable; 

	 /********************************************************************************/
 PCONP 	|= TIMER3_PCONP;   /*To Enable the power for Timer1*/ 

	  T3TCR	=  TxTCR_Counter_Reset;	  /* Reset and disable timer counter1*/
	  T3PR=14400-1;

    T3CCR = ZERO;                   /* Disable Capture Contol registers */
	T3EMR = ZERO;                   /* Disable External Match register */
	T3MCR = ZERO;                   /* Disable Match Control registers */


	  T3TCR = TxTCR_Counter_Enable; 


	 /**************************************************/

}	/* End of SpoiSysTimeInit */







/******************************************************************************
*	File Header           SystemTimer.c
*	Procedure Name :      SpoiGetSysTICs    
*	Package Name   :      SPOI   
*	Date of creation :    21/10/2009    
*	Created by     :       dskr     	   
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 21/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function returns the current syetem time in TICs
*
*	Allocation	  :	   	NIL    
*
*	DR            :     NIL    
*
*	Interfaces	  :		 None 	
*	Calls                 
*
*	Called by     :     1. CommWatchDogStrobe()
*                       2. SpoiElapsTICs()  
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
*                          uint32_t               Now             System TICs
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
*	Step1:Return the System Ticks.
*
******************************************************************************/

uint32_t SpoiGetSysTICs(void)
{
//int i,j;
    uint32_t ui_Now = T0TC;
	//    printf("%ld=T0TC\n",i);
	#if 0	
	j=32;
	   while(j--)
	   printf("%d",(i>>j)&1);
	   printf("\n");
		 #endif
    return ui_Now;
}	/* End of SpoiGetSysTICs */


/******************************************************************************
*	File Header         SystemTimer.c
*	Procedure Name :    SpoiElapsTICs      
*	Package Name   :    SPOI     
*	Date of creation :  21/10/2009      
*	Created by     :    dskr     	      
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 21/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function then returns the difference in TICs  
*                       between the given starting time and the current system
*						time.
*
*	Allocation	  :	   	NIL    
*
*	DR            :     NIL    
*
*	Interfaces	  :		1. SpoiGetSysTICs()	
*	Calls                 
*
*	Called by     :     1. CommWatchDogStrobe()   
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                      uint32_t             startTime      TICs counting start  
*						                                   time
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
*	Step1:Returns the difference between the current system ticks and pre 
*		  calculated system ticks.
*
******************************************************************************/

uint32_t SpoiElapsTICs(uint32_t ui_StartTime)
{
    return SpoiGetSysTICs() - ui_StartTime;
}	/* End of SpoiElapsTICs */

/******************************************************************************
*	File Header         SystemTimer.c
*	Procedure Name :    SpoiPause    
*	Package Name   :    SPOI    
*	Date of creation :  15/12/2009      
*	Created by     :    dskr     	     
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 15/12/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function pause the control for specified time
*
*	Allocation	  :	   	NIL    
*
*	DR            :     NIL    
*
*	Interfaces	  :		1. SpoiGetSysTICs()
*   Calls               2. SpoiElapsTICs()	
*						3. Comm_ReadLPRCmdReply()
*						4. Evlg_NewFileCreation()
*						5. Evlg_NewFileCreate()
*	                 
*	Called by     :     1. Spoi_InitPowerFail()   
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                     uint32_t             ui_Duration          Time to Pause   
*                     uint32_t             ui_StartTime         Store System  
*						                                        Ticks.
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
*	Step1:If elapse time is less than the required time then dont perfrom any 
*         operation.
*
******************************************************************************/

void SpoiPause(uint32_t ui_Duration)
{
  uint32_t ui_StartTime = SpoiGetSysTICs();

  while (SpoiElapsTICs(ui_StartTime) < ui_Duration)
  {
    ;/* Required to relod watchdog if pause time more */
  }
}


/*End Of File*/
