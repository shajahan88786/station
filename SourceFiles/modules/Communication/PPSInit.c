#include "Header.h"

extern unsigned char sucPPSDebugFlag ;
extern unsigned char  processTransmitFlag;
//extern unsigned char processSlotTransmitFlag;
#if 0
void EINT3_Handler (void) __irq 
{
	
	sucPPSDebugFlag = 1;

	EXTINT |= EINT3;		/* clear interrupt */

	//loadTimer(stnTimeSlot[stSelfInfo.ucSelfTimeSlot - 1]);		/* mSec for testing*/

	VICVectAddr = 0x00000000;		/* Acknowledge Interrupt */
}

void EINTInit( void )
{	
	PINSEL4 |= 0x04000000;	
	FIO2DIR = 0x00000000;	

	EXTMODE = EINT3_EDGE;	
	EXTPOLAR = EINT3_RISING;	
	
	EXTINT &= ~EINT3;		/* clear interrupt */
	
	VICVectCntl17 = 0x00000005; 


	VICVectAddr17 = (unsigned long)EINT3_Handler; 
	
	VICIntEnable = (1 << 17); 
	
}

void EINT3_Handler (void) __irq 
{
	unsigned char ucTSlot = 0;
	
	EXTINT |= EINT3;		/* clear interrupt */
	if(stSelfInfo.ucSelfTimeSlot > 0)
		ucTSlot = stSelfInfo.ucSelfTimeSlot-1;
	sucPPSDebugFlag = 1;
	
	loadTimer(stnTimeSlot[ucTSlot] - 1500);		/* 15 ms Modem Delay*/
	PPS_Clock = SpoiGetSysTICs();
	

	VICVectAddr = 0x00000000;		/* Acknowledge Interrupt */
}
#endif

void EINTInit( void )
{	

	#if 0
	PINSEL4 |= 0x04000000;	
	FIO2DIR = 0x00000000;	

	EXTMODE |= EINT3_EDGE;	
	EXTPOLAR |= EINT3_RISING;	
	
	//EXTINT &= ~EINT3;		/* clear interrupt */

	VICIntEnClr = (0x01 << 17);	/* Disable Interrupt */	

	VICVectAddr17 = (unsigned long)EINT3_Handler; 

	VICVectCntl17 = 0x00000005; 
	
	VICIntEnable = (0x01 << 17); 	
   #endif

	/*External Interrupt 1 - EINT1*/

	PINSEL4		|=	EINT1_PINSEL;
	EXTMODE		|=	EINT1_EDGE;	
	EXTPOLAR	|=	EINT1_RISING;

	VICIntEnClr			|=	VIC_EINT1_BIT15_DISABLE;	
	VICVectAddr15		 =	(unsigned long)EINT1_Handler; 
	VICVectPriority15	 =	VIC_INTERRUPT_PRIORITY_FIVE; 	
	VICIntEnable		|=	VIC_EINT1_BIT15_ENABLE;


	/*External Interrupt 2 - EINT2*/

	PINSEL4		|=	EINT2_PINSEL;	
	EXTMODE		|=	EINT2_EDGE;	
	EXTPOLAR	|=	EINT2_RISING;

	VICIntEnClr			|=	VIC_EINT2_BIT16_DISABLE;	
	VICVectAddr16		 =	(unsigned long)EINT2_Handler; 
	VICVectPriority16	 =	VIC_INTERRUPT_PRIORITY_FIVE; 	
	VICIntEnable		|=	VIC_EINT2_BIT16_ENABLE;

	/*Setting all PORT2 32 pins Direction as Input*/
	
}

void EINT1_Handler (void) __irq 
{
	//static unsigned int PPS_check=0;
	//static unsigned long diff=0;
	T1TCR = 2;
	T2TCR = 2;
	T3TCR = 2;
	if ((SpoiElapsTICs(PPS_Clock) < (1500)))
	{
		printf("\n**eLapsed Tics:%d",SpoiElapsTICs(PPS_Clock));
		;
		/*Do Not Consider This PPS Int*/
	}
	else
	{

		if((stSelfInfo.ucSelfTimeSlot > 0)&&(locoPresentFlag > 0))
		{
		//printf("\n stSelfInfo.ucFreqPair PPS 1 is %d",stSelfInfo.ucFreqPair);
		
			 	T2TCR = 1;
			 	T3TCR = 1;
				loadTimer2MR0(stnTimeSlot[0]); 
				loadTimer2MR1(stnTimeSlot[26]);	
				loadTimer2MR2(stnTimeSlot[39]);
				loadTimer2MR3(stnTimeSlot[66]);
		
		}
		else
		{
				T2TCR = 0;
				T3TCR = 0;
		}	
	 sucPPSDebugFlag=1;
	 if((stSelfInfo.ucSelfTimeSlot > 0)&&(3 == gucSelfSlot))
	 {
	 //T1TCR = 2;
	 T1TCR = 1;
	 loadTimer1MR0(TWO_SEC_NS);
	 }
//	  if((SpoiElapsTICs(gCommHealthClock) >= (20*ONE_SEC))&&((4 == gucSelfSlot)))
//	  {
//	  		printf("\n MIE 3 is not working");
//	 		gucSlot3Fail++;
//	 }

	}	
		PPS_Clock = SpoiGetSysTICs();
		PPS_ONE_OK_Clock = SpoiGetSysTICs();
		EXTINT |= EINT1;					/* clear interrupt */
		VICVectAddr = 0x00000000;		/* Acknowledge Interrupt */
}


void EINT2_Handler (void) __irq 
{
	//static unsigned int PPS_check=0;

	if (SpoiElapsTICs(PPS_ONE_OK_Clock) < 3000)
	{
		//printf("\n PPS ONE OK Ignoring PPS TWO");
	}
	else if (SpoiElapsTICs(PPS_Clock) < (1500))
	{
		//printf("\n****eLapsed Tics:%d PPS2",SpoiElapsTICs(PPS_Clock));
		;
		/*Do Not Consider This PPS Int*/
	}
	else
	{			
			   
   //printf("\n PPS 1 not working PPS 2 INTERRUPT RECIEVED\n");
	 //if(T2TCR == 0)
   		T1TCR = 2; 
		T2TCR = 2;
		T3TCR = 2;

		if((stSelfInfo.ucSelfTimeSlot > 0)&&(locoPresentFlag > 0))
		{
		//printf("\n stSelfInfo.ucFreqPair PPS 1 is %d",stSelfInfo.ucFreqPair);
		
			 T2TCR = 1;
			 T3TCR = 1;
		loadTimer2MR0(stnTimeSlot[0]); 
		loadTimer2MR1(stnTimeSlot[26]);	
		loadTimer2MR2(stnTimeSlot[39]);
		loadTimer2MR3(stnTimeSlot[66]);
		
		}
		else
		{
			T2TCR = 0x00;
			T3TCR = 0x00;
		}
	 sucPPSDebugFlag = 1;
	 if((stSelfInfo.ucSelfTimeSlot > 0)&&(3 == gucSelfSlot))
	 {
	 	//T1TCR = 2;
	 	T1TCR = 1;
	 	loadTimer1MR0(TWO_SEC_NS);
	 }
     
//	  if((SpoiElapsTICs(gCommHealthClock) >= (20*ONE_SEC))&&((4 == gucSelfSlot)))
//	  {
//	  		printf("\n MIE 3 is not working");
//	 		gucSlot3Fail++;
//	 }
 
		
		PPS_Clock = SpoiGetSysTICs();
		
	}
	EXTINT |= EINT2;					/* clear interrupt */
	VICVectAddr = 0x00000000;		/* Acknowledge Interrupt */
}

