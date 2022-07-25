#ifndef GPS_H
#define GPS_H

#define START_RMC			'$'
#define END_RMC				0x0A
#define CONV_KNOTS_KMPH		1.845f
#define TIME_OUT_GPS_CHECK	3
#define MAX_CATEGORY  32
#define MAX_STATICINFO  31
#define MAX_LCPERSTATION 10
#define MAX_LM_TYPE				8
#undef GPS_DEBUG

typedef struct readgps
{
	char cTime[10];	/*  1st Field - UTC ofPosition Fix */
	char cDate[10];	/*  9th Field - Date : dd/mm/yy */
	float fLat;		/*  3rd Field - Latitude */
	float fLon;		/*  5th Field - Longitude */
	char cLatDir;	/*  4th Field - Latitude Direction N (North) or S (South)*/
	char cLonDir;	/*  6th Field - Longitude Direction E (East) or W (West)*/
	float fSpeed;	/*  7th Field - Speed over the ground (SOG) in knots */
	float fAng;		/*  8th Field - Track made good in degrees true*/
	char cStat;		/*  2nd Field - Status 'A'=Valid, 'V'=navigation receiver warning */
	float magVar;	/* 10th Field - Magnetic variation in degrees */
	char cMagVarDir;/* 11th Field - Magnetic variation Direction, E = East / W = West */	
	uint32_t avblClk;

}READGPS_t;

#pragma pack(1)
typedef struct
{
	unsigned char ucHour;
	unsigned char ucMin;
	unsigned char ucSec;
	unsigned char ucDate;
	unsigned char ucMonth;
	unsigned char ucYear;
	
}GPS_DATE_TIME_t;

typedef struct 
{
	//unsigned char ucHealth;
	unsigned char Swap_flag;
}stCAN_COM1_COM2_STATUSCHK_t;
#if 0
typedef struct
{
	unsigned long ulSubStaicSegmentStartABSLoc;
	unsigned short usSegmentDistance;
	unsigned char  ucStaticProfID;
	unsigned char ucSubStaitcProfCnt;
	unsigned char ucSubStaitcProfID;
	//unsigned char ucSegmentCountforGroup;
	//unsigned char ucCurrentSegmentIDinGroup;
	unsigned char ucSigmentDirection;
	unsigned char ucType[LM_TYPE];
	unsigned char ucSpeed_Info_Cnt;
	unsigned char ucStatic_Speed_Type[MAX_CATEGORY];
	unsigned short usStatic_Speed_Distance[MAX_CATEGORY];
	unsigned char ucStatic_Speed_Value[MAX_CATEGORY];
	unsigned char ucGradient_Info_Cnt;
	unsigned short usGradient_Distance[MAX_CATEGORY]; 
	unsigned char ucGDIR[MAX_CATEGORY];
	unsigned char ucGradient[MAX_CATEGORY];
	unsigned char ucLC_Info_Cnt;
	unsigned short usLC_Distance[MAX_CATEGORY];
	unsigned short usLC_ID_Numaric[MAX_CATEGORY];
 	unsigned char ucLC_ID_Alpha_Suffix[MAX_CATEGORY];
	unsigned char ucLC_Manning_Type[MAX_CATEGORY];
	unsigned char ucLC_Class[MAX_CATEGORY];
	unsigned char ucAuto_Whisling_Enable[MAX_CATEGORY];
	unsigned char ucAuto_Whisling_Type[MAX_CATEGORY];
	
}STATIC_PROFILE_INFO_t;
#endif

typedef struct locomsg2
{
	unsigned long ulLocoID;
	unsigned long ulSubStaicSegmentStartABSLoc;
	unsigned short usSegmentDistance;
	
	unsigned short usStatic_Speed_Distance[MAX_CATEGORY];
	
	unsigned short usGradient_Distance[MAX_STATICINFO]; 
	
	unsigned short usLC_Distance[MAX_LCPERSTATION];
	unsigned short usLC_ID_Numaric[MAX_LCPERSTATION];
	
	unsigned char  ucStaticProfID;
	unsigned char ucSubStaitcProfCnt;
	unsigned char ucSubStaitcProfID;
	unsigned char ucSigmentDirection;

	unsigned char ucSpeed_Info_Cnt;
//	unsigned char ucStatic_Speed_Type[MAX_CATEGORY];
	unsigned char ucStatic_Speed_Value[MAX_CATEGORY][MAX_LM_TYPE];
	
	unsigned char ucGradient_Info_Cnt;
	unsigned char ucGDIR[MAX_STATICINFO];
	unsigned char ucGradient[MAX_STATICINFO];
	
	unsigned char ucLC_Info_Cnt;
 	unsigned char ucLC_ID_Alpha_Suffix[MAX_LCPERSTATION];
	unsigned char ucLC_Manning_Type[MAX_LCPERSTATION];
	unsigned char ucLC_Class[MAX_LCPERSTATION];
	unsigned char ucAuto_Whisling_Enable[MAX_LCPERSTATION];
	unsigned char ucAuto_Whisling_Type[MAX_LCPERSTATION];
}STATIC_PROFILE_INFO_t;

#pragma pack(4)

extern stCAN_COM1_COM2_STATUSCHK_t stCanCom1Com2_SwapStatusInfo, stCanCom1Com2StatusInfo_SwapFillStruct;
extern STATIC_PROFILE_INFO_t staticProfileInfo,tempStaticProfileInfo[2];


extern unsigned char syncTime;
extern GPS_DATE_TIME_t stCanGpsInfo;

void FormAndTransmitGPSData(READGPS_t *stGPSData);
void ReadGPSData(short int iPort);
short int GetGPSData(short int iPort,READGPS_t * pstGPSData);
short int CheckSumOk (unsigned char *ucTxt);
void StrH2I (unsigned char *pcPtr,unsigned short int *piNum);
unsigned short int ComputeChecksum(unsigned char *pcLineToParse );
void extractGPSData(char *pcGPSBuf, READGPS_t *pstGPSData);
short int DetectSpike(short int iSpeed);
void NetworkTimeSync(READGPS_t *stGPSData);
unsigned char SetRTCDateTime(READGPS_t *stGPSData);
void printgpsdata(READGPS_t *stGPSData);

void formTimeCanPkt(void);
unsigned bcdToDec(unsigned char );


#endif	/*#define GPS_H*/
