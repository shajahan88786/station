
#include "header.h"


void vfnFormAndTransDataLogSigPkt(void)
{
	BITSTUFFINIT(0,7)
	unsigned char dataLogPkt[25],i=0;
	unsigned long SysTime = 0;

	dataLogPkt[0] = '$';
	dataLogPkt[1] = DATALOG_SIGPKT;
	

	SysTime |= bcdToDec(Read_Rtc(0XD0,0X02));//RTC_HOUR;
	SysTime = SysTime<<6;
	SysTime	|= bcdToDec(Read_Rtc(0XD0,0X01));//RTC_MIN;
	SysTime = SysTime<<6;
	SysTime	|= bcdToDec(Read_Rtc(0XD0,0X00));//RTC_SEC;
	SysTime = SysTime<<7;
	SysTime	|= (unsigned char)(((labs(SpoiGetSysTICs()-PPS_Clock))%1000)/10 );//for millisec
	InsertBits(0,  24, &dataLogPkt[2],SysTime);
	dataLogPkt[5] = stSelfInfo.stationId;
	dataLogPkt[6] = SigStatus.ucNoOfSignal;	
	for(i = 0; i<SigStatus.ucNoOfSignal; i++)
	{
		InsertBits(ucBit,  4, &dataLogPkt[ucByte], SigStatus.ucCurSigAsp[i]);
		BITSTUFFINC(4);
	}
	ComputeCRC(dataLogPkt, ucByte);
	dataLogPkt[ucByte+2] = '&';
		
	CommTransmitMessage(ISP_PORT,dataLogPkt,ucByte+2);
	
}

void vfnTransmitDataloggerStnPkt(void)
{
	unsigned long SysTime = 0;
	unsigned char siNoOfBytes = 0;
	
	dataLoggerPkt[0] = '$';
	dataLoggerPkt[1] = DATALOG_STNTX;	
	
	siNoOfBytes = 16 * (ExtractBits(4,3,&dataLoggerPkt[5]) + 1);

	if (0 ==siNoOfBytes)
		return;

	SysTime |= bcdToDec(Read_Rtc(0XD0,0X02));//RTC_HOUR;
	SysTime = SysTime<<6;
	SysTime	|= bcdToDec(Read_Rtc(0XD0,0X01));//RTC_MIN;
	SysTime = SysTime<<6;
	SysTime	|= bcdToDec(Read_Rtc(0XD0,0X00));//RTC_SEC;
	if(SysTime%2)
		SysTime -= 1;
	SysTime = SysTime<<7;
	SysTime	|= (unsigned char)(((labs(SpoiGetSysTICs()-PPS_Clock))%1000)/10 );//for millisec
	InsertBits(0,  24, &dataLoggerPkt[2],SysTime);
	ComputeCRC(dataLoggerPkt, siNoOfBytes+5);
	dataLoggerPkt[siNoOfBytes+7] = '&';
	CommTransmitMessage(ISP_PORT,dataLoggerPkt,siNoOfBytes+7);
}

void processAuthenticationKeyRequest(void)
{
	unsigned char i =0;
	Authentication_KEY_comSend.AuthKeyReqPkt[0] = '$'; Authentication_KEY_comSend.AuthKeyReqPkt[1] = 0x02 ; Authentication_KEY_comSend.AuthKeyReqPkt[2] = 0x06; Authentication_KEY_comSend.AuthKeyReqPkt[3] = 0x07;
	Authentication_KEY_comSend.AuthKeyReqPkt[4] = 0xFF; 
	ComputeCRC(Authentication_KEY_comSend.AuthKeyReqPkt,5);
	Authentication_KEY_comSend.AuthKeyReqPkt[7] = '&';
	printf("\nAuthKeyReqPkt:");
	for(i = 0; i < 7; i++)
		printf("0x%x ",Authentication_KEY_comSend.AuthKeyReqPkt[i]);	
	printf("\nReq Pkt crc:0x%X  0x%X\n",Authentication_KEY_comSend.AuthKeyReqPkt[5],Authentication_KEY_comSend.AuthKeyReqPkt[6]);
	//TransmitCanPkt(REQ_PKT_ID);	
}
