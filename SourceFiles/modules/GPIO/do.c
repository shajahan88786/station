#include "Header.h"


//void SetDO(/* Desired output macro*/, /*Buf*/)
void SetDO(short int iDoNum)
{
	switch (iDoNum)
	{
	case NORMAL_BRAKE:
	case EMERGENCY_BRAKE:
	case FIRST_SERVICE_BRAKE:
		Lpso_OutputControlling(Y0_BUF,stIdrvTcas.uc_CurOutputs[Y0_BUF]);
		break;

	case HOOTER:
		Lpso_OutputControlling(Y1_BUF,stIdrvTcas.uc_CurOutputs[Y1_BUF]);
		break;

	default:
		break;
	
	}


}


void Lpso_OutputControlling( unsigned char uc_YBufferSel,unsigned char uc_Byte)
{
    //#if 0
	/* Setting the direction of P3.0 to P3.7 as output */
	FIO3DIR = 0x060000FF;
	
	FIO3CLR |= 0x02000000;	   // Output Enable Bit Disble before selection 
	//FIO3CLR = 0x00;
	/* Setting P0.23 and P0.31 as L and L for setting outputs */
	IOCLR0 |= FIB_CHK;
	
	/* Selecting the buffer */	
	IOCLR0 |= (BUFFER_SELECTION - uc_YBufferSel) << TWENTY_FOUR;
	IOSET0 |= (uc_YBufferSel << TWENTY_FOUR); 

	FIO3SET |= 0x04000000;

	FIO3CLR = ((~(uc_Byte))& 0xFF);    /* SET specific BitNumber */
	FIO3SET |= uc_Byte;               /* CLEAR specific BitNumber */

	/* Set P3.25 and P3.26 as high for output */
	//FIO3SET |= BUFFER_DIRECTION;
	FIO3SET |= 0x02000000;	
	//FIO3SET |= 0x40000; /* output Enable two */

	/* After buffer selection s/w delay as 1ms */

	SpoiPause(TWO_MS);

    FIO3CLR |= 0x02000000;	   // Output Enable Bit Disble before selection 

}



void DriveOutputs(void)
{
	static uint32_t ui_GpioTime = ZERO;
	//static uint32_t ui_GpioSetTime = ZERO;
	static short int i=0;
	short int j=0;

	if (0 == ui_GpioTime)	
			ui_GpioTime = SpoiGetSysTICs();

	/*if (0 == ui_GpioSetTime)	
			ui_GpioSetTime = SpoiGetSysTICs();*/
		
	if (SpoiElapsTICs(ui_GpioTime) > 1000)
	{
		ui_GpioTime = 0;

		//ui_GpioSetTime = 0;

		for (; i<=7; i++)
		{
			stIdrvTcas.uc_CurOutputs[i] = 0xFF;  
			for (j=0; j<=7; j++)
			{
				//if (SpoiElapsTICs(ui_GpioSetTime) > 1000)
				{
					stIdrvTcas.uc_CurOutputs[i] &= ~((0x01)<<j);
					printf("stIdrvTcas.uc_CurOutputs[%d] = %x\n",i,stIdrvTcas.uc_CurOutputs[i]);
					Lpso_OutputControlling(i,stIdrvTcas.uc_CurOutputs[i]);

					//ui_GpioSetTime = 0;
				}		
			}

			if (i == 7)
			{
				i=0;
			}

			break;
		}

	}


}


/* End of File */
