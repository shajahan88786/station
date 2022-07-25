#ifndef __DI_H_
#define __DI_H_


#define MAX_FIB						2   /* Total FIB Modules */
#define MAX_BUFFER					12  /* Total Buffers of all FIBs */
#define MAX_INPUT_BUFFER			12  /* Max Input Buffers */
#define NO_OF_BUFFERS_OF_EACH_FIB	6   /* No of Buffers of Each FIB Card */

#define TWENTY_SEVEN                27  /* Used for FIB Selection */
#define TWENTY_FOUR                 24  /* Used for Buffer Selection */

#define ONE                         1   /* For Variable Set */
#define ZERO                        0   /* For Variable Reset */
#define FOUR						4
#define EIGHT						8

#define FIB_CARD_SELECTION      0x03        /* For FIB Card Selection */
#define BUFFER_SELECTION        0x07        /* Address Line Buffer Selection */
#define BUFFER_DIRECTION        0x06000000   /* Data Bus and Decoder Enable */
#define FIB_CHK			        0x80800000  /* For FIB Cards Diagnostics */

#define FIB_ONE_CHK      		0x800000    /* For FIB Cards Diagnostics */
#define FIB_TWO_CHK       		0x80000000  /* For FIB Cards Diagnostics */

#define MAX_OUTPUT_BUF  8   /* Total Output Buffers */



/****************************************************************************
 *		TCAS GPIO INPUTS		11/25/2013
 *
 *				P3.7    P3.6    P3.5    P3.4   P3.3   P3.2    P3.1   P3.0
 *		I0BUF:		  |		  |       |	     |	    |		|	   |	  |				
 *		I1BUF:  LPBRK |BBU    |BIU2   |BIU1  |	    |		|	   |      |	
 *		I2BUF:	CPLD_M|STAFF_M|REST_M |COMMON|CNCL  |BRK-TST|ACK   |SOS	  |
 *		I3BUF:		  |		  |       |	     |	    |		|	   |	  |
 *		I4BUF:		  |		  |       |	     |	    |		|	   |	  |
 *		I5BUF:		  |		  |       |	     |	    |		|	   |	  |
 *		I6BUF:		  |		  |       |	     |	    |		|	   |	  |
 *		I7BUF:		  |		  |       |	     |	    |		|	   |	  |
 ******************************************************************************/

/* I1BUF */
#define DI_TCAS_ABU_ISO_1OF2				BIT4
#define DI_TCAS_ABU_ISO_2OF2				BIT5
#define DI_TCAS_BBU_BATT_LOW				BIT6
#define DI_BRAKE_APP_LOCO_PILOT				BIT7

/* I2BUF */
#define DI_TCAS_SOS_PRESSED					BIT0 
#define DI_TCAS_ACK							BIT1 
#define	DI_TCAS_BRAKE_TEST					BIT2 
#define DI_TCAS_CNCL_PRESSED				BIT3 
#define DI_TCAS_COMMON_PRESSED				BIT4
#define DI_TCAS_MODE_SELECT_RESTRICTED		BIT5 
#define DI_TCAS_MODE_SELECT_STAFF_RESPN		BIT6 
#define DI_TCAS_MODE_SELECT_COUPLED			BIT7 






void GetDI(void);


#endif /* __DI_H_*/ 
