#ifndef __GLOBALS_H_
#define __GLOBALS_H_
#include "station.h"

#ifndef PRINTF_DEBUG
	#define PRINTF_DEBUG
#endif /*PRINTF_DEBUG*/
#define STATIC_PROFILE    0x05

#ifndef GPIO_DEBUG
	#define GPIO_DEBUG
#endif /*GPIO_DEBUG*/


typedef enum _integrity
{
	CRCHK	= 0,
	CHKSUM,
	MAX_INTEGRITY		
}INTEGRITY;


extern unsigned char gucRFDataFlag;
extern unsigned char timeflag;
extern unsigned char gucSelfSlot;
extern unsigned char gucHealthFlag;
extern unsigned char gucSlot3Fail;
extern unsigned int uiframeno;
extern unsigned char ucProfileID;
extern  unsigned int  uiDestnationLOcoID; 
extern short int gui_CalCrc;
extern unsigned long GPSframeNo;
extern unsigned char gucRTSHighRMShiftFlag;
//extern unsigned long  ulCANCLK ;
extern unsigned char StaticProfilePkt[256];
//#define TWO_SEC_NS 201404		if 143
#define TWO_SEC_NS 197505
#define MODEM_DELAY 1500
#define FORTY_MS 4000
//#define TWENTY_MS 2000
#define RTS_HIGH_LOW_TIME	2000	 
#define NEGATIVE_CUTOFF 6500
#define PPS_TIMER_CORRECTION 60
#define PPS_ONE 1
#define MR0_INT 0x01
#define MR1_INT 0x02
#define MR2_INT 0x04
#define MR3_INT 0x08

typedef struct
{
	unsigned char ucCrcReqRec;
}stCAN_HEXFILECRCREQREC_t;

typedef struct
{
	unsigned char ucSlotNo;
	unsigned short int ucHexFileCrc;
}stCAN_HEXFILECRC_t;

extern stCAN_HEXFILECRC_t stCanComCrcVal;
extern stCAN_HEXFILECRCREQREC_t stCanHexCrcvalReqRec,tempstCanComCrcVal[2];

//extern void AES128_CBC_encrypt_buffer(unsigned char* output, unsigned char* input, unsigned int length, const unsigned char* key, const unsigned char* iv);

extern unsigned char gucT2MR0, gucT2MR1;
extern unsigned char gucRadioModemResetFlag,gucRadioModemResetFlagHex;
extern RADIOMODEMHEALTH_t RadioModemHealth;	//sid
extern CAN_RADIOMODEM_FAIL_STATUS_t stCanRadioModemFailStatusTx,stCanRadioModemFailStatusRx,stCanRadioModemFailStatusRxFillStruct;		//sid (For radio failure)	
extern Authentication_KEY_t Authentication_KEY,tempAuthentication_KEY[2];
extern Authentication_KEY_comSend_t Authentication_KEY_comSend,tempAuthentication_KEY_comSend[2];
extern CAN_RADIOMODEM_STATUS_LOG_t stCanRadioModemStatusLog;

//extern unsigned char COM_KEY_REQ_FLAG ;

// For Radio Modem 
#define GET_BIT_MASK(bit)	((0x01)<<(bit))
#define SET_BIT(bit,val)	((val) |= (GET_BIT_MASK(bit)))
#define CLEAR_BIT(bit,val)	((val) &= ~(GET_BIT_MASK(bit)))
#define CHECKFLAG(bit,val)	(((val) & (GET_BIT_MASK(bit)))?SET:CLEAR)

//For Radio Modem ERRORS (sid)
//Modem Status 

#define NO_ERRORS					0
#define TIMER_QUEUE_OVERFLOW		1
#define UART_BUFFER_UNAVILABLE		2
#define MESSAGE_QUEUE_OVERFLOW		3
#define EEPROM_WRITE_FAILED			4
#define CONFIG_FILE_CORRUPT			5
#define MODEM_QUEUE_OVERFLOW		6
#define REQUIRE_FILE_MISSING		7
#define FILE_IS_CORRUPT				8
#define RX_MODEM_SAMPLE_OVERFLOW	9
#define RX_RADIO_DATA_NOT_PROCESSED	10
#define TX_RADIO_DATA_NOT_PROCESSED	11
#define RX_CODEC_DATA_NOT_PROCESSED	12
#define TX_CODEC_DATA_NOT_PROCESSED	13
#define RADIO_BAD					14
#define RECEIVER_ERROR				15
#define TRANSMITTER_ERROR			16
#define RECEIVER_BAD				17
#define TRANSMITTER_BAD				18
#define CANT_TALK_TO_RADIO_MODEM	19
#define RAIO_MISSING_DETECT_FAILED	20
#define TRANSMIT_INHIBITED			21

// Radio Status

#define RADIO_STATUS				0
#define RX_SYNTH_NOT_LOCKED			1
#define TX_SYNTH_NOT_LOCKED			2
#define RX_SYNTH_LOCKING			3
#define TX_SYNTH_LOCKING			4
#define RX_SYNTH_UNABLE_TO_LOCK		5
#define TX_SYNTH_UNABLE_TO_LOCK		6
#define RX_TUNE_FAILED				7
#define RADIO_EEPROM_FAILURE		8
#define RADIO_DCXO_FAILURE			9
#define RADIO_IN_DEBUG_MODE			10
#define BAD_ASD_CHECKSUM			11
#define BAD_ASD_DATA				12
#define TX_DIAGNOSTIC_INVALID		13
#define RADIO_FIRMWARE_INCOMPATIBLE	14


#endif /*__GLOBALS_H_*/
