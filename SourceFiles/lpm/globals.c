
#include "Header.h"

LOCOTCASIO_t stIdrvTcas;

SELFINFO_t stSelfInfo,tempStSelfInfo[2];
CanSigStatus SigStatus,tempSigStatus[2];

LOCOMSG_t stLocMsg;

ENCRYPT Encryption[MAX_NO_OF_LOCOS];

STN_NMS_MSG stStnNmsMsg;
unsigned char gucNoOfLoco_sig = 0;
//unsigned long  ulCANCLK = 0;

SIGINFO_t siginfo[MAX_NO_OF_LOCOS],tempSigInfo[2];
unsigned long sigUpdateTime[MAX_NO_OF_LOCOS];
TRNLEN_t trnLenInfo[MAX_TRNLEN_LOCO],tempTrnLenInfo[2];
TRNLENSTAT_t trnLenStat[MAX_TRNLEN_LOCO];


stCAN_HEXFILECRC_t stCanComCrcVal;
stCAN_HEXFILECRCREQREC_t stCanHexCrcvalReqRec,tempstCanComCrcVal[2];

uint32_t PPS_Clock;
uint32_t PPS_ONE_OK_Clock;
uint32_t GPSclk;
#ifdef LANDMARKPKT 
LAND_MARK_PKT_t landMarkInfo[MAX_LANDMRK_LOCO],tempLandMarkInfo[2]; 
#endif
unsigned char stationPkt[256];
unsigned char stationPkt2[256];
unsigned char gucSlotControlPacket[256];
unsigned char gucEmrgncyPkt[256];
unsigned char dataLoggerPkt[256] = "\0";
RTCDateTime_t st_CanDateTime;
unsigned char gucPPSDebugFlag = 0;
unsigned char timeflag;
unsigned char syncTime = 0;
unsigned char gucSelfSlot = 0;
unsigned char gucHealthFlag =0;
unsigned char gucSlot3Fail = 0;
unsigned int uiframeno = 0; 
unsigned char StaticProfilePkt[256];
//unsigned char ucProfileID = 0;
unsigned int  uiDestnationLOcoID = 0;
GPS_DATE_TIME_t stCanGpsInfo;
stCAN_COM1_COM2_STATUSCHK_t stCanCom1Com2_SwapStatusInfo, stCanCom1Com2StatusInfo_SwapFillStruct;
STATIC_PROFILE_INFO_t staticProfileInfo,tempStaticProfileInfo[2];

volatile unsigned char TimerFlag = 0;
volatile unsigned char TxFlag = 0;
volatile unsigned char Tx1Flag = 0;	
volatile unsigned char Tx2Flag = 0;
unsigned long timerClk = 0;
uint32_t gCommHealthClock=0;
short int gui_CalCrc =0;
unsigned long GPSframeNo = 0;
unsigned char gucSlotPktOnPort = 0;
unsigned char gucEmgPktOnPort = 0;
unsigned char gucTimerFrequencySet = 0;
unsigned char gucTimerFrequencyClr = 0;
unsigned char locoPresentFlag  =0;

 #if 0
unsigned long stnTimeSlot[9] = {  /*11000*/ 3458 ,
																	/*21000*/ /*12833*/ 16291,
																	/*41000*/ /*34708*/ 46291,
																	/*61000*/ 56583,
																	/*81000*/ 90958,
																	/*101000*/103583,
																	/*103000*/112833,
																	/*105000*/161833,
																	/*107000*/190958
																	};

 #endif
 
//unsigned long stnTimeSlot[86] = {  3666,5833,8000,10166,12333
//                                  ,14500,16666,18833,21000,23166
//	                                ,25333,27500,29666,31833,34000
//                                  ,36166,38333,40500,42666,44833
//                                  ,47000,49166,51333,53500,55666
//                                  ,57833,60000,62166,64333,66500
//                                  ,68666,70833,73000,75166,77333
//                                  ,79500,83833,86000,88166,90333
//                                  ,94666,96833,101500,103666,105833
//                                  ,108000,110166,112333,114500,116666
//                                  ,118833,121000,123166,125333,127500
//                                  ,129666,131833,134000,136166,138333
//                                  ,140500,142666,144833,147000,149166
//                                  ,151333,153500,155666,157833,160000
//                                  ,162166,164333,166500,168666,170833
//                                  ,173000,175166,177333,181666,183833
//                                  ,186000,188166,190333,194666,196833
//                              };


unsigned long stnTimeSlot[79] = {2500,4833,7166,9500,11833,
									14166,16500,18833,21166,23500,
									25833,28166,30500,32833,35166,
									37500,39833,42166,44500,46833,
									49166,51500,53833,56166,58500,
									60833,67666,70000,72333,74666,
									77000,79333,81666,84000,86333,
									88666,91000,93333,95666,102500,
									104833,107166,109500,111833,114166,
									116500,118833,121166,123500,125833,
									128166,130500,132833,135166,137500,
									139833,142166,144500,146833,149166,
									151500,153833,156166,158500,160833,
									167666,170000,172333,174666,177000,
									179333,181666,184000,186333,188666,
									191000,193333,195666};


unsigned char gcMidBlockSectionSlots[4] = {36, 37, 75, 76};
unsigned char gcEmergencySlots[4] = {38, 39, 77, 78};
unsigned char BroadcastSlot[8] = {28,29,30,31,32,33,34,35};
unsigned char gucT2MR0=0, gucT2MR1=0;
unsigned char gucRTSHighRMShiftFlag = 0;

//for RM 
unsigned char gucRadioModemResetFlag = 0,gucRadioModemResetFlagHex = 0;
RADIOMODEMHEALTH_t RadioModemHealth;	//sid
CAN_RADIOMODEM_FAIL_STATUS_t stCanRadioModemFailStatusTx,stCanRadioModemFailStatusRx,stCanRadioModemFailStatusRxFillStruct;		//sid (For radio failure)
Authentication_KEY_t Authentication_KEY,tempAuthentication_KEY[2];
Authentication_KEY_comSend_t Authentication_KEY_comSend,tempAuthentication_KEY_comSend[2];
CAN_RADIOMODEM_STATUS_LOG_t stCanRadioModemStatusLog;


//unsigned char COM_KEY_REQ_FLAG = 0;
