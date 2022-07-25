#include "Header.h"

void spoiInitializeTcasHardware()
{
	InitHardware();

	//IdrvOutputDefaultInit();

}

void InitHardware()
{
	SpoiGPIOInit(); 	  		/* Initalization of GPIO Pins */

	#ifdef WATCHDOG
		SpoiWDTInit();		    /* Initalization of WDT */
	#endif
	 printf("GPIO initialized\n");
	
	
	EINTInit();
	 printf("Interrupts enabled\n");

	
	CommWatchDogStrobe();			/* Watchdog Strobe Signal */	
	  printf("watch dog init\n");
	SpoiUartInitialize(ISP_PORT,BAUD115200);   	/* Initalize UART0 */
		   printf("uart1 init\n");
	SpoiUartInitialize(GPSPORT,BAUD38400);   	/* Initalize UART1 */
	  printf("uart2 init\n");
	//SpoiUartInitialize(RXPORT,BAUD19200);		/* Initalize UART2 */
	SpoiUartInitialize(RXPORT,BAUD57600);		/* Initalize UART2 */

	printf("initializing timer1\n");
    
	SpoiSysTimeInit();		   	/* Initalization of System Timer */
	  printf("system time initialized\n");
 
 	gucSelfSlot =   getMIESlotNumber();
	if( 0 ==  gucSelfSlot)
	gucSelfSlot = 4;

	 timer1Init();
	 timer2Init();
	 timer3Init();
	  printf("timers initializedd\n");


	//SpoiUartInitialize(TXPORT,BAUD19200);   	/* Initalize UART3 */
	SpoiUartInitialize(TXPORT,BAUD57600);   	/* Initalize UART3 */		
	

	
	//SpoiRTCInit();  			/* Initalization of RTC */
	
	rtc_intl();
	
	can_Init();
	
	

//	printf("333333333333333333\n");
}





