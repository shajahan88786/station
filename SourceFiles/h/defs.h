#ifndef __DO_H_
#define __DO_H_


#define BIT0    0x1			/* For checking Bit 0 status of 32 bit buffer */
#define BIT1    0x2			/* For checking Bit 1 status of 32 bit buffer */
#define BIT2    0x4			/* For checking Bit 2 status of 32 bit buffer */
#define BIT3    0x8			/* For checking Bit 3 status of 32 bit buffer */
#define BIT4    0x10		/* For checking Bit 4 status of 32 bit buffer */
#define BIT5    0x20		/* For checking Bit 5 status of 32 bit buffer */
#define BIT6    0x40		/* For checking Bit 6 status of 32 bit buffer */
#define BIT7    0x80		/* For checking Bit 7 status of 32 bit buffer */
#define BIT8    0x100		/* For checking Bit 8 status of 32 bit buffer */
#define BIT9    0x200		/* For checking Bit 9 status of 32 bit buffer */
#define BIT10   0x400		/* For checking Bit 10 status of 32 bit buffer */
#define BIT11   0x800		/* For checking Bit 11 status of 32 bit buffer */
#define BIT12   0x1000		/* For checking Bit 12 status of 32 bit buffer */
#define BIT13   0x2000		/* For checking Bit 13 status of 32 bit buffer */
#define BIT14   0x4000		/* For checking Bit 14 status of 32 bit buffer */
#define BIT15   0x8000		/* For checking Bit 15 status of 32 bit buffer */
#define BIT16   0x10000		/* For checking Bit 16 status of 32 bit buffer */
#define BIT17   0x20000		/* For checking Bit 17 status of 32 bit buffer */
#define BIT18   0x40000		/* For checking Bit 18 status of 32 bit buffer */
#define BIT19   0x80000		/* For checking Bit 19 status of 32 bit buffer */
#define BIT20   0x100000	/* For checking Bit 20 status of 32 bit buffer */
#define BIT21   0x200000	/* For checking Bit 21 status of 32 bit buffer */
#define BIT22   0x400000	/* For checking Bit 22 status of 32 bit buffer */
#define BIT23   0x800000	/* For checking Bit 23 status of 32 bit buffer */
#define BIT24   0x1000000	/* For checking Bit 24 status of 32 bit buffer */
#define BIT25   0x2000000	/* For checking Bit 25 status of 32 bit buffer */
#define BIT26   0x4000000	/* For checking Bit 26 status of 32 bit buffer */
#define BIT27   0x8000000	/* For checking Bit 27 status of 32 bit buffer */
#define BIT28   0x10000000	/* For checking Bit 28 status of 32 bit buffer */
#define BIT29   0x20000000	/* For checking Bit 29 status of 32 bit buffer */
#define BIT30   0x40000000	/* For checking Bit 30 status of 32 bit buffer */
#define BIT31   0x80000000	/* For checking Bit 31 status of 32 bit buffer */

#define Y0_BUF		  0 
#define Y1_BUF		  1
#define Y2_BUF		  2
#define Y3_BUF		  3
#define Y4_BUF		  4
#define Y5_BUF		  5
#define Y6_BUF		  6
#define Y7_BUF		  7
#define Y8_BUF		  8
#define Y9_BUF		  9
#define Y10_BUF		 10
#define Y11_BUF		 11
#define Y12_BUF		 12
#define Y13_BUF		 13
#define Y14_BUF		 14
#define Y15_BUF		 15
#define Y16_BUF		 16
#define Y17_BUF		 17
#define Y18_BUF		 18
#define Y19_BUF		 19
#define Y20_BUF		 20


/****************************************************************************
 *		TCAS GPIO OUTPUTS:		11/25/2013
 ****************************************************************************
 *				    P3.7    P3.6    P3.5    P3.4   P3.3   P3.2    P3.1   P3.0
 *		OUT0BUF:  LE2	  |LE1    |EB2	  |EB1   |FSB2	|FSB1	|NB2   |NB1	  |				
 *		OUT1BUF:          |       |       |HOOTER|BBU-BL|SOS-LMP|TCAS-M|TCASOK|	
 *		OUT2BUF:	      |       |		  |		 |		|		|      |      |
 *		OUT3BUF:		  |		  |       |	     |	    |		|	   |	  |
 *		OUT4BUF:		  |		  |       |	     |	    |		|	   |	  |
 *		OUT5BUF:		  |		  |       |	     |	    |		|	   |	  |
 *		OUT6BUF:		  |		  |       |	     |	    |		|	   |	  |
 *		OUT7BUF:		  |		  |       |	     |	    |		|	   |	  |
 ******************************************************************************/


/*OUT0BUF*/
#define DO_TCAS_NB_1OF2				BIT0 	
#define DO_TCAS_NB_2OF2				BIT1 
#define DO_TCAS_FSB_1OF2			BIT2  
#define DO_TCAS_FSB_2OF2			BIT3 
#define DO_TCAS_EB_1OF2				BIT4 
#define DO_TCAS_EB_2OF2				BIT5 
#define DO_TCAS_LE_1OF2				BIT6 
#define DO_TCAS_LE_2OF2				BIT7 

/*OUT1BUF*/
#define DO_TCAS_FAULTY_LAMP			BIT0
#define DO_TCAS_SOS_LAMP			BIT1
#define DO_HOOTER					BIT2







#define NORMAL_BRAKE			1
#define	EMERGENCY_BRAKE			2
#define FIRST_SERVICE_BRAKE		3
#define ALL_BRAKE				4
#define HOOTER					5


void SetDO(short int iDoNum);

void Lpso_OutputControlling( unsigned char uc_YBufferSel,unsigned char uc_Byte);

void IdrvOutputDefaultInit(void);

void DriveOutputs(void);

#endif /* __DO_H_*/ 

