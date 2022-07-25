/******************************************************************************
* File Name			: BitManip.h
*
* Abstract		    : This file contains the declarations for the routines of 
*					  BitManip.c                                                  
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

#ifndef BITMAINP_H
#define BITMAINP_H

#define BITSTUFFINIT(x,y)	unsigned char ucByte = y, ucBit = x;
//BITSTUFFSIZE(x) ucSize = x;
#define BITSTUFFINC(x)	{ucByte = (unsigned char)((short int)ucByte+(((short int)ucBit+x)/8)); ucBit = (unsigned char)((short int)(ucBit+x)%8);}


#define ONE					1
#define TWO					2
#define THREE				3
#define FOUR				4
#define FIVE				5
#define SEVEN				7
#define EIGHT				8
#define FIFTEEN				15
#define SIXTEEN				16
#define TWENTY_FOUR			24
#define THIRTY_ONE			31

/* Function for extraction of Data*/

unsigned long ExtractBits(unsigned short int, unsigned short int, 
								unsigned char *);
/* Function for insertion of Data*/
unsigned long InsertBits(unsigned short int, unsigned short int, 
								unsigned char *, unsigned long);

#endif  /* BITMAINP_H */


/*End Of File*/

