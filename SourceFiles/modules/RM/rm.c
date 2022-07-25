#include"header.h"
#define SOP1 0xA5
#define SOP2 0xC3
#define DUMMY 0x7E

#define TRAINLENGTHDEBUG
unsigned char ucHealthReplayASCII[400]={0},ModemDiagnosticReqFlag=0;
unsigned long RmReqClk=0;


extern unsigned char locoPresentFlag;
//extern LOCO_NMS_MSG stLocoNmsMsg;
extern STN_NMS_MSG stStnNmsMsg;

void processReceiveMessage(unsigned char *szReceivedMessage)
{
	short int iNoOfBytes = 0;
	unsigned char pktToDataLoggerRx[25];
	unsigned long SysTime = 0;
	static unsigned long locoNmsClk =0;

	iNoOfBytes = rReadAndFormMessageNoDle(RXPORT, szReceivedMessage, 2, CRCHK, 50);
//iNoOfBytes = rReadAndFormMessage_Generic(RM2PORT, szReceivedMessage, 2, CRCHK, 50);
	stStnNmsMsg.locoPktLen = iNoOfBytes;

	if (iNoOfBytes > 0) 
	{
		locoPresentFlag =1;
		stStnNmsMsg.locoPktLen = iNoOfBytes+1;
		memcpy(stStnNmsMsg.RxLocoMessage,szReceivedMessage,iNoOfBytes+1);
//		printf("\nREC Number of bytes =%d\n",iNoOfBytes);
		AnalyzeHeader(szReceivedMessage,iNoOfBytes);
		pktToDataLoggerRx[0] = '$';
		pktToDataLoggerRx[1] = DATALOG_STNRX;		
		SysTime |= bcdToDec(Read_Rtc(0XD0,0X02));//RTC_HOUR;
		SysTime = SysTime<<6;
		SysTime	|= bcdToDec(Read_Rtc(0XD0,0X01));//RTC_MIN;
		SysTime = SysTime<<6;
		SysTime	|= bcdToDec(Read_Rtc(0XD0,0X00));//RTC_SEC;
		SysTime = SysTime<<7;
		if(SysTime%2)
			SysTime -= 1;
		SysTime	|= (unsigned char)(((labs(SpoiGetSysTICs()-PPS_Clock))%1000)/10 );//for millisec
		InsertBits(0,  24, &pktToDataLoggerRx[2],SysTime);		
		memcpy(&pktToDataLoggerRx[5],szReceivedMessage,iNoOfBytes);
		ComputeCRC(pktToDataLoggerRx, iNoOfBytes+5);
		pktToDataLoggerRx[iNoOfBytes+7] = '&';
		if( 3 == gucSelfSlot)
		TransmitCanPkt(STN_NMS_PKT);
//		printf("\n Sent1 Can NMS Stn PKT stn %d loc %d\n",stStnNmsMsg.Paketlength,stStnNmsMsg.locoPktLen);
		locoNmsClk = SpoiGetSysTICs();
	
		CommTransmitMessage(ISP_PORT,pktToDataLoggerRx,iNoOfBytes+7);		
	}
	 if((SpoiElapsTICs(locoNmsClk) >30000)&&((0 == siginfo[0].ulLocoId)))
	{
	    locoPresentFlag =0;
	 // printf("\nLoco node deleted\n");
		if(iNoOfBytes > 0)
		stStnNmsMsg.locoPktLen = iNoOfBytes;
		memset(stStnNmsMsg.RxLocoMessage,0,50);	
	}
	return;
}



unsigned short int AnalyzeHeader(unsigned char *pszMessage, short int iRcvdBytes)
{
    unsigned short int iRetVal = 1;
	unsigned char ucBit = 0,ucByte = 0, i=0, j=0, k=0;
	short int iSize = 0;
																	  
	HEADER_t stRcvMsg;
	
	ucBit = 0, ucByte = 0, iSize = 4;
	stRcvMsg.ucPktType = ( char )ExtractBits(ucBit, iSize, &pszMessage[ucByte]);
	ucByte = (unsigned char)((short int)ucByte+(((short int)ucBit+iSize)/8));
	ucBit = (unsigned char)((short int)(ucBit+iSize)%8);

	//iSize = 3;
	iSize = 7;
	stRcvMsg.ucPktLength = ( unsigned char )ExtractBits(ucBit, iSize, &pszMessage[ucByte]);
	ucByte = (unsigned char)((short int)ucByte+(((short int)ucBit+iSize)/8));
	ucBit = (unsigned char)((short int)(ucBit+iSize)%8);
	
	iSize = 17;
	stRcvMsg.uiFrameNum = ( unsigned int )ExtractBits(ucBit, iSize, &pszMessage[ucByte]);
	ucByte = (unsigned char)((short int)ucByte+(((short int)ucBit+iSize)/8));
	ucBit = (unsigned char)((short int)(ucBit+iSize)%8);

	//printf("stRcvMsg.uiFrameNum is %d\n",stRcvMsg.uiFrameNum);
     k=ucByte; j=ucBit;
		 
	switch (stRcvMsg.ucPktType)
	{
/*	case SIGNALLING_INFO_BY_STN_ILC_IBS:
		printf("\nRcvd SIGNALLING_INFO_BY_STN_ILC_IBS ...\n");
		break;*/
	
/*	case GEN_DESCRIPTOR_PKT_BY_STN_ILC_IBS:
		printf("\nRcvd GEN_DESCRIPTOR_PKT_BY_STN_ILC_IBS...\n");
		break;*/
	
/*	case REDIRECT_REGULAR_PACKET_BY_LOCO:
	case REDIRECT_EMERGENCY_PACKET_BY_LOCO:
		if (REDIRECT_REGULAR_PACKET_BY_LOCO == stRcvMsg.ucPktType)
		{
			printf("\nRcvd Regular packet from Loco TCAS...\n");
		}
		else
		{
			printf("\nRcvd Emergency packet from Loco TCAS...\n");
		}
		break;*/
	
	case PACKET_FROM_LOCO_TCAS:
			extractLocoPacket(pszMessage, &stRcvMsg, iRcvdBytes,PACKET_FROM_LOCO_TCAS);
		break;
	
	case AUTHENTICATION_PACKET_FROM_LOCO_TCAS:

		for(i=0; i<MAX_NO_OF_LOCOS; i++) 
		{
			if(ExtractBits(j, 17, &pszMessage[k]) == siginfo[i].ulLocoId)
			{
			  //printf("\n labs(GPSframeNo - siginfo[i].uiFrameNum )/2) is %d",labs(GPSframeNo - siginfo[i].uiFrameNum )/2);
				
				if(((unsigned char)(labs(GPSframeNo - siginfo[i].uiFrameNum )/2) < 5)||(siginfo[i].ucNextSigIntlkg == 1))
				{
				 return 0;
				}
				else
					break;
			}
		}
		//printf("\n Received Authentication With T2TC %ld",T2TC);	  
		extractLocoPacket(pszMessage, &stRcvMsg, iRcvdBytes,AUTHENTICATION_PACKET_FROM_LOCO_TCAS);
		break;
	
	/*case TRAIN_LEN_START_REF_PACKET_BY_STN:
		printf("\nRcvd TRAIN_LEN_START_REF_PACKET_BY_STN...\n");
		break;*/

	/*case TRAIN_LEN_STOP_REF_PACKET_BY_STN:
		break;*/


	default:
		iRetVal = 0;
		//printf("\nNo Match Packet..\n");
		break;
	}

	return iRetVal;
}
#ifdef RXDEBUG
	#undef RXDEBUG
#endif

short int rReadAndFormMessageNoDle(short int iPort,			
							  unsigned char *pcReadMsg, 
							  short int iIntegritySize, 
							  short int iWhichIntegrity, 
							  short int iMaxSize)
{
	unsigned char ucRByte = 0;
    short int iIntegrityByteLoc = 0;
	static unsigned char suc_RcvStatus = ONE;
	int iNrepBytes = 0;
	static unsigned short int i = ZERO;
	static short int pktlength;
   // i = 0;	
    while(Comm_ComDataReady(iPort)) 
    {
		#ifdef WATCHDOG
			//SpoiWDTReload();		
			CommWatchDogStrobe();			/* Watchdog Strobe Signal */
		#endif /*WATCHDOG*/

		ucRByte = Comm_ComGetByte(iPort);  
		
	//	#ifdef RXDEBUG
	//	printf("[%d]%x .",i,ucRByte);
	//	#endif
		
		switch(suc_RcvStatus)
		{
		    case 1: 
				/* Receive Start of Message 
			     */
			    if(SOP1 == ucRByte)
			    {
					i = 0;
					suc_RcvStatus = 2;
					//printf("\n SOP1 is %d ",ucRByte);
			    }
			    break;

		    case 2: 
				/* Receive body of message or end of message 
			     */
			    switch(ucRByte)
				{
					case SOP2:
						i = 0;
						suc_RcvStatus = 3;
						//printf("\n SOP2 is %d ",ucRByte);
						break;

					default:
						i = 0;
						//printf("\n default SOP2 is %d ",ucRByte);
						suc_RcvStatus= 1;
						break;
				}
			    break;

		    case 3: 
				/* Receive body of message specially if $ or & are part of body
			     * i.e characters escaped with DLE 
				 */
					if(!(((ucRByte>>4) == 0x02) || ((ucRByte>>4) == 0x06)))
					{
						i = 0;
						suc_RcvStatus= 1;
						return 0;
						//break;
					}

					pcReadMsg[0] = ucRByte;
					//printf("\n  case 3 is %d ",ucRByte);
					i++ ;
					suc_RcvStatus = 4;
			    break;

		    case 4: 
				/* Receive body of message specially if $ or & are part of body
			     * i.e characters escaped with DLE 
				 */
					pcReadMsg[1] = ucRByte;
					pktlength = ((unsigned char)ExtractBits(4,7,&(pcReadMsg[0])));
					//printf("\n****Recv comPtr[iPort].pktLength : %d",comPtr[iPort].pktLength);

//Lekhya					pktlength -= 1 ;
					//printf("\n  case 4 is %d ",ucRByte);
					i++ ;
					suc_RcvStatus = 5;

			    break;

		    case 5: 
					pcReadMsg[i] = ucRByte;

					if (pktlength > i)
					{
						i++;
					}

					else if ((pktlength) == i )
					{

						//printf("\nReceived Packet Length : %d\n",pktlength);
						iIntegrityByteLoc = (pktlength) - 1;

						iNrepBytes = pktlength ;

						//printf("\n pktlength is %d ",pktlength);
						
						i = 0;
						suc_RcvStatus = 1;
						pktlength = 0;

						if(CheckIntegrity(pcReadMsg,iIntegrityByteLoc, iWhichIntegrity))
						{
							if( PACKET_FROM_LOCO_TCAS == ( char )ExtractBits(0, 4, &pcReadMsg[0]))
							{ 
								printf("\nREG PKT REC\n");
								if(0 == CheckMAC(pcReadMsg, iNrepBytes))
								{
									printf("\nMAC_CODE Failed\n");
									return 0;
								}
							
							}
							else if( AUTHENTICATION_PACKET_FROM_LOCO_TCAS == ( char )ExtractBits(0, 4, &pcReadMsg[0]))
								printf("\nATHEN PKT REC\n");
							else
								return 0;
							return iNrepBytes;
						}
						else
						{
							//fprintf(gfPktLog,"CRC FAIL\n");
							printf("\nReceived Paket CRC FAIL\n");
							
							return 0;
						}

					}

	
			   break;
		}

    }
	
    return 0;
}

unsigned int getFrameNum()
{
	unsigned int iRetVal = 0;
	unsigned char ucHour = 0,ucMin = 0,ucSec = 0;
//	unsigned char ucYear = 0, ucMonth = 0, ucDay = 0;
	
		ucSec=bcdToDec(Read_Rtc(0XD0,0X00)); // read sec
		ucMin=bcdToDec(Read_Rtc(0XD0,0X01)); // read min
		ucHour=bcdToDec(Read_Rtc(0XD0,0X02)); // read hour
					
		//rec_day_of_week=Read_Rtc(0XD0,0X03); // DAY OF WEEK
//		ucDay=bcdToDec(Read_Rtc(0XD0,0X04)); // date
//		ucMonth=bcdToDec(Read_Rtc(0XD0,0X05)); //month
//		ucYear=bcdToDec(Read_Rtc(0XD0,0X06)); //year

	
//	  ucDay 	= (ucDay/16) * 10 + (ucDay%16);
//	  ucMonth = (ucMonth/16) * 10 + (ucMonth%16);
//	  ucYear 	= (ucYear/16) * 10 + (ucYear%16);
//	  ucHour	= (ucHour/16) * 10 + (ucHour%16);
//	  ucMin		= (ucMin/16) * 10 + (ucMin%16);
//	  ucSec 	= (ucSec/16) * 10 + (ucSec%16);
	
//	ucHour = RTC_HOUR;	
//	ucMin  = RTC_MIN;
//	ucSec  = RTC_SEC;
	
//	printf("\nDate :%d/%d/%d, Time%d:%d:%d:",ucDay,ucMonth,ucYear,ucHour,ucMin,ucSec);


 	iRetVal = ((ucHour * 3600) + (ucMin * 60) + ucSec) + 1;
	if((iRetVal%2)== 0)
	{	
	iRetVal = iRetVal-1;
	return  iRetVal;
  }
	else
	return  iRetVal;	
	
}


unsigned char formStationPacket(unsigned char *ucstationPkt, unsigned char ucLocoIndex)
{
	unsigned char i = 0,j=0,ucPktLength,ucTLIndex = MAX_TRNLEN_LOCO,ucNoOfLocos = 0;
	unsigned int uiCurFrameNum = 0;
	unsigned char ucStartMacByte = 0;
	unsigned short MAC_CODE = 0;
	unsigned char ucNoOfValidLoco = 0;

//	static unsigned short locorandomnum =0;
//	static unsigned long locoid = 0;

	BITSTUFFINIT(0,0)


	memset(ucstationPkt, 0 , 256);

	for(i	= ucLocoIndex; i < MAX_NO_OF_LOCOS;	i++) 
	{ 
		if((0 == siginfo[i].ulLocoId) || (0 == siginfo[i].ucPreferredTxWindow))
			continue;
			
		if(1 == siginfo[i].ucAthenticFlag)
		{
			continue;
		}
		if((12+((ucNoOfLocos+1)*21)) <= 128)
			ucNoOfLocos++;
		ucNoOfValidLoco++;

	}
//#ifndef BROADCAST_PKT_IGNORE
//	if(0 == ucNoOfLocos)
//		return 0;	
//#endif


	InsertBits(ucBit,  4, &ucstationPkt[ucByte], STATION_PACKET);
	BITSTUFFINC(4);

	ucPktLength = (10 + (ucNoOfLocos*21) + 2 -1);

	InsertBits(ucBit, 7, &ucstationPkt[ucByte], ucPktLength);
	BITSTUFFINC(7);
	//printf("\n ucPktLength %d......",ucPktLength);
	if(SpoiElapsTICs(GPSclk)>(ONE_MIN))
	{
			GPSframeNo = 0;	
	}

	if(GPSframeNo > 3)
	{		
	 uiCurFrameNum = GPSframeNo;	
	 if((uiCurFrameNum%2)== 0)
	 uiCurFrameNum = uiCurFrameNum-1;
	 printf("\n GPS Frame No is %d",uiCurFrameNum);
	}
	if(GPSframeNo < 3)
	{
	  uiCurFrameNum = getFrameNum();
		printf("\n RTC Frame No is %d",uiCurFrameNum); 
	}
   uiframeno = uiCurFrameNum;

	InsertBits(ucBit,  17, &ucstationPkt[ucByte], uiCurFrameNum);
	BITSTUFFINC(17);

	InsertBits(ucBit,  16, &ucstationPkt[ucByte], stSelfInfo.stationId);                   
	BITSTUFFINC(16);

	InsertBits(ucBit,  3, &ucstationPkt[ucByte],stSelfInfo.ucStnVer);
	BITSTUFFINC(3);	

	InsertBits(ucBit,  22, &ucstationPkt[ucByte],stSelfInfo.ulAbsLoc);
	BITSTUFFINC(22);

	InsertBits(ucBit,  1, &ucstationPkt[ucByte],stSelfInfo.ucSos);
	BITSTUFFINC(1);	

	InsertBits(ucBit,  4, &ucstationPkt[ucByte],ucNoOfLocos);
	BITSTUFFINC(4)		    // Number of Locos 

	InsertBits(ucBit,  6, &ucstationPkt[ucByte],0);
	BITSTUFFINC(6)                                                                      
//printf("\n\n*************************************************************\n");
	for(i	= ucLocoIndex; i	< MAX_NO_OF_LOCOS;	i++) 
	{ 
		if((0 == siginfo[i].ulLocoId) || (0 == siginfo[i].ucPreferredTxWindow))
			continue;
			
		if(1 == siginfo[i].ucAthenticFlag)
			continue;

		j++;
		if(j > ucNoOfLocos)
			break;
		
		ucStartMacByte = 	ucByte;	
		//printf("\nInserted Loco Id : %d",siginfo[i].ulLocoId);
		
		InsertBits(ucBit,  17, &ucstationPkt[ucByte],siginfo[i].ulLocoId);
		BITSTUFFINC(17);	

		if ((uiCurFrameNum % 2) == 1)
		{
			uiCurFrameNum -= 1;
	    }
		if ((siginfo[i].uiFrameNum % 2) == 1)
		{
			siginfo[i].uiFrameNum -= 1;
		}	
		//printf("\tOffset : %d",(unsigned char)(labs(uiCurFrameNum -siginfo[i].uiFrameNum)/2));	
	    //printf("\tLoco frameNo : %d",siginfo[i].uiFrameNum);

		InsertBits(ucBit,  4, &ucstationPkt[ucByte],(unsigned char)(labs(uiCurFrameNum - siginfo[i].uiFrameNum )/2));
 		BITSTUFFINC(4);
		

		InsertBits(ucBit,  1, &ucstationPkt[ucByte],siginfo[i].ucCollision);
 		BITSTUFFINC(1);

//		#ifdef TRAINLENGTH
		ucTLIndex = getTrnLocoIndex(siginfo[i].ulLocoId);
		if((MAX_TRNLEN_LOCO != ucTLIndex) && (2 != trnLenStat[ucTLIndex].ucType)
				&& (trnLenStat[ucTLIndex].ulLocoId ==  siginfo[i].ulLocoId))
		{
			#ifdef TRAINLENGTHDEBUG
//			printf("\n*****\n******Train Len info Stuffing");
//			printf(":::Type : %d",trnLenStat[ucTLIndex].ucType);
//			printf(":::FrameNum : %ld",trnLenStat[ucTLIndex].iRefFrameNum);
//			printf(":::offset : %d\n*******",trnLenStat[ucTLIndex].ucOffset);	
			#endif //TRAINLENGTHDEBUG
//			InsertBits(ucBit,  1, &ucstationPkt[ucByte],AVAILABLE);
//  		BITSTUFFINC(1);			

			InsertBits(ucBit, 17, &ucstationPkt[ucByte],trnLenStat[ucTLIndex].iRefFrameNum);
			BITSTUFFINC(17);					

			InsertBits(ucBit, 8, &ucstationPkt[ucByte], trnLenStat[ucTLIndex].ucOffset);
			BITSTUFFINC(8);	

			InsertBits(ucBit,  1, &ucstationPkt[ucByte],trnLenStat[ucTLIndex].ucType);
			BITSTUFFINC(1);	
		}
		else
		{
			InsertBits(ucBit, 17, &ucstationPkt[ucByte],0x1FFFF);
			BITSTUFFINC(17);					

			InsertBits(ucBit, 8, &ucstationPkt[ucByte], 0xFF);
			BITSTUFFINC(8);	

			InsertBits(ucBit, 1, &ucstationPkt[ucByte], 0x01);
			BITSTUFFINC(1);			
		}
//		#else
//
//		InsertBits(ucBit,  1, &ucstationPkt[ucByte],0);
//  		BITSTUFFINC(1);
//		#endif
    locoPresentFlag = 1;
		InsertBits(ucBit,  6, &ucstationPkt[ucByte],siginfo[i].ucTypeOfSignal);
  		BITSTUFFINC(6);

		InsertBits(ucBit,  1, &ucstationPkt[ucByte],siginfo[i].ucSigDir);
  		BITSTUFFINC(1);

		InsertBits(ucBit,  4, &ucstationPkt[ucByte],siginfo[i].ucLineNumber);
  		BITSTUFFINC(4);

		InsertBits(ucBit,  5, &ucstationPkt[ucByte],siginfo[i].ucCurSigAspect);
  		BITSTUFFINC(5)

		InsertBits(ucBit,  5, &ucstationPkt[ucByte],siginfo[i].ucNextSigAspect);
  		BITSTUFFINC(5)

		InsertBits(ucBit,  16, &ucstationPkt[ucByte],(siginfo[i].uiMAwrtSig));
		 	BITSTUFFINC(16)
//		InsertBits(ucBit,  6, &ucstationPkt[ucByte],siginfo[i].uiGradMAwrtSig);
//  		BITSTUFFINC(6)

//		InsertBits(ucBit,  1, &ucstationPkt[ucByte],siginfo[i].ucNextSigIntlkg);
//  		BITSTUFFINC(1)


		if (ADJACENT_STATION == siginfo[i].ucNextSigIntlkg)
			InsertBits(ucBit,  16, &ucstationPkt[ucByte],siginfo[i].uiAppStnId);
		else
			InsertBits(ucBit,  16, &ucstationPkt[ucByte],0);	
		BITSTUFFINC(16)

		InsertBits(ucBit,  16, &ucstationPkt[ucByte],siginfo[i].uiDiffDistNextSig);                                               //ANAND
  		BITSTUFFINC(16)

		InsertBits(ucBit,  4, &ucstationPkt[ucByte],siginfo[i].ucToSpeed);
  		BITSTUFFINC(4)

		if (UNRESTRICTED != siginfo[i].ucToSpeed)
		{
			InsertBits(ucBit,  11, &ucstationPkt[ucByte],siginfo[i].uiDiffDistTo);
  			BITSTUFFINC(11)

			InsertBits(ucBit,  8, &ucstationPkt[ucByte],siginfo[i].ucToSpeedRelDist);                                           //ANAND
  			BITSTUFFINC(8)
		}
		else
		{
			InsertBits(ucBit,  11, &ucstationPkt[ucByte],0x7FF);
  			BITSTUFFINC(11)

			InsertBits(ucBit,  8, &ucstationPkt[ucByte],0xFF);                                           //ANAND
  			BITSTUFFINC(8)
		}

		InsertBits(ucBit,  6, &ucstationPkt[ucByte],siginfo[i].uiGradMAwrtSig);
 		BITSTUFFINC(6)

//		InsertBits(ucBit,  7, &ucstationPkt[ucByte],siginfo[i].ucPreferredTxWindow);                                       //ANAND
//   		BITSTUFFINC(7)
		
		if (ucBit > 0)
		{
		InsertBits(ucBit,  (8-ucBit), &ucstationPkt[ucByte],0x00);
    		BITSTUFFINC((8-ucBit))
		}
//		printf("\n********Station Packet of Loco %d ucStartMacByte:%d ucByte: %d\n",j,ucStartMacByte,ucByte);

		MAC_CODE = ComputeMAC_Code(ucstationPkt,ucStartMacByte,ucByte-1,siginfo[i].usLocoRandomNumbr,siginfo[i].ulLocoId);
		InsertBits(ucBit, 16, &ucstationPkt[ucByte],MAC_CODE);
		BITSTUFFINC(16)
		
	}
//printf("\n*************************************************************\n\n");
	if (ucBit > 0)
	{
		InsertBits(ucBit,  (8-ucBit), &ucstationPkt[ucByte],0x00);
    		BITSTUFFINC((8-ucBit))
	}
	/*	Padding 0's so as to make the packet(including 2 bytes CRC)
	 *	in chunks of 128 bits i.e.16 bytes 
	 */

	ComputeCRC(ucstationPkt, ucByte);

	if(ucNoOfValidLoco == ucNoOfLocos)
		return 0;
	else
		return i;
}


void formSlotControlPacket(void)
{
  	unsigned char i = 0,ucPktLength= 0;
	unsigned int uiCurFrameNum = 0;
	unsigned short MAC_CODE = 0;
	
	BITSTUFFINIT(0,0)
	memset(gucSlotControlPacket, 0 , 256);
	for(i=0; i<MAX_NO_OF_LOCOS; i++)
	{
		if((siginfo[i].ucAthenticFlag == 1)	&& (0 != siginfo[i].ulLocoId))
			break;		
	}
	if(MAX_NO_OF_LOCOS == i)
	{
		
		return;
	}
	//printf("\nForming Access Control Packet Loco %d\n",siginfo[i].ulLocoId);
	InsertBits(ucBit,  4, &gucSlotControlPacket[ucByte], 0x03);
	BITSTUFFINC(4);

	BITSTUFFINC(7);

  if(GPSframeNo > 3)
	{
		
	 	uiCurFrameNum = GPSframeNo;
		printf("\n GPS Frame No is %d",uiCurFrameNum);	
	}
	if((uiCurFrameNum%2)== 0)
	uiCurFrameNum = uiCurFrameNum-1;
	 if(GPSframeNo < 3)
	 {
	  printf("\n RTC Frame No is %d",uiCurFrameNum);	
	  uiCurFrameNum = getFrameNum();
	 }

	InsertBits(ucBit,  17, &gucSlotControlPacket[ucByte], uiCurFrameNum);
	BITSTUFFINC(17);

	InsertBits(ucBit,  16, &gucSlotControlPacket[ucByte], stSelfInfo.stationId);                    
	BITSTUFFINC(16);

	
	InsertBits(ucBit,  3, &gucSlotControlPacket[ucByte],stSelfInfo.ucStnVer);
	BITSTUFFINC(3);	

	InsertBits(ucBit,  22, &gucSlotControlPacket[ucByte],stSelfInfo.ulAbsLoc);
	BITSTUFFINC(22);

	InsertBits(ucBit,  17, &gucSlotControlPacket[ucByte],siginfo[i].ulLocoId);
	BITSTUFFINC(17);
//	stLocMsg.uiSourceID = 0;

	stSelfInfo.ucFreqPair =1;
	InsertBits(ucBit,  4, &gucSlotControlPacket[ucByte],stSelfInfo.ucFreqPair);
	BITSTUFFINC(4);

//	siginfo[i].ucPreferredTxWindow = 65;
	InsertBits(ucBit,  7, &gucSlotControlPacket[ucByte],siginfo[i].ucPreferredTxWindow);
	BITSTUFFINC(7);

	InsertBits(ucBit,  16, &gucSlotControlPacket[ucByte],siginfo[i].usSTNRandomNmbr);
	BITSTUFFINC(16)
	
	if (ucBit > 0)
	{
		InsertBits(ucBit,  (8-ucBit), &gucSlotControlPacket[ucByte],0x00);
    	BITSTUFFINC((8-ucBit))
	}

//	ucPktLength = ((ucByte + 2+ 2)/16) - 1;
	ucPktLength = (ucByte + 2+ 2-1);
	InsertBits(4, 7, &gucSlotControlPacket[0], ucPktLength);

	MAC_CODE = ComputeMAC_Code(gucSlotControlPacket,0,ucByte-1,siginfo[i].usLocoRandomNumbr,siginfo[i].ulLocoId);

	InsertBits(ucBit,  16, &gucSlotControlPacket[ucByte],MAC_CODE);
	BITSTUFFINC(16)

//	printf("CRC ucByte %d\n",ucByte);
	ComputeCRC(gucSlotControlPacket, ucByte);

}


unsigned char formEmergencyPacket()
{
	unsigned char i = 0, ucPktLength,ucNoOfLocos = 0;
	unsigned int uiCurFrameNum = 0;

//	static unsigned short locorandomnum =0;
//	static unsigned long locoid = 0;

	BITSTUFFINIT(0,0)

//	printf("\n******** Emergency Packet\n");
	memset(gucEmrgncyPkt, 0 , 256);
	printf("\n");
	
	if(0 == stSelfInfo.ucSos)
	{
		for(i = 0; i < MAX_NO_OF_LOCOS; i++) 
		{ 
			if((0 == siginfo[i].ulLocoId) || (0 == siginfo[i].ucPreferredTxWindow) || (0 == siginfo[i].ucCollision))
			{
//				printf("Loco Id : %d\n",siginfo[i].ulLocoId);
				continue;
			}
//			printf("Emergency Loco Id : %d\n",siginfo[i].ulLocoId);
			ucNoOfLocos++;
		}
		if(0 == ucNoOfLocos)
			return 0;	
	}


	InsertBits(ucBit,  4, &gucEmrgncyPkt[ucByte], EMERGENCY_PACKET);
	BITSTUFFINC(4);

	BITSTUFFINC(7);

	if(GPSframeNo > 3)
	{	
	 uiCurFrameNum = GPSframeNo;
	 printf("\nEmergency Packet GPS Frame No is %d",uiCurFrameNum);	
	}
	 if((uiCurFrameNum%2)== 0)
	 uiCurFrameNum = uiCurFrameNum-1;
	 if(GPSframeNo < 3)
	 {
	  printf("\nEmergency Packet RTC Frame No is %d",uiCurFrameNum);	
	  uiCurFrameNum = getFrameNum();
	 }

	InsertBits(ucBit,  17, &gucEmrgncyPkt[ucByte], uiCurFrameNum);
	BITSTUFFINC(17);

	InsertBits(ucBit,  16, &gucEmrgncyPkt[ucByte], stSelfInfo.stationId);                   
	BITSTUFFINC(16);

	InsertBits(ucBit,  3, &gucEmrgncyPkt[ucByte],stSelfInfo.ucStnVer);
	BITSTUFFINC(3);	

	InsertBits(ucBit,  22, &gucEmrgncyPkt[ucByte],stSelfInfo.ulAbsLoc);
	BITSTUFFINC(22);

	InsertBits(ucBit,  1, &gucEmrgncyPkt[ucByte],stSelfInfo.ucSos);
	BITSTUFFINC(1);	

   	ucNoOfLocos = 0;
	if(0 == stSelfInfo.ucSos)
	{   
		//printf("\n******* Forming Emergency Packet for Loco : ");
		for(i = 0; i < MAX_NO_OF_LOCOS;	i++) 
		{ 
			if((0 == siginfo[i].ulLocoId) || (0 == siginfo[i].ucPreferredTxWindow) || (0 == siginfo[i].ucCollision))
				continue;
			ucNoOfLocos++;
			//printf("%d ",siginfo[i].ulLocoId);
			InsertBits(ucBit,  17, &gucEmrgncyPkt[ucByte],siginfo[i].ulLocoId);
			BITSTUFFINC(17);
		
			InsertBits(ucBit,  1, &gucEmrgncyPkt[ucByte],siginfo[i].ucCollision);
			BITSTUFFINC(1);

			if(ucNoOfLocos == 2)
				break;
		}
	}
	else
	{  
		printf("\n******* Forming Manual SOS Emergency Packet");
		InsertBits(ucBit,  36, &gucEmrgncyPkt[ucByte],0);
		BITSTUFFINC(36);
	}
	printf("\n");

	if(ucNoOfLocos == 1)
	{ 
		InsertBits(ucBit,  18, &gucEmrgncyPkt[ucByte],0);
		BITSTUFFINC(18);
	}

	if (ucBit > 0)
	{
		InsertBits(ucBit,  (8-ucBit), &gucEmrgncyPkt[ucByte],0x00);
    	BITSTUFFINC((8-ucBit))
	}

	ucPktLength = (ucByte + 2+ 2-1);
	InsertBits(4, 7, &gucEmrgncyPkt[0], ucPktLength);

	ComputeCRC(gucEmrgncyPkt, ucByte);

	if((i == MAX_NO_OF_LOCOS) || (1 == stSelfInfo.ucSos))
		return 0;
	return (i+1);
}

#ifdef LANDMARKPKT
void formLandMarkInfoPkt(unsigned char index)
{
	HEADER_t stTrans;
	unsigned char ucPaddingSize = 0, i= 0;
	//short int iSize = 0;
	BITSTUFFINIT(0,0)

/*	
	if (77777 == pstLocoTemp->stInfo.uiSourceID)
	{
		return 0;
	}
*/	



	InsertBits(ucBit,  4, &LM_Buf[index][ucByte], LAND_MARK_PKT);
	BITSTUFFINC(4)



	InsertBits(ucBit,  3, &LM_Buf[index][ucByte], stTrans.ucPktLength);
	BITSTUFFINC(3)
	

	InsertBits(ucBit,  17, &LM_Buf[index][ucByte], getFrameNum());
	BITSTUFFINC(17)

	InsertBits(ucBit,  10, &LM_Buf[index][ucByte], Station->uiStnSourceID);
	BITSTUFFINC(10)
	
	InsertBits(ucBit,  3, &LM_Buf[index][ucByte],Station->ucVersion);
	BITSTUFFINC(3)
	

	InsertBits(ucBit,  17, &LM_Buf[index][ucByte], pstLocoTemp->stInfo.uiSourceID);
	BITSTUFFINC(17)
	
	InsertBits(ucBit,  22, &LM_Buf[index][ucByte], pstLocoTemp->stLMInfo.ulLMStartAbsLoc);
	BITSTUFFINC(22)
	

	InsertBits(ucBit,  16, &LM_Buf[index][ucByte], (unsigned short int)pstLocoTemp->stLMInfo.uiLMStartLocOffset);
	BITSTUFFINC(16)
	

	InsertBits(ucBit,  7, &LM_Buf[index][ucByte], pstLocoTemp->stLMInfo.ucLMInfoCount);
	BITSTUFFINC(7)//99
	
	for (i=0; i<pstLocoTemp->stLMInfo.ucLMInfoCount; i++)
	{

		InsertBits(ucBit,  2, &LM_Buf[index][ucByte], pstLocoTemp->stLMInfo.ucLMInfoType[i]);
		BITSTUFFINC(2)
		
		//if (0x0 == pstLocoTemp->stLMInfo.ucLMInfoType[i])
		{
			InsertBits(ucBit,  8, &LM_Buf[index][ucByte], pstLocoTemp->stLMInfo.ucLMInfoDistInterval[i]);
			BITSTUFFINC(8)
		
			InsertBits(ucBit,  5, &LM_Buf[index][ucByte], (unsigned char)pstLocoTemp->stLMInfo.ulLMInfoVal[i]);
			BITSTUFFINC(5)
		}		

	}//15

	/*	Padding 0's to the uncompleted byte	*/
	if (ucBit > 0)
	{
		InsertBits(ucBit,  (8 - ucBit), &LM_Buf[index][ucByte],0x00);
		BITSTUFFINC((8 - ucBit))
	}
		
	
	/*	Padding 0's so as to make the packet(including 2 bytes CRC)
	 *	in chunks of 128 bits i.e.16 bytes 
	 */
	if ( ((ucByte+2) % 16) > 0)
	{
		ucPaddingSize = 16 - ((ucByte+2) % 16);
		
		for (i=0; i<ucPaddingSize; i++)
		{
			InsertBits(ucBit,  8, &LM_Buf[index][ucByte],0x00);
			BITSTUFFINC(8)
		}
	}
	
	InsertBits(4, 3, &LM_Buf[index][0], (((ucByte + 2)/16) - 1));

	ComputeCRC(LM_Buf[index], ucByte);

	return (ucByte+1);
}
#endif


#if 0 
void transmitStationPacket()
{
	unsigned short int siNoOfBytes;
	unsigned long delay = 0L,SysTime = 0;
	unsigned char dataLoggerPkt[256] = "\0";
	
	siNoOfBytes = 16 * (ExtractBits(4,3,&stationPkt[0]) + 1);
	//printf("length:%d",siNoOfBytes);	
	
	if (siNoOfBytes > 0)
	{
		#ifdef CTS_PROTOCOL
	
		FIO4CLR |= 0x00000400;		//RTS LOW
		FIO4SET |= 0x00000400;		//RTS HIGH
		while((!((FIO4SET)) & CTS_BIT));		//wait for CTS to go HIGH		
		//TransmitMessage_NoDle(RMPORT,stationPkt, siNoOfBytes);	//Transmit Message
		FIO4CLR |= 0x00000400;		//RTS LOW

		#endif
		
		#ifdef RTS_PROTOCOL
		FIO4CLR |= 0x00000400;			//RTS LOW
		
		
		SpoiPause(FIVE_MS);
		SysTime |= bcdToDec(Read_Rtc(0XD0,0X02));//RTC_HOUR;
		SysTime = SysTime<<6;
		SysTime	|= bcdToDec(Read_Rtc(0XD0,0X01));//RTC_MIN;
		SysTime = SysTime<<6;
		SysTime	|= bcdToDec(Read_Rtc(0XD0,0X00));//RTC_SEC;
		if(SysTime%2)
			SysTime -= 1;
		SysTime = SysTime<<7;
		SysTime	|= (unsigned char)(((labs(SpoiGetSysTICs()-PPS_Clock))%1000)/10 );//for millisec
		
		TransmitMessage_NoDle(RMPORT,stationPkt, siNoOfBytes);//Transmit Message
		SpoiPause(20);					//wait for calculated delay in ms 					
		FIO4SET |= 0x00000400;		//RTS HIGH
		
		dataLoggerPkt[0] = '$';
		dataLoggerPkt[1] = DATALOG_STNTX;
		InsertBits(0,  24, &dataLoggerPkt[2],SysTime);
		memcpy(&dataLoggerPkt[5],stationPkt,siNoOfBytes);
		ComputeCRC(dataLoggerPkt, siNoOfBytes+5);
		dataLoggerPkt[siNoOfBytes+7] = '&';
		
		CommTransmitMessage(ISP_PORT,dataLoggerPkt,siNoOfBytes+7);
		delay = (unsigned long)(((siNoOfBytes + 12 + 5)* 10 * 1000)/BAUD19200);
		SpoiPause(delay);					//wait for calculated delay in ms 					
//		FIO4CLR |= 0x00000400;		//RTS LoW		

		#endif

		#ifdef RTS_PROTOCOL_old
		
		FIO4CLR |= 0x00000400;			//RTS LOW
		SpoiPause(TEN_MS);
		
		//FIO4SET |= 0x00000400;		//RTS HIGH
		//SpoiPause(TEN_MS);
		//TransmitMessage_NoDle(RMPORT,stationPkt, siNoOfBytes);//Transmit Message
		
		SpoiPause(TWENTY_MS);					//wait for 7 ms

		FIO4SET |= 0x00000400;			//RTS HIGH
		//delay = (unsigned long)(((siNoOfBytes + 12 + 5)* 10 * 1000)/BAUD19200);
		//SpoiPause(delay);					//wait for calculated delay in ms 					
		//FIO4CLR |= 0x00000400;		//RTS LoW		

		#endif
		
		#ifndef RTS_PROTOCOL
			#ifndef CTS_PROTOCOL
					//TransmitMessage_NoDle(RMPORT,stationPkt, siNoOfBytes);
			#endif
		#endif
	}
}
#endif

void transmitStnPktToModem()
{
	unsigned short int siNoOfBytesPkt1 = 0, siNoOfBytesPkt2 = 0,siNoOfStaticTrackBytes = 0;
	siNoOfBytesPkt1 				= (ExtractBits(4,7,&stationPkt[0]));
	siNoOfStaticTrackBytes  = (ExtractBits(4,7,&StaticProfilePkt[0])); 

	if ((siNoOfBytesPkt1 > 0)/*&&(PacketType == STATION_PACKET)*/)
	{
		//printf("\nPutting data on port\n");
		TransmitMessage_NoDle(TXPORT,stationPkt, siNoOfBytesPkt1);//Transmit Message
		
		siNoOfBytesPkt2 = (ExtractBits(4,7,&stationPkt2[0]));

		if(siNoOfBytesPkt2 > 0)
		{
			printf("\n");
			TransmitMessage_NoDle(TXPORT,stationPkt2, siNoOfBytesPkt2);	
		}
		
		if(siNoOfStaticTrackBytes > 0)
		{
			//printf("\nPutting Static Profile Packet on Port");
			TransmitMessage_NoDle(TXPORT,StaticProfilePkt, siNoOfStaticTrackBytes);
			memset(StaticProfilePkt, 0 , siNoOfStaticTrackBytes);
		}
           
		memcpy(&dataLoggerPkt[5],stationPkt,siNoOfBytesPkt1);
	}
}

void vfnFireRadioPkt(void)
{
//	FIO4CLR |= 0x00000400;		//RTS HIGH
//	SpoiPause(FIVE_MS);
//
//	FIO4SET |= 0x00000400;		//RTS LOW

	PINSEL1 &=0xFFFFFC3F;	//need to study
	PINSEL4 &=0xFFFF000F;
	FIO2DIR |=0x000000A0;
	FIO2DIR &=0xFFFFFFA3;
	
	FIO2CLR |= 0x00000080;			//RTS HIGH
	SpoiPause(FIVE_MS);
	FIO2SET |= 0x00000080;		//RTS LOW

	//printf("\nRTS HIGH at %ld",labs(SpoiGetSysTICs()-PPS_Clock));
	vfnTransmitDataloggerStnPkt();
}

unsigned char processTransmissionToModem(void)
{
	if(1 == TxFlag)
	{
		transmitStnPktToModem();
		TxFlag=0;
		return 1;		
	}	
	return 0;
}


unsigned char processSlotControlPacketToModem(void)
{
//	if(gucSlotControlPacket[0] == 0)
//	{
//		Tx1Flag = 0;
//		return 0;
//	}
	
	if( 1 == Tx1Flag)
	{
		transmitAccConPktToModem();
//		printf("\nAccess Athentication Paket Sent to Modem\n");
		memset(gucSlotControlPacket, 0 , 256);
		//printf("\n putting  Slot Contol data on port");
		Tx1Flag = 0;
		return 1;
	}	
		
	return 0;
}

unsigned char processEmergencyPacketToModem(void)
{
	unsigned short int siNoOfBytes = 0;

	siNoOfBytes = (ExtractBits(4,7,&gucEmrgncyPkt[0]));
	
	if(1 == Tx2Flag)
	{
		if(siNoOfBytes > 0)
		{
			printf("\n");
			TransmitMessage_NoDle(TXPORT,gucEmrgncyPkt, siNoOfBytes);
//			printf("\nEmergency Paket Sent to Modem\n");
			memset(gucEmrgncyPkt, 0 , 256);
			gucEmgPktOnPort = 1;
			Tx2Flag = 0;
			return 1;
		}
		Tx2Flag = 0;
	}	
	return 0;
}

void transmitAccConPktToModem(void)
{
	unsigned short int siNoOfBytes = 0;
//	unsigned short int PacketType =0;
	
//	siNoOfBytes = 16 * (ExtractBits(4,3,&gucSlotControlPacket[0]) + 1);

	siNoOfBytes = (ExtractBits(4,7,&gucSlotControlPacket[0]));

	if (siNoOfBytes > 0)
	{
		printf("\n Transmit Access Control Packet ");
		//printf("\n");
		TransmitMessage_NoDle(TXPORT,gucSlotControlPacket, siNoOfBytes);
		gucSlotPktOnPort = 1;
		return ;
	}	
	gucSlotPktOnPort = 0;
}	

#if 0
void SendingCrcValue(void)
{

	static unsigned char gucHexCrcFlag = 0;

	if( (gucHexCrcFlag == 0) || (stCanHexCrcvalReqRec.ucCrcReqRec == 1))
	{
		stCanComCrcVal.ucSlotNo = gucSelfSlot;
		stCanComCrcVal.ucHexFileCrc = gui_CalCrc;
		stCanHexCrcvalReqRec.ucCrcReqRec = 0;
		gucHexCrcFlag = 1;
		printf("\n-----sending CRC values::%d--%d------\n",stCanComCrcVal.ucSlotNo,stCanComCrcVal.ucHexFileCrc);
		TransmitCanPkt(HEXFILE_CRC);
	}
	
}
#endif

void formStaticTrackProfilePkt(void)
{
	
	unsigned char i = 0,ucPktLength,cnt=0;
	unsigned int uiCurFrameNum = 0;
  unsigned short int MAC_CODE = 0;
	BITSTUFFINIT(0,0);

	memset(StaticProfilePkt, 0 , 256);

	

	InsertBits(ucBit,  4, &StaticProfilePkt[ucByte], STATIC_PROFILE);
	BITSTUFFINC(4);
	
	//ucPktLength = (10*
	//InsertBits(ucBit,  7, &StaticProfilePkt[ucByte], ucPktLength);
	BITSTUFFINC(7);
	
	if(GPSframeNo > 3)
	{		
	 uiCurFrameNum = GPSframeNo;	
	 if((uiCurFrameNum%2)== 0)
	 uiCurFrameNum = uiCurFrameNum-1;
	 //printf("\n GPS Frame No is %d",uiCurFrameNum);
	}
	if(GPSframeNo < 3)
	{
	  uiCurFrameNum = getFrameNum();
	  //printf("\n RTC Frame No is %d",uiCurFrameNum); 
	}
   	uiframeno = uiCurFrameNum;

	
	InsertBits(ucBit,  17, &StaticProfilePkt[ucByte], GPSframeNo);
	BITSTUFFINC(17);

	InsertBits(ucBit,  16, &StaticProfilePkt[ucByte], stSelfInfo.stationId);                     
	BITSTUFFINC(16);
	
	InsertBits(ucBit,  3, &StaticProfilePkt[ucByte], stSelfInfo.ucStnVer);
	BITSTUFFINC(3);	


	InsertBits(ucBit,  17, &StaticProfilePkt[ucByte], staticProfileInfo.ulLocoID);
	BITSTUFFINC(17);

//	if( 0 == ucProfileID)
//	ucProfileID = 1;
//	else
//	ucProfileID = ucProfileID + 1;
//	if(ucProfileID > 62)
//	ucProfileID = 0;
	InsertBits(ucBit,  6, &StaticProfilePkt[ucByte],staticProfileInfo.ucStaticProfID);		// Profile ID
	BITSTUFFINC(6);
		
	InsertBits(ucBit,  2, &StaticProfilePkt[ucByte],0x00);	// HEADER Fill Zeros
	BITSTUFFINC(2);	
		//printf("\n****** staticProfileInfo.ucSigmentDirection is %d",staticProfileInfo.ucSigmentDirection);
	InsertBits(ucBit,  2, &StaticProfilePkt[ucByte],staticProfileInfo.ucSigmentDirection); //LM_Segment_Dir
	BITSTUFFINC(2);
    //staticProfileInfo.ucSubStaitcProfCnt = 1;
	InsertBits(ucBit,  3, &StaticProfilePkt[ucByte],staticProfileInfo.ucSubStaitcProfCnt); //Sub_Static_Profile_CNT
    BITSTUFFINC(3);
	  //staticProfileInfo.ucSubStaitcProfID = 1;

	InsertBits(ucBit,  3, &StaticProfilePkt[ucByte],staticProfileInfo.ucSubStaitcProfID); //Sub_Static_Profile_ID
	BITSTUFFINC(3);
		//staticProfileInfo.ulSubStaicSegmentStartABSLoc = 12345;
	InsertBits(ucBit,  19, &StaticProfilePkt[ucByte],(staticProfileInfo.ulSubStaicSegmentStartABSLoc/10)); //LM_Segment_Start_Abs_Loc
	BITSTUFFINC(19);
	
	//printf("\n****** staticProfileInfo.usSegmentDistance is %d",staticProfileInfo.usSegmentDistance);
	//printf("\n *********staticProfileInfo.ucSpeed_Info_Cnt is %d",staticProfileInfo.ucSpeed_Info_Cnt);
	//printf("\n *********staticProfileInfo.ucGradient_Info_Cnt is %d",staticProfileInfo.ucGradient_Info_Cnt);
		//staticProfileInfo.usSegmentDistance = 1500;
	InsertBits(ucBit,  11, &StaticProfilePkt[ucByte],(staticProfileInfo.usSegmentDistance/10)); //LM_Segment_Distance
	BITSTUFFINC(11);

	InsertBits(ucBit,  3, &StaticProfilePkt[ucByte],0x01); //static or gradient LM_Type
	BITSTUFFINC(3);
		
//		if((labs(uiCurFrameNum - siginfo[i].uiFrameNum )/2) > 2)
//			return;	
		 //staticProfileInfo.ucSpeed_Info_Cnt = 0x01;
		InsertBits(ucBit,  5, &StaticProfilePkt[ucByte],staticProfileInfo.ucSpeed_Info_Cnt);//LM_Speed_Info_CNT
		BITSTUFFINC(5);
		
		//printf("\n *********staticProfileInfo.ucSpeed_Info_Cnt is %d",staticProfileInfo.ucSpeed_Info_Cnt);
		for(cnt=0;cnt<staticProfileInfo.ucSpeed_Info_Cnt; cnt++)
		{
		
		    
//			if((staticProfileInfo.ucStatic_Speed_Value[cnt][0]) > 0)
			{
				InsertBits(ucBit,  3, &StaticProfilePkt[ucByte],0x01); //LM_Static_Speed_Type
				BITSTUFFINC(3);

				InsertBits(ucBit,  9, &StaticProfilePkt[ucByte],(staticProfileInfo.usStatic_Speed_Distance[cnt]/10));	//LM_Static_Speed_Distance
				BITSTUFFINC(9);

				InsertBits(ucBit,  5, &StaticProfilePkt[ucByte],staticProfileInfo.ucStatic_Speed_Value[cnt][0]);	//LM_Static_Speed_Value
				BITSTUFFINC(5);
			}
//			else
//			{
//				InsertBits(ucBit,  3, &StaticProfilePkt[ucByte],0x02); //LM_Static_Speed_Type
//				BITSTUFFINC(3);
//
//				InsertBits(ucBit,  9, &StaticProfilePkt[ucByte],staticProfileInfo.usStatic_Speed_Distance[cnt]);	//LM_Static_Speed_Distance
//				BITSTUFFINC(9);
//
//				InsertBits(ucBit,  5, &StaticProfilePkt[ucByte],staticProfileInfo.ucStatic_Speed_Value[cnt][1]);	//LM_Static_Speed_Value
//				BITSTUFFINC(5);
//				
//				InsertBits(ucBit,  3, &StaticProfilePkt[ucByte],0x03); //LM_Static_Speed_Type
//				BITSTUFFINC(3);
//
//				InsertBits(ucBit,  9, &StaticProfilePkt[ucByte],staticProfileInfo.usStatic_Speed_Distance[cnt]);	//LM_Static_Speed_Distance
//				BITSTUFFINC(9);
//
//				InsertBits(ucBit,  5, &StaticProfilePkt[ucByte],staticProfileInfo.ucStatic_Speed_Value[cnt][2]);	//LM_Static_Speed_Value
//				BITSTUFFINC(5);
//				
//				InsertBits(ucBit,  3, &StaticProfilePkt[ucByte],0x04); //LM_Static_Speed_Type
//				BITSTUFFINC(3);
//
//				InsertBits(ucBit,  9, &StaticProfilePkt[ucByte],staticProfileInfo.usStatic_Speed_Distance[cnt]);	//LM_Static_Speed_Distance
//				BITSTUFFINC(9);
//
//				InsertBits(ucBit,  5, &StaticProfilePkt[ucByte],staticProfileInfo.ucStatic_Speed_Value[cnt][3]);	//LM_Static_Speed_Value
//				BITSTUFFINC(5);
//				
//			}
				
		}
    //staticProfileInfo.ucType[1] = 0x02;
		InsertBits(ucBit,  3, &StaticProfilePkt[ucByte],0x02);	//static or gradient (2nd time)
		BITSTUFFINC(3);
		//staticProfileInfo.ucGradient_Info_Cnt = 0x01;
		InsertBits(ucBit,  5, &StaticProfilePkt[ucByte],staticProfileInfo.ucGradient_Info_Cnt); //LM_Grad_Info_CNT
		BITSTUFFINC(5);

		//printf("\n *********staticProfileInfo.ucGradient_Info_Cnt is %d",staticProfileInfo.ucGradient_Info_Cnt);
		for(cnt=0 ;  cnt<staticProfileInfo.ucGradient_Info_Cnt ; cnt++)
		{
//			if(StaticProfilePkt[ucByte],staticProfileInfo.usGradient_Distance[cnt] > 5110)
//			StaticProfilePkt[ucByte],staticProfileInfo.usGradient_Distance[cnt] = 5110;
			InsertBits(ucBit,  9, &StaticProfilePkt[ucByte],(staticProfileInfo.usGradient_Distance[cnt]));	//LM_Gradient_Distance
			BITSTUFFINC(9);
			
			InsertBits(ucBit,  1, &StaticProfilePkt[ucByte],staticProfileInfo.ucGDIR[cnt]);	//LM_GDIR
			BITSTUFFINC(1);
			
			InsertBits(ucBit,  5, &StaticProfilePkt[ucByte],staticProfileInfo.ucGradient[cnt]);	//LM_GRADIENT
			BITSTUFFINC(5);
		}
    if((staticProfileInfo.ucLC_Info_Cnt > 0)&&(staticProfileInfo.ucLC_Info_Cnt <= 3))
		{
		InsertBits(ucBit,  3, &StaticProfilePkt[ucByte],0x03);	//static or gradient (3rd time)
		BITSTUFFINC(3);
		InsertBits(ucBit,  5, &StaticProfilePkt[ucByte],staticProfileInfo.ucLC_Info_Cnt);	//LM_LC_Info_CNT
		BITSTUFFINC(5);
    			
		for(cnt=0 ;  cnt < staticProfileInfo.ucLC_Info_Cnt ; cnt++)
		{
			
			InsertBits(ucBit,  11, &StaticProfilePkt[ucByte], staticProfileInfo.usLC_Distance[cnt]);	//LM_LC_Distance
			BITSTUFFINC(11);
			//staticProfileInfo.usLC_ID_Numaric[cnt] = 1;
			InsertBits(ucBit,  10, &StaticProfilePkt[ucByte], staticProfileInfo.usLC_ID_Numaric[cnt]);	//LM_LC_ID_Numeric
			BITSTUFFINC(10);

			//staticProfileInfo.ucLC_ID_Alpha_Suffix[cnt] = 1;
			InsertBits(ucBit,  3, &StaticProfilePkt[ucByte],staticProfileInfo.ucLC_ID_Alpha_Suffix[cnt]);	//LM_LC_ID_Alpha_Suffix
			BITSTUFFINC(3);
			//staticProfileInfo.ucLC_Manning_Type[cnt] = 0;
			InsertBits(ucBit,  1, &StaticProfilePkt[ucByte],staticProfileInfo.ucLC_Manning_Type[cnt]);	//LM_LC_Manning_Type
			BITSTUFFINC(1);

			//staticProfileInfo.ucLC_Class[cnt] = 1;
			InsertBits(ucBit,  3, &StaticProfilePkt[ucByte],staticProfileInfo.ucLC_Class[cnt]);	//LM_LC_Class
			BITSTUFFINC(3);
	

	        //staticProfileInfo.ucAuto_Whisling_Enable[cnt] = 0;
			InsertBits(ucBit,  1, &StaticProfilePkt[ucByte],staticProfileInfo.ucAuto_Whisling_Enable[cnt]);	//LM_LC_Auto_Whisling_Enabled
			BITSTUFFINC(1);

			//staticProfileInfo.ucAuto_Whisling_Type[cnt] = 0;
			InsertBits(ucBit,  2, &StaticProfilePkt[ucByte],staticProfileInfo.ucAuto_Whisling_Type[cnt]);	//LM_LC_Auto_Whisling_Type
			BITSTUFFINC(2);
		}
	}	
	if (ucBit > 0)
	{
		        //printf("\n staticucBit is %d",ucBit);
				InsertBits(ucBit,  (8-ucBit), &StaticProfilePkt[ucByte],0x00);
				BITSTUFFINC((8-ucBit))
	}
		
  ucPktLength = ((ucByte+2+2) - 1);
	printf("\n...Static Profile Length.. is %d",ucPktLength );
	InsertBits(4, 7, &StaticProfilePkt[0], ucPktLength);
	
		
	
	MAC_CODE = ComputeMAC_Code(StaticProfilePkt,0,ucByte-1,siginfo[i].usLocoRandomNumbr,staticProfileInfo.ulLocoID);

	InsertBits(ucBit,  16, &gucSlotControlPacket[ucByte],MAC_CODE);
	BITSTUFFINC(16)
  	//uiDestnationLOcoID = 0;
	//stLocMsg.ucStaticProffReq = 0;
	ComputeCRC(StaticProfilePkt, ucByte);	//require
	/**********************************************************/
}	


//		For Radio Modem		//

/* ************************************************************************************************** 

Function Name:	SendModemDiagnosticReqASCII()
Parameter:		unsigned char
Return Type:	void
Created Date:	01/08/2017
Last Modified:	29/08/2017
Created By:		Siddhu
Description:	This Function will send the ASCII Format STATUS Command to Radio Modem.
	
**************************************************************************************************** */

void SendModemDiagnosticReqASCII(unsigned char iport)
{
  	unsigned int i=0;
	unsigned char Command[15]={'S','T','A','T','U','S','\r','\n'}; 

  	for(i=0;i<8;i++)
	{
	  Comm_ComSendByte(iport, Command[i]);	
	  //printf("%c",Command[i]);
	}
  	printf("\nSent STATUS Request \n");
	
}

/* ************************************************************************************************** 

Function Name:	ReadRMSetupPortASCII()
Parameter:		unsigned char
Return Type:	void
Created Date:	01/08/2017
Last Modified:	28/09/2017
Created By:		Siddhu
Description:	This Function will read the reply byte from Radio Modem of SetUp Port.If Valid number of 
				bytes updated then it will call ProcessRmHealthHEXPkt() function. 
	
**************************************************************************************************** */
void ReadRMSetupPortASCII(unsigned char port)
{
 		//unsigned char i=0;
	
		static unsigned int modem_clk =0;
		static unsigned char sucRMFailFlag = 0;

		if(modem_clk == 0)
			modem_clk = SpoiGetSysTICs();
		
	
		if(ReadModemHealthASCII(port,ucHealthReplayASCII)>0)
		{		
		  	ProcessRmHealthASCIIPkt(ucHealthReplayASCII);
			//printf("\nRecieved Rm Health ASCII Pkt\n");
			//TransmitCanPkt(CM_LPM_RADIOMODEMSTATUS);
			//gucRadioSetupPortFlag = 0;
			stCanRadioModemFailStatusTx.ucRadioFailStatus = 0;

			if(sucRMFailFlag == 1)
			{
				if(gucSelfSlot == 3)
					TransmitCanPkt(CM1_CM2_RADIO_FAIL);
				if(gucSelfSlot == 4)
					TransmitCanPkt(CM2_CM1_RADIO_FAIL);
				sucRMFailFlag = 0;
			}//if
			modem_clk = 0;
			
		}
		else
		{
			if((SpoiElapsTICs(modem_clk)) >= 30 * ONE_SEC)
			{
				//gucRadioSetupPortFlag = 1;
				stCanRadioModemFailStatusTx.ucRadioFailStatus = 1;
				if(gucSelfSlot == 3)
					TransmitCanPkt(CM1_CM2_RADIO_FAIL);
				if(gucSelfSlot == 4)
					TransmitCanPkt(CM2_CM1_RADIO_FAIL);
				modem_clk = 0;
				sucRMFailFlag = 1;
			}
		
		}

}

/* ************************************************************************************************** 

Function Name:	ReadModemHealthASCII()
Parameter:		unsigned char,unsigned char *
Return Type:	unsigned int
Created Date:	01/08/2017
Last Modified:	29/08/2017
Created By:		Siddhu
Description:	This Function will read the reply byte from Radio Modem SetUp Port & update into buffer. 
	
**************************************************************************************************** */
unsigned int ReadModemHealthASCII(unsigned char iport,unsigned char *Rep)
{
	static unsigned int index=0;
	static unsigned int foundSop=0;

	unsigned char Checkbyte=0;
	while(Comm_ComDataReady(iport))
	{
		Checkbyte=Comm_ComGetByte(iport);

		//printf("%c ",Checkbyte);

		if(foundSop == 8)
		{
		Rep[index] = Checkbyte;
	 	//printf("%d = %c ",index,Rep[index]);
		index++;
		}
		if((Checkbyte == 'S')&& (foundSop == 0))
		{
		foundSop=1;
		//printf("1%c-----------\n",Checkbyte);
		}

		if((Checkbyte == 'T') && (foundSop == 1))
		{
		//printf("2%c-----------\n",Checkbyte);
		foundSop=2;
		}

		if((Checkbyte == 'A') && (foundSop == 2))
		{
		//printf("3%c-----------\n",Checkbyte);
		foundSop=3;
		}

		if((Checkbyte == 'T') && (foundSop == 3))
		{
		//printf("4%c-----------\n",Checkbyte);
		foundSop=4;
		}

		if((Checkbyte == 'U') && (foundSop == 4))
		{
		//printf("5%c-----------\n",Checkbyte);
		foundSop=5;
		}
				 
		if((Checkbyte == 'S') && (foundSop == 5))
		{
		//printf("6%c-----------\n",Checkbyte);
		foundSop=6;
		}
		if((Checkbyte == '\r') && (foundSop == 6))
		{
		//printf("7%c-----------\n",Checkbyte);
		foundSop=7;
		}
		if((Checkbyte == '\n') && (foundSop == 7))
		{
		//printf("7%c-----------\n",Checkbyte);
		foundSop=8;
		}
	}
	if((Rep[index-1]== 0x0d) && (Rep[index-2]== 0x0a) && (Rep[index-3]== 0x0d) &&
			(Rep[index-4]== 0x0a))
	{	
		index=0;
	 	foundSop=0;
		return 1;
	}
	else
	return 0;
}

/* ************************************************************************************************** 

Function Name:	ProcessRmHealthASCIIPkt()
Parameter:		unsigned char *
Return Type:	int
Created Date:	01/08/2017
Last Modified:	28/09/2017
Created By:		Siddhu
Description:	This Function will check if Radio Modem has any error. 
	
**************************************************************************************************** */	
								    

void ProcessRmHealthASCIIPkt(unsigned char *Health)
{
	short int iField=0;
	char *pcGPSPtr = NULL;
	static unsigned int modem_clk =0;
	static unsigned char sucRMFailFlag = 0; 

 	pcGPSPtr = strtok((char *)Health,"\n");

	if(modem_clk == 0)
		modem_clk = SpoiGetSysTICs();

 	if(strstr(pcGPSPtr,"No Errors.") != NULL)
	{
		//CLEAR_BIT(NO_ERRORS,stCanRadioModemStatusLog.Modem_Status);
		printf("No Errors.\n");
		gucRadioModemResetFlag = 0;
		RadioModemHealth.ucRadioModemHealth = 0;
		stCanRadioModemStatusLog.Modem_Status = 0;

		stCanRadioModemFailStatusTx.ucRadioFailStatus = 0;

		if(sucRMFailFlag == 1)
		{
			if(gucSelfSlot == 3)
				TransmitCanPkt(CM1_CM2_RADIO_FAIL);
			if(gucSelfSlot == 4)
				TransmitCanPkt(CM2_CM1_RADIO_FAIL);
			sucRMFailFlag = 0;
		}//if
		
		modem_clk = 0;
						
	//	gucRadioFailFlag = 0;
	}
	else
	{
		SET_BIT(NO_ERRORS,stCanRadioModemStatusLog.Modem_Status);	
		gucRadioModemResetFlag = 1;
		printf("\n Radio Modem Has error...\n");
		if((SpoiElapsTICs(modem_clk)) >= 10 * ONE_SEC)
		{
			//gucRadioSetupPortFlag = 1;
			stCanRadioModemFailStatusTx.ucRadioFailStatus = 1;
			if(gucSelfSlot == 3)
				TransmitCanPkt(CM1_CM2_RADIO_FAIL);
			if(gucSelfSlot == 4)
				TransmitCanPkt(CM2_CM1_RADIO_FAIL);
			modem_clk = 0;
			sucRMFailFlag = 1;
		}//if	
 	//	gucRadioFailFlag = 1;
	}

	for (iField = 1; iField < 37;iField++ )
	{
		pcGPSPtr = strtok(NULL,"\n");

		  //////////////   MODEM STATUS ////////////////

		if(strstr(pcGPSPtr,"Timer Queue overflow.") != NULL)
		{
			printf("Timer Queue overflow.\n");
			SET_BIT(TIMER_QUEUE_OVERFLOW,stCanRadioModemStatusLog.Modem_Status);
		}
		else if(strstr(pcGPSPtr,"UART buffer unavailable.") != NULL)
		{
			printf("UART buffer unavailable.\n");
			SET_BIT(UART_BUFFER_UNAVILABLE,stCanRadioModemStatusLog.Modem_Status);

		}	
		else if(strstr(pcGPSPtr,"Message Queue overflow.") != NULL)
		{
			printf("Message Queue overflow.\n");
			SET_BIT(MESSAGE_QUEUE_OVERFLOW,stCanRadioModemStatusLog.Modem_Status);
		}
		else if(strstr(pcGPSPtr,"EEPROM write failed.") != NULL)
		{
			printf("EEPROM write failed.\n");
			SET_BIT(EEPROM_WRITE_FAILED,stCanRadioModemStatusLog.Modem_Status);
		}
		else if(strstr(pcGPSPtr,"Config File Corrupt.") != NULL)
		{
			printf("Config File Corrupt.\n");
			SET_BIT(CONFIG_FILE_CORRUPT,stCanRadioModemStatusLog.Modem_Status);
		}
		else if(strstr(pcGPSPtr,"Modem Queue overflow.") != NULL)
		{
			printf("Modem Queue overflow.\n");
			SET_BIT(MODEM_QUEUE_OVERFLOW,stCanRadioModemStatusLog.Modem_Status);
		}
		else if(strstr(pcGPSPtr,"Require file is missing.") != NULL)
		{
			printf("Require file is missing\n");
			SET_BIT(REQUIRE_FILE_MISSING,stCanRadioModemStatusLog.Modem_Status);
		}
		else if(strstr(pcGPSPtr,"File is corrupt.") != NULL)
		{
			printf("File is corrupt.\n");
			SET_BIT(FILE_IS_CORRUPT,stCanRadioModemStatusLog.Modem_Status);
		}
		else if(strstr(pcGPSPtr,"Rx Modem sample overflow.") != NULL)
		{
			printf("Rx Modem sample overflow.\n");
			SET_BIT(RX_MODEM_SAMPLE_OVERFLOW,stCanRadioModemStatusLog.Modem_Status);
		}
		else if(strstr(pcGPSPtr,"Rx Radio data not processed.") != NULL)
		{
			printf("Rx Radio data not processed.\n");
			SET_BIT(RX_RADIO_DATA_NOT_PROCESSED,stCanRadioModemStatusLog.Modem_Status);
		}
		else if(strstr(pcGPSPtr,"Tx Radio data not processed.") != NULL)
		{
			printf("Tx Radio data not processed.\n");
			SET_BIT(TX_RADIO_DATA_NOT_PROCESSED,stCanRadioModemStatusLog.Modem_Status);
		}
		else if(strstr(pcGPSPtr,"Rx Codec data not processed.") != NULL)
		{
			printf("Rx Codec data not processed.\n");
			SET_BIT(RX_CODEC_DATA_NOT_PROCESSED,stCanRadioModemStatusLog.Modem_Status);
		} 
		else if(strstr(pcGPSPtr,"Tx Codec data not processed.") != NULL)
		{
			printf("Tx Codec data not processed.\n");
			SET_BIT(TX_CODEC_DATA_NOT_PROCESSED,stCanRadioModemStatusLog.Modem_Status);
		}
		else if(strstr(pcGPSPtr,"Radio Bad.") != NULL)
		{
			printf("Radio Bad.\n");
			SET_BIT(RADIO_BAD,stCanRadioModemStatusLog.Modem_Status);
			SET_BIT(0,RadioModemHealth.ucRadioModemHealth);
			printf("\n0.bit SET:%d\n",RadioModemHealth.ucRadioModemHealth);
		}
		else if(strstr(pcGPSPtr,"Receiver Error.") != NULL)
		{
			printf("Receiver Error.\n");
			SET_BIT(RECEIVER_ERROR,stCanRadioModemStatusLog.Modem_Status);
			SET_BIT(1,RadioModemHealth.ucRadioModemHealth);
			printf("\n1.bit SET:%d\n",RadioModemHealth.ucRadioModemHealth);
		}
		else if(strstr(pcGPSPtr,"Transmitter Error.") != NULL)
		{
			printf("Transmitter Error.\n");
			SET_BIT(TRANSMITTER_ERROR,stCanRadioModemStatusLog.Modem_Status);
			SET_BIT(2,RadioModemHealth.ucRadioModemHealth);
			printf("\n2.bit:%d\n",RadioModemHealth.ucRadioModemHealth);
		
		}
		else if(strstr(pcGPSPtr,"Receiver Bad.") != NULL)
		{
			printf("Receiver Bad.\n");
			SET_BIT(RECEIVER_BAD,stCanRadioModemStatusLog.Modem_Status);
		}
		else if(strstr(pcGPSPtr,"Transmitter Bad.") != NULL)
		{
			printf("Transmitter Bad.\n");
			SET_BIT(TRANSMITTER_BAD,stCanRadioModemStatusLog.Modem_Status);
		}
		else if(strstr(pcGPSPtr,"Can't talk to radio.") != NULL)
		{
			printf("Can't talk to radio.\n");
			SET_BIT(CANT_TALK_TO_RADIO_MODEM,stCanRadioModemStatusLog.Modem_Status);
		}
		else if(strstr(pcGPSPtr,"Radio Missing.Detect failed.") != NULL)
		{
			printf("Radio Missing.Detect failed.\n");
			SET_BIT(RAIO_MISSING_DETECT_FAILED,stCanRadioModemStatusLog.Modem_Status);
		}

		else if(strstr(pcGPSPtr,"Transmit Inhibited.") != NULL)
		{
			printf("Transmit Inhibited.\n");
			SET_BIT(TRANSMIT_INHIBITED,stCanRadioModemStatusLog.Modem_Status);
		}


		   //////////////   RADIO STATUS ////////////////

		else if(strstr(pcGPSPtr,"Radio Status:") != NULL)
		{
		  	//printf("Radio Status:\n");
			SET_BIT(RADIO_STATUS,stCanRadioModemStatusLog.Radio_Status);

		}
		else if(strstr(pcGPSPtr,"Rx Synth Not Locked.") != NULL)
		{
		  	printf("Rx Synth Not Locked.\n");
			SET_BIT(RX_SYNTH_NOT_LOCKED,stCanRadioModemStatusLog.Radio_Status);
			SET_BIT(3,RadioModemHealth.ucRadioModemHealth);
			printf("\n3.bit SET:%d\n",RadioModemHealth.ucRadioModemHealth);
		}
		else if(strstr(pcGPSPtr,"Tx Synth Not Locked.") != NULL)
		{
		  	printf("Tx Synth Not Locked.\n");
			SET_BIT(TX_SYNTH_NOT_LOCKED,stCanRadioModemStatusLog.Radio_Status);
			SET_BIT(4,RadioModemHealth.ucRadioModemHealth);
			printf("\n4.bit SET:%d\n",RadioModemHealth.ucRadioModemHealth);
		}
		else if(strstr(pcGPSPtr,"Rx Synth Locking.") != NULL)
		{
		  	printf("Rx Synth Locking.\n");
			SET_BIT(RX_SYNTH_LOCKING,stCanRadioModemStatusLog.Radio_Status);
		}
		else if(strstr(pcGPSPtr,"Tx Synth Locking.") != NULL)
		{
		  	printf("Tx Synth Locking.\n");
			SET_BIT(TX_SYNTH_LOCKING,stCanRadioModemStatusLog.Radio_Status);
		}
		else if(strstr(pcGPSPtr,"Rx Synth Unable to Lock.") != NULL)
		{
		  	printf("Rx Synth Unable to Lock.\n");
			SET_BIT(RX_SYNTH_UNABLE_TO_LOCK,stCanRadioModemStatusLog.Radio_Status);
		}
		else if(strstr(pcGPSPtr,"Tx Synth Unable to Lock.") != NULL)
		{
		  	printf("Tx Synth Unable to Lock.\n");
			SET_BIT(TX_SYNTH_UNABLE_TO_LOCK,stCanRadioModemStatusLog.Radio_Status);
		}
		else if(strstr(pcGPSPtr,"Rx Tune failed.") != NULL)
		{
		  	printf("Rx Tune failed.\n");
			SET_BIT(RX_TUNE_FAILED,stCanRadioModemStatusLog.Radio_Status);
		}
		else if(strstr(pcGPSPtr,"Radio Eeprom failure.") != NULL)
		{
		  	printf("Radio Eeprom failure.\n");
			SET_BIT(RADIO_EEPROM_FAILURE,stCanRadioModemStatusLog.Radio_Status);

		}
		else if(strstr(pcGPSPtr,"Radio Dcxo failure.") != NULL)
		{
		  	printf("Radio Dcxo failure.\n");
			SET_BIT(RADIO_DCXO_FAILURE,stCanRadioModemStatusLog.Radio_Status);
		}
		else if(strstr(pcGPSPtr,"Radio in Debug Mode.") != NULL)
		{
		  	printf("Radio in Debug Mode.\n");
			SET_BIT(RADIO_IN_DEBUG_MODE,stCanRadioModemStatusLog.Radio_Status);
		}
		else if(strstr(pcGPSPtr,"Bad ASD Checksum.") != NULL)
		{
		  	printf("Bad ASD Checksum.\n");
			SET_BIT(BAD_ASD_CHECKSUM,stCanRadioModemStatusLog.Radio_Status);
			SET_BIT(5,RadioModemHealth.ucRadioModemHealth);
			printf("\n5.bit SET:%d\n",RadioModemHealth.ucRadioModemHealth);
		}
		else if(strstr(pcGPSPtr,"Bad ASD Data.") != NULL)
		{
		  	printf("Bad ASD Data.\n");
			SET_BIT(BAD_ASD_DATA,stCanRadioModemStatusLog.Radio_Status);
			
		}
		else if(strstr(pcGPSPtr,"Tx Diagnostics Invalid.") != NULL)
		{
		  	//printf("Tx Diagnostics Invalid.\n");
			SET_BIT(TX_DIAGNOSTIC_INVALID,stCanRadioModemStatusLog.Radio_Status);
		}
		else if(strstr(pcGPSPtr,"Radio Firmware Incompatible.") != NULL)
		{
		  	printf("Radio Firmware Incompatible.\n");
			SET_BIT(RADIO_FIRMWARE_INCOMPATIBLE,stCanRadioModemStatusLog.Radio_Status);
		}
	}
}

void SendResetCmdToRM(void)
{
	unsigned char ucResetCMD[10];
	unsigned char i = 0;
	
	ucResetCMD[0] = 'R'; ucResetCMD[1] = 'E'; ucResetCMD[2] = 'S'; ucResetCMD[3] = 'E'; ucResetCMD[4] = 'T'; ucResetCMD[5] = '!'; ucResetCMD[6] = '\r'; ucResetCMD[7] = '\n';

	for(i = 0; i <= 7; i++)
	{
		Comm_ComSendByte(RXPORT, ucResetCMD[i]);
	}//for
	ReadTXReplay(TXPORT);
}//if
	
void ReadTXReplay(unsigned char ucPort)
{
	char ch;
	while(Comm_ComDataReady(ucPort))
	{
		ch=Comm_ComGetByte(ucPort);
		printf("%c ",ch);
	}//while
}
