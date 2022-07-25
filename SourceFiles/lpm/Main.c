/******************************************************************************
* File Name			: Main.c
*
* Abstract		    : This file contains the routines to start the application. 
*					  
* Date of creation  :       09/11/2013
* Date of Modification :               
* Created by        :        kernex
* Modification history :
* +--------------------------------------------------------------------------+
* |   Revision  |      SPR        |  AR    |    DATE	|     Remarks	     |
* |-------------|-----------------|--------|------------|--------------------|
* |    1.0		| Initial Release |        |		    |                    |
* +--------------------------------------------------------------------------+
*
* Compiler/Assembler/Linker:                    
******************************************************************************/

#include <RTL.h>                      /* RTL kernel functions & defines */

#include "Main.h"
#include "Header.h"
//uint32_t sui_AppSensorFailIndTime = ZERO;

/******************************************************************************
* File Header			:   Main.c
* Procedure Name        :   main
* Package Name          :   
* Date of creation      :   09/11/2013
* Date of Modification  :   
* Created by            :   kernex
* Modification history  :
* +--------------------------------------------------------------------------+
* |   Revision  |      SPR        |  AR    |    DATE			|     Remarks	     |
* |-------------|-----------------|--------|------------|--------------------|
* |   	 1.0		| Initial Release |        |				    |                    |
* +--------------------------------------------------------------------------+
*
* Abstract			: This function starts the application.
*						                           
*					   
* Allocation		:  NIL	    
* DR                :  SRS		SDR		SWRS		DR        
*					   							
* 					   							
* 					   							
* 					   							
* 					   							
* Interfaces			
* Calls				: 
*						1.SpoiGPIOInit(), 
*						2.SpoiWDTInit(), 
*						3.SpoiRTCInit(),
*                       4.SpoiSysTimeInit(),
*						5.CommWatchDogStrobe(),
*                       6.SpoiUartInitialize(),
*						7.CommMCMSelection(),
*                       8.SpoiWDTReload(),
*						9.IdrvOutputDefaultInit(),
*						10.DateTime(),
*						11.CommProcessMaster(),
*						12.OndsCbit(),
*						13.CommTransmitBroadcastPacket(),
*						14.OfdsMbit(),
*						15.LpsoModuleControlFunction(),
*						16.CommChanHealth(),
*                       17.LpsoIntilizeFunction(),
*						18.initLpsoConfigAtStartUpOnly(),
*						19.CBitIntilizeFunction(),
*						20.MBitStructInitialzeFunc(),
*						21.CommInitEventStruct(),
*						22.IdrvInputDataReading(),
*					    23.Cmgt_ReadAndValidateConfig(),
*						24.SpoiresetTazOnPowerOn()
*						25.IdrvFlBellsConfigData(),
*						26.Idrv_BarrierEmergencyConfigFromDIPSwitch(),
*						27.CommTransmitEvent()
*						28.IdrvOutputReload();
*
* Called by			: None
*					  
* Input variables   
*					   Type              Name		   comments 
* Local variables	:unsigned char	uc_MCMOpMode	To Store the Mode of
*					 								  operation           
* 					 unsigned char	uc_LoopCnt		For looping         
*
*					   Type              Name		   comments 
* Global variables	: HltChk_t    st_Onds_HltChk   Health Check of the ECM 
*					  
* Output variables    	       
* Local variables   : None
*					 
*					   Type             Name	   	   comments 
* Global variables  : None
*						
* Reference	SWDD      
*
* Derived Requirements
* Program Design Language:  
*
* Step1: Initalize general purpose I/O pins
* Step2: Initalize Watch Dog Timer
* Step3: Initalize RTC
* Step4: Initalize of System Timer
* Step5: Generate Watchdog Strobe Signal 
* Step6: Initalize UART0 
* Step7: Initalize UART2 
* Step8: Select Self MCM Id
* Step9: Set the O/P's to default values

******************************************************************************/
extern unsigned char sucPPSDebugFlag;
extern unsigned char processTransmitFlag ;
extern unsigned char processslotcontolTransmitFlag ;
extern unsigned char processEmergencyFlag ;

extern unsigned char FormSlotControlPkt;

//extern unsigned char PPS_check;
void   timercontrolRegister(void);
//unsigned char locoPresentFlag  =0;
#undef CYCLETIMECHECK
extern STN_NMS_MSG stStnNmsMsg;
int main()
{
	
    //	unsigned char ucTSlot = 0;
    //	unsigned long slotdifference=0;
//	unsigned short int j =0;
	unsigned char szReceivedMessage[60] = "\0";
	unsigned long dataLoggerClk = 0;
	unsigned long nmsClk =0;
	unsigned char ucLocoIndex =0;
	#ifdef CYCLETIMECHECK
	unsigned long cycleClk=0;
	unsigned short int cycles = 0;
	#endif
	//unsigned long ulRMStatusClk = 0;
	//unsigned long ulRMResetClk = 0;

	processTransmitFlag=2;	
	trnLenStat[0].ucType = 2;
	trnLenStat[1].ucType = 2;
	spoiInitializeTcasHardware();
	printf("TCAS initialization successfull For Communication...\n");
	
	CheckCrcOnStartup();

	//processAuthenticationKeyRequest(); // process key management.It req to LPM for key at the start 
	//ulRMStatusClk = SpoiGetSysTICs();
	//ulRMResetClk = SpoiGetSysTICs();
	while(ONE)
	{ 	
	
		#ifdef WATCHDOG
			SpoiWDTReload();
			CommWatchDogStrobe();			/* Watchdog Strobe Signal */
		#endif	
		readCanToStructs();
		processTransmitFlag = processTransmissionToModem();
		processslotcontolTransmitFlag	= processSlotControlPacketToModem();

		ReadRMSetupPortASCII(TXPORT); // Read ASCII Reply From RadioModem SetUp Port
		//ReadRMSetupPortHex(TXPORT);		//Read Hex Reply From RadioModem SetUp Port

		//processEmergencyFlag = processEmergencyPacketToModem();
		if (sucPPSDebugFlag == 1)
		{
			if((locoPresentFlag == 0)&&(stSelfInfo.ucFreqPair > 0))
			{
				//printf("\nLOco is not present");
				FrquncyShift_FSToF0();
				
			}	
			if(3 == gucSelfSlot)
			{	
				
				stCanCom1Com2_SwapStatusInfo.Swap_flag = stCanCom1Com2_SwapStatusInfo.Swap_flag + 1;
					if(((stCanCom1Com2_SwapStatusInfo.Swap_flag % 2) != 0)
					 &&(0x00 == stCanRadioModemFailStatusRx.ucRadioFailStatus))
					{
					  T3TCR = 0;
					  T1TCR = 0;
					  T1TC = 0;
			    //if(locoPresentFlag == 0)
					{
						//ulRMStatusClk = SpoiGetSysTICs();
						
					//	printf("loco not present.......\n");
//						
//						if(gucRadioModemResetFlag == 1)
//						{
//							TransmitCanPkt(LPM_RADIO_MODEM_HEALTH);
//							SendResetCmdToRM();
//						}
//						memset(ucHealthReplayASCII,'\0',sizeof(ucHealthReplayASCII)) ;
//						SendModemDiagnosticReqASCII(RXPORT);
						//SendModemDiagnosticReqHEX(RXPORT);
						
				
		       	}
				
						
				}
				else if( 0x00 == stCanRadioModemFailStatusTx.ucRadioFailStatus)
				    {
					sucPPSDebugFlag = 0;
					updadeTrnLenNodes();
					{

						formSlotControlPacket();
						configTimers(stSelfInfo.ucSelfTimeSlot);
						configSlotControlPkt();	
						ConfigEmergencyPkt();
				
					}
					ucLocoIndex = 0;
				ucLocoIndex = formStationPacket(stationPkt,ucLocoIndex);
				if(ucLocoIndex > 0)
				{
				formStationPacket(stationPkt2,ucLocoIndex);	
				}
				else
				memset(stationPkt2, 0 , 256);	
					
				}
				else
				{
				   T3TCR = 0x00;
				   T1TCR = 0x00;
				}
			if(stCanCom1Com2_SwapStatusInfo.Swap_flag >= 60)
			{
				stCanCom1Com2_SwapStatusInfo.Swap_flag = 0;
			}
			
		}
		sucPPSDebugFlag = 0;
		if((4 == gucSelfSlot) && ((1== gucHealthFlag)
		||(1 ==  stCanRadioModemFailStatusRx.ucRadioFailStatus)))
		{

				T1TCR = 1;
			   	T1TC =0;
     		loadTimer1MR0(TWO_SEC_NS);
			formSlotControlPacket();
			formEmergencyPacket();
			updadeTrnLenNodes();
			configTimers(stSelfInfo.ucSelfTimeSlot);
			configSlotControlPkt();	
			ConfigEmergencyPkt();
			gucHealthFlag = 0;
			ucLocoIndex = 0;
			ucLocoIndex = formStationPacket(stationPkt,ucLocoIndex);
			if(ucLocoIndex > 0)
			{
				formStationPacket(stationPkt2,ucLocoIndex);	
			}
			else
				memset(stationPkt2, 0 , 256);
			//printf("\n*** T1TC is %d",T1TC);
			
	 
	  //gucSlot3Fail = 0;		//comment here
	}
	#if 0
	else if(4 == gucSelfSlot)
	{
		if(locoPresentFlag == 0)
		{
					
			
			if(gucRadioModemResetFlag == 1)
			{
				TransmitCanPkt(LPM_RADIO_MODEM_HEALTH);
				SendResetCmdToRM();
			}
			memset(ucHealthReplayASCII,'\0',sizeof(ucHealthReplayASCII)) ;

			SendModemDiagnosticReqASCII(RXPORT);
			//SendModemDiagnosticReqHEX(RXPORT);
		}
    			

	}
	#endif
		
	//printf("\n T1TC is %ld ", T1TC);
	 if(T1TC < 3)
	 {
		 //if(locoPresentFlag == 0)
		 {
	  		if(gucRadioModemResetFlag == 1)
			{
					TransmitCanPkt(LPM_RADIO_MODEM_HEALTH);
					SendResetCmdToRM();
			}
				memset(ucHealthReplayASCII,'\0',sizeof(ucHealthReplayASCII)) ;
				SendModemDiagnosticReqASCII(RXPORT);
		}
	 }
	 sucPPSDebugFlag = 0;
	}
	if((gucRTSHighRMShiftFlag == 1)
		&&(3 == gucSelfSlot))
	{
	    if(0x00 == stCanRadioModemFailStatusRx.ucRadioFailStatus)
		TransmitCanPkt(CM1_CM2_STATUSINFO);
		gucRTSHighRMShiftFlag = 0;
    }		
	
	if( 1 == gucTimerFrequencySet)
	{
		
		
		    timeflag = 1;
			FrquncyShift_F0ToFS();
			gucTimerFrequencySet = 0;
			
	}
	if( 1 == gucTimerFrequencyClr)
	{

		      timeflag = 0;
			  FrquncyShift_FSToF0();
		      gucTimerFrequencyClr = 0;

   }		
  	

	if(labs(SpoiGetSysTICs()-dataLoggerClk > 10000))
	{
			dataLoggerClk = SpoiGetSysTICs();
	}
	
		ReadGPSData(GPSPORT);
				

		delSigInfoNodes();
		
		

		#ifdef LOCO_SIMULATE
			vfnSimulatedLocoPkt1();
			vfnSimulatedLocoPkt2();
			vfnSimulatedLocoPkt3();
			vfnSimulatedLocoPkt4();
			vfnSimulatedLocoPkt5();
		#endif

		processReceiveMessage(szReceivedMessage);

		#ifdef WATCHDOG
			SpoiWDTReload();
			CommWatchDogStrobe();			/* Watchdog Strobe Signal */
		#endif
		
	  if(((labs(SpoiGetSysTICs()-nmsClk)> 2000)&&(locoPresentFlag ==0))&&( 3 == gucSelfSlot))
    {
			TransmitCanPkt(STN_NMS_PKT);
			//printf("\n Sent Can NMS Stn PKT stn %d loc %d\n",stStnNmsMsg.Paketlength,stStnNmsMsg.locoPktLen);
			nmsClk = SpoiGetSysTICs();
	   }
		
	}
	

}
/*End of file*/
