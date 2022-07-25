
#ifndef _STATION_H_
#define _STATION_H_
#include "header.h"
#include "stdint.h"
extern uint32_t PPS_Clock;
extern uint32_t PPS_ONE_OK_Clock;
extern uint32_t GPSclk;

#define MAX_SIGNALS						30 

typedef struct
{

    unsigned char ucPktType;
    unsigned char ucPktLength;
	unsigned int uiFrameNum;
} HEADER_t;

typedef struct
{
	unsigned char ucRadioModemHealth;
}RADIOMODEMHEALTH_t;

// Radio Modem failure status
typedef struct
{
	unsigned char ucRadioFailStatus;
}CAN_RADIOMODEM_FAIL_STATUS_t;


extern unsigned long stnTimeSlot[79];
extern unsigned char gcMidBlockSectionSlots[4];	
extern unsigned char gcEmergencySlots[4];
extern unsigned char BroadcastSlot[8];
//extern unsigned long stnTimeSlot[9];

#pragma pack(1)
typedef struct
{
	unsigned short stationId;
	unsigned char ucStnVer;
	unsigned char ucSos;
	unsigned long ulAbsLoc;
	unsigned char ucSelfTimeSlot;
	unsigned char ucFreqPair;
}SELFINFO_t;

typedef struct
{
	unsigned char ucNoOfSignal;
	unsigned char ucCurSigAsp[MAX_SIGNALS];
} CanSigStatus;
#pragma pack(4)
extern SELFINFO_t stSelfInfo,tempStSelfInfo[2];
extern CanSigStatus SigStatus,tempSigStatus[2];
typedef struct 
{
	unsigned char MsgType;				//1-byte
	unsigned char SrcID;				//1 -byte
	unsigned char DesID;				//1-byte
	unsigned char NofKeySets;			//1-byte
	unsigned char KeySet_Vstart[4];		//4-byte
	unsigned char KeySet_Vend[4];		//4-byte
	unsigned char KeySet[2][16];		//32-byte
}Authentication_KEY_t;

//Radio_Modem_Status Logging For Datalogger
typedef struct
{
	signed int temp;
	float RxLineCntlVtg;
	unsigned char InstantaneousTxRevPower;
	unsigned char InstantaneousTxFowPower;
	float TxCntlLineVtg;
	unsigned char PA_Supply_Vtg;
	unsigned char InstantaneousTxPACurrent;
	unsigned char VtgAppliedToModem;
	unsigned char PA_Temperature;
	float TxRevPowerfromlastTx;
	float TxForPowerfromlastTx;
	float TxPACurrentfromlastTx;
	short int RSSI; 
	unsigned int Modem_Status;
	unsigned int Radio_Status;

}CAN_RADIOMODEM_STATUS_LOG_t;


typedef struct
{
	unsigned char AuthKeyReqPkt[50];
}Authentication_KEY_comSend_t;
#endif/*_STATION_H_*/


/*End Of File*/


