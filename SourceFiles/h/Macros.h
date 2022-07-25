/******************************************************************************
* File Name			: Macros.h
*
* Abstract		    : This file contains the macros to be included.
*					      
* Date of creation  :       13/11/2009 
* Date of Modification :               
* Created by        :        PM
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


#ifndef MACROS_H
#define MACROS_H

//#define CONFIG_STORE_BATT_BACKUP

//#define RM2PORT			2
//#define RMPORT			3
//#define DELAY_TRAIN_APP_DETECTION
//#define DELAY_TRAIN_DEP_DETECTION

#define TRAINLENGTH

#define LAND_MARK_PKT				0x03	/* Land Mark Info Pkt to loco  (11/16/2013) */
#define PACKET_FROM_LOCO_TCAS		0x02	/* BY LOCO Annexure -  II	   (10/22/2013)	*/
#define STATION_PACKET				0x01	/* Station Transmission Packet (10/22/2013) */
#define EMERGENCY_PACKET			0x04
#define AUTHENTICATION_PACKET_FROM_LOCO_TCAS 		0x06

#define AVAILABLE			1
#define UNRESTRICTED		0x0F
#define	SAME_STATION		0
#define ADJACENT_STATION	1



#define ZMS_BITS

#ifdef CONFIG_STORE_BATT_BACKUP
#define FORCED_DEFAULT_CONFIGURATION
#endif /*CONFIG_STORE_BATT_BACKUP*/


#define LPM_CONFIG_BYTES			12
#define LPM_CONFIG_CHECK_WITH_SDM

#ifdef FORCED_DEFAULT_CONFIGURATION
#define DEFAULT_CONFIGURATION
#endif /*#ifdef FORCED_DEFAULT_CONFIGURATION*/

#define AXM_CARD_FAILURE

#define DEBUG_VERSION
//#undef DEBUG_VERSION	

#define IPV_DEBUG
//#undef IPV_DEBUG

#define CONFIG_DEBUG
//#undef CONFIG_DEBUG

#define LPSO_DEBUG
//#undef LPSO_DEBUG

#define CBIT_DEBUG
//#undef CBIT_DEBUG

#define POST_DEBUG
//#undef POST_DEBUG

#define MBIT_DEBUG
//#undef MBIT_DEBUG

#define DEBUG_COMM_MODULE 		/* For Debugging of Comm Module */	
//#undef 	DEBUG_COMM_MODULE

#define EVENT_DEBUG	 		/* For Debugging of events */
//#undef EVENT_DEBUG

#define TWENTY_FOUR             24
#define FOUR                    4
#define FIVE                    5
#define SIX                     6
#define SEVEN                   7
#define EIGHT                   8
#define NINE                    9
#define TEN                     10
#define ELEVEN	                11
#define TWELVE	                12
#define FIFTY				    50
#define FIFTYFIVE               55
#define SIXTY                   60



#define ZERO                    0
#define DEFAULT                 0
#define CLEAR                   0
#define NULL_STRING             "\0"
#define ON						1
#define OFF						2
#define CLOSE					3
#define OPEN					4

#define UP				        1
#define DN				        2

#define SET                     1
#define RESET                   2

#define TWO                     2
#define THREE                   3

#define EXCLOSE                 1
#define EXOPEN                  2

#define SEMI_AUTO_MODE          1
#define RES_OP_MODE             2
#define MANUAL_MODE             3
#define ERROR_MODE              4

#define MAINT_MODE		        1

#define EM_SWITCH_A             1
#define EM_SWITCH_B             2
#define EM_SWITCH_C             3
#define EM_SWITCH_ERROR         4

#define LOCKED 			        1
#define RELEASE                 2

#define NORMAL                  1
#define REVERSE			        2

#define SINGLE 		        	1
#define DUAL		       		2

#define CONNECTED 		        1

#define MMODE_DESEL_ON_TR       3
#define MMODE_DESEL_BY_HHU      2
#define NO_MAINT_MODE           0 

/* For Ecah Bit status of Flasher as High Detected */
#define HIGH                    1
/* For Ecah Bit status of Flasher as Low Detected */
#define LOW                     2
/* For Ecah Bit status of Flasher as Pulse Detected */
#define PULSE                   3

/* Defined for Flasher Failures */
#define ALL_FLASHERS_OK	                    1
#define SINGLE_FLASHER_FAIL                 2
#define SINGLE_FLFAIL_ON_EACH_PAIR          3
#define BOTH_FLASHERS_FAIL                  4
#define THREE_FLASHERS_FAIL                 5
#define ALL_FLASHERS_FAIL                   6

#define DIR_RHS_LHS_OK			0
#define DIR_RHS_FAIL			1
#define DIR_LHS_FAIL			2
#define DIR_RHS_LHS_FAIL		3	



#define OK                                  1
#define FAIL                                2

#define INSERTED                            2
#define REMOVED                             1 

#define FALSE       						0
#define TRUE 								1


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

#define Y0_BUF                        0 
#define Y1_BUF                        1
#define Y2_BUF                        2
#define Y3_BUF                        3
#define Y4_BUF                        4
#define Y5_BUF                        5
#define Y6_BUF                        6
#define Y7_BUF                        7
#define Y8_BUF                        8
#define Y9_BUF                        9
#define Y10_BUF                      10
#define Y11_BUF                      11
#define Y12_BUF                      12
#define Y13_BUF                      13
#define Y14_BUF                      14
#define Y15_BUF                      15
#define Y16_BUF                      16
#define Y17_BUF                      17
#define Y18_BUF                      18
#define Y19_BUF                      19
#define Y20_BUF                      20


/* Macros for DIP Switch Configuration */

#define SINGLE_TRACK                    1
#define DOUBLE_TRACK                    2
#define THREE_TRACKS                    3
#define FOUR_TRACKS                     4

#define BELL_CONNECTED                  1
#define DVRS_CONNECTED                  1
#define GATE_CONNECTED                  1
#define GATE1_CONNECTED                 1
#define GATE1_2_CONNECTED               2

#define NOT_CONNECTED			        0
#define SINGLE_FLASHER_ON_POST          1
#define BOTH_FLASHERS_ON_POST           2
#define FLASHERS_ON_CANTILEVER          3
#define DIR_INDI_CONNECTED              1


#define UP_CONNECTED			        1
#define DN_CONNECTED			        2
#define ERROR_CONNECTED			        3

#define MECHANICAL				        1
#define UP_ELECTRICAL_DN_MECHANICAL     2
#define UP_MECHANICAL_DN_ELECTRICAL     3
#define ELECTRICAL				        4

#define MAX_MEMEORY_READ_CNT            3

#define WSSWRONGDIRRESETTIME			THREE_MIN

#ifdef FORCED_DEFAULT_CONFIGURATION

/* Define Gate Configuration
 */
#define KAFRL_GAMAL

#ifdef EL_GAZ
	#define CONFIG_TIMER_1		(8 * ONE_SEC)	/*Delay B/w ON-Flashers&Bell And CLOSE-Barrier*/
	#define CONFIG_TIMER_2		(16	* ONE_SEC)/*Delay To Detect Barrier Fail*/
	#define CONFIG_BUZZER_STAT	0x0	/*Config Buzzer Indications for individual Failure*/
    #define CONFIG_BYTE_0		0xFA56
    #define CONFIG_BYTE_1		0x0009
    #define CONFIG_BYTE_2		0x0000
    #define CONFIG_BYTE_3		0x0000
#endif /*#ifdef EL_GAZ*/

#ifdef TALKHA
	#define CONFIG_TIMER_1		(8 * ONE_SEC)	/*Delay B/w ON-Flashers&Bell And CLOSE-Barrier*/ 
	#define CONFIG_TIMER_2		(16	* ONE_SEC)/*Delay To Detect Barrier Fail*/                   
	#define CONFIG_BUZZER_STAT	0x0	/*Config Buzzer Indications for individual Failure*/
    #define CONFIG_BYTE_0		0xEA08
    #define CONFIG_BYTE_1		0x0001
    #define CONFIG_BYTE_2		0x0000
    #define CONFIG_BYTE_3		0x0000
#endif /*#ifdef TALKHA*/

#ifdef KAFRL_GAMAL
	#define CONFIG_TIMER_1		(8 * ONE_SEC)	/*Delay B/w ON-Flashers&Bell And CLOSE-Barrier*/ 
	#define CONFIG_TIMER_2		(16	* ONE_SEC)/*Delay To Detect Barrier Fail*/                   
	#define CONFIG_BUZZER_STAT	0x0	/*Config Buzzer Indications for individual Failure*/
    #define CONFIG_BYTE_0		0xFB16
    #define CONFIG_BYTE_1		0x0009
    #define CONFIG_BYTE_2		0x0000
    #define CONFIG_BYTE_3		0x0000
#endif /*#ifdef KAFRL_GAMAL*/


#ifdef QUAHA	
	#define CONFIG_TIMER_1		(8 * ONE_SEC)	/*Delay B/w ON-Flashers&Bell And CLOSE-Barrier*/ 
	#define CONFIG_TIMER_2		(16	* ONE_SEC)/*Delay To Detect Barrier Fail*/                   
	#define CONFIG_BUZZER_STAT	0x0	/*Config Buzzer Indications for individual Failure*/

    #define CONFIG_BYTE_0		0xEA16
    #define CONFIG_BYTE_1		0x0009
    #define CONFIG_BYTE_2		0x0000
    #define CONFIG_BYTE_3		0x0000
#endif /*#ifdef QUAHA*/

#ifdef ROZEL_YOUSEF

	#define CONFIG_TIMER_1		(8 * ONE_SEC)	/*Delay B/w ON-Flashers&Bell And CLOSE-Barrier*/ 
	#define CONFIG_TIMER_2		(16	* ONE_SEC)/*Delay To Detect Barrier Fail*/                   
	#define CONFIG_BUZZER_STAT	0x0	/*Config Buzzer Indications for individual Failure*/

    #define CONFIG_BYTE_0		0xEA16
    #define CONFIG_BYTE_1		0x0009
    #define CONFIG_BYTE_2		0x0000
    #define CONFIG_BYTE_3		0x0000
#endif /*#ifdef ROZEL_YOUSEF*/

#ifdef EL_SHOOLA

	#define CONFIG_TIMER_1		(10 * ONE_SEC)	/*Delay B/w ON-Flashers&Bell And CLOSE-Barrier*/ 
	#define CONFIG_TIMER_2		(16	* ONE_SEC)/*Delay To Detect Barrier Fail*/                   
	#define CONFIG_BUZZER_STAT	0x0	/*Config Buzzer Indications for individual Failure*/

    #define CONFIG_BYTE_0		0xF210
    #define CONFIG_BYTE_1		0x0009
    #define CONFIG_BYTE_2		0x0000
    #define CONFIG_BYTE_3		0x0000

#endif /*#ifdef EL_SHOOLA */

#ifdef EL_NEIL

	#define CONFIG_TIMER_1		(8 * ONE_SEC)	/*Delay B/w ON-Flashers&Bell And CLOSE-Barrier*/ 
	#define CONFIG_TIMER_2		(16	* ONE_SEC)/*Delay To Detect Barrier Fail*/                   
	#define CONFIG_BUZZER_STAT	0x0	/*Config Buzzer Indications for individual Failure*/

    #define CONFIG_BYTE_0		0xF410
    #define CONFIG_BYTE_1		0x0009
    #define CONFIG_BYTE_2		0x2000  /* 13th bit for Type of Control Panels */
    #define CONFIG_BYTE_3		0x0000

#endif /*#ifdef EL_NEIL */

#endif /* FORCED_DEFAULT_CONFIGURATION */

//#define RTC_HEALTH_CHECK
#undef RTC_HEALTH_CHECK

#define PERIODIC_RTC_UPDATE_INT (60 * 1000)
#define PRINT_GPS_DATA_TIME     (1  * 1000)


#define DATALOG_STNTX			0x01
#define DATALOG_STNRX			0x01
#define DATALOG_SIGPKT		0x02

#endif /* MACROS_H */

/*End of file*/

