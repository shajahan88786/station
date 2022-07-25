#include "header.h"


unsigned char FormSlotControlPkt = 0;

/********************************************************************************
 *	Function Name :	extractLocoPacket
 *	Description		: Extract the loco parameters received from loco radio packet
										and transmit the same to Station LPM through CAN	
 *	Arguemnts			:	Data recieved from port,Haeder strucure,no. of bytes received
 *	Return				:	void
********************************************************************************/
void extractLocoPacket(unsigned char *pszMsg,
											HEADER_t * pstRcv,
											short int iRcvdBytes,unsigned char ucPacketType)
											
{
	
	unsigned char i = 0;
	
	BITSTUFFINIT(0,3)

	ucBit = 4, ucByte = 3;
	
	stLocMsg.uiSourceID	= ExtractBits(ucBit,17,&pszMsg[ucByte]);
	stStnNmsMsg.locoId=	stLocMsg.uiSourceID;
	BITSTUFFINC(17)

	stLocMsg.ulAbsLoc	= ExtractBits(ucBit,22,&pszMsg[ucByte]);
	BITSTUFFINC(22)

	//printf("\nRecieved Loco Pkt %d, ulAbsLoc: %ld",stLocMsg.uiSourceID,stLocMsg.ulAbsLoc);
	//printf(" LOcotimeflag is %d ",timeflag);
	
	stLocMsg.uiTrainLength	= ExtractBits(ucBit,11,&pszMsg[ucByte]);
	BITSTUFFINC(11)

	stLocMsg.ucTrainSpeed	= ExtractBits(ucBit,8,&pszMsg[ucByte]);
	BITSTUFFINC(8)

	stLocMsg.ucTrafficDir	= ExtractBits(ucBit,2,&pszMsg[ucByte]);
	BITSTUFFINC(2)

	stLocMsg.ucEmergencyStatus	= ExtractBits(ucBit,3,&pszMsg[ucByte]);
	BITSTUFFINC(3)

	stLocMsg.ucMode	= ExtractBits(ucBit,4,&pszMsg[ucByte]);
	BITSTUFFINC(4)

	stLocMsg.ucLastRFIDTAG	= (unsigned short)ExtractBits(ucBit,10,&pszMsg[ucByte]);
	BITSTUFFINC(10)
//	printf("TAG ID %d\n",stLocMsg.ucLastRFIDTAG);
	stLocMsg.ucTIN	= ExtractBits(ucBit,7,&pszMsg[ucByte]);
	BITSTUFFINC(7)

//	stLocMsg.ucRecByLoco	= ExtractBits(ucBit,2,&pszMsg[ucByte]);
//	BITSTUFFINC(3)
//	stLocMsg.ucLastTrackProofID = ExtractBits(ucBit,4,&pszMsg[ucByte]);
//	BITSTUFFINC(3)

	stLocMsg.ucRecByLoco	= ExtractBits(ucBit,3,&pszMsg[ucByte]);
	BITSTUFFINC(3)
	stLocMsg.ucProfileID    = ExtractBits(ucBit,6,&pszMsg[ucByte]);
	BITSTUFFINC(6)
//	printf("\n******** stLocMsg.ucProfileID is %d",stLocMsg.ucProfileID);

	stLocMsg.ucStaticProffReq = ExtractBits(ucBit,1,&pszMsg[ucByte]);
	BITSTUFFINC(1)
	
	if( 0 == stLocMsg.ucStaticProffReq)
	{
	   uiDestnationLOcoID          = stLocMsg.uiSourceID;
	}	

	BITSTUFFINC(6)

	
	if(( AUTHENTICATION_PACKET_FROM_LOCO_TCAS == ucPacketType) && (0 != stLocMsg.uiSourceID))
	{
//		FormSlotControlPkt = 1;
		stLocMsg.usLocoRandomNmbr = ExtractBits(ucBit,16,&pszMsg[ucByte]);
//		stLocMsg.usLocoRandomNmbr = pszMsg[iRcvdBytes-3];
//		stLocMsg.usLocoRandomNmbr = ((stLocMsg.usLocoRandomNmbr << 8)&0xFF00);
//		stLocMsg.usLocoRandomNmbr |= pszMsg[iRcvdBytes-2];

		stLocMsg.ucAthenticFlag = 1;
		
		for(i=0; i<MAX_NO_OF_LOCOS; i++)
		{
			if(stLocMsg.uiSourceID == siginfo[i].ulLocoId)
			{
				stLocMsg.usSTNRandomNmbr = siginfo[i].usSTNRandomNmbr;
				break;
			}
		}
		if(i == MAX_NO_OF_LOCOS)
			stLocMsg.usSTNRandomNmbr = ((rand() % 0xFFFF));

		//printf("\nReceived Loco Random Number: %x\n",stLocMsg.usLocoRandomNmbr);
		//printf("Generated Loco Random Number: %x\n",stLocMsg.usSTNRandomNmbr);
	}
  else
	{
//		FormSlotControlPkt = 0;
		stLocMsg.ucAthenticFlag = 0;
		for(i=0; i<MAX_NO_OF_LOCOS; i++)
		{
			if(stLocMsg.uiSourceID == siginfo[i].ulLocoId)
			{
				stLocMsg.usLocoRandomNmbr = siginfo[i].usLocoRandomNumbr;	
				stLocMsg.usSTNRandomNmbr = siginfo[i].usSTNRandomNmbr;	
				break;
			}
		}	
	}
	

	stLocMsg.uiFrameNum = pstRcv->uiFrameNum;

	if( 3 == gucSelfSlot)
 {
		//printf("\n################### MIE3 TRANSMITTING LOCO PKT###################\n");
		TransmitCanPkt(LOCO_INFO_PKT);
 }
 if( 4 == gucSelfSlot)
 {
		//printf("\n################### MIE4 TRANSMITTING LOCO PKT###################\n");
		TransmitCanPkt(LOCO_INFO_PKT_2); 
 }
}


/********************************************************************************
 *	Function Name :	getLocoIndex
 *	Description		: Extract the loco parameters received from loco radio packet
										and transmit the same to Station LPM through CAN	
 *	Arguemnts			:	Data recieved from port,Haeder strucure,no. of bytes received
 *	Return				:	void
********************************************************************************/
unsigned char getLocoIndex(unsigned long ulLocoId)
{
	unsigned char ucFirstFreeLoc = 	MAX_NO_OF_LOCOS, i = 0;
	for(i=0;i<MAX_NO_OF_LOCOS;i++)
	{
		if(siginfo[i].ulLocoId == ulLocoId)
		{
			return i;
		}
		if((MAX_NO_OF_LOCOS == ucFirstFreeLoc) &&
			((0 == siginfo[i].ulLocoId) || (0 == siginfo[i].ucPreferredTxWindow)))
		{
			ucFirstFreeLoc = i;
			gucNoOfLoco_sig++;
		}
	}
	return ucFirstFreeLoc;
}

/*unsigned char getTrnLocoIndex(unsigned long ulLocoId)
{
	unsigned char ucFirstFreeLoc = 	MAX_TRNLEN_LOCO, i = 0;
	for(i=0;i<MAX_TRNLEN_LOCO;i++)
	{
		if(trnLenInfo[i].ulLocoId == ulLocoId)
		{
			return i;
		}
		if((MAX_TRNLEN_LOCO == ucFirstFreeLoc) &&
			((0 == trnLenInfo[i].ulLocoId) || (2 == trnLenInfo[i].ucType)))
		{
			ucFirstFreeLoc = i;
		}
	}
	return ucFirstFreeLoc;
}*/

#ifdef LOCO_SIMULATE
void vfnSimulatedLocoPkt1(void)
{
	static unsigned long simLocoCLk = 0;
	
	if(SpoiElapsTICs(simLocoCLk) < 5000)
		return;
	
	simLocoCLk = SpoiGetSysTICs();
		
	stLocMsg.uiSourceID	= 12345;
	stLocMsg.uiFrameNum = getFrameNum();
	stLocMsg.dir				= DN;
	stLocMsg.ucABUIsolation = 0;
	stLocMsg.ucEmergencyStatus = 0x00;
	
	stLocMsg.ucLastRFIDTAG 	= 134;
	
	stLocMsg.ucTIN			= 125;
	stLocMsg.ulAbsLoc		= 93780;
	stLocMsg.ucMode			= 1;
	stLocMsg.ucRecByLoco	= 0;
	stLocMsg.ucTrafficDir 	= DN;
	stLocMsg.uiTrainLength 	= 50;
	stLocMsg.ucTrainSpeed	= 0;
	
	stLocMsg.usSTNRandomNmbr	= 0x1234;
	stLocMsg.usLocoRandomNmbr	= 0x5678;	

	stLocMsg.ucAthenticFlag = 0;
	
	TransmitCanPkt(LOCO_INFO_PKT);
}

void vfnSimulatedLocoPkt2(void)
{
	static unsigned long simLocoCLk = 0;
	
	if(SpoiElapsTICs(simLocoCLk) < 5000)
		return;
	
	simLocoCLk = SpoiGetSysTICs();
		
	stLocMsg.uiSourceID	= 28016;
	stLocMsg.uiFrameNum = getFrameNum();
	stLocMsg.dir				= DN;
	stLocMsg.ucABUIsolation = 0;
	stLocMsg.ucEmergencyStatus = 0x00;
	
	stLocMsg.ucLastRFIDTAG 	= 110;
	
	stLocMsg.ucTIN			= 26;
	stLocMsg.ulAbsLoc		= 90960;
	stLocMsg.ucMode			= 1;
	stLocMsg.ucRecByLoco	= 0;
	stLocMsg.ucTrafficDir 	= DN;
	stLocMsg.uiTrainLength 	= 50;
	stLocMsg.ucTrainSpeed	= 0;
	
	stLocMsg.usSTNRandomNmbr	= 0x4321;
	stLocMsg.usLocoRandomNmbr	= 0x8765;	 

	stLocMsg.ucAthenticFlag = 0;
	
	TransmitCanPkt(LOCO_INFO_PKT);
}

void vfnSimulatedLocoPkt3(void)
{
	static unsigned long simLocoCLk = 0;
	
	if(SpoiElapsTICs(simLocoCLk) < 5000)
		return;
	
	simLocoCLk = SpoiGetSysTICs();
		
	stLocMsg.uiSourceID	= 13418;
	stLocMsg.uiFrameNum = getFrameNum();
	stLocMsg.dir				= DN;
	stLocMsg.ucABUIsolation = 0;
	stLocMsg.ucEmergencyStatus = 0x00;
	
	stLocMsg.ucLastRFIDTAG 	= 78;
	
	stLocMsg.ucTIN			= 29;
	stLocMsg.ulAbsLoc		= 90790;
	stLocMsg.ucMode			= 1;
	stLocMsg.ucRecByLoco	= 0;
	stLocMsg.ucTrafficDir 	= DN;
	stLocMsg.uiTrainLength 	= 50;
	stLocMsg.ucTrainSpeed	= 0;
	
	stLocMsg.usSTNRandomNmbr	= 0x4312;
	stLocMsg.usLocoRandomNmbr	= 0x8756;  

	stLocMsg.ucAthenticFlag = 0;
	
	TransmitCanPkt(LOCO_INFO_PKT);
}


void vfnSimulatedLocoPkt4(void)
{
	static unsigned long simLocoCLk = 0;
	
	if(SpoiElapsTICs(simLocoCLk) < 5000)
		return;
	
	simLocoCLk = SpoiGetSysTICs();
		
	stLocMsg.uiSourceID	= 13417;
	stLocMsg.uiFrameNum = getFrameNum();
	stLocMsg.dir				= DN;
	stLocMsg.ucABUIsolation = 0;
	stLocMsg.ucEmergencyStatus = 0x00;
	
	stLocMsg.ucLastRFIDTAG 	= 89;
	
	stLocMsg.ucTIN			= 31;
	stLocMsg.ulAbsLoc		= 90850;
	stLocMsg.ucMode			= 1;
	stLocMsg.ucRecByLoco	= 0;
	stLocMsg.ucTrafficDir 	= DN;
	stLocMsg.uiTrainLength 	= 50;
	stLocMsg.ucTrainSpeed	= 0;
	
	stLocMsg.usSTNRandomNmbr	= 0x2134;
	stLocMsg.usLocoRandomNmbr	= 0x6578;  

	stLocMsg.ucAthenticFlag = 0;
	
	TransmitCanPkt(LOCO_INFO_PKT);
}


void vfnSimulatedLocoPkt5(void)
{
	static unsigned long simLocoCLk = 0;
	
	if(SpoiElapsTICs(simLocoCLk) < 5000)
		return;
	
	simLocoCLk = SpoiGetSysTICs();
		
	stLocMsg.uiSourceID	= 13444;
	stLocMsg.uiFrameNum = getFrameNum();
	stLocMsg.dir				= DN;
	stLocMsg.ucABUIsolation = 0;
	stLocMsg.ucEmergencyStatus = 0x00;
	
	stLocMsg.ucLastRFIDTAG 	= 94;
	
	stLocMsg.ucTIN			= 33;
	stLocMsg.ulAbsLoc		= 90960;
	stLocMsg.ucMode			= 1;
	stLocMsg.ucRecByLoco	= 0;
	stLocMsg.ucTrafficDir 	= DN;
	stLocMsg.uiTrainLength 	= 50;
	stLocMsg.ucTrainSpeed	= 0;
	
	stLocMsg.usSTNRandomNmbr	= 0x2314;
	stLocMsg.usLocoRandomNmbr	= 0x6758;

	stLocMsg.ucAthenticFlag = 0;
	
	TransmitCanPkt(LOCO_INFO_PKT);
}
/*
void vfnSimulatedLocoPkt(void)
{
	static unsigned long simLocoCLk = 0;
	
	if(SpoiElapsTICs(simLocoCLk) < 5000)
		return;
	
	simLocoCLk = SpoiGetSysTICs();
		
	stLocMsg.uiSourceID	= 12345;
	stLocMsg.uiFrameNum = getFrameNum();
	stLocMsg.dir				= DN;
	stLocMsg.ucABUIsolation = 0;
	stLocMsg.ucEmergencyStatus = 0x00;
	
	stLocMsg.ucLastRFIDTAG 	= 5;
	
	stLocMsg.ucTIN			= 124;
	stLocMsg.ulAbsLoc		= 74270;
	stLocMsg.ucMode			= 1;
	stLocMsg.ucRecByLoco	= 0;
	stLocMsg.ucTrafficDir 	= DN;
	stLocMsg.uiTrainLength 	= 50;
	stLocMsg.ucTrainSpeed	= 0;
	
	stLocMsg.usSTNRandomNmbr	= 0x1234;
	stLocMsg.usLocoRandomNmbr	= 0x5678;
	stLocMsg.ucAthenticFlag = 0;
	
	TransmitCanPkt(LOCO_INFO_PKT);
}  */
#endif
void delSigInfoNodes(void)
{
	unsigned char i = 0;
	for(i=0;i<MAX_NO_OF_LOCOS;i++)
	{
		if(siginfo[i].ulLocoId == 0)
				continue;
		if((labs(SpoiGetSysTICs() - sigUpdateTime[i])) > 15000)
		{
			gucNoOfLoco_sig--;
			printf("Deleted Loco %ld on Timeout \n",siginfo[i].ulLocoId);
			memset(&siginfo[i], 0, sizeof(SIGINFO_t));
		}
		
	}
}
#ifdef LANDMARKPKT
unsigned char getTsrLocoIndex(unsigned long ulLocoId)
{
	unsigned char ucFirstFreeLoc = 	MAX_LANDMRK_LOCO, i = 0;
	for(i=0;i<MAX_LANDMRK_LOCO;i++)
	{
		if(landMarkInfo[i].ulLocoId == ulLocoId)
		{
			return i;
		}
		if((MAX_TRNLEN_LOCO == ucFirstFreeLoc) &&
			((0 == landMarkInfo[i].ulLocoId) || (0 == landMarkInfo[i].ucLMInfoCount)))
		{
			ucFirstFreeLoc = i;
		}
	}
	return ucFirstFreeLoc;
}

#endif

void updateTrainLenStat(TRNLEN_t tempTrnLenInfo)
{
	unsigned char index;
	index = getTrnLocoIndex(tempTrnLenInfo.ulLocoId);
	
	trnLenStat[index].ulLocoId = tempTrnLenInfo.ulLocoId;
	trnLenStat[index].ucType	 = tempTrnLenInfo.ucType;
	//trnLenStat[index].iRefFrameNum = getFrameNum();
	trnLenStat[index].iRefFrameNum = GPSframeNo;
	trnLenStat[index].ucOffset = (unsigned char)(labs((SpoiGetSysTICs() - PPS_Clock)%1000)/10);
	trnLenStat[index].ucReTxCnt= 0;
}

void updadeTrnLenNodes(void)
{
	unsigned char i = 0;
	for(i = 0 ; i<MAX_TRNLEN_LOCO ; i++)
	{
		if((0 == trnLenStat[i].ulLocoId) || (2 == trnLenStat[i].ucType))
			continue;
		
		if(trnLenStat[i].ucReTxCnt >= 5)
			trnLenStat[i].ucType = 2;
			
		trnLenStat[i].ucReTxCnt++;		
	}
}


unsigned char getTrnLocoIndex(unsigned long ulLocoId)
{
	unsigned char ucFirstFreeLoc = 	MAX_TRNLEN_LOCO, i = 0;
	for(i=0;i<MAX_TRNLEN_LOCO;i++)
	{
		if(trnLenStat[i].ulLocoId == ulLocoId)
		{
			return i;
		}
		if((MAX_TRNLEN_LOCO == ucFirstFreeLoc) &&
			((0 == trnLenStat[i].ulLocoId) || (2 == trnLenStat[i].ucType)))
		{
			ucFirstFreeLoc = i;
		}
	}
	return ucFirstFreeLoc;
}

/* End of File */

