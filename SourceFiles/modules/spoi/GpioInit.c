/******************************************************************************
* File Name: GpioInit.c
*
* File Description: This file contains the routines for GPIO initalization. 
*                   
* Modification History: Ver/Rev      CR        ATR         Remarks
*
* Created by:   dskr             20/10/2009
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
unsigned long ul_Calbytcnt =0;
unsigned short int ui_CalCrc =0;


/******************************************************************************
*	File Header           GpioInit.c
*	Procedure Name :      SpoiGPIOInit    
*	Package Name   :      SPOI   
*	Date of creation :    13/11/2009     
*	Created by     :      dskr        
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 13/11/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function is called initially to initialize the    
*                       GPIO pins. from DIP Switches.
*
*	Allocation	  :	   	NIL    
*
*	DR            :     LxCS-DR-1
*						LxCS-DR-2
*						LxCS-DR-3
*						LxCS-DR-4    
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
*	Step1:Set the port functions to default
*	Step2:Enable pull up registers to port pins
*	Step3:Set the directions of port pins.
*
******************************************************************************/

void SpoiGPIOInit()
{
	/* PINSEL Declarations */
	

	PINSEL0 = 0x00000000;
	PINSEL1 = 0x00000000;		 
	PINSEL2 = 0x00000000;		 
	PINSEL3 = 0x00000000;		 
	PINSEL4 = 0x00000000;
	
	/* PINSEL5 (Reserved) is not required to initialize */
	 		 
	PINSEL6 = 0x00000000;	
	PINSEL7 = 0x00000000;		 
	PINSEL8 = 0x00000000;
	PINSEL9 = 0x00000000;
	
	/* PINSEL10 (ETM interface) is not required to initialize */
	
	/* Pull Up Selected for PINMODE */		 		 

	PINMODE0 = 0x00000000;		 
	PINMODE1 = 0x00000000;
	PINMODE2 = 0x00000000;
	PINMODE3 = 0x00000000;		 
	PINMODE4 = 0x00000000;		 

	/* PINMODE5 (Reserved) is not required to initialize */

	PINMODE6 = 0x00000000;		 
	PINMODE7 = 0x00000000;
	PINMODE8 = 0x00000000;
	PINMODE9 = 0x00000000;

	/* For Selecting the Buffer P0.23, P0.24, P0.25, P0.26, P0.27, 
	 * P0.28, P0.31 direction should be as Output and P3.25, P3.26 
	 * direction should be as Output */
//	 IODIR0  |= 0x9F835000;
//	IODIR1 	|= 0xBE000000;	//For P1.0 to P1.31 - DIRECTION Setting)
//	FIO2DIR	|= 0x00000000;	 		//For P2.0 to P2.31 - DIRECTION Setting)	
//	FIO3DIR	|= 0x06000000;	//For P3.0 to P3.31 - DIRECTION Setting)
//	FIO4DIR	 = 0x81000400;	//For P4.0 to P4.31 - DIRECTION Setting)
	
	
	IODIR0  |= 0x9F835000;
	IODIR1 	|= 0xBFC00000;	//For P1.0 to P1.31 - DIRECTION Setting)
	//FIO2DIR	|= 0x00000080;	 		//For P2.0 to P2.31 - DIRECTION Setting)	
	FIO2DIR	|= 0x000000A0;	 		//For P2.0 to P2.31 - DIRECTION Setting)	
	FIO3DIR	|= 0x06000000;	//For P3.0 to P3.31 - DIRECTION Setting)
	FIO4DIR	 = 0x81000400;	//For P4.0 to P4.31 - DIRECTION Setting)
	FIO4DIR	 |= 0x00003880;	//For P4.0 to P4.31 - DIRECTION Setting)

	FIO4CLR |= 0x00000800;

//  FIO4CLR |= 0x00000400;		//RTS LOW
   

} /* End of SpoiGPIOInit */	 

unsigned char getMIESlotNumber()
{
	unsigned char ucSlotNo=0; //,ucSlotNo25=0,ucSlotNo24=0,ucSlotNo23=0;
	unsigned int value = 0;

	value = FIO3PIN;

	/*
	ucSlotNo25 = (FIO3PIN3 & BIT1);
	ucSlotNo24 = (FIO3PIN3 & BIT0);
	ucSlotNo23 = (FIO3PIN2 & BIT7);

	printf("\n%d %d %d",ucSlotNo25,ucSlotNo24,ucSlotNo23); 
	*/

	printf("\nValue 0x%x PIN25:%s   PIN24:%s    PIN23:%s \n",value,(value & BIT25)?"SET":"CLEAR",
		(value & BIT24)?"SET":"CLEAR",
		(value & BIT23)?"SET":"CLEAR");

	
	if(!(FIO3PIN & BIT25) && !(FIO3PIN & BIT24) &&(FIO3PIN & BIT23))
	{
		ucSlotNo = ONE;
		printf("Slot Number %d\n",ucSlotNo);
//		printf("\n################### LOCO LPM 1 START ###################\n");
	}
	else if(!(FIO3PIN & BIT25) && (FIO3PIN & BIT24) &&!(FIO3PIN & BIT23))
	{
		ucSlotNo = TWO;
		printf("\nSlot Number %d",ucSlotNo);
		//printf("\n################### LOCO LPM 2 START ###################\n");
	}
	else if(!(FIO3PIN & BIT25) && (FIO3PIN & BIT24) && (FIO3PIN & BIT23))
	{
		ucSlotNo = THREE;
		printf("\nSlot Number %d",ucSlotNo);
	}
	else if((FIO3PIN & BIT25) && !(FIO3PIN & BIT24) && !(FIO3PIN & BIT23))
	{
		ucSlotNo = FOUR;
		printf("\nSlot Number %d",ucSlotNo);
	}
	else if((FIO3PIN & BIT25) && !(FIO3PIN & BIT24) && (FIO3PIN & BIT23))
	{
		ucSlotNo = FIVE;
		printf("\nSlot Number %d",ucSlotNo);
	}
	else if((FIO3PIN & BIT25) && (FIO3PIN & BIT24) && !(FIO3PIN & BIT23))
	{
		ucSlotNo = SIX;
		printf("\nSlot Number %d",ucSlotNo);
	}
	else
	{
		printf("Slot selection wrong:%ld %ld %ld ", (FIO3PIN & BIT25),(FIO3PIN & BIT24),(FIO3PIN & BIT23));
	}
  return ucSlotNo;	
}

void CheckCrcOnStartup(void)
{
	unsigned short int one =0;
	unsigned long two =0;
	unsigned char uc_tempbuf[15]="\0";
     unsigned long i=0;

    printf("\nExtracted Data from CRC Location");

	for (i=0;i<6;i++)
	{ 
		uc_tempbuf[i] = (*(volatile unsigned char *)(CRC_BASE_ADDR + i));
		//printf("%02X",uc_tempbuf[i]);
	}
   
	two = (unsigned long)(uc_tempbuf[0]);
     ul_Calbytcnt |= (two);

     two = (unsigned long)(uc_tempbuf[1]);
     ul_Calbytcnt |= (two<<8);

     two = (unsigned long)(uc_tempbuf[2]);
     ul_Calbytcnt |= (two<<16);

     two = (unsigned long)(uc_tempbuf[3]);
     ul_Calbytcnt |= (two<<24);

	one = (unsigned short int)uc_tempbuf[4];
	ui_CalCrc |= (one);
	
	one = (unsigned short int)uc_tempbuf[5];
	ui_CalCrc |= (one<<8);

	gui_CalCrc =ui_CalCrc;
	printf("\nTotal No.of Data Bytes are: %ld\n",ul_Calbytcnt);
	
	printf("Stored CRC is : %u\n",ui_CalCrc);
	
	return;
}







/*End Of File*/
