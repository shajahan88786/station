#include "Header.h"
 unsigned char sucPPSDebugFlag=0;
unsigned char processTransmitFlag = 0;
unsigned char processslotcontolTransmitFlag  = 0;
unsigned char processSlotTransmitFlag = 0;
unsigned char processEmergencyFlag = 0;

void timer1Init(void)
{

	T1IR=15;
	T1MCR = 0x24B;//3;
  //111-> 0th bit = MR0I an interrupt is generated when T1MR0 matches the value in T1TC
	               //-> 1st bit = MROR Reset on T1MR0 :The TC wiil be reset if MR0 matches it
				  //->2nd bit  =MROS	  TC and PC will be stoppedd and TCR will be set to 0 if MR0 matches the TC
	
	T1PR = T1_PCLK_DIV - 1;         /* Set the prescale divider */
	
	VICIntEnClr = (0x01 << 5);	/* Disable Interrupt */	
	
	VICVectAddr5 = (unsigned long) TIMER1_ISR; /* Set interrupt vector for Timer1 */
	VICVectPriority5 = VIC_INTERRUPT_PRIORITY_TEN;

	//VICVectCntl5 = 10;

	VICIntEnable = (0x01 << 5);	/* Enable Interrupt */
	T1TCR = 2;

	
}	/* End of SpoiSysTimeInit */



void timer2Init(void)
{	
	T2IR =15;							
	T2MCR = 0x249;					//i=T1MCR;  //111-> 0th bit = MR0I an interrupt is generated when T1MR0 matches the value in T1TC
	            		//-> 1st bit = MROR Reset on T1MR0 :The TC wiil be reset if MR0 matches it
				  		//->2nd bit  =MROS	  TC and PC will be stoppedd and TCR will be set to 0 if MR0 matches the TC
	
	T2PR = T1_PCLK_DIV - 1;         /* Set the prescale divider */
	VICIntEnClr = (0x01 << 26);	/* Disable Interrupt */	
		  
	VICVectAddr26 = (unsigned long) TIMER2_ISR; /* Set interrupt vector for Timer1 */
	VICVectPriority26 = VIC_INTERRUPT_PRIORITY_EIGHT;     

	//VICVectCntl5 = 10;

	VICIntEnable = (0x01 << 26);	/* Enable Interrupt */
	
	T2TCR = 2;


}	/* End of SpoiSysTimeInit */


void loadTimer1MR0(unsigned long ticks)
{

	#if 0
	T1TC = 0;
	T1MR0 = ticks;
	#endif

//	T1TC=0;
//	T1TCR = 1;
	T1IR=15;
	T1MR0 = (ticks );
		
}

void loadTimer2MR0(unsigned long ticks) 
{

//	T2TC=0;
//	T2TCR = 1;
	T2IR=15;
	T2MR0 = (ticks );


}
void loadTimer2MR1(unsigned long ticks) 
{

//	T2TC=0;
//	T2TCR = 1;
	T2IR=15;
	T2MR1 = (ticks );

}
void loadTimer2MR2(unsigned long ticks) 
{

//	T2TC=0;
//	T2TCR = 1;
	T2IR=15;
	T2MR2 = (ticks );

}

void loadTimer2MR3(unsigned long ticks) 
{

//	T2TC=0;
//	T2TCR = 1;
	T2IR=15;
	T2MR3 = (ticks );

}

void loadTimer3MR0(unsigned long ticks) 
{

//	T3TC=0;
//	T3TCR = 1;
	T3IR=15;
	T3MR0 = (ticks );
	//printf("**************ticks is %ld",ticks);
}

void loadTimer3MR1(unsigned long ticks) 
{
//
//	T3TC=0;
//	T3TCR = 1;
	T3IR=15;
	T3MR1 = (ticks );

}
void loadTimer3MR2(unsigned long ticks) 
{

//	T3TC=0;
//	T3TCR = 1;
	T3IR=15;
	T3MR2 = (ticks );

}

void loadTimer3MR3(unsigned long ticks) 
{

//	T3TC=0;
//	T3TCR = 1;
	T3IR=15;
	T3MR3 = (ticks );

}



void loadTimer1MR1(unsigned long ticks)
{

	T1IR=15;
//	T1TCR = 1;
	T1MR1 = (ticks - 1);
//	printf("\n**************** Loading T1 MR1\n");
}


void loadTimer1MR2(unsigned long ticks)
{//	int i,j;
	#if 0
	T1TC = 0;
		
	T1MR0 = ticks;
	#endif
	T1IR=15;
	//T1TCR = 1;
	T1MR2 = (ticks - 1); 
//	printf("\n**************** Loading T1 MR2\n");
		
}
void loadTimer1MR3(unsigned long ticks)
{//	int i,j;
	#if 0
	T1TC = 0;
		
	T1MR0 = ticks;
	#endif
	//T1TCR = 1;
	T1MR3 = (ticks - 1);
	T1IR=15;  
//	printf("\n**************** Loading T1 MR3\n");
		
}

void FrquncyShift_FSToF0()
{
// Link 1 frequency set to Tx- 441.8MHZ Rx- 441.8MHZ for Encryption
	  unsigned char i = 0, c = 0;
	//stSelfInfo.ucFreqPair=0;
	stSelfInfo.ucFreqPair = 1;
	switch(stSelfInfo.ucFreqPair)
	{
		
		case 1:
				IOCLR1 = 0x00400000;
				for(i = 0;i<10;i++)
				{
					 c++;
				}
				IOCLR1 = 0x00400000;
		    //printf("\n L1 CLR stSelfInfo.ucFreqPair is %d ",stSelfInfo.ucFreqPair);
				break;
		case 2:
		
				IOCLR1  = 0x01000000;
				for(i = 0;i<10;i++)
				{
					 c++;
				}
				IOCLR1  = 0x01000000;
		    //printf("\n L2 CLR stSelfInfo.ucFreqPair is %d ",stSelfInfo.ucFreqPair);
			     break;
		case 3:
				IOCLR1 = 0x01400000;
				break;
		case 4:
				IOCLR1 = 0x00800000;
				break;
		case 5:
				IOCLR1 = 0x00c00000;
				break;
		case 6:
			    IOCLR1 = 0x01800000;
				break;
		case 7:
			  
			  IOCLR1 = 0x01c00000;
				break;
	case ZERO:				
					 IOCLR1 = 0x00000000;
								break;
		default: 
		     printf("\n default");
	}
}

void FrquncyShift_F0ToFS()
{ 
// defualt frequency set to 466.8 MHZ Rx- 441.8MHZ for Encryption

	//stSelfInfo.ucFreqPair=0;
	//printf("\nstSelfInfo.ucFreqPair is %d",stSelfInfo.ucFreqPair);
	stSelfInfo.ucFreqPair = 1;
	switch(stSelfInfo.ucFreqPair)
	{

		
		case 1:
				IOSET1 = 0x00400000;
	            break;
		case 2:
				
				IOSET1  = 0x01000000;
		    //printf("\n L2 SET stSelfInfo.ucFreqPair is %d ",stSelfInfo.ucFreqPair);
			  break;
		case 3:
			  
				IOSET1 = 0x01400000;
		    //printf("\n L3 SET stSelfInfo.ucFreqPair is %d ",stSelfInfo.ucFreqPair);
				break;
		case 4:		
				IOSET1  = 0x00800000;
				break;
		case 5:
				IOSET1  = 0x00c00000;
				break;
		case 6:
	      		IOSET1 = 0x01800000;
				break;
		case 7:
	      		IOSET1 = 0x01c00000;
				break;
		case ZERO:				
					 IOSET1 = 0x00000000;
						break;
		default: 
    				;
	}
}	


 #if 0
void timer3Init(void)
{
//	unsigned long i=0;			
	//T3MCR = 7;
	PCONP |= (0x01 << 23);
	T3IR =15;							
	//T3MCR = 0x24B;
	 T3MCR = 0x249;
	
	T3PR = T1_PCLK_DIV - 1;         /* Set the prescale divider */ 
	VICIntEnClr |= (0x01 << 27);	/* Disable Interrupt */	
	
	VICVectAddr27 = (unsigned long) TIMER3_ISR; /* Set interrupt vector for Timer1 */
	VICVectPriority27 =VIC_INTERRUPT_PRIORITY_ELEVEN;

	VICIntEnable |= (0x01 << 27);	/* Enable Interrupt */	
	
	
}	/* End of SpoiSysTimeInit */
#endif



void timer3Init(void)
{
	PCONP |= (0x01 << 23);

	T3CTCR = 0x00;


  T3TCR = 2;

	   T3MCR = 0x649;

	T3PR = T1_PCLK_DIV - 1;         /* Set the prescale divider */
	
	VICIntEnClr |= (0x01 << 27);	/* Disable Interrupt */	
	
	VICVectAddr27 = (unsigned long) TIMER3_ISR; /* Set interrupt vector for Timer3 */
	VICVectPriority27 = VIC_INTERRUPT_PRIORITY_TWELVE;

	VICIntEnable |= (0x01 << 27);	/* Enable Interrupt */

    //T2TCR = 1;

}

static void TIMER1_ISR (void) __irq 
{
//	printf("\n&&&&&&&& T1IR = %x\n",T1IR);
	if((T1IR>>ZERO)&1)
	{	   
		//processTransmitFlag=0;
		//if(3 == gucSelfSlot)
		T1TCR = 0;
		T3TCR = 0;
		T1IR|=MR0_INT;

	}	
	 if((T1IR>>ONE)&1)
	{
		//printf("\n****** Raising TxFlag\n");
		TxFlag=1;
		T1IR|=MR1_INT;
	}

   if((T1IR>>TWO)&1)
	{

//		printf("\nTransmitting Station Broadcast Packet\n");
		//printf("\n T1TC = %ld ,actualslot = %d wen RTS HIGH\n",T1TC,stnTimeSlot[stSelfInfo.ucSelfTimeSlot-1]);	
		//printf("\n RTS High  T2TC %ld",T2TC);
		//printf("\n timeflag  %d",timeflag);
		PINSEL1 &=0xFFFFFC3F;	//need to study
		PINSEL4 &=0xFFFF000F;
		FIO2DIR |=0x000000A0;
		FIO2DIR &=0xFFFFFFA3;
		FIO2CLR |= 0x00000080;
		T1IR|=MR2_INT;	
	}
   if((T1IR>>THREE)&1)
	{

		PINSEL1 &=0xFFFFFC3F;	//need to study
		PINSEL4 &=0xFFFF000F;
		FIO2DIR |=0x000000A0;
		FIO2DIR &=0xFFFFFFA3;
//		printf("\n T1TC = %ld ,actualslot = %d wen RTS low\n",T1TC,stnTimeSlot[stSelfInfo.ucSelfTimeSlot-1]);
		FIO2SET |= 0x00000080;		//RTS LOW
		if(3 == gucSelfSlot)
		gucRTSHighRMShiftFlag = 1;
//		if(4 == gucSelfSlot)
//		{
//		    //SpoiPause(ONE_MS);	
//			T1TCR = 0;
//		}
		T1IR|=MR3_INT;
	

	}

		VICVectAddr = 0; 
		return;
	                    /* Acknowledge Interrupt */	
}


static void TIMER2_ISR (void) __irq 
{
	//stSelfInfo.ucFreqPair = 0;
	 
// F0 Frequency has to in channel 1, FS1 to FS8 in other successive channels.

// For encryption channel 1 changed to FS Frqncy and channel 2 is F0 Frqncy
	
	if((T2IR>>ZERO)&1)
	{
		gucTimerFrequencySet = 1;
		T2IR|=MR0_INT;
	}
	if((T2IR>>ONE)&1)
	{
		gucTimerFrequencyClr = 1;
		T2IR|=MR1_INT;
	}
	if((T2IR>>TWO)&1)
	{
		gucTimerFrequencySet = 1;
		T2IR|=MR2_INT;
	}
	if((T2IR>>THREE)&1)
	{
		gucTimerFrequencyClr = 1;
		T2TCR = 0;
		T2TC = 0;
		T2IR|=MR3_INT;	
	}
	
	VICVectAddr = 0; 
	return;

}



static void TIMER3_ISR (void) __irq 
{

   if((T3IR>>ZERO)&1)
   {
		//Tx2Flag=1;
		//printf("\n T3MR0");
		T3IR|=MR0_INT;
   }
	if((T3IR>>ONE)&1)
	{
		Tx1Flag=1;
		T3IR|=MR1_INT;
			 
	}
		 
	if((T3IR>>TWO)&1)
	{
		if(1 == gucSlotPktOnPort)
		{
		 // printf("\n RTS High Access Control T2TC %ld",T2TC);
			//printf("\n timeflag  %d",timeflag);
			IOCLR1 = 0x00000000;
			PINSEL1 &=0xFFFFFC3F;	
			PINSEL4 &=0xFFFF000F;
			FIO2DIR |=0x000000A0;
			FIO2DIR &=0xFFFFFFA3;
			FIO2CLR |= 0x00000080;			//RTS HIGH

			SpoiPause(TWO_MS);

			FIO2SET |= 0x00000080;
		}
			gucSlotPktOnPort=0;				
//			if(4 == gucSelfSlot)
//			{
//			//SpoiPause(ONE_MS);
				T3TCR = 0;
//			}

		T3IR|=MR2_INT;	
	}
	if((T3IR>>THREE)&1)
	{
		 if(1 == gucEmgPktOnPort)
		{
		  printf("\nEmergency packet firing\n");
		  	gucEmgPktOnPort = 0;
			PINSEL1 &=0xFFFFFC3F;	
			PINSEL4 &=0xFFFF000F;
			FIO2DIR |=0x000000A0;
			FIO2DIR &=0xFFFFFFA3;
			FIO2CLR |= 0x00000080;			//RTS HIGH

			SpoiPause(TWO_MS);

			FIO2SET |= 0x00000080;
	}
	  T3TCR = 0;
		T3IR|=MR3_INT;
	}

	VICVectAddr = 0;  /* Acknowledge Interrupt */
	return;
	
}

void configTimers(unsigned char ucSelfTimeSlot)
{
		unsigned char ucTSlot=0;// ucbroadcastSlot=0;
		ucTSlot = stSelfInfo.ucSelfTimeSlot+1;
    //ucTSlot = 19;
		if(stnTimeSlot[ucTSlot] < NEGATIVE_CUTOFF)
		{			

			ucTSlot = 5;
			loadTimer1MR1(stnTimeSlot[ucTSlot]-MODEM_DELAY-4000);
		}
		else
		{
			loadTimer1MR1(stnTimeSlot[ucTSlot]-MODEM_DELAY-4000);
		}

		loadTimer1MR2(stnTimeSlot[ucTSlot]-MODEM_DELAY );
		loadTimer1MR3(stnTimeSlot[ucTSlot] -MODEM_DELAY+ (2000));
				
}

void configSlotControlPkt(void)
{

	static unsigned char irand = 0;
	unsigned long ulTimeHandler = 0;
	

   ulTimeHandler = (gcMidBlockSectionSlots[irand]);
	 irand = irand + 1;
	if(irand >= 3)
	irand = 0;
	ulTimeHandler = ulTimeHandler - 1;
		loadTimer3MR1(stnTimeSlot[ulTimeHandler]-MODEM_DELAY- 2000);
		loadTimer3MR2(stnTimeSlot[ulTimeHandler]-MODEM_DELAY);	


}

void ConfigEmergencyPkt()
{
	int irand = 0;
	unsigned long ulTimeHandler = 0;
	
	irand = rand() % 4;	
    ulTimeHandler = (gcEmergencySlots[irand]-1);

//	printf("\n****** Emergency packet sending Slot %d \n",ulTimeHandler+1);

	if((stnTimeSlot[ulTimeHandler]-MODEM_DELAY- TWENTY_MS) > 0)
	{									
		loadTimer3MR0(stnTimeSlot[ulTimeHandler]-MODEM_DELAY- 2000);
		loadTimer3MR3(stnTimeSlot[ulTimeHandler]-MODEM_DELAY);
   }

}

