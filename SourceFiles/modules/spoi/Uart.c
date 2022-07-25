/******************************************************************************
* File Name: Uart.c
*
* File Description: This file contains the routines to send and receive the 
*                   data through serial communication
*
* Modification History: Ver/Rev      CR        ATR         Remarks
*
* Created by:   dskr             23/10/2009
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

Buf_t st_ReadBuf[NOOFUARTS];


/******************************************************************************
*	File Header          Uart.c
*	Procedure Name :     SpoiUartInitialize    
*	Package Name   :     SPOI    
*	Date of creation :   23/10/2009     
*	Created by     :     dskr     	     
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function initiate the initializations for UARTs 
*
*	Allocation	  :	   	NIL    
*
*	DR            :     NIL    
*
*	Interfaces	  :		1. Spoi_InitUartBuffers()
*   Calls               2. Spoi_InitUartZero()
*                       3. Spoi_InitUartOne() 
*				        4. Spoi_InitUartTwo() 
*                       5. Spoi_InitUartThree()	
*	                 
*	Called by     :     1. main()   
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                     unsigned short int     us_UartNum           Uart Number
*                     unsigned long          ul_Baud        Buadrate for Uart  
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
*	Step1:Initialize the UART buffers
*	Step2:Initialize the UART's
*
******************************************************************************/

void SpoiUartInitialize(unsigned short int us_UartNum, unsigned long ul_Baud)
{
    if (UART0 == us_UartNum)
    {
	    Spoi_InitUartBuffers(us_UartNum);
	    Spoi_InitUartZero(us_UartNum,ul_Baud);
    }
    else if (UART1 == us_UartNum)
    {
	    Spoi_InitUartBuffers(us_UartNum);
	    Spoi_InitUartOne(us_UartNum,ul_Baud);
    }
    else if (UART2 == us_UartNum)
    {
	    Spoi_InitUartBuffers(us_UartNum);
	    Spoi_InitUartTwo(us_UartNum,ul_Baud);	
    }
    else if (UART3 == us_UartNum)
    {
	    Spoi_InitUartBuffers(us_UartNum);
		Spoi_InitUartThree(us_UartNum,ul_Baud);	
    }  
    return;
}	/* End of SpoiUartInitialize */

/******************************************************************************
*	File Header          Uart.c
*	Procedure Name :     Spoi_InitUartZero   
*	Package Name   :     SPOI    
*	Date of creation :   23/10/2009     
*	Created by     :     dskr     	     
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function initialize UART0
*
*	Allocation	  :	   	NIL    
*
*	DR            :     LxCS-DR-9
*						LxCS-DR-36
*						LxCS-DR-37
*						LxCS-DR-38
*						LxCS-DR-39
*						LxCS-DR-40
*						LxCS-DR-41
*						LxCS-DR-42    
*
*	Interfaces	  :		1. Spoi_Uart_Baudrate()	
*	Calls                 
*
*	Called by     :     1. SpoiUartInitialize()   
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                      unsigned short int     us_UartNum          Uart Number
*                      unsigned long          ul_Baud       Buadrate for Uart  
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
*	Step1:Enable TxD0 (P0.2) and RxD0 (P0.3)
*	Step2:Configure UART0 to 8 bit data, no Parity, 1 Stop bit
*	Step3:Disable UART0 Interrupts
*	Step4:Assigning the UART0 irq to Vcetor Interrupt Controller
*	Step5:Set the Priority for UART0 interrupt.
*	Step6:Set the Buard rate 
*	Step7:Enable Recieve data available interrupt bit in IER register.
*
******************************************************************************/

static void Spoi_InitUartZero(unsigned short int us_UartNum
                                ,unsigned long ul_BaudRate)
{ 

   	volatile char vc_Dummy;



	/* Enable TxD0 (P0.2) and RxD0 (P0.3) */
	PINSEL0 |= UART0PINSEL0;

	/* 8 bits, no Parity, 1 Stop bit */
	U0LCR = DATAREG;

	/* Disable UART0 Interrupts */
	U0IER = DISABLEIIR;               

	/* Assigning the uart 0 irq to VIC */
    VICVectAddr6 = (unsigned long)Spoi_SerialIoIrq0;

	/* use it for UART0 Interrupt */
	VICVectCntl6 = UARTPRIORITYLEVEL14;       

	/* Enable UART1 Interrupt */
	VICIntEnable = ONE << UART_ZERO_IRQ;   

	/* setup for 115200 baud (14,4MHz) */
	Spoi_Uart_Baudrate(us_UartNum,ul_BaudRate);   

	/* Read IrqID - Required to Get Interrupts Started */
	vc_Dummy = U0IIR;   

	/* Enable UART0 RX */
	U0IER = ENABLE_INT_FOR_RX;
}
	
/******************************************************************************
*	File Header         Uart.c
*	Procedure Name :    Spoi_SerialIoIrq0    
*	Package Name   :    SPOI     
*	Date of creation :  23/10/2009      
*	Created by     :    dskr     	      
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function reads the data when interrupt occurs for
*                       UART0 irq .
*
*	Allocation	  :	   	NIL    
*
*	DR            :     NIL    
*
*	Interfaces	  :		None	
*	Calls                 
*
*	Called by     :     1. Spoi_InitUartZero()   
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                  volatile char              vc_Dummy         For storing the 
*                                                              LSR Value
*				   volatile char                 IIR		   For storing the 
*                                                              IIR Value 
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
*                      Buf_t              st_ReadBuf          For storing data
*															  in buffer
*
*	Reference	     :      SRS		SDR		SWRS		DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*	Step1:Check the Interrupt status from IIR register if atleast one interrupt 
*		  is pending then check the type of interrupt.
*	Step2:If the interrupt type is parity error or framing error or over run or
*		  break interrupt then clear the interrupt by reading the LSR resigter.
*	Step3:If the Interrupt type is receive data available or char time out 
*		  then read the data from the uart buffer.
*
******************************************************************************/	  

static void Spoi_SerialIoIrq0 (void) __irq 
{
    volatile char vc_Dummy;
    volatile char IIR;

    while (((IIR = U0IIR) & READY) == ZERO)
    {
        switch (IIR & IIRREADY)
	    {
            case RECVLINESTAUS:			/* Receive Line Status */
     		    vc_Dummy = U0LSR;		/* Just clear the interrupt source */
                break;

            case RECVDATAAVAIL:			/* Receive Data Available */
            case CHARTIMEOUT:			/* Character Time-Out */
	         
                if ((st_ReadBuf[UART0].ui_In - st_ReadBuf[UART0].ui_Out) 
                                < (RBUF_SIZE - ONE))
			    {
	                st_ReadBuf[UART0].uc_Buf [st_ReadBuf[UART0].ui_In 
                                            & (RBUF_SIZE - ONE)] = U0RBR;
			        st_ReadBuf[UART0].ui_In++;
	        }
			    else
			    {
				    /* Reset the Buffer*/
                    
                    st_ReadBuf[UART0].ui_In = ZERO;
				    st_ReadBuf[UART0].ui_Out = ZERO;
				    memset(st_ReadBuf[UART0].uc_Buf,'\0',
                                sizeof(st_ReadBuf[UART0].uc_Buf));
			    }
			    break;  
            default:
                break;
        }
    }

    VICVectAddr = ZERO; /* Acknowledge Interrupt */
 }

/******************************************************************************
*	File Header          Uart.c
*	Procedure Name :     static void Spoi_InitUartOne   
*	Package Name   :     SPOI    
*	Date of creation :   23/10/2009      
*	Created by     :     dskr     	    
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :      This function initialize UART1
*
*	Allocation	  :	   	 NIL   
*
*	DR            :     LxCS-DR-10
*						LxCS-DR-43
*						LxCS-DR-44
*						LxCS-DR-45
*						LxCS-DR-46
*						LxCS-DR-47
*						LxCS-DR-48
*						LxCS-DR-49   
*
*	Interfaces	  :		1. Spoi_Uart_Baudrate()	
*	Calls                 
*
*	Called by     :     1. SpoiUartInitialize()  
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                  unsigned short int        us_UartNum            Uart Number
*                 unsigned long              ul_Baud         Buadrate for Uart    
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
*	Step1:Enable TxD0 (P2.0) and RxD0 (P2.1)
*	Step2:Configure UART1 to 8 bit data, no Parity, 1 Stop bit
*	Step3:Disable UART1 Interrupts
*	Step4:Assigning the UART1 irq to Vcetor Interrupt Controller
*	Step5:Set the Priority for UART1 interrupt.
*	Step6:Set the Buard rate 
*	Step7:Enable Recieve data available interrupt bit in IER register.
*
******************************************************************************/

static void Spoi_InitUartOne(unsigned short int us_UartNum,
                                unsigned long ul_BaudRate)
{
	volatile char vc_Dummy;

	PINSEL4 |= UART1PINSEL4;    /* Enable TxD1 (P2.0)and RxD1 (P2.1) */
	
	/* 8 bits, no Parity, 1 Stop bit */
	U1LCR = DATAREG;

	/* Disable UART1 Interrupts */
	U1IER = DISABLEIIR;  
	
	PINSEL1 &=0xFFFFFC3F;	//need to study
	PINSEL4 &=0xFFFF000F;
	FIO2DIR |=0x000000A0;
	FIO2DIR &=0xFFFFFFA3;
	FIO2SET |= 0x00000080;		//RTS LOW
	             
	/* Assigning the uart 1 irq to VIC */
    VICVectAddr7 = (unsigned long)Spoi_SerialIoIrq1;

	/* use it for UART1 Interrupt */
	VICVectCntl7 = UARTPRIORITYLEVEL15; 

	/* Enable UART1 Interrupt */
	VICIntEnable = ONE << UART_ONE_IRQ;   

	/* setup for 115200 baud (14,4MHz) */
	Spoi_Uart_Baudrate(us_UartNum,ul_BaudRate);   

	/* Read IrqID - Required to Get Interrupts Started */
	vc_Dummy = U1IIR;   

	/*Enable UART1 RX*/
	U1IER = ENABLE_INT_FOR_RX; 
}

/******************************************************************************
*	File Header           Uart.c
*	Procedure Name :      Spoi_SerialIoIrq1  
*	Package Name   :      SPOI   
*	Date of creation :    23/10/2009    
*	Created by     :      dskr     	    
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function reads the data when interrupt occurs for
*                       UART1 irq
*
*	Allocation	  :	   	NIL    
*
*	DR            :     NIL    
*
*	Interfaces	  :		 None	
*	Calls                 
*
*	Called by     :     1. Spoi_InitUartOne()  
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                  volatile char              vc_Dummy         For storing the
*                                                              LSR Value 
*				   volatile char                IIR			   For storing the
*                                                              IIR Value 
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
*                          Buf_t            st_ReadBuf       For storing data
*															 in buffer
*
*	Reference	     :      SRS		SDR		SWRS		DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*	Step1:Check the Interrupt status from IIR register if atleast one interrupt
*		  is pending then check the type of interrupt.
*	Step2:If the interrupt type is parity error or framing error or over run or
*		  break interrupt then clear the interrupt by reading the LSR resigter.
*	Step3:If the Interrupt type is receive data available or char time out 
*		  then read the data from the uart buffer.
*
******************************************************************************/

static void Spoi_SerialIoIrq1 (void) __irq 
{
    volatile char vc_Dummy;
    volatile char IIR;

    while (((IIR = U1IIR) & READY) == ZERO)
    {

        switch (IIR & IIRREADY)
	    {
            //case RECVLINESTAUS:		    /* Receive Line Status */
     		  //  vc_Dummy = U1LSR;	    /* Just clear the interrupt source */
                //break;

            case RECVDATAAVAIL:			/* Receive Data Available */
           // case CHARTIMEOUT:			/* Character Time-Out */
							
						st_ReadBuf[UART1].uc_Buf [st_ReadBuf[UART1].ui_In++ ] = U1RBR;
					
					if(RBUF_SIZE == st_ReadBuf[UART1].ui_In)
						st_ReadBuf[UART1].ui_In = 0;
					
					
				#if 0
	            if ((st_ReadBuf[UART1].ui_In - st_ReadBuf[UART1].ui_Out) 
                                    < (RBUF_SIZE - ONE))
			    {
	                st_ReadBuf[UART1].uc_Buf [st_ReadBuf[UART1].ui_In 
                                            & (RBUF_SIZE - ONE)] = U1RBR;
			        st_ReadBuf[UART1].ui_In++;
				}
			    else
			    {
				    /* Reset the Buffer*/
                    
                    st_ReadBuf[UART1].ui_In = ZERO;
				    st_ReadBuf[UART1].ui_Out = ZERO;
				    memset(st_ReadBuf[UART1].uc_Buf,'\0',
                                    sizeof(st_ReadBuf[UART1].uc_Buf));
			    }
				#endif /* #if 0*/
					

			    break;

            default:
                break;
        }
    }

  VICVectAddr = ZERO; /* Acknowledge Interrupt */ 
}

/******************************************************************************
*	File Header         Uart.c
*	Procedure Name :    Spoi_InitUartTwo   
*	Package Name   :    SPOI    
*	Date of creation :  23/10/2009     
*	Created by     :    dskr     	      
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function initialize UART2
*
*	Allocation	  :	   	NIL    
*
*	DR            :     LxCS-DR-11
*						LxCS-DR-50
*						LxCS-DR-51
*						LxCS-DR-52
*						LxCS-DR-53
*						LxCS-DR-54
*						LxCS-DR-55
*						LxCS-DR-56   
*
*	Interfaces	  :		1. Spoi_Uart_Baudrate()	
*	Calls                 
*
*	Called by     :     1. SpoiUartInitialize()   
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                 unsigned short int         us_UartNum            Uart Number
*                 unsigned long              ul_Baud         Buadrate for Uart 
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
*	Step1:Enable TxD0 (P0.10) and RxD0 (P0.11)
*	Step2:Configure UART2 to 8 bit data, no Parity, 1 Stop bit
*	Step3:Disable UART2 Interrupts
*	Step4:Assigning the UART2 irq to Vcetor Interrupt Controller
*	Step5:Set the Priority for UART2 interrupt.
*	Step6:Set the Buard rate 
*	Step7:Enable Recieve data available interrupt bit in IER register.
*
******************************************************************************/

static void Spoi_InitUartTwo(unsigned short int us_UartNum,
                                unsigned long ul_BaudRate)
{
	volatile char vc_Dummy;

	PCONP  |=  UART2PINCON;

	PINSEL0 |= UART2PINSEL0;	/* Enable TxD2 (P0.10) and RxD2 (P0.11) */
	
	/* 8 bits, no Parity, 1 Stop bit */
	U2LCR = DATAREG;

	/* Disable UART1 Interrupts */
	U2IER = DISABLEIIR;               

	/* Assigning the uart 2 irq to VIC */
    VICVectAddr28 = (unsigned long)Spoi_SerialIoIrq2;

	/* use it for UART1 Interrupt */
	VICVectCntl28 = UARTPRIORITYLEVEL15; 

	/* Enable UART1 Interrupt */
	VICIntEnable = ONE << UART_TWO_IRQ;   

	/* setup for 115200 baud (14,4MHz) */
	Spoi_Uart_Baudrate(us_UartNum,ul_BaudRate);   
	
	/* Read IrqID - Required to Get Interrupts Started */
	vc_Dummy = U2IIR;   

	/*Enable UART1 RX  */
	U2IER = ENABLE_INT_FOR_RX; 	
}

/******************************************************************************
*	File Header         Uart.c
*	Procedure Name :    Spoi_SerialIoIrq2     
*	Package Name   :    SPOI     
*	Date of creation :  23/10/2009      
*	Created by     :    dskr     	      
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function read the data when interrupt occurs for 
*                       UART2 irq.
*
*	Allocation	  :	   	NIL    
*
*	DR            :     NIL    
*
*	Interfaces	  :	      None		
*	Calls                 
*
*	Called by     :      1. Spoi_InitUartTwo() 
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                   volatile char              vc_Dummy       For storing the
*                                                             LSR Value
*					volatile char                 IIR		  For storing the 
*	                                                          IIR Value	
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
*                          Buf_t            st_ReadBuf       For storing data
*                                                            in buffer
*
*	Reference	     :     SRS		SDR		SWRS		DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*	Step1:Check the Interrupt status from IIR register if atleast one interrupt
*		  is pending then check the type of interrupt.
*	Step2:If the interrupt type is parity error or framing error or over run or
*		  break interrupt then clear the interrupt by reading the LSR resigter.
*	Step3:If the Interrupt type is receive data available or char time out 
*		  then read the data from the uart buffer.
*
******************************************************************************/

static void Spoi_SerialIoIrq2 (void) __irq 
{
    volatile char vc_Dummy;
    volatile char IIR;

    while (((IIR = U2IIR) & READY) == ZERO)
    {
		//printf(".");
        switch (IIR & IIRREADY)
	    {
            case RECVLINESTAUS:			/* Receive Line Status */
     		    vc_Dummy = U2LSR;		/* Just clear the interrupt source */
                break;

            case RECVDATAAVAIL:			/* Receive Data Available */
            case CHARTIMEOUT:			/* Character Time-Out */
							
						
						st_ReadBuf[UART2].uc_Buf [st_ReadBuf[UART2].ui_In++ ] = U2RBR;
							
						
						if((RBUF_SIZE) == st_ReadBuf[UART2].ui_In)
						st_ReadBuf[UART2].ui_In = 0;
						
					#if 0

	            if ((st_ReadBuf[UART2].ui_In - st_ReadBuf[UART2].ui_Out) 
                                    < (RBUF_SIZE - ONE))
			    {
	                st_ReadBuf[UART2].uc_Buf [st_ReadBuf[UART2].ui_In 
                                        & (RBUF_SIZE - ONE)] = U2RBR;
			        st_ReadBuf[UART2].ui_In++;
	            }
			    else
			    {
				    /* Reset the Buffer*/

                    st_ReadBuf[UART2].ui_In = ZERO;
				    st_ReadBuf[UART2].ui_Out = ZERO;
				    memset(st_ReadBuf[UART2].uc_Buf,'\0',
                                    sizeof(st_ReadBuf[UART2].uc_Buf));
			    }
					
					#endif /* #if 0*/
			    break;

            default:
                break;
        }
    }

  VICVectAddr = ZERO; /* Acknowledge Interrupt */ 
}

/******************************************************************************
*	File Header         Uart.c
*	Procedure Name :    Spoi_InitUartThree    
*	Package Name   :    SPOI     
*	Date of creation :  23/10/2009      
*	Created by     :    dskr     	      
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function initialize UART3
*
*	Allocation	  :	   	NIL    
*
*	DR            :     LxCS-DR-12
*						LxCS-DR-57
*						LxCS-DR-58
*						LxCS-DR-59
*						LxCS-DR-60
*						LxCS-DR-61
*						LxCS-DR-62
*						LxCS-DR-63    
*
*	Interfaces	  :		1. Spoi_Uart_Baudrate()	
*	Calls                 
*
*	Called by     :     1. SpoiUartInitialize()   
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                       unsigned short int     us_UartNum         Uart Number
*                       unsigned long          ul_Baud      Buadrate for Uart      
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
*	Step1:Enable TxD0 (P0.0) and RxD0 (P0.1)
*	Step2:Configure UART3 to 8 bit data, no Parity, 1 Stop bit
*	Step3:Disable UART3 Interrupts
*	Step4:Assigning the UART3 irq to Vcetor Interrupt Controller
*	Step5:Set the Priority for UART3 interrupt.
*	Step6:Set the Buard rate 
*	Step7:Enable Recieve data available interrupt bit in IER register.
*
******************************************************************************/

static void Spoi_InitUartThree(unsigned short int us_UartNum,
                                unsigned long ul_BaudRate)
{
	 volatile char vc_Dummy;

	/*For UART 3 PCNOP valve has to enabled*/
	PCONP  |=  UART3PINCON;

	/* Enable TxD3 (P0.0) and RxD3 (P0.1) */
	//PINSEL0 |= UART3PINSEL0;		
	PINSEL1 = 0x143C003C;
	PINSEL1 |= UART3PINSEL0;		

	 /* 8 bits, no Parity, 1 Stop bit */
	U3LCR = DATAREG;

	/* Disable UART3 Interrupts */
	U3IER = DISABLEIIR;                  

	/* Assigning the uart 0 irq to VIC */
    VICVectAddr29 = (unsigned long)Spoi_SerialIoIrq3;
	
    /* use it for UART3 Interrupt */
	VICVectCntl29 = UARTPRIORITYLEVEL15;   
	
	/* Enable UART3 Interrupt */
	VICIntEnable = ONE << UART_THREE_IRQ;   

	/* setup for 115200 baud (14,4MHz) */
	Spoi_Uart_Baudrate(us_UartNum,ul_BaudRate);   
	
	/* Read IrqID - Required to Get Interrupts Started */
	vc_Dummy = U3IIR;  
	 
	/* Enable UART3 RX */
	U3IER = ENABLE_INT_FOR_RX;  	
}

/******************************************************************************
*	File Header         Uart.c
*	Procedure Name :    Spoi_SerialIoIrq3   
*	Package Name   :    SPOI     
*	Date of creation :   23/10/2009     
*	Created by     :    dskr     	      
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function is used to read the data when interrupt
*                       occurs for  UART3 irq.
*
*	Allocation	  :	   	NIL    
*
*	DR            :     NIL    
*
*	Interfaces	  :		 None	
*	Calls                 
*
*	Called by     :     1. Spoi_InitUartThree()  
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                     volatile char           vc_Dummy         For storing the
*															   LSR Value
*					  volatile char              IIR		   For storing the
*															   IIR Value
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
*                          Buf_t            st_ReadBuf       For storing data
*															 in buffer
*
*	Reference	     :      SRS		SDR		SWRS		DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*	Step1:Check the Interrupt status from IIR register if atleast one interrupt
*		  is pending then check the type of interrupt.
*	Step2:If the interrupt type is parity error or framing error or over run or
*	      break interrupt then clear the interrupt by reading the LSR resigter.
*	Step3:If the Interrupt type is receive data available or char time out 
*		  then read the data from the uart buffer.
*
******************************************************************************/

static void Spoi_SerialIoIrq3 (void) __irq 
{
    volatile char vc_Dummy;
    volatile char IIR;

    while (((IIR = U3IIR) & READY) == ZERO)
    {
        switch (IIR & IIRREADY)
	    {
            case RECVLINESTAUS:			/* Receive Line Status */
     		    vc_Dummy = U3LSR;		/* Just clear the interrupt source */
                break;

            case RECVDATAAVAIL:			/* Receive Data Available */
            case CHARTIMEOUT:			/* Character Time-Out */

									
						st_ReadBuf[UART3].uc_Buf [st_ReadBuf[UART3].ui_In++ ] = U3RBR;
							
						
						if((RBUF_SIZE) == st_ReadBuf[UART3].ui_In)
						st_ReadBuf[UART3].ui_In = 0;
				#if 0
	            if ((st_ReadBuf[UART3].ui_In - st_ReadBuf[UART3].ui_Out) 
                                            < (RBUF_SIZE - ONE))
			    {
	                st_ReadBuf[UART3].uc_Buf [st_ReadBuf[UART3].ui_In 
                                                & (RBUF_SIZE - ONE)] = U3RBR;
			        st_ReadBuf[UART3].ui_In++;
	            }
			    else
			    {
				    /* Reset the Buffer*/

                    st_ReadBuf[UART3].ui_In = ZERO;
				    st_ReadBuf[UART3].ui_Out = ZERO;
				    memset(st_ReadBuf[UART3].uc_Buf,'\0',
                                    sizeof(st_ReadBuf[UART3].uc_Buf));
			    }
				#endif
			    break;

            default:
                break;
        }
    }

  VICVectAddr = ZERO; /* Acknowledge Interrupt */ 
}

/******************************************************************************
*	File Header         Uart.c
*	Procedure Name :    Spoi_Uart_Baudrate     
*	Package Name   :    SPOI    
*	Date of creation :   23/10/2009     
*	Created by     :    dskr     	      
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :    This function set the baudrate of each Uart 
*
*	Allocation	  :	   NIL	    
*
*	DR            :    NIL     
*
*	Interfaces	  :		 None	
*	Calls                 
*
*	Called by     :     1. Spoi_InitUartZero()
*                       2. Spoi_InitUartOne() 
*                       3. Spoi_InitUartTwo()
*                       4. Spoi_InitUartThree()  
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                          unsigned short int     us_UartNum        Uart Number
*                          unsigned long          ul_Baud     Buadrate for Uart 
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
*	Step1:Calculate the valve to fill Divisior Latch LSB register 
*		  and Divisior Latch MSB register .
*	Step2:Enable the Access to Divisor Latches by setting 1 in the 7th bit of 
*		  LCR register.
*	Step3:Load the calculated value in DLL and DLM registers.
*	Step4:Disable DLAB by set 0 in the 7th bit of LCR register.
*
******************************************************************************/

static void Spoi_Uart_Baudrate(unsigned short int us_UartNum,
                                unsigned long ul_BaudRate)
{
    unsigned long ul_Reload;
  
    /* Calculation of reload valve to fill Divisior Latch LSB 
     * register(UnDLL) and Divisior Latch MSB register (UnDLM)*/

    ul_Reload = ((FREQUENCY / DIVSIOR) + (ul_BaudRate - ONE)) / ul_BaudRate;

    if (UART0 == us_UartNum)
    {
	    /* Enable Access to Divisor Latches by set 1 in the 7th bit of U0LCR */
        U0LCR |= DLAB;
	  
        /* Stores Lower 8-Bits */
	    U0DLL = ul_Reload;
	  
        /* Stores Hihger 8-Bits */
	    U0DLM = (ul_Reload >> EIGHT);
	  
        /* Disable DLAB by set 0 in the 7th bit of U0LCR */
	    U0LCR &= ~DLAB; 
    }
    else if (UART1 == us_UartNum)
    {
	    /* Enable Access to Divisor Latches by set 1 in the 7th bit of U1LCR */
        U1LCR |= DLAB;
        
        /* Stores Lower 8-Bits */
	    U1DLL = ul_Reload;

        /* Stores Hihger 8-Bits */
	    U1DLM = (ul_Reload >> EIGHT);

        /* Disable DLAB by set 0 in the 7th bit of U1LCR */
	    U1LCR &= ~DLAB; 
    }
    else if (UART2 == us_UartNum)
    {
	    /* Enable Access to Divisor Latches by set 1 in the 7th bit of U2LCR */
        U2LCR |= DLAB;
        
        /* Stores Lower 8-Bits */
	    U2DLL = ul_Reload;

        /* Stores Hihger 8-Bits */
	    U2DLM = (ul_Reload >> EIGHT);

        /* Disable DLAB by set 0 in the 7th bit of U2LCR */
	    U2LCR &= ~DLAB; 
    }
    else if (UART3 == us_UartNum)
    {
	    /* Enable Access to Divisor Latches by set 1 in the 7th bit of U3LCR */
        U3LCR |= DLAB;
        
        /* Stores Lower 8-Bits */
	    U3DLL = ul_Reload;

        /* Stores Hihger 8-Bits */
	    U3DLM = (ul_Reload >> EIGHT);

        /* Disable DLAB by set 0 in the 7th bit of U3LCR */
	    U3LCR &= ~DLAB; 
    }                          
}

/******************************************************************************
*	File Header          Uart.c
*	Procedure Name :     Spoi_InitUartBuffers    
*	Package Name   :     SPOI    
*	Date of creation :   23/10/2009     
*	Created by     :     dskr     	     
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :    This function initialize the uart buffers 
*
*	Allocation	  :	   NIL	    
*
*	DR            :    NIL     
*
*	Interfaces	  :		None	
*	Calls                 
*
*	Called by     :    1. SpoiUartInitialize()   
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*                      unsigned short int     us_Index          Uart Number to
*                                                               initalize
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
*                          Buf_t            st_ReadBuf    Read Buffer Structure
*
*	Reference	     :      SRS		SDR		SWRS		DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*	Step1:Initalize the UART buffers with Zero's
*
******************************************************************************/

static void Spoi_InitUartBuffers(unsigned short int us_Index)
{

	st_ReadBuf[us_Index].ui_In = ZERO;
	st_ReadBuf[us_Index].ui_Out = ZERO;

	memset(st_ReadBuf[us_Index].uc_Buf,'\0',
					sizeof(st_ReadBuf[us_Index].uc_Buf));
}
/*End Of File*/
