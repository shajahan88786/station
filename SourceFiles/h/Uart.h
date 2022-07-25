/******************************************************************************
* File Name			: Uart.h
*
* Abstract		    : This file contains the declarations for the routines of 
*					  Uart.c                                                  
* Date of creation  :       21/10/2009 
* Date of Modification :               
* Created by        :        dskr
* Modification history :
* +--------------------------------------------------------------------------+
* |   Revision  |      SPR        |  AR    |    DATE	|     Remarks	     |
* |-------------|-----------------|--------|------------|--------------------|
* |    1.0		| Initial Release |        |		    |                    |
* +--------------------------------------------------------------------------+
*
* Compiler/Assembler/Linker: Armcc.exe V3.1.0.919, Armasm.exe V3.1.0.919,
*                               ArmLink.exe V3.1.0.919                   
******************************************************************************/

#ifndef UART_H
#define UART_H

#include <LPC23XX.H>                       /* LPC23xx definitions */
#include <string.h>
#include <limits.h>

#define ZERO				0
#define ONE					1
#define EIGHT				8

#define BAUD115200			115200
#define BAUD38400			38400
#define BAUD19200			19200
#define BAUD9600			9600
#define BAUD57600			57600



/*Buard rate related Macros*/
#define FREQUENCY		14400000UL
#define DLAB			0x80
#define DIVSIOR			16UL

/*Data transfer for 8 N 1*/
#define DATAREG				0x03

#define DISABLEIIR			0
#define UARTPRIORITYLEVEL14	14
#define UARTPRIORITYLEVEL15	15
#define UART_ZERO_IRQ		6
#define UART_ONE_IRQ		7
#define UART_TWO_IRQ		28
#define UART_THREE_IRQ		29
#define ENABLE_INT_FOR_RX	1

/*PIN Selctors for UARTs*/

#define UART0PINSEL0	0x00000050

#define UART1PINSEL4	0x0000000A

#define UART2PINSEL0	0x00500000
#define UART2PINCON		0x01000000

#define UART3PINSEL0	0x0000000A
#define UART3PINCON		0x02000000

#define READY			0x01
#define IIRREADY		0x0E

#define RECVLINESTAUS	0x06
#define RECVDATAAVAIL	0x04
#define CHARTIMEOUT		0x0C

/* The length of the receive buffer must be a power of 2.
 * (in - out) % buffer_size = the number of characters in the buffer.
 */

/*Reciever Buffer Size*/
#define RBUF_SIZE   1024   

#if RBUF_SIZE < 2
	#error RBUF_SIZE is too small.  It must be larger than 1.
#elif ((RBUF_SIZE & (RBUF_SIZE-1)) != 0)
	#error RBUF_SIZE must be a power of 2.
#endif

/*Total No Of UARTS in USE*/
#define NOOFUARTS		4

#define UART0			0
#define UART1			1
#define UART2			2
#define UART3			3

typedef struct  
{
    unsigned int ui_In;                     /* In Index */
    unsigned int ui_Out;                    /* Out Index */
    unsigned char uc_Buf[RBUF_SIZE];        /* Buffer */
}Buf_t;

extern Buf_t st_ReadBuf[NOOFUARTS];/*To maintain UART Buffer*/


/*Initialize UART Buffers */
static void Spoi_InitUartBuffers(unsigned short int );
/*Initialize of UART*/
void SpoiUartInitialize(unsigned short int , unsigned long );
/*Initialize of UART0*/
static void Spoi_InitUartZero(unsigned short int, unsigned long );
/*Process UART0 Interrupt*/ 
static void Spoi_SerialIoIrq0 (void) __irq;
/*Initialize of UART1*/
static void Spoi_InitUartOne(unsigned short int, unsigned long );
/*Process UART1 Interrupt*/ 
static void Spoi_SerialIoIrq1 (void) __irq ;
/*Initialize of UART2*/
static void Spoi_InitUartTwo(unsigned short int ,unsigned long );
/*Process UART2 Interrupt*/ 
static void Spoi_SerialIoIrq2 (void) __irq ; 
/*Initialize of UART3*/
static void Spoi_InitUartThree(unsigned short int,unsigned long );
/*Process UART3 Interrupt*/ 
static void Spoi_SerialIoIrq3 (void) __irq;
/*Set UART Buard rates*/
static void Spoi_Uart_Baudrate(unsigned short int, unsigned long );


#endif /* UART_H */



/*End Of File*/

