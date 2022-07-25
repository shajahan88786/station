/******************************************************************************
* File Name			: CBit.h
*
* Abstract		    : This file contains the routines for feedback checking 
*					  of Flashers, Bells, Dvrs, Barriers, Batt Low, AcMains 
*					  WSS/Track Circuits e.t.c.                             
*
* Date of creation  :       21/10/2009 
* Date of Modification :               
* Created by        :        dskr
* Modification history :
* +--------------------------------------------------------------------------+
* |   Revision  |      SPR        |  AR    |    DATE	|     Remarks	     |
* |-------------|-----------------|--------|------------|--------------------|
* |    1.0		| Initial Release |        |		    |                    |
* +--------------------------------------------------------------------------+
*
* Compiler/Assembler/Linker: Armcc.exe V3.1.0.919, Armasm.exe V3.1.0.919,
*                               ArmLink.exe V3.1.0.919                   
******************************************************************************/


#ifndef CBITINIT_H
#define CBITINIT_H
						

//extern unsigned char uc_FIBDiagAlterationFlag; /* for FIB Diag */
typedef struct 
{
    unsigned char uc_OccUP; /* For Occ UP status in Electrical */
    uint32_t ui_TimerOccUP[3];/*for three state : HIGH, LOW, THREE (Fail)*/   
    unsigned char uc_OccDN; /* For Occ DN status in Electrical */
    uint32_t ui_TimerOccDN[3];/*for three state : HIGH, LOW, THREE (Fail)*/   
    unsigned char uc_ClearUP; /* For Clear UP status in Electrical */
    uint32_t ui_TimerClearUP[3];/*for three state : HIGH, LOW, THREE (Fail)*/   
    unsigned char uc_ClearDN; /* For Clear DN status in Electrical */
    uint32_t ui_TimerClearDN[3];/*for three state : HIGH, LOW, THREE (Fail)*/   
} TrainApp_t;

extern TrainApp_t st_Onds_ElecTrApp; /* Declared for Track Circuit Fail */

typedef struct 
{
    unsigned char uc_EmA; /* For Emergency A Selection */
    unsigned char uc_EmB; /* For Emergency B Selection */
    unsigned char uc_EmC; /* For Emergency C Selection */
} Emergency_t;

extern Emergency_t st_Onds_ABCSwitch; /* Declared for Emergency Switch Fail */

typedef struct 
{
    unsigned char uc_SAM; /* For Semi Auto Mode Selection */
    unsigned char uc_ROM; /* For Restricted Mode Selection */
    unsigned char uc_MANUAL; /* For Manual Mode Selection */
} Mode_t;

extern Mode_t st_Onds_ModeSwitch; /* Declared for Mode Switch Fail */

typedef struct 
{
    unsigned char uc_Normal; /* For Noraml Operation*/
    unsigned char uc_Reverse; /* For Reverse Opeartion */
} Lever_t;

extern Lever_t st_Onds_LxLever; /* Declared for Lx Lever Status */ 
extern Lever_t st_Onds_SignalLever; /* Declared for Signal Lever Status */ 

extern Lever_t st_Onds_ManTrApp;/*Declared To detect wrong track movement from signal cabin*/


typedef struct 
{
    unsigned char uc_CrankLockStatus; /* For Crank lock Status*/
    //unsigned char uc_CrankReleaseStatus; /*For Crank lock Status */
} Crank_t;

extern Crank_t st_Onds_CrankLock; /* Declared for Crank lock Status */ 


extern uint32_t ui_WaitingTimeToCallFIBDiag;/*for FIB diagnostic*/

extern unsigned char uc_LPM_IP_DEV_Log_Flag;

typedef struct  
{
    /* For counting Pulses for Each Bit of RHS and LHS Yellow Flasher */
    unsigned short int us_YFPulseCnt[2][2][2]; 
    /* For counting Pulses for Each Bit of RHS and LHS Red Flasher */
    unsigned short int us_RFPulseCnt[2][2][2];
    /* For maintain Each Bit status of RHS and LHS Yellow Flasher */
    unsigned short int us_YFPulseDet[2][2];
    /* For maintain Each Bit status of RHS and LHS Red Flasher */
    unsigned short int us_RFPulseDet[2][2];
} Pulse_t;

extern Pulse_t st_Onds_PulseDet; /* Declared for Flasher Pulse Detection */

typedef struct  
{
    unsigned char uc_RHSYFONStatus; /* For RHS YF ON Fail */
    unsigned char uc_LHSYFONStatus; /* For LHS YF ON Fail */
    unsigned char uc_RHSRFONStatus; /* For RHS RF ON Fail */
    unsigned char uc_LHSRFONStatus; /* For LHS RF ON Fail */
    unsigned char uc_RHSBellONStatus; /* For RHS Bell ON Fail */
    unsigned char uc_LHSBellONStatus; /* For LHS Bell ON Fail */

    unsigned char uc_RHSUPDirIndiONStatus; /* For UP Dir Indicator ON Fail */
    unsigned char uc_LHSUPDirIndiONStatus; /* For UP Dir Indicator ON Fail */
    unsigned char uc_RHSDNDirIndiONStatus; /* For DN Dir Indicator ON Fail */
    unsigned char uc_LHSDNDirIndiONStatus; /* For DN Dir Indicator ON Fail */

    unsigned char uc_RHSYFOFFStatus; /* For RHS YF OFF Fail */
    unsigned char uc_LHSYFOFFStatus; /* For LHS YF OFF Fail */
    unsigned char uc_RHSRFOFFStatus; /* For RHS RF OFF Fail */
    unsigned char uc_LHSRFOFFStatus; /* For LHS RF OFF Fail */
    unsigned char uc_RHSBellOFFStatus; /* For RHS Bell OFF Fail */
    unsigned char uc_LHSBellOFFStatus; /* For LHS Bell OFF Fail */

    unsigned char uc_RHSUPDirIndiOFFStatus; /* For UP Dir Indicator OFF Fail */
    unsigned char uc_LHSUPDirIndiOFFStatus; /* For UP Dir Indicator OFF Fail */
    unsigned char uc_RHSDNDirIndiOFFStatus; /* For DN Dir Indicator OFF Fail */
    unsigned char uc_LHSDNDirIndiOFFStatus; /* For DN Dir Indicator OFF Fail */
	
	unsigned char uc_UPDirIndiONStatus; /* For UP Dir Indicator Status to ZMS */
    unsigned char uc_UPDirIndiOFFStatus; /* For UP Dir Indicator Status to ZMS */
    unsigned char uc_DNDirIndiONStatus; /* For DN Dir Indicator Status to ZMS */
    unsigned char uc_DNDirIndiOFFStatus; /* For DN Dir Indicator Status to ZMS */

    unsigned char uc_RHSEnCloseStatus;  /* For RHS Entry Close Barrier Fail*/
    unsigned char uc_RHSEnClCloseSensor;/* For Individual Checking*/
    unsigned char uc_RHSEnClOpenSensor ;/* For Individual Checking*/


    unsigned char uc_RHSExCloseStatus; /* For RHS Exit Close Barrier Fail*/
    unsigned char uc_RHSExClCloseSensor;/* For Individual Checking*/ 
    unsigned char uc_RHSExClOpenSensor ;/* For Individual Checking*/ 

    
    unsigned char uc_LHSEnCloseStatus; /* For LHS Entry Close Barrier Fail*/
    unsigned char uc_LHSEnClCloseSensor;/* For Individual Checking*/
    unsigned char uc_LHSEnClOpenSensor; /* For Individual Checking*/

    unsigned char uc_LHSExCloseStatus; /* For LHS Exit Close Barrier Fail*/
    unsigned char uc_LHSExClCloseSensor;/* For Individual Checking*/
    unsigned char uc_LHSExClOpenSensor;/* For Individual Checking*/


    unsigned char uc_RHSEnOpenStatus; /* For RHS Entry Open Barrier Fail*/
    unsigned char uc_RHSEnOpeCloseSensor; /* For Individual Checking*/
    unsigned char uc_RHSEnOpeOpenSensor;  /* For Individual Checking*/


    unsigned char uc_RHSExOpenStatus; /* For RHS Exit Open Barrier Fail*/
    unsigned char uc_RHSExOpeCloseSensor;/* For Individual Checking*/  
    unsigned char uc_RHSExOpeOpenSensor; /* For Individual Checking*/  

    unsigned char uc_LHSEnOpenStatus; /* For LHS Entry Open Barrier Fail*/ 
    unsigned char uc_LHSEnOpeCloseSensor ;/* For Individual Checking*/
    unsigned char uc_LHSEnOpeOpenSensor  ;/* For Individual Checking*/

    unsigned char uc_LHSExOpenStatus; /* For LHS Exit Open Barrier Fail*/
    unsigned char uc_LHSExOpeCloseSensor ;/* For Individual Checking*/ 
	unsigned char uc_LHSExOpeOpenSensor;/* For Individual Checking*/

    unsigned char uc_DvrsStatus; /* For DVRS Fail */
    unsigned char uc_BattLowStatus; /* For Battery Low Fail */
    unsigned char uc_ACMainStatus; /* For AC Mains Fail */
    unsigned char uc_ChargerStatus;/* For charger Fail */
    unsigned char uc_RTCHealthStatus; /* For RTC Health Check */
    unsigned char uc_AppSensorStatus; /* For Train Approach Sensor fail */
    uint32_t ui_ManualModeDelayTime;/*For Manual Mode Delay*/

    unsigned char uc_CmnErrLEDStatus; /* For Common Error LED Status */
    unsigned char uc_BuzzerStatus; /* For Buzzer Lit ON Status */
    unsigned char uc_ModeSwitchErrStatus; /* For Mode Switch Error Detection*/
    unsigned char uc_ModeSwitchLowStatus; /* For Mode Switch Low Error Detection*/
    unsigned char uc_EmSwitchErrStatus; /* For Emergency Switch Error Detect*/
    unsigned char uc_RHSEnCrankStatus; /* For RHS Entry barrier Crank Status */
    unsigned char uc_LHSEnCrankStatus; /* For LHS Entry barrier Crank Status */
    unsigned char uc_RHSExCrankStatus; /* For RHS Exit barrier Crank Status */
    unsigned char uc_LHSExCrankStatus; /* For LHS Exit barrier Crank Status */
	unsigned char uc_LxLeverStatus;/*For Lx Lever Status*/
	unsigned char uc_SigLeverStatus;/*Signal Lever Status*/
    unsigned char uc_ManTrAppFrmSigCabin;/*For Train Approach From Signal Cabin*/
    unsigned char uc_ManTrDepFrmSigCabin;/*For Train Departure From Signal Cabin*/
    unsigned char uc_LxLeverLock;/*For Lx Lever Lock*/
    unsigned char uc_SignalLeverLock;/*For Signal Lever Lock*/

	uint32_t ui_PulseDetectTime;/*For Pulse Detection Time*/
    unsigned char uc_FIBStatus[MAX_FIB];/*For FIB Status*/
	
	unsigned char uc_FIB1_LPM1Status;
	unsigned char uc_FIB2_LPM1Status;
	unsigned char uc_FIB3_LPM1Status;

	unsigned char uc_FIB1_LPM2Status;
	unsigned char uc_FIB2_LPM2Status;
	unsigned char uc_FIB3_LPM2Status;

	unsigned char uc_FIB1_LPM3Status;
	unsigned char uc_FIB2_LPM3Status;
	unsigned char uc_FIB3_LPM3Status;
	

	unsigned int ul_IpDevStatus;       /*All input device Staus*/  
} Gate_t;

extern Gate_t st_Onds_GateFB; /* Declared for Maintain Status of subsystems */



extern unsigned char guc_FailandImpEvent[13];

//extern uint32_t sui_AppSensorFailTime ;
//extern uint32_t sui_AppSensorOkTime ;
//extern unsigned char guc_PrevFailsandImpEvent[13];
//extern unsigned short us_MismatchFlag;     




typedef struct 
{
	unsigned char uc_RHSYFSTATUS;
	unsigned char uc_RHSRFSTATUS;
	unsigned char uc_LHSYFSTATUS;
	unsigned char uc_LHSRFSTATUS;
	unsigned char uc_LHSBellSTATUS;
	unsigned char uc_RHSBellSTATUS;
	unsigned char uc_UPDirSTATUS;
	unsigned char uc_DNDirSTATUS;
	unsigned char uc_LHSEntryBarrier;
	unsigned char uc_RHSEntryBarrier;
	unsigned char uc_LHSExitBarrier;
	unsigned char uc_RHSExitBarrier;
	unsigned char uc_LxLeverStatus;
	//unsigned char uc_LxLeverNormalStatus;
	unsigned char uc_SignalLeverStatus;
	//unsigned char uc_SignalLeverNormalStatus;
}LxChangeOver_t;

extern  LxChangeOver_t st_Onds_PrvStatus;
extern  LxChangeOver_t st_Onds_Status;

typedef struct 
{
	unsigned char uc_FlasherandBell;
	unsigned char uc_EntryBarrier;
//	unsigned char uc_EntryBarrier;
	unsigned char uc_LxLeverLock;
	unsigned char uc_SignalLeverLock;
	unsigned char uc_Input1InterLock;
	unsigned char uc_Input2InterLock;
	unsigned char uc_UPDir;
	unsigned char uc_DNDir;
	unsigned char uc_MaintMode;
	unsigned char uc_ModeSwitchPos;
}ROMStatusLogging_t;

extern ROMStatusLogging_t st_Onds_ROMStatus;
extern ROMStatusLogging_t st_Onds_PrvROMStatus;

extern uint32_t ui_UPDirIndiOFFTimer; 
extern uint32_t ui_UPDirIndiONTimer;

extern uint32_t ui_DNDirIndiOFFTimer; 
extern uint32_t ui_DNDirIndiONTimer;
extern uint32_t ui_ManualModeForcedTime;
/*This function is called to call Cbit Initialization functions*/
void CBitIntilizeFunction(void);
/*This function is called to Initialize Train Approach Structure*/
void InitCBitTrainAppStruct(void);
/*This function is called to Initialize Emergency Switch Structure*/
void InitCBitEmergencySwitchStruct(void);
/*This function is called to Initialize Mode Switch Structure*/
void InitCBitModeSwitchStruct(void);
/*This function is called to Initialize Pulse Detection Structure*/
void InitCBitPulseDetStruct(void);
/*This function is called to Initialize Gate Maintainance Structure*/
void InitCBitGateMaintainStatusStruct(void);
/*This function is called to Initialize Lx Lever Structure*/
void InitCBitLxLeverStruct(void);
/*This function is called to Initialize Signal Lever Structure*/
void InitCBitSignalLeverStruct(void);
/*This function is called to Initialize Train Approach from signal cabin 
  Structure*/ 
void InitCbitManTrainTrainApproach(void);
/*This function is called to Initialize Crank Box Structure*/
void InitCbitCrankBoxStruct(void);

/* For counting pulses of each yellow & Red Flasher in RHS and LHS */
void Onds_FlasherPulseCounter(void);
/* For counting pulses of each yellow in RHS and LHS */
void Onds_YFConfigPulseCount(void);
/* For counting pulses of each Red Flasher in RHS and LHS */
void Onds_RFConfigPulseCount(void);
/* For detection of pulse of each yellow flasher in RHS and LHS*/
void Onds_YFFlasherPulseDetection(void);
/* For detection of pulse of each red flasher in RHS and LHS*/
void Onds_RFFlasherPulseDetection(void);

/* For detection of Yellow flasher failures in RHS */
void Onds_RHSYFONFailureDetection(void);
/* For detection of Yellow flasher failures in RHS */
void Onds_RHSYFOFFFailureDetection(void);

/* For detection of Yellow flasher failures in LHS */
void Onds_LHSYFONFailureDetection(void);
/* For detection of Yellow flasher failures in LHS */
void Onds_LHSYFOFFFailureDetection(void);

/* For detection of Red flasher failures in RHS */
void Onds_RHSRFONFailureDetection(void);
/* For detection of Red flasher failures in RHS */
void Onds_RHSRFOFFFailureDetection(void);

/* For detection of Red flasher failures in LHS */
void Onds_LHSRFONFailureDetection(void);
/* For detection of Red flasher failures in LHS */
void Onds_LHSRFOFFFailureDetection(void);


/* For detection of Bell failures in RHS */
void Onds_RHSBellFeedbackCheck(void);
/* For detection of Bell failures in LHS */
void Onds_LHSBellFeedbackCheck(void);

/* For detection of Direction Indicator failures in UP dircetion */
void Onds_UPDirIndiFBCheck(void);
/* For detection of Direction Indicator failures in DN dircetion */
void Onds_DNDirIndiFBCheck(void);

/* For detection of RHS Entry Close barrier Fail */
void Onds_RHSEnCloseBarrierFBCheck(void);
/* For detection of RHS Entry Open barrier Fail */
void Onds_RHSEnOpenBarrierFBCheck(void);
/* For detection of LHS Entry Close barrier Fail */
void Onds_LHSEnCloseBarrierFBCheck(void);
/* For detection of LHS Entry Open barrier Fail */
void Onds_LHSEnOpenBarrierFBCheck(void);
/* For detection of RHS Exit Close barrier Fail */
void Onds_RHSExCloseBarrierFBCheck(void);
/* For detection of RHS Exit Open barrier Fail */
void Onds_RHSExOpenBarrierFBCheck(void);
/* For detection of LHS Exit Close barrier Fail */
void Onds_LHSExCloseBarrierFBCheck(void);
/* For detection of LHS Exit Open barrier Fail */
void Onds_LHSExOpenBarrierFBCheck(void);

/* For resetting pulse counting array */
void Onds_ResetPulseCountArray(void);
void Onds_ResetOnlyPulseCountArray(void);

/* For detection of Dvrs failure */
void Onds_DVRSFBCheck(void);
/* For detection of Battery Low failure */
void Onds_BattLowFBCheck(void);
/* For detection of ACMains failure */
void Onds_ACMainsFBCheck(void);
/* For detection of charger failure */
void Onds_ChargerFBCheck(void);

#ifdef RTC_HEALTH_CHECK
/* For detection of RTC health Fail */
void Onds_RTCHealthFBCheck(void);
#endif /* #ifdef RTC_HEALTH_CHECK */

/* For detection of Train Approach Sensor Fail */
void Onds_TrainAppSensorFBCheck(void);
/* For detection of Common Error LED Status */
void Onds_CmmErrLEDStatusUpdation(void);
/* For detection of Buzzor Status */
void Onds_BuzzerStatusUpdation(void);
/* For detection of Mode Switch Error */
void Onds_ModeSwitchErrStatusFBCheck(void);
/* For detection of Mode Switch LOW Error */
void Onds_ModeSwitchLOWFBCheck(void);
/* For detection of Emergency Switch Error */
void Onds_EmSwitchErrStatusFBCheck(void);
/* For detection of Lx Lever Position and Error */
void Onds_LxLeverErrStatusFBCheck(void);
/* For detection of Signal Lever Position and Error */
void Onds_SignalLeverErrStatusFBCheck(void);
/* For Detection of Barrier Crank Insertion Status */
void Onds_CrankSignalStatusLogging(void);
/*This function checks Mode Switch Error Status feedback.*/
void Onds_ManTrAppPbFBCheckFrmSigCabin(void);
/*This function is called to check the FIB cards working status*/
void Onds_FIBChecking(void);

/*This function is used to detect Failure of RHS single yellow ON 
  flasher*/
void Onds_RHSSINGLEFLONPOSTYFONFailDetection(void);
/*This function is used to detect Failure of RHS both Yellow ON  
  Flashers*/
void Onds_RHSBothFlOnPostYFFailDetection(void);
/*This function is used to detect Failure of RHS Yellow Flashers in
  ON condition on Cantilever*/
void Onds_RHSFlOnCantiYFONFailDetection(void);
/*This function is used to detect All Failure of RHS Contilever Yellow ON  
  Flashers.*/
void Onds_RHSFlOnCantiYFONALLFlasherFailDetection(void);
/*This function is used to detect Failure of RHS Contilever both Yellow ON  
  Flashers.*/
void Onds_RHSFlOnCantiYFON3and4FlasherFailDetection(void);
/*This function is used to detect Failure of RHS Contilever both Yellow ON  
  Flashers.*/
void Onds_RHSFlOnCantiYFON1and2FlasherFailDetection(void);
/*This function is used to detect All OK of RHS Contilever Yellow ON  
  Flashers.*/
void Onds_RHSFlOnCantiYFONALLFlasherOKDetection(void);
/*This function is used to detect Failure of RHS Contilever three Yellow ON  
  Flashers.*/
void Onds_RHSFlonCantiYFON3AND4AND1OR2FailDetection(void);
/*This function is used to detect Failure of RHS Contilever three Yellow ON  
  Flashers.*/
void Onds_RHSFlonCantiYFON1AND2AND3OR4FailDetection(void);
/*This function is used to detect Failure of RHS Contilever single Yellow ON  
  Flashers.*/
void Onds_RHSFlonCantiYFON1OR2FailDetection(void);
/*This function is used to detect Failure of RHS Contilever single Yellow ON  
  Flashers.*/
void Onds_RHSFlonCantiYFON3OR4FailDetection(void);
/*This function is used to detect Failure of RHS Contilever single flasher on 
	each pair Yellow ON Flashers.*/
void Onds_RHSFlonCantiYFON1OR2AND3OR4FailDetection(void);
/*This function is used to detect Failure of RHS single Yellow 
  OFF Flashers.*/
void Onds_RHSSingleFlOnPostYFOFFFailDetection(void);
/*This function is used to detect Failure of RHS both Yellow 
  flashers in OFF condition*/
void Onds_RHSBothFlOnPostYFOFFFailDetection(void);
/*This function is used to detect Failure of RHS Yellow Flashers in
  OFF condition on Cantilever*/
void Onds_RHSFlOnCantiYFOFFFailDetection(void);
/*This function is used to detect All Failure of RHS Contilever Yellow OFF 
  Flashers.*/
void Onds_RHSFlOnCantiYFOFFALLFlasherFailDetection(void);
/*This function is used to detect Failure of RHS Contilever both Yellow OFF  
  Flashers.*/
void Onds_RHSFlOnCantiYFOFF3and4FlasherFailDetection(void);
/*This function is used to detect Failure of RHS Contilever both Yellow OFF  
  Flashers.*/
void Onds_RHSFlOnCantiYFOFF1and2FlasherFailDetection(void);
/*This function is used to detect All OK of RHS Contilever Yellow OFF  
  Flashers.*/
void Onds_RHSFlOnCantiYFOFFALLFlasherOKDetection(void);
/*This function is used to detect Failure of RHS Contilever THREE Yellow OFF  
  Flashers.*/
void Onds_RHSFlonCantiYFOFF3AND4AND1OR2FailDetection(void);
/*This function is used to detect Failure of RHS Contilever THREE Yellow OFF  
  Flashers.*/
void Onds_RHSFlonCantiYFOFF1AND2AND3OR4FailDetection(void);
/*This function is used to detect Failure of RHS Contilever SINGLE Yellow OFF  
  Flashers.*/
void Onds_RHSFlonCantiYFOFF1OR2FailDetection(void);
/*This function is used to detect Failure of RHS Contilever SINGLE Yellow OFF  
  Flashers.*/
void Onds_RHSFlonCantiYFOFF3OR4FailDetection(void);
/*This function is used to detect Failure of RHS Contilever single flasher on 
	each pair Yellow ON Flashers.*/
void Onds_RHSFlonCantiYFOFF1OR2AND3OR4FailDetection(void);
/*This function is used to detect Failure of LHS single Yellow ON 
  Flashers.*/
void Onds_LHSSingleFlOnPostYFONFailDetection(void);
/*This function is used to detect Failure of LHS both Yellow ON 
  Flashers.*/
void Onds_LHSBothFlOnPostYFONFailDetection(void);
/*This function is used to detect Failure of LHS Yellow Flashers in
  ON condition on Cantilever*/
void Onds_LHSFlOnCantiYFONFailDetection(void);
/*This function is used to detect All Failure of LHS Contilever Yellow ON 
  Flashers.*/
void Onds_LHSFlOnCantiYFONALLFlasherFailDetection(void);
/*This function is used to detect Failure of LHS Contilever both Yellow ON  
  Flashers.*/
void Onds_LHSFlOnCantiYFON3and4FlasherFailDetection(void);
/*This function is used to detect Failure of LHS Contilever both Yellow ON  
  Flashers.*/
void Onds_LHSFlOnCantiYFON1and2FlasherFailDetection(void);
/*This function is used to detect ALL OK of LHS Contilever both Yellow ON  
  Flashers.*/
void Onds_LHSFlOnCantiYFONALLFlasherOKDetection(void);
/*This function is used to detect Failure of LHS Contilever three Yellow ON  
  Flashers.*/
void Onds_LHSFlonCantiYFON3AND4AND1OR2FailDetection(void);
/*This function is used to detect Failure of LHS Contilever three Yellow ON  
  Flashers.*/
void Onds_LHSFlonCantiYFON1AND2AND3OR4FailDetection(void);
/*This function is used to detect Failure of LHS Contilever single Yellow ON  
  Flashers.*/
void Onds_LHSFlonCantiYFON1OR2FailDetection(void);
/*This function is used to detect Failure of LHS Contilever single Yellow ON  
  Flashers.*/
void Onds_LHSFlonCantiYFON3OR4FailDetection(void);
/*This function is used to detect Failure of lHS Contilever single flasher on 
	each pair Yellow ON Flashers.*/
void Onds_LHSFlonCantiYFON1OR2AND3OR4FailDetection(void);
/*This function is used to detect Failure of LHS single Yellow OFF 
  Flashers.*/
void Onds_LHSSingleFlOnPostYFOFFFailDetection(void);
/*This function is used to detect Failure of LHS both Yellow
  Flashers in OFF condition*/
void Onds_LHSBothFlOnPostYFOFFFailDetection(void);
/*This function is used to detect Failure of LHS
  Yellow Flashers in OFF condition on Cantilever*/
void Onds_LHSFlOnCantiYFOFFFailDetection(void);
/*This function is used to detect All Failure of LHS Contilever Yellow OFF 
  Flashers.*/
void Onds_LHSFlOnCantiYFOFFALLFlasherFailDetection(void);
/*This function is used to detect Failure of LHS Contilever both Yellow OFF  
  Flashers.*/
void Onds_LHSFlOnCantiYFOFF3and4FlasherFailDetection(void);
/*This function is used to detect Failure of LHS Contilever both Yellow OFF  
  Flashers.*/
void Onds_LHSFlOnCantiYFOFF1and2FlasherFailDetection(void);
/*This function is used to detect ALL OK of LHS Contilever both Yellow ON  
  Flashers.*/
void Onds_LHSFlOnCantiYFOFFALLFlasherOKDetection(void);
/*This function is used to detect Failure of LHS Contilever three Yellow OFF  
  Flashers.*/
void Onds_LHSFlonCantiYFOFF3AND4AND1OR2FailDetection(void);
/*This function is used to detect Failure of LHS Contilever three Yellow OFF  
  Flashers.*/
void Onds_LHSFlonCantiYFOFF1AND2AND3OR4FailDetection(void);
/*This function is used to detect Failure of LHS Contilever single Yellow OFF  
  Flashers.*/
void Onds_LHSFlonCantiYFOFF1OR2FailDetection(void);
/*This function is used to detect Failure of LHS Contilever single Yellow OFF  
  Flashers.*/
void Onds_LHSFlonCantiYFOFF3OR4FailDetection(void);
/*This function is used to detect Failure of lHS Contilever single flasher on 
	each pair Yellow OFF Flashers.*/
void Onds_LHSFlonCantiYFOFF1OR2AND3OR4FailDetection(void);
/*This function is used to detect RHS red single Flasher 
  Failure in ON condition*/
void Onds_RHSSingleFlOnPostRFONFailDetection(void);
/*This function is used to detect RHS red both Flashers 
  failure in ON condition*/
 void Onds_RHSBothFlOnPostRFONFailDetection(void);
/*This function is used to detect Failure of RHS Red Flashers
  in ON condition on Cantilever.*/
 void Onds_RHSFlOnCantiRFONFailDetection(void);
 /*This function is used to detect All Failure of RHS Contilever Red ON  
  Flashers.*/
void Onds_RHSFlOnCantiRFONALLFlasherFailDetection(void);
/*This function is used to detect Failure of RHS Contilever both Red ON  
  Flashers.*/
void Onds_RHSFlOnCantiRFON3and4FlasherFailDetection(void);
/*This function is used to detect Failure of RHS Contilever both Red ON  
  Flashers.*/
void Onds_RHSFlOnCantiRFON1and2FlasherFailDetection(void);
/*This function is used to detect All OK of RHS Contilever Red ON  
  Flashers.*/
void Onds_RHSFlOnCantiRFONALLFlasherOKDetection(void);
/*This function is used to detect Failure of RHS Contilever three Red ON  
  Flashers.*/
void Onds_RHSFlonCantiRFON3AND4AND1OR2FailDetection(void);
/*This function is used to detect Failure of RHS Contilever three Red ON  
  Flashers.*/
void Onds_RHSFlonCantiRFON1AND2AND3OR4FailDetection(void);
/*This function is used to detect Failure of RHS Contilever single Red ON  
  Flashers.*/
void Onds_RHSFlonCantiRFON1OR2FailDetection(void);
/*This function is used to detect Failure of RHS Contilever single Red ON  
  Flashers.*/
void Onds_RHSFlonCantiRFON3OR4FailDetection(void);
/*This function is used to detect Failure of RHS Contilever single Red on 
	each pair Yellow ON Flashers.*/
void Onds_RHSFlonCantiRFON1OR2AND3OR4FailDetection(void);
 /*This function is used to detect Failure of
  RHS single Red Flasher in OFF condition*/
 void Onds_RHSSingleFlOnPostRFOFFFailDetection(void);
/*This function is used to detect Failure of RHS both Red 
  Flashers in OFF condition*/
 void Onds_RHSBothFlOnPostRFOFFFailDetection(void);
/*This function is used to detect Failure of RHS  Red Flashers
  in OFF condition on cantilever*/
 void Onds_RHSFlOnCantiRFOFFFailDetection(void);
 /*This function is used to detect All Failure of RHS Contilever Red OFF 
  Flashers.*/
void Onds_RHSFlOnCantiRFOFFALLFlasherFailDetection(void);
/*This function is used to detect Failure of RHS Contilever both Red OFF  
  Flashers.*/
void Onds_RHSFlOnCantiRFOFF3and4FlasherFailDetection(void);
/*This function is used to detect Failure of RHS Contilever both Red OFF  
  Flashers.*/
void Onds_RHSFlOnCantiRFOFF1and2FlasherFailDetection(void);
/*This function is used to detect All OK of RHS Contilever Red OFF  
  Flashers.*/
void Onds_RHSFlOnCantiRFOFFALLFlasherOKDetection(void);
/*This function is used to detect Failure of RHS Contilever THREE Red OFF  
  Flashers.*/
void Onds_RHSFlonCantiRFOFF3AND4AND1OR2FailDetection(void);
/*This function is used to detect Failure of RHS Contilever THREE Red OFF  
  Flashers.*/
void Onds_RHSFlonCantiRFOFF1AND2AND3OR4FailDetection(void);
/*This function is used to detect Failure of RHS Contilever SINGLE Red OFF  
  Flashers.*/
void Onds_RHSFlonCantiRFOFF1OR2FailDetection(void);
/*This function is used to detect Failure of RHS Contilever SINGLE Red OFF  
  Flashers.*/
void Onds_RHSFlonCantiRFOFF3OR4FailDetection(void);
/*This function is used to detect Failure of RHS Contilever single flasher on 
	each pair Red ON Flashers.*/
void Onds_RHSFlonCantiRFOFF1OR2AND3OR4FailDetection(void);
/*This function is used to detect Failure of LHS single Red 
  Flashers in ON condition*/
 void Onds_LHSSingleFlOnPostRFONFailDetection(void);
/*This function is used to detect Failure of LHS both Red 
  Flashers in ON condition*/
 void Onds_LHSBothFlOnPostRFONFailDetection(void);
/*This function is used to detect Failure of LHS Red Flashers in
  ON condition on cantilever.*/
void Onds_LHSFlOnCantiRFONFailDetection(void);
/*This function is used to detect All Failure of LHS Contilever Red ON 
  Flashers.*/
void Onds_LHSFlOnCantiRFONALLFlasherFailDetection(void);
/*This function is used to detect Failure of LHS Contilever both Red ON  
  Flashers.*/
void Onds_LHSFlOnCantiRFON3and4FlasherFailDetection(void);
/*This function is used to detect Failure of LHS Contilever both Red ON  
  Flashers.*/
void Onds_LHSFlOnCantiRFON1and2FlasherFailDetection(void);
/*This function is used to detect ALL OK of LHS Contilever both Red ON  
  Flashers.*/
void Onds_LHSFlOnCantiRFONALLFlasherOKDetection(void);
/*This function is used to detect Failure of LHS Contilever three Red ON  
  Flashers.*/
void Onds_LHSFlonCantiRFON3AND4AND1OR2FailDetection(void);
/*This function is used to detect Failure of LHS Contilever three Red ON  
  Flashers.*/
void Onds_LHSFlonCantiRFON1AND2AND3OR4FailDetection(void);
/*This function is used to detect Failure of LHS Contilever single Red ON  
  Flashers.*/
void Onds_LHSFlonCantiRFON1OR2FailDetection(void);
/*This function is used to detect Failure of LHS Contilever single Red ON  
  Flashers.*/
void Onds_LHSFlonCantiRFON3OR4FailDetection(void);
/*This function is used to detect Failure of lHS Contilever single flasher on 
	each pair Red ON Flashers.*/
void Onds_LHSFlonCantiRFON1OR2AND3OR4FailDetection(void);
/*This function is used to detect Failure of LHS single Red Flashers
  in OFF condition*/
 void Onds_LHSSingleFlOnPostRFOFFFailDetection(void);
/*This function is used to detect Failure of LHS Both Red Flashers 
  in OFF condition*/
 void Onds_LHSBothFlOnPostRFOFFFailDetection(void);
/*This function is used to detect Failure of LHS Red Flashers in
  OFF condition on cantilever*/
 void Onds_LHSFlOnCantiRFOFFFailDetection(void);
 /*This function is used to detect All Failure of LHS Contilever Red OFF 
  Flashers.*/
void Onds_LHSFlOnCantiRFOFFALLFlasherFailDetection(void);
/*This function is used to detect Failure of LHS Contilever both Red OFF  
  Flashers.*/
void Onds_LHSFlOnCantiRFOFF3and4FlasherFailDetection(void);
/*This function is used to detect Failure of LHS Contilever both Red OFF  
  Flashers.*/
void Onds_LHSFlOnCantiRFOFF1and2FlasherFailDetection(void);
/*This function is used to detect ALL OK of LHS Contilever both Red ON  
  Flashers.*/
void Onds_LHSFlOnCantiRFOFFALLFlasherOKDetection(void);
/*This function is used to detect Failure of LHS Contilever three Red OFF  
  Flashers.*/
void Onds_LHSFlonCantiRFOFF3AND4AND1OR2FailDetection(void);
/*This function is used to detect Failure of LHS Contilever three Red OFF  
  Flashers.*/
void Onds_LHSFlonCantiRFOFF1AND2AND3OR4FailDetection(void);
/*This function is used to detect Failure of LHS Contilever single Red OFF  
  Flashers.*/
void Onds_LHSFlonCantiRFOFF1OR2FailDetection(void);
/*This function is used to detect Failure of LHS Contilever single Red OFF  
  Flashers.*/
void Onds_LHSFlonCantiRFOFF3OR4FailDetection(void);
/*This function is used to detect Failure of lHS Contilever single flasher on 
	each pair Red OFF Flashers.*/
void Onds_LHSFlonCantiRFOFF1OR2AND3OR4FailDetection(void);

/*This function is used to check feedback of subsytems*/
void OndsCbit(void);

/*This function is used to check feedback of RHS Entry Gate on Power ON*/
void Onds_RHSEnGateFBonPbit(void);
/*This function is used to check feedback of LHS Entry Gate on Power ON*/
void Onds_LHSEnGateFBonPbit(void);
/*This function is used to check feedback of RHS Exit Gate on Power ON*/
void Onds_RHSExGateFBonPbit(void);
/*This function is used to check feedback of LHS Exit Gate on Power ON*/
void Onds_LHSExGateFBonPbit(void);
/*This function is used to check feedback of Crank Handle*/
void Onds_CrankHandleCheck(void);
/*This function is used to check feedback of Lever Lock*/
void Onds_LeverLockStatus(void);
/*This function is used to check feedback of WSS*/
void Onds_WssStatus(void);

void Onds_CurrnetStatusInManualMode(void);
void Onds_FlandBellStatusInManualMode(void);
void Onds_BarrierStatusInManualMode(void);
void Onds_LxLeverStatusInManualMode(void);
void Onds_SignalLeverStatusInManualMode(void);

void Onds_IntialStatusLoggindInManualMode(void);
void Onds_PrvFlandBellStatusInManualMode(void);
void Onds_PrvBarrierStatusInManualMode(void);
void Onds_PrvLxLeverStatusInManualMode(void);
void Onds_PrvSignalLeverStatusInManualMode(void);

void Onds_ChangeOverLoggingInManualMode(void);

void Onds_VLMOutputUpdation(void);
void Onds_VLMOutputLogging(void);
void InitCbitLxChangeOverStructure(void);
void InitCbitROMStausLoggingStructure(void);
void InitCbitVLMOutputLoggingStructure(void);
void Onds_PrvVLMOutputUpdation(void);
void InitCbitROMStausLoggingStructure(void);
void Onds_InputDevBitStuffing(void);

void Onds_CSMFailureDetection(void);

#ifdef AXM_CARD_FAILURE
void Onds_AXMCardFailDetection1(void);
void Onds_AXMCardFailDetection(void);
#endif /*#ifdef AXM_CARD_FAILURE*/
void Onds_CSM_AUXCardFailDetection(void);
void Onds_SSRCardFailDetection(void);
#endif /* CBITINIT_H */



void Onds_FailsandImpEvent(void);
void Onds_RHSYFONStatustoSDM(void);
void Onds_RHSYFOFFStatustoSDM(void);
void Onds_RHSBELLStatustoSDM(void);
void Onds_LHSYFONStatustoSDM(void);
void Onds_LHSYFOFFStatustoSDM(void);
void Onds_LHSBELLStatustoSDM(void);
void Onds_RHSRFONStatustoSDM(void);
void Onds_RHSRFOFFStatustoSDM(void);
void Onds_EnCrankInsStatustoSDM(void);
void Onds_LHSRFONStatustoSDM(void);
void Onds_LHSRFOFFStatustoSDM(void);
void Onds_ExCrankInsStatustoSDM(void);
void Onds_UpDirONStatustoSDM(void);
void Onds_UpDirOFFStatustoSDM(void);
void Onds_DnDirONStatustoSDM(void);
void Onds_DnDirOFFStatustoSDM(void);
void Onds_EnBarrierStatustoSDM(void);
void Onds_ExBarrierStatustoSDM(void);
void Onds_IpDevStatustoSDM(void);
void Onds_FIBStatustoSDM(void);
void Onds_OtherStatustoSDM(void);
void Onds_ImpEvntsToSDM(void);









/*End Of File*/
