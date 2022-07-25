#ifndef __LOCO_H_
#define __LOCO_H_

#include "header.h"

//#define LOCO_SIMULATE
#undef LOCO_SIMULATE
/*	PACKET HEADER
 */



/* MODE OF OPERATIONS
 */	


/* SECTION TYPE*/

/* TCAS AREA */


/* TCAS HEALTH STATUS
 */

/* ABU STATUS
 */


/* TIN DETAILS
 */


/* Traffic Direction Details
 */

#define MAX_NO_OF_LOCOS  10
#define MAX_TRNLEN_LOCO	 2
//#define MAX_LANDMRK_LOCO 2

typedef struct 
{
	unsigned long ulLocoId;
	unsigned long ulRefFrameNo;
	unsigned char ucType;
	unsigned char ucOffset;
	unsigned long iRefFrameNum;
	unsigned char ucReTxCnt;
	
}TRNLENSTAT_t;
extern TRNLENSTAT_t trnLenStat[MAX_TRNLEN_LOCO];
#pragma pack(1)
typedef struct locomsg
{
	unsigned int uiFrameNum;
	unsigned int uiSourceID;
	unsigned long ulAbsLoc;
	unsigned int  uiTrainLength;
	unsigned char ucTrainSpeed;
	unsigned char ucTrafficDir;
	unsigned char ucEmergencyStatus;
	unsigned char ucPrevEmergencyStat;
	unsigned char ucMode;
	unsigned char ucHealth;
	unsigned char ucABUIsolation;
	unsigned short ucLastRFIDTAG;
	unsigned char ucRXSuccRate;
	unsigned char ucTIN;
	unsigned char dir;
	unsigned char ucRecByLoco;
	unsigned char ucProfileID;
	unsigned char ucStaticProffReq;
	unsigned char ucAthenticFlag;
	unsigned short usSTNRandomNmbr;
	unsigned short usLocoRandomNmbr;
} LOCOMSG_t;

extern LOCOMSG_t stLocMsg;

void extractLocoPacket(unsigned char *,HEADER_t * , short int,unsigned char);





typedef struct stLocoMessage
{
	unsigned long ulLocoId;

}LOCOMESSAGE_t;

typedef struct StnNMSmsg
{
	unsigned char Paketlength;
	unsigned char TxStnMessage[100];
	unsigned char locoPktLen;
	unsigned char RxLocoMessage[50];
	unsigned short int locoId;
	
} STN_NMS_MSG;
extern STN_NMS_MSG stStnNmsMsg;

typedef struct 
{
	unsigned long ulLocoId;
	unsigned char ucCollision;
	unsigned char ucTypeOfSignal;
	unsigned char ucSigDir;
	unsigned char ucLineNumber;
	unsigned char ucCurSigAspect;
	unsigned char ucNextSigAspect;
	unsigned short int uiMAwrtSig;
	unsigned char uiGradMAwrtSig;
	unsigned char ucNextSigIntlkg;
	unsigned short int uiDiffDistNextSig;
	unsigned short int uiAppStnId;
	unsigned char ucToSpeed;
	unsigned short int uiDiffDistTo;
	unsigned char ucToSpeedRelDist;
	unsigned char ucPreferredTxWindow;
	//unsigned char ucFreqPair;	
	unsigned int uiFrameNum;
	unsigned char ucAthenticFlag;
	unsigned short usSTNRandomNmbr; 
	unsigned short usLocoRandomNumbr; 
} SIGINFO_t;


typedef struct
{
	unsigned long ulLocoId;
	unsigned char ucType;
//	unsigned short iRefFrameNum;
//	unsigned char ucOffset;	
} TRNLEN_t;

#pragma pack(4)
extern SIGINFO_t siginfo[MAX_NO_OF_LOCOS],tempSigInfo[2];
extern unsigned long sigUpdateTime[MAX_NO_OF_LOCOS];
extern TRNLEN_t trnLenInfo[MAX_TRNLEN_LOCO],tempTrnLenInfo[2];


extern unsigned char gucNoOfLoco_sig;
typedef struct stSelfLocoInfo
{
	unsigned long ulLocoId ;
	SIGINFO_t siginfo; 
} LOCOINFO_t;


#ifdef LOCO_SIMULATE
void vfnSimulatedLocoPkt(void);
void vfnSimulatedLocoPkt1(void);
void vfnSimulatedLocoPkt2(void);
void vfnSimulatedLocoPkt3(void);
void vfnSimulatedLocoPkt4(void);
void vfnSimulatedLocoPkt5(void);
#endif
void delSigInfoNodes(void);
unsigned char getLocoIndex(unsigned long );
unsigned char getTrnLocoIndex(unsigned long );
void updadeTrnLenNodes(void);
void updateTrainLenStat(TRNLEN_t );
//unsigned char getTsrLocoIndex(unsigned long );
#endif /* #ifndef __LOCO_H_ */

