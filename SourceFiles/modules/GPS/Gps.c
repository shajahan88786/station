
#include "Header.h"
//#define GPS_DEBUG
unsigned short int  consideforDate = 0;

unsigned bcdToDec(unsigned char bcd)
{
	return (((bcd/16)*10) + (bcd%16));
}

void ReadGPSData(short int iPort)
{
	READGPS_t stGPSData; 

	memset(&stGPSData,0,sizeof(stGPSData));

	if(GetGPSData(iPort,&stGPSData))
	{		
//		printf("\n %d:%d:%d GPS DATA (GPRMC packet) RECEIVED",bcdToDec(Read_Rtc(0XD0,0X02)),bcdToDec(Read_Rtc(0XD0,0X01)),bcdToDec(Read_Rtc(0XD0,0X00)));
		//if( DetectSpike(( short int ) stGPSData.fSpeed))
		{			
			//printf("No Spike\n");
			NetworkTimeSync(&stGPSData);
      GPSclk = SpoiGetSysTICs();
			
		}
		
	}
			
}



void extractGPSData1(char *pcGPSBuf, READGPS_t *pstGPSData)
{
	char *pcGPSPtr = NULL;
	short int iField = 0;
//    float  tempSpeed =0;

	pcGPSPtr = strtok(pcGPSBuf, ",");

	for (iField = 1; iField < 5; )
	{
		pcGPSPtr = strtok(NULL, ",");

		iField = iField + 1;

		switch (iField)
		{
			case 2:
				sscanf(pcGPSPtr, "%s", pstGPSData->cTime);
				strcat(pstGPSData->cTime, "\0");
				//printf("\nGPS time %s",pstGPSData->cTime);
				break;

			case 4:
				sscanf(pcGPSPtr, "%s", pstGPSData->cDate); 
				strcat(pstGPSData->cDate, "\0");
				//printf("\nGPS date %s",pstGPSData->cDate);

				break;
	

			default:
				break;
		} 
	}
}


short int GetGPSData(short int iPort,READGPS_t * pstGPSData)
{
	short int iRetVal = 0;
	char ch = 0;
	static char cGPSBuf[90] = "\0";
	static unsigned short int iGPSCnt = 0;

	while(Comm_ComDataReady(iPort))
	{
		CommWatchDogStrobe();
		ch = Comm_ComGetByte(iPort);
	

		#ifdef GPS_DEBUG
		//	printf("%c ",ch);
		#endif	/*#ifdef GPS_DEBUG*/
		//printf("%c ",ch);

		if(ch == START_RMC)
		{
			cGPSBuf[0] = ch;
			iGPSCnt = 1;
		}
		else
		{
			cGPSBuf[iGPSCnt++] = ch;
		
			/* check Over-run of the bufffer
			 */
			if( iGPSCnt >= 85 )
			{
				cGPSBuf[0] = '\0';
				iGPSCnt = 0;
				ch = 0;
			}
		}

		if(ch == END_RMC)
		{
			cGPSBuf[iGPSCnt-1] = '\0';

			//printf("\nINDEX : %d",iGPSCnt);

			iGPSCnt = 0;
			
			if(strlen (cGPSBuf) == 23)
			{
				if((cGPSBuf[8] == 'v') || (cGPSBuf[8] == 'V'))
				{
					printf("\n Void Packet Recieved From GPS");
				}
			}

			if( strlen(cGPSBuf) == 39)
			{
				if(ONE == (iRetVal = CheckSumOk((unsigned char *)cGPSBuf)))
				{
					//printf("\nCRC OK ");
					extractGPSData1(cGPSBuf, pstGPSData);
				} 
				break;
			}


			if( ( strlen(cGPSBuf) < 65 ) || ( strlen(cGPSBuf) > 78 ) )
			{
				break;
			}

			if( ( strlen(cGPSBuf) < 68 ) )
			{
				consideforDate = 0;
			}
			else
			{
				consideforDate = 1;
			}
			
			if(ONE == (iRetVal = CheckSumOk((unsigned char *)cGPSBuf)))
			{
				#ifdef GPS_DEBUG
							//;printf("\nGPS CRC OK ");
				#endif	/*#ifdef GPS_DEBUG*/

				extractGPSData(cGPSBuf, pstGPSData);
			} 
			else
			{
				#ifdef GPS_DEBUG
					printf("\nGPS CRC NOT OK");
				#endif	/*#ifdef GPS_DEBUG*/
			}
		}	
	} 
	
	return iRetVal;
}

short int CheckSumOk(unsigned char *ucTxt)
{
	short int i,iPassed = 1,iLen;
    unsigned short int uiXcs, uiIcs;				/*Expected checksum */
	iLen = (short int) strlen ((char *) ucTxt);		 /*Length of TAIP packet */

    /* Search for the checksum identifier ('*') starting at the end of the packet */
    for (i = iLen - 1; i > 0; i--) 
	{
		if (ucTxt [i] == '*')
		{
			/* Checksum identifier found */
			/* convert checksum characters into an integer */
			StrH2I (&ucTxt [i + 1], &uiXcs);

			/* if calculated checksum matches the expected checksum... */
			uiIcs = ComputeChecksum (ucTxt);

			if (uiIcs != uiXcs)		iPassed = 0;		 /*Checksum not correct */
			break;
		}
    } 
    return iPassed;
}

void StrH2I(unsigned char *pcPtr,unsigned short int *piNum)
{
    short int i = 0, j = 0, c;

	for (c = *pcPtr; isxdigit (c); c = pcPtr [++j])
    {
		i <<= 4;

		if (isdigit (c))	
			i |= c - '0';

		if (isupper (c))	
			i |= c - 'A' + 10;

		if (islower (c))	
			i |= c - 'a' + 10;

    }

    *piNum = i;
}

unsigned short int ComputeChecksum(unsigned char *pcLineToParse )
{
   int iCheckSumVal = 0,iIndx = 1;
   int iStringLen = (int) strlen((char *)pcLineToParse);

   /* Skip over the $ at the begining of the sentence */
   while( iIndx < iStringLen && pcLineToParse[ iIndx ] != '*' )
   {
      iCheckSumVal ^= pcLineToParse[ iIndx ];
      iIndx++;

   }
    return((unsigned short int) iCheckSumVal );
}

void extractGPSData(char *pcGPSBuf, READGPS_t *pstGPSData)
{
	char *pcGPSPtr = NULL;
	short int iField = 0;

	pcGPSPtr = strtok(pcGPSBuf, ",");

	for (iField = 1; iField < 11; )
	{
		pcGPSPtr = strtok(NULL, ",");

		iField = iField + 1;

		switch (iField)
		{
			case 2:
				sscanf(pcGPSPtr, "%s", pstGPSData->cTime);
				strcat(pstGPSData->cTime, "\0");
				#ifdef GPS_DEBUG
					printf("\nGPS time %s",pstGPSData->cTime);
				#endif	/*#ifdef GPS_DEBUG*/
				break;

			case 3:
				sscanf(pcGPSPtr, "%c", &pstGPSData->cStat);
				break;
			
			case 4:
				sscanf(pcGPSPtr, "%f", &pstGPSData->fLat);
				break;

			case 5:
				sscanf(pcGPSPtr, "%f", &pstGPSData->fLat);
				break;

			case 6:
				sscanf(pcGPSPtr, "%f", &pstGPSData->fLon);
				break;

			case 7:
				break;

			case 8:
				sscanf(pcGPSPtr, "%f", &pstGPSData->fSpeed);
				pstGPSData->fSpeed *= (float)CONV_KNOTS_KMPH;
				#ifdef GPS_DEBUG
					printf("\nSpeed %.3f",pstGPSData->fSpeed);
				#endif	/*#ifdef GPS_DEBUG*/
				break;

		/*	case 9:
				sscanf(pcGPSPtr, "%f", &pstGPSData->fAng);
				break;

			case 10:
				sscanf(pcGPSPtr, "%s", pstGPSData->cDate); 
				strcat(pstGPSData->cDate, "\0");
				break; */

			case 9:
			case 10:

				if((0 == consideforDate) &&  (9 == iField ))
				{
					//printf(" 9th field date \n");
					sscanf(pcGPSPtr, "%s", pstGPSData->cDate); 
					strcat(pstGPSData->cDate, "\0");
					#ifdef GPS_DEBUG
						printf("\nGPS date %s",pstGPSData->cDate);
					#endif	/*#ifdef GPS_DEBUG*/
					pstGPSData->fAng = 0.0f;
					break;
	
				}
				else if ((1 == consideforDate) &&  (9 == iField ))
				{
					sscanf(pcGPSPtr, "%f", &pstGPSData->fAng);
					break;
				}
				else if ((1 == consideforDate) &&  (10 == iField ))
				{
					sscanf(pcGPSPtr, "%s", pstGPSData->cDate); 
					strcat(pstGPSData->cDate, "\0");
					#ifdef GPS_DEBUG
						printf("\nGPS date %s",pstGPSData->cDate);
					#endif	/*#ifdef GPS_DEBUG*/
					break;
				}
				break;			

			default:
				break;
		} 
	}
}

short int DetectSpike(short int iSpeed)
{
	short int iFlag = 0;
	static uint32_t spikeClk = 0;
	static short int siPrevSpeed = 0;
	
	if ( 0 == siPrevSpeed )
	{
		siPrevSpeed = iSpeed;
		iFlag = 1;
	}
		
	/* Since, @160Kmph one travels 44.44m per second.
	 * so utmost in one second gap lat/lon diff may come 0.0246
	 * Hence, considering 0.030 diff.
	 * Similarly, speed diff in one second can't go beyond 5Kmph.
	 */
	if( abs(siPrevSpeed - iSpeed) >= 5 )
	{
		/* Removed the concept of spike count,
		 * added time basis checking for spike 
		 */
		if (0 == spikeClk)
		{
			spikeClk = SpoiGetSysTICs();
		}
	}
	else
	{	   
		spikeClk = 0; 
		iFlag = 1;
	}
	
	/* Added 3 seconds concept to take it as valid packet
	 * TIME_OUT_GPS_CHECK can be configured to change the time constraint 
	 */
	if ( SpoiElapsTICs(spikeClk) >= TIME_OUT_GPS_CHECK * ONE_SEC )
	{
		spikeClk = 0;
		iFlag = 1;
	}

	siPrevSpeed = iSpeed;

	if (iFlag)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


void NetworkTimeSync(READGPS_t *stGPSData)
{
	static uint32_t clkSync = 0;
	static uint32_t rtcupdateclkSync = 0;
	static uint32_t printgpsclkSync = 0;
//	long rtcupdationtime = PERIODIC_RTC_UPDATE_INT ;

	/*For Time beeing date and time are sending on every ONE Second*/
	
	if ((0 == clkSync) && (ONE == SetRTCDateTime(stGPSData)))
	{
//		printf("\n %d:%d:%d RTC TIME UPDATED",bcdToDec(Read_Rtc(0XD0,0X02)),bcdToDec(Read_Rtc(0XD0,0X01)),bcdToDec(Read_Rtc(0XD0,0X00)));
		#ifdef GPS_DEBUG
			printf("\nRTC Time Updated");
		#endif	/*#ifdef GPS_DEBUG*/
		clkSync = SpoiGetSysTICs();

		FormAndTransmitGPSData(stGPSData);
	}	
	
	#if 0
	if( ONE == syncTime )  
	{
		clkSync = SpoiGetSysTICs();

		if( ONE == SetRTCDateTime(stGPSData))
		{
//			printf("\nRecieved LPM Startup:: RTC Time Updated");
			FormAndTransmitGPSData(stGPSData);
			syncTime = 0;
			
		}

	}
	#endif

	if( SpoiElapsTICs(rtcupdateclkSync) >= PERIODIC_RTC_UPDATE_INT )/*For Every 1 hour update Date and time*/
	{
//		printf("Periodic RTC Time Updated( %ld milli secs)",rtcupdationtime);
		if( ONE == SetRTCDateTime(stGPSData))
		{
			rtcupdateclkSync = SpoiGetSysTICs();

			FormAndTransmitGPSData(stGPSData);

		}
	}
	if( SpoiElapsTICs(printgpsclkSync) >= PRINT_GPS_DATA_TIME )
	{
		printgpsdata( stGPSData );
		printgpsclkSync = SpoiGetSysTICs();
	}
	
}

void printgpsdata(READGPS_t *stGPSData)
{
	int iHour, iMin, iSec, iDay, iMonth, iYear;
	int cMonDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	char cBuf[3] = "\0";

	iHour  = atoi(memcpy(cBuf, &(stGPSData->cTime[0]), 2));
	iMin   = atoi(memcpy(cBuf, &(stGPSData->cTime[2]), 2));
	iSec   = atoi(memcpy(cBuf, &(stGPSData->cTime[4]), 2));

	iDay   = atoi(memcpy(cBuf, &(stGPSData->cDate[0]), 2));
	iMonth = atoi(memcpy(cBuf, &(stGPSData->cDate[2]), 2));
	iYear  = atoi(memcpy(cBuf, &(stGPSData->cDate[4]), 2));

	if( ( iYear % 4 ) == 0 )
	{
		cMonDays[1]++;
	}

	if( ( ( iHour == 18 ) && ( iMin >= 30 ) )
		|| ( iHour > 18 ) )
	{
		iDay++;
	
		if( iDay > cMonDays[iMonth - 1] )
		{
		    iMonth++;
		    iDay = 1;
		
			if( iMonth > 12 )
		    {
				iMonth = 1;
				iYear++;
		    }
		}
	}

	iHour = ( short int ) (iHour + 5 + ( short int ) (iMin + 30) / 60 ) % 24;
	iMin  = ( unsigned int ) ( (iMin + 30) % 60);
	stCanGpsInfo.ucHour	= iHour;
	stCanGpsInfo.ucSec	= iSec;
	stCanGpsInfo.ucMin	= iMin;
	
	stCanGpsInfo.ucDate = iDay;
	stCanGpsInfo.ucMonth = iMonth;
	stCanGpsInfo.ucYear =  iYear;	
	
	GPSframeNo = ((iHour * 3600) + (iMin * 60) + iSec) + 1;
//printf("\nREAL GPS DATE %2d-%2d-%2d TIME %2d:%2d:%2d\n",iDay,iMonth,iYear,iHour,iMin,iSec);
}

unsigned char  SetRTCDateTime(READGPS_t *stGPSData)
{
	int iHour, iMin, iSec, iDay, iMonth, iYear;
	int cMonDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	char cBuf[3] = "\0";
	RTCDateTime_t stlocalDateTime;

	iHour  = atoi(memcpy(cBuf, &(stGPSData->cTime[0]), 2));
	iMin   = atoi(memcpy(cBuf, &(stGPSData->cTime[2]), 2));
	iSec   = atoi(memcpy(cBuf, &(stGPSData->cTime[4]), 2));

	iDay   = atoi(memcpy(cBuf, &(stGPSData->cDate[0]), 2));
	iMonth = atoi(memcpy(cBuf, &(stGPSData->cDate[2]), 2));
	iYear  = atoi(memcpy(cBuf, &(stGPSData->cDate[4]), 2));

	if( ( iYear % 4 ) == 0 )
	{
		cMonDays[1]++;
	}

	if( ( ( iHour == 18 ) && ( iMin >= 30 ) )
		|| ( iHour > 18 ) )
	{
		iDay++;
	
		if( iDay > cMonDays[iMonth - 1] )
		{
		    iMonth++;
		    iDay = 1;
		
			if( iMonth > 12 )
		    {
				iMonth = 1;
				iYear++;
		    }
		}
	}

	iHour = ( short int ) (iHour + 5 + ( short int ) (iMin + 30) / 60 ) % 24;
	stlocalDateTime.ui_RTCHour = ( unsigned int ) iHour;
	stlocalDateTime.ui_RTCMin  = ( unsigned int ) ( (iMin + 30) % 60);
	stlocalDateTime.ui_RTCSec  = ( unsigned int ) iSec;

	stlocalDateTime.ui_RTCMday = ( unsigned int ) iDay;
	stlocalDateTime.ui_RTCMon = ( unsigned int ) iMonth;
	stlocalDateTime.ui_RTCYear =  iYear;

	if (1==SpoiRTCSetDateTime(stlocalDateTime))
	{
		return 1;
	}
	
	else
	{
		return 0;
	}

}


void FormAndTransmitGPSData(READGPS_t *stGPSData)
{

	//RTCDateTime_t stlocalDateTime;

	//stlocalDateTime = SpoiRTCGetDateTime();

	//stCanGpsInfo.ucGPSspeed		=	(unsigned short int)stGPSData->fSpeed;
//	stCanGpsInfo.ucHour			=	(unsigned char)stlocalDateTime.ui_RTCHour;
//	stCanGpsInfo.ucMin			=	(unsigned short int)stlocalDateTime.ui_RTCMin;
//	stCanGpsInfo.ucSec			=	(unsigned short int)stlocalDateTime.ui_RTCSec;
//	stCanGpsInfo.ucDate			=	(unsigned short int)stlocalDateTime.ui_RTCMday;
//	stCanGpsInfo.ucMonth		=	(unsigned short int)stlocalDateTime.ui_RTCMon;
//	stCanGpsInfo.ucYear			=	(unsigned short int)stlocalDateTime.ui_RTCYear;

  if(3 == gucSelfSlot)
	TransmitCanPkt(GPS_TIME_PKT);
  if(4 == gucSelfSlot)
  TransmitCanPkt(CM2_LPM_GPS_TIME_PKT);
	#ifdef GPS_DEBUG
		printf("\nSent CM_LPM_GPSINFO ");
	#endif	/*#ifdef GPS_DEBUG*/

	return;
}


