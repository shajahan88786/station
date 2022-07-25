#ifndef __RM_H_
#define __RM_H_



/* Type Of Packet on RM
 */
#define SIGNALLING_INFO_BY_STN_ILC_IBS		0x01	/* BY STN  Annexure -   I			*/
#define PACKET_FROM_LOCO_TCAS				0x02	/* BY LOCO Annexure -  II			*/
#define LM_INFO_BY_STN_ILC_IBS				0x03	/*BY LOCO Annexure -  III			*/

#define TRAIN_LEN_START_PACKET				0
#define TRAIN_LEN_END_PACKET				1

#define SOP1 0xA5
#define SOP2 0xC3

#define RTS_PROTOCOL

#define PRETRANSMITTIME     50
extern volatile unsigned char TxFlag;
extern volatile unsigned char Tx1Flag; 
extern volatile unsigned char Tx2Flag;
extern volatile unsigned char TimerFlag;
extern unsigned char stationPkt[256]; 
extern unsigned char stationPkt2[256];
extern unsigned char gucSlotControlPacket[256];	
extern unsigned char gucEmrgncyPkt[256];

extern unsigned char dataLoggerPkt[256];
extern unsigned char gucSlotPktOnPort;
extern unsigned char gucEmgPktOnPort;
extern unsigned char gucTimerFrequencySet;
extern unsigned char gucTimerFrequencyClr;
extern unsigned char locoPresentFlag;
typedef struct stnMsg
{
	unsigned int uiStnSourceID;/*Self ID*/
	unsigned int  fAbsLoc;/* To Maintain self Absolute Distance*/	
	char cNoOfLocos;/* To Maintain no of Locos that need to be handled. */
	short int iFrameNum;/* To Maintain FrameNum used while trans*/
	unsigned int ucVersion;
	unsigned char ucPreferredTXWindow;/*Station*/
	short int iSOSstat;
} STNMSG_t;


typedef struct stSignalInfo
{
	unsigned char ucSigLineNo;
	unsigned char ucSigDir;
	unsigned char ucSigType;
}stSIGINFO_t;



extern STNMSG_t stStnMsg;




void processReceiveMessage(unsigned char *);
short int rReadAndFormMessageNoDle(short int iPort,			
							  unsigned char *pcReadMsg, 
							  short int iIntegritySize, 
							  short int iWhichIntegrity, 
							  short int iMaxSize);

unsigned short int AnalyzeHeader(  unsigned char	* pszMessage, short int);

							   
unsigned int getFrameNum(void);

unsigned char formStationPacket(unsigned char *ucstationPkt, unsigned char ucLocoIndex);
void formSlotControlPacket(void);
unsigned char formEmergencyPacket(void);
void processAuthenticationKeyRequest(void);

//void transmitStationPacket(void);

unsigned char processTransmissionToModem(void);

unsigned char processSlotControlPacketToModem(void);

unsigned char processEmergencyPacketToModem(void);

void formStaticTrackProfilePkt(void);

void transmitAccConPktToModem(void);

void vfnFireRadioPkt(void);

void transmitStnPktToModem(void);

//	Radio Modem SET up Port
int ProcessRmHealthHEXPkt(unsigned char *Health);
void ProcessRmHealthASCIIPkt(unsigned char *Health);
void ReadRMSetupPortASCII(unsigned char port);
void ReadRMSetupPortHex(unsigned char port);

unsigned int ReadModemHealthHEX(unsigned char iport,unsigned char *Rep);
unsigned int ReadModemHealthASCII(unsigned char iport,unsigned char *Rep);
void SendModemDiagnosticReqHEX(unsigned char iport);
void SendModemDiagnosticReqASCII(unsigned char iport);
void FindRMHealth(unsigned char port);

void ReadTXReplay(unsigned char ucPort);
void SendResetCmdToRM(void);



#endif /* __RM_H_ */

