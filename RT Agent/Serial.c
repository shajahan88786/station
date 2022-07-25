/******************************************************************************
* File Name: Serial.c
*
* File Description: This file contains the routines to initialize UART1 for
*                   diaplay the information on hyper terminal
*
* Modification History: Ver/Rev      CR        ATR         Remarks
*
* Created by:   PM             26/10/2009
*
* Modified by:  
*
* Compiler/Assembler/Linker: 
*
* Version/Revision: 
*
******************************************************************************/


#include <LPC23xx.H>                    /* LPC23xx definitions               */


/******************************************************************************
* Function Name : void init_serial (void)
*
* Abstract : This function initialize UART1
*
* Requirement History :		SRS		SDR		SWRS		DR
*														LxCS-DR-9
*
* Created by  : PM     	26/10/2009
*  
* Modification History :
*
* Modified by : 
*
* Description : Initial Version
*
* Calling Functions :   
*
* Called Function :     None
*
*						Name			Type			Description
*
* Input Variables :
*
* Locals :	        None             
*
* Globals :			None
*
* Output Variables :
*
* Locals :	        None        		
*
* Globals :			None
*
* Program Design Language :		"Restricted C"
*
*Step1:Enable Rx0 and TxD0 pin
*Step2:Disable Fractional Baud Generator
*Step3:Enable Divisor Latches Access Bit
*Step4:configure UART0 for 115200 buad rate
*Step5:Disable Divisor Latches Access Bit
*
******************************************************************************/

void init_serial (void) 
{
    
	#if 0
	/* Configure UART1 for 115200 baud. */
 
    PINSEL0 |=  0x40000000;                /* Enable TxD1 pin */
    PINSEL1 |=  0x00000001;                /* Enable RxD1 pin */

    U1FDR   = 0;                /* Disable Fractional Baud Generator */
	U1LCR 	= 0x00000083; 		/* Enable Divisor Latches Access */    
	U1DLL 	= 0x000004E;  	 	/* Setting for 115200 baud rate */
	U1DLM   = 0x00;       
	U1LCR 	= 0x00000003;  		/* Disable Divisor Latches Access */
	#endif 

	

	//#if 0
	/* Configure UART0 for 115200 baud. */
 
    PINSEL0 |=  0x00000050;        /* Enable Rx0 and TxD0 pin */

    U0FDR   = 0;                /* Disable Fractional Baud Generator */
	U0LCR 	= 0x00000083; 		/* Enable Divisor Latches Access */    
	U0DLL 	= 0x000004E;  	 	/* Setting for 115200 baud rate */
	U0DLM   = 0x00;       
	U0LCR 	= 0x00000003;  		/* Disable Divisor Latches Access */
	//#endif
}

/******************************************************************************
* Function Name : int sendchar (int ch)
*
* Abstract : This function send a charecter
*
* Requirement History :		SRS		SDR		SWRS		DR
*
* Created by  : PM     	26/10/2009
*  
* Modification History :
*
* Modified by : 
*
* Description : Initial Version
*
* Calling Functions :   _ttywrch(), _sys_write()
*
* Called Function :     None
*
*						Name			Type			Description
*
* Input Variables :
*
* Locals :	        ch                int             charecter to send
*
* Globals :			None
*
* Output Variables :
*
* Locals :	        None		
*
* Globals :			None
*
* Program Design Language :		"Restricted C"
*
*Step1:If character to send is "\n" and transmitter holding register contains
*		a valid data then append the data with "\r" at the end.
*
******************************************************************************/

int sendchar (int ch) 
{
    #if 0
	
	if (ch == '\n') 
    	{
        	while (!(U1LSR & 0x20));
        	U1THR = '\r';
    	}

    	while (!(U1LSR & 0x20));
   
    	return (U1THR = ch);

	#endif
   

   	
	if (ch == '\n') 
    {
        while (!(U0LSR & 0x20));
        U0THR = '\r';
    }

    while (!(U0LSR & 0x20));
   
    return (U0THR = ch);
   	  
}

/******************************************************************************
* Function Name : int getkey (void)
*
* Abstract : This function get a charecter
*
* Requirement History :		SRS		SDR		SWRS		DR
*
* Created by  : PM     	26/10/2009
*  
* Modification History :
*
* Modified by : 
*
* Description : Initial Version
*
* Calling Functions :   _sys_read()
*
* Called Function :     None
*
*						Name			Type			Description
*
* Input Variables :
*
* Locals :	        None    
*
* Globals :			None
*
* Output Variables :
*
* Locals :	        None       		
*
* Globals :			None
*
* Program Design Language :		"Restricted C"
*
*Step1:Read the bit 0 of LSR register if it set then return content of  
*		RBR register otherwise block.
*
******************************************************************************/

int getkey (void) 
{
    #if 0
	while (!(U1LSR & 0x01));
    	return (U1RBR);
	#endif
	
	while (!(U0LSR & 0x01));
    return (U0RBR);
	 
}



