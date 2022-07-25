/******************************************************************************
* File Name			: RxAndTx.h
*
* Abstract		    : This file contains the declarations for the routines of 
*					  RxAndTx.c                                                  
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


#ifndef RXANDTX_H
#define RXANDTX_H

#include <LPC23XX.H>                      /* LPC23xx definitions */
#include <limits.h>

extern const unsigned short int Kus_Crc16Table[16];

#define TRANSMITBIT			    0x20

#define EIGHT				    8
#define DLE					    0x05

#define HEX_F				    0x000F
#define HEX_FF				    0x00FF
#define HEX_FFF				    0x0FFF
#define HEX_FFFF			    0xFFFF

#define ONE					1
#define TWO					2
#define THREE				3
#define FOUR				4
#define FIVE				5
#define SIX					6
#define SEVEN				7
#define EIGHT				8

#define START_OF_MESSAGE	    '$'
#define END_OF_MESSAGE		    '&'
#define ACK_FOR_UNICAST		    0
#define ACK_FOR_BROADCAST		1


/*Read and form the message from the port*/
unsigned short int CommReadAndFormMessage(unsigned short int ,
                                           unsigned char *,
                                           unsigned short int );

/*Transmit the message*/
void CommTransmitMessage(unsigned short int,
   						 unsigned char *,
                         unsigned short int);
/*Send data to COM port*/
void Comm_ComSendByte(unsigned short int,unsigned char);
/*Process to compute CRC for the message*/
unsigned short int CommComputeCRC(unsigned char *,unsigned short int);
/*Process to checking of CRC for the message*/
unsigned short int CommCheckCRC(unsigned char *,unsigned short int);
/*Process to compute CRC16 for the message*/
unsigned short int CommGetCRC16(unsigned short int,unsigned char *, 
                                 unsigned short int );
unsigned short int Comm_ComDataReady(unsigned short int);
unsigned char Comm_ComGetByte(unsigned short int );
void TransmitMessage_NoDle(short int iPort, unsigned char *pszMessage,short int iTBytes);

#endif /* RXANDTX_H */


/*End Of File*/
