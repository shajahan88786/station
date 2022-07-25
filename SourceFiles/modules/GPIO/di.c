#include "Header.h"


void GetDI(void)
{
    /* Temparary Inputs for storing the Buffer Data */
    static unsigned char suc_Inputs1[MAX_INPUT_BUFFER] = {ZERO,};
    static unsigned char suc_Inputs2[MAX_INPUT_BUFFER] = {ZERO,};	
    unsigned short int i = ZERO;   /* Using for Loop */
    unsigned short int j = ZERO;   /* Using for Loop */
    static unsigned short int sus_FirstTimeReadFlag = ZERO;/* Flag for Read */
    static uint32_t ui_WaitingTime = ZERO;
		static uint32_t ui_GpioTime = ZERO;
	
	#ifdef GPIO_DEBUG
		unsigned char cnt =0;
		unsigned char Bytecnt;
		int Bitcnt;
	#endif /* GPIO_DEBUG */
	
	#ifdef WATCHDOG
		//SpoiWDTReload();	 /* Reload WDT at regular intervals */
	#endif
	
	/* To maintain the current inputs */    
    
    /* 	for(i = ZERO; i < MAX_BUFFER; i++)
     * 	{
     *		st_Idrv_LxGate.uc_PrevInputs[i] = st_Idrv_LxGate.uc_CurInputs[i]; 
     *	}
	 */

    /* To select the FIB Cards */    

    for(i = ZERO; i < MAX_FIB; i++)
    {
       /* Setting P3.25 and P3.26 as L and L - enable Data Bus and Decoder */  
        FIO3CLR |= BUFFER_DIRECTION;

		/* Setting the direction of P3.0 to P3.7 as input */
		FIO3DIR = 0x06000000;
		/* Setting P0.23 and P0.31 as L and L for FIB data reading */
        IOCLR0 |= FIB_CHK;
		//FIO3CLR |= 0x40000; /* output Enable two */  				   
	    /* Setting P0.27 and P0.28 as L and L for FIB1
		 *                         as L and H for FIB2
		 *                         as H and L for FIB3
		 */					
		 			  
		/* After buffer selection s/w delay as 2ms */
		SpoiPause(TWO_MS);

		IOSET0 |= 0x1F000000;        
        if (ONE == i)
        {
            IOCLR0 |= (FIB_CARD_SELECTION - (i+ONE)) << TWENTY_SEVEN;
        }
        else if (TWO == i)
        {
            IOCLR0 |= (FIB_CARD_SELECTION - (i-ONE)) << TWENTY_SEVEN;
        }
        else
        {
            IOCLR0 |= (FIB_CARD_SELECTION - i) << TWENTY_SEVEN;
        }
                      		        				
        /* To read the data from the buffers */    
        
        for(j = ZERO  ; j < NO_OF_BUFFERS_OF_EACH_FIB; j++)
        {
            /* Setting P0.24 , P0.25 and P0.26 as L/H for buffer reading */
            IOSET0 |= 0x07000000;
			IOCLR0 |= (BUFFER_SELECTION - j) << TWENTY_FOUR;

            /* Each buffer selection s/w delay as 1ms */
            ui_WaitingTime = SpoiGetSysTICs();
            while (SpoiElapsTICs(ui_WaitingTime) < (ONE_MS));
       
			/* For First Time Reading */
            if (ZERO == sus_FirstTimeReadFlag)
            {		
                suc_Inputs1[(i * NO_OF_BUFFERS_OF_EACH_FIB) + j] = FIO3PIN0;
            }

            suc_Inputs2[i * NO_OF_BUFFERS_OF_EACH_FIB + j] = FIO3PIN0;
		}
        
        IOSET0 |= 0x1F000000;        
    }
		

	/* For First Time Reading */
    if (ZERO == sus_FirstTimeReadFlag)
    {
        sus_FirstTimeReadFlag = ONE;	
    }
    /* Storing the latest inputs in the current inputs */    
    for(i = ZERO; i < MAX_BUFFER; i++)
    {
        if(suc_Inputs1[i] == suc_Inputs2[i])
        {
            stIdrvTcas.uc_CurInputs[i] = suc_Inputs1[i];			
        }
        suc_Inputs1[i] = suc_Inputs2[i]; 		
    }

	/* For Input Data Validation */

	//IdrvInputDataValidation();
    
	/* For printing the current inputs */

	/*for(i = ZERO; i < MAX_BUFFER; i++)
	{
		printf("%x ",stIdrvTcas.uc_CurInputs[i]);
	}
		printf("\n");*/

	/*for(i = ZERO; i < MAX_BUFFER; i++)
      {
		st_Idrv_LxGate.uc_CurInputs[i] = i;
	  }*/
	#ifdef GPIO_DEBUG
		
		if (0 == ui_GpioTime)	
			ui_GpioTime = SpoiGetSysTICs();
		
		if (SpoiElapsTICs(ui_GpioTime) > 1000)
		{
			
			ui_GpioTime = 0;
		for(Bytecnt=0;Bytecnt<12;Bytecnt++)
		{
			CommWatchDogStrobe();
			if(Bytecnt<10)
				printf("B[%d]  = ",Bytecnt);
			else
				printf("B[%d] = ",Bytecnt);

			for(Bitcnt=7;Bitcnt>=0;Bitcnt--)
			{
			  printf(" %d",(stIdrvTcas.uc_CurInputs[Bytecnt] >> Bitcnt) & 1);
			}

			cnt+=1;

			if(cnt == 1)
				printf("\t");

			if(cnt == 2)
			{
				printf("\n");
				cnt =0;
			}
		}
		printf("\n");
	}

	#endif	/* #ifdef GPIO_DEBUG*/ 
}
