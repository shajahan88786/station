#ifndef __SPEEDO_H
#define __SPEEDO_H


#define SPEEDOFAIL				0x80

#define WHEELDIAMETER			1092
#define WHEELROTATIONPERSEC		60


#define CONVERSIONFACTOR	3.6f
#define PI					3.1428

#define MAX_PEEKS			4000




typedef struct stSpeedo
{
	unsigned char ucSpeedoStatus;
	unsigned int uiCurrentSpeedoPeeks;
	float fSpeedometerSpeed;
	float fSpeedometerDistance;
	unsigned int uiSpeedometerPeeks;


	unsigned long ulWheelDiameter;
	unsigned long ulWheelRotation;
	float fCalibrationConstant;

}SPEEDO_t;

extern SPEEDO_t stSpeedo;


unsigned short int rReadAndFormMessageForSpeedo1(unsigned short int us_Port,
                    unsigned char *puc_ReadMsg,unsigned short int us_MaxSize);

short int rReadAndFormMessageForSpeedo(short int iPort,			
							  unsigned char *pcReadMsg, 
							  short int iIntegritySize, 
							  short int iWhichIntegrity, 
							  short int iMaxSize);

void readSpeedometerData(short int iPort);

void AnalyzeSpeedometerAndComputeSpeed(unsigned char *RecvMsg);


#endif /* __SPEEDO_H */
