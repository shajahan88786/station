/******************************************************************************
* File Name			: LxOpProcess.h
*
* Abstract		  : This file contains the routines for the operations of       
*				    of Flashers, Bells, Dvrs, Barriers, Mode Control switch,   
*					Emergency switch,Direction indicators,Inter Locking System,
*					WSS/Track Circuits e.t.c.                                  
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


#ifndef LXOPPROCESS_H
#define LXOPPROCESS_H

#define TIMEOUT_AC_MAINS_FB				HALF_SEC //ONE_SEC
#define TIMEOUT_CHRGR_FB				HALF_SEC //ONE_SEC

#define TIMEOUT_APP_SENSOR_FB			TWO*TWO_SEC
#define TIMEOUT_APP_SIG_CAB_FB			HALF_SEC //TWO*TWO_SEC
#define TIMEOUT_DEP_SIG_CAB_FB 			HALF_SEC //TWO*TWO_SEC

#define TIMEOUT_CP_DETECT_DELAY			FIVE_MS 
#define TIMEOUT_MAN_MODE_FORCED			TWO_SEC
#define TIMEOUT_SAM_MODE_DETECT			HALF_SEC
#define TIMEOUT_MAN_MODE_DETECT			HALF_SEC
#define TIMEOUT_ROM_MODE_DETECT			HALF_SEC
#define TIMEOUT_MODE_SW_ERROR			HALF_SEC		//ONE_SEC
#define TIMEOUT_MODE_SW_ERROR_LOW		HALF_SEC		//TEN_SEC
#define TIMEOUT_MODE_SW_RECOVERED		HALF_SEC		//Nothing
#define TIMEOUT_EM_SW_ERROR				ONE_SEC			//TWO_SEC

/* Staggered driving for Barrier to reduce current consumption in Motor,
 * Otherwise, high current consumption if driven at same time.
 */
#define TIMEOUT_LHS_BARRIER_CLOSE_DELAY   QUARTER_SEC  //HALF_SEC
#define TIMEOUT_LHS_BARRIER_OPEN_DELAY    QUARTER_SEC  //HALF_SEC

#define TIMEOUT_LHS_X_BARRIER_OPEN_DELAY  QUARTER_SEC  //HALF_SEC
#define TIMEOUT_LHS_X_BARRIER_CLOSE_DELAY QUARTER_SEC  //HALF_SEC


#define TIMEOUT_BELL_ON_FB			12*HUNDRED_MS
#define TIMEOUT_BELL_OFF_FB			3*ONE_SEC

#define TIMEOUT_FLSR_ON_FB			11*HUNDRED_MS		//11*HUNDRED_MS
#define TIMEOUT_FLSR_OFF_FB			3*ONE_SEC		//3*ONE_SEC

#define TIMEOUT_FLSR_ON_FB_MAINT	15*HUNDRED_MS
#define TIMEOUT_FLSR_OFF_FB_MAINT	3*ONE_SEC

#define TIMEOUT_DIR_ON_FB			12*HUNDRED_MS
#define TIMEOUT_DIR_OFF_FB			3*ONE_SEC

#define TIMEOUT_DIR_ON_FB_MAINT		11*HUNDRED_MS
#define TIMEOUT_DIR_OFF_FB_MAINT	3*ONE_SEC

#define TIMEOUT_DVR_FB				HUNDRED_MS

#define TIMEOUT_YF_FB_MANUAL		ONE_SEC				//TWO_SEC
#define TIMEOUT_RF_FB_MANUAL		ONE_SEC				//TWO_SEC


#define INITIAL_DELAY_DIFB_NXT		ONE_SEC		//TEN_SEC

/* Prior to checking the feedback (FB) of Flashers (FL)
 * it shall have an initial delay of around 500ms.
 */
#define INITIAL_DELAY_FLFB			HALF_SEC

/* Prior to checking the feedback (FB) of Direction Indicator (DI) 
 * it shall have an initial delay of around 500ms.
 */
#define INITIAL_DELAY_DIFB			HALF_SEC


/*Mode sync logic*/
#define OUTPUT_PORT4_10_PIN   0x400           /* P4.10 Manual of Other 1 */
#define OUTPUT_PORT4_11_PIN   0x800           /* P4.11 Manual of Other 2 */
#define OUTPUT_PORT4_12_PIN   0x1000          /* P4.12 SAM of Other 1 */
#define OUTPUT_PORT4_13_PIN   0x2000          /* P4.13 SAM of Other 2 */
#define OUTPUT_PORT4_14_PIN   0x4000          /* P4.14 ROM of Other 1 */
#define OUTPUT_PORT4_15_PIN   0x8000          /* P4.15 ROM of Other 2 */

#define OUTPUT_PORT4_25_PIN   0x2000000        /* P4.25 WDT Health OTHER1 */
#define OUTPUT_PORT4_28_PIN   0x10000000       /* P4.28 WDT Health OTHER2 */

#define OUTPUT_PORT1_26_PIN   0x4000000        /* P1.26 self in Manual*/
#define OUTPUT_PORT1_27_PIN   0x8000000        /* P1.27 self in SAM */
#define OUTPUT_PORT1_28_PIN   0x10000000       /* P1.28 self in ROM */


typedef struct 
{
    unsigned char uc_FlasherAndBellSet;     /*FLasher And Bell op*/
    uint32_t ui_YFRFBellOnTime;             /*To Start the Barrier op*/
    uint32_t ui_YFRFBellOffTime;            /*To Start the Barrier op*/
    unsigned char uc_UPDirIndForRDUser;     /*To Switch ON/OFF UP Direction*/
    unsigned char uc_DNDirIndForRDUser;     /*To Switch ON/OFF DN Direction*/
    unsigned char uc_DVROp;                 /*To Control DVR recording */                                                            
    unsigned char uc_CloseBarrierOp;        /*To Control Barrier Closing op*/
    uint32_t  ui_CloseBarrierFBTime;        /*Timer To Check clousre Fail */                                                 
    unsigned char uc_OpenBarrierOp;         /*To Control Barrier Opening op*/                                                       
    uint32_t  ui_OpenBarrierFBTime;         /*Timer To Check the open Failure*/                                                    
    uint32_t  ui_BToBOpDelay;               /*To Cntrl Barrier To Barrier op*/
    
    unsigned char uc_RHSEnBarrierOp;        /*For RHS Entry Barrier op*/                                          
    unsigned char uc_LHSEnBarrierOp;        /*For LHS Entry Barrier op*/ 
    unsigned char uc_RHSExBarrierOp;        /*For RHS Exit Barrier op*/                                           
    unsigned char uc_LHSExBarrierOp;        /*For LHS Exit Barrier op*/
    unsigned char uc_EnBarrierLatchOp;      /*For Entry Barrier latch*/
    unsigned char uc_RHSExBarrLatchOp;      /*For Exit Barrier latch*/
    unsigned char uc_LHSExBarrLatchOp;      /*For Exit Barrier latch*/

    uint32_t ui_RHSExBarrFBTime;			/*For RHS Exit Barrier FB time*/ 
    uint32_t ui_LHSExBarrFBTime;			/*For LHS Exit Barrier FB time*/ 
    
    unsigned char uc_RHSExBarrierPBOp;      /*For RHS Exit Barrier op*/                                           
    unsigned char uc_LHSExBarrierPBOp;      /*For LHS Exit Barrier op*/

    
    unsigned char uc_LxLeverOp;             /*LxLever Normalicy/Reverse*/                                                       
    unsigned char uc_SignalLeverOp;         /*SignalLever Normalicy/Reverse*/                                                   
    unsigned char uc_LxLeverLockOp;         /*LxLever Lock/Release*/                                                            
    unsigned char uc_SignalLeverLockOp;     /*SignalLever Lock/Release*/                                                        
    unsigned char uc_CHLockOp;              /*Cntr C Handle Lock/Release*/                                                       
    unsigned char uc_IpToInterLockFAndB;    /*Flasher and Bell Inter Lock */                                           
    unsigned char uc_IpToInterLockBarrier;  /* Barrier Inter Lock Staus*/
    
    unsigned char uc_ResetToWSSUP;          /*Flag to Reset WSS-UP*/  
    uint32_t ui_WssResetUpTime;				/*Reset WSS-UP time*/ 
    unsigned char uc_ResetToWSSDN;          /*Flag to Reset WSS-DN*/  
    uint32_t ui_WssResetDnTime;				/*Reset WSS-DN time*/ 
        
    unsigned char uc_TrainAppInUP;          /*Train Approach in Up Dir*/                                              
    unsigned char uc_TrainAppInDN;          /*Train Approach in DN Dir*/  
    unsigned char uc_TrainAppByPB;          /*To Detect the Train Approach By PB*/
    unsigned char uc_TrainAppFrmSigCab;     /*To Detect the Train App from 
                                              signal Cabin*/

    unsigned char uc_TrainAppInUPLED;       /*Train Approach in Up Dir*/                                              
    unsigned char uc_TrainAppInDNLED;       /*Train Approach in DN Dir*/  
    unsigned char uc_TrainAppBuzzOp;        /*Train Appr Buzzer Operation*/ 
   
	unsigned char uc_TrainAppSet;           /*For Train App set*/
	unsigned char uc_UPTrainAppSet;			/*For UP Train App set*/
	unsigned char uc_DNTrainAppSet;			/*For DN Train App set*/
    uint32_t ui_UPDirTime;                  /*for dir indi ON/OFF*/
    uint32_t ui_DNDirTime;                  /*for dir indi ON/OFF*/
        
    unsigned char uc_TrPassedInd;           /*Train Passed Operation*/                                                      
    unsigned char uc_PushButtonLEDOp;       /*PB LED Operation*/                                                     
    uint32_t ui_TimerPushButton;            /*Timer for Push Button LED*/
	uint32_t ui_TrPassedTimer;				/*Timer for Train passed Indicator */
	uint32_t ui_UpTrPassedTimer;				/*Timer for Train passed Indicator */
	uint32_t ui_DnTrPassedTimer;				/*Timer for Train passed Indicator */


    unsigned char uc_ModeSwitchPos;         /*Mode Switch Position*/ 
	unsigned char uc_ModeSwitchDriven;      /*Mode Switch Driving*/ 	
	unsigned char uc_DetectModeSwitch;                                                    
    unsigned char uc_ModeSwitchLEDInd;      /*Mode Switch LED operation*/                                                   
    unsigned char uc_EmSwitchPos;    		/*The Emergency Switch Position*/                                               
    uint32_t uc_CfgDelayBwFBAndBarrier;     /*Cfg delay flasherBell to Barr*/ 
    uint32_t uc_CfgDelayToDetectBarrFail;   /*Delay bn Barrrcmd to fail decl*/ 
    unsigned short int us_CfgBuzzerOp;      /*config of Buzzor operation*/ 

    unsigned short int us_CFGData[4];       /*DIP Switches Data */
    unsigned char uc_EmGCOp;                /*Emergency Gate close Operation*/
    unsigned char uc_EmGOOp;                /*Emergency Gate open Operation*/

    unsigned char uc_TrainAppBuzzSet;		/*Train Approach Buzzer*/
    unsigned char uc_BattBKPRAMStatus;		/*Battery Back Up RAM Status*/
    unsigned char uc_FIBHealth;				/*FIB Health*/
    unsigned char uc_ECM_Partial_Fail;		/*ECM Partial Fail*/
    unsigned char uc_Input_DatVal_Fail;		/*Input Data Validation Fail*/
    uint32_t ui_TAppTime;					/*Train Approach Time*/

    unsigned char uc_WrongDirTimerFlag;		/*Wrong Direction Timer Flag*/
    uint32_t ui_WrongDirTimer;				/*Wrong Direction Timer*/
	unsigned char uc_CrankLock;				/*Crank Lock*/
	
	unsigned char uc_CTPUP;					/* For reading CTP UP PB pressed */  
	unsigned char uc_CTPDN;					/* For reading CTP DN PB pressed */
	unsigned char uc_UpDirTrPassedInd;
	unsigned char uc_DnDirTrPassedInd;
	
} GateInfo_t;

extern GateInfo_t st_Lpso_GateOp; /* Declared for Gate Opearations */

extern unsigned char uc_LPM_Reset_Flag;/*Flag To Maintain LPM Restart*/
extern uint32_t sui_SemiAutoTime;
extern uint32_t sui_ManualModeTime;
extern uint32_t sui_ROMTime;

/* For WSS Reset */
extern unsigned char uc_CTPUpFlag;
extern unsigned char uc_CTPDnFlag;
extern uint32_t ui_CTPPBTimer;

//extern uint32_t sui_AppSensorFailIndTime;

typedef struct 
{
    unsigned char uc_CmnErrInd;              /*Common Error operation*/                                 
    unsigned char uc_ErrBuzzOp;              /*Error Buzzor operation*/                                 
    unsigned char uc_AppSensorFailInd;       /*Approach sensor fail op*/                         
    unsigned char uc_ErrIpToSignalCabin;     /*Err input to signal cabin op*/                  
    unsigned char uc_RHSEnBarFailInd;        /*RHS Entry fail operation*/                               
    unsigned char uc_LHSEnBarFailInd;        /*LHS Entry fail operation*/                               
    unsigned char uc_RHSExBarFailInd;        /*RHS Exit fail operation*/                                
    unsigned char uc_LHSExBarFailInd;        /*LHS Exit fail operation*/                                
    unsigned char uc_RHSYFFailInd;           /*RHS Yellow fail operation*/                              
    unsigned char uc_LHSYFFailInd;           /*LHS Yellow fail operation*/                              
    unsigned char uc_RHSRFFailInd;           /*RHS Red fail operation*/                                 
    unsigned char uc_LHSRFFailInd;           /*LHS Red fail operation*/                                 
    unsigned char uc_RHSBellFailInd;         /*RHS Bell fail operation*/                                
    unsigned char uc_LHSBellFailInd;         /*LHS Bell fail operation*/ 
    unsigned char uc_CSMFailSet;             /*CSM Failure */
	#ifdef AXM_CARD_FAILURE
    unsigned char uc_AXMFailSet;             /*AXM Failure */
	#endif /*#ifdef AXM_CARD_FAILURE*/
	unsigned char uc_CSMAUXFailSet;             /*CSM AUX Card Failure */
	unsigned char uc_SSRFailSet;             /*SSR Card Failure */
	uint32_t ui_BuzzOnTime;					 /*Buzzer ON time*/
    unsigned char uc_EmswitchFailInd;		 /*Emergency Switch Fail operation*/
    unsigned char uc_ModeswitchFailInd;		 /*Mode Switch Fail operation*/
} Failure_t;

extern Failure_t st_Lpso_GFOp; /* Declared for Gate Failure Operations*/

typedef struct 
{
    unsigned char uc_CPEnable;  /*Log CP enable/disable*/
    unsigned char uc_CTPUP;     /*Log CTP-UP PB Pressed*/
    unsigned char uc_CTPDN;     /*Log CTP-DN PB Pressed*/
    unsigned char uc_EXRHSG0;   /*Log Exit B1 GO PB Pressed*/
    unsigned char uc_EXRHSGC;   /*Log Exit B1 GC PB Pressed*/
    unsigned char uc_EXLHSG0;   /*Log Exit B2 GO PB Pressed*/
    unsigned char uc_EXLHSGC;   /*Log Exit B2 Gc PB Pressed*/
    unsigned char uc_GOPB;      /*Log PB Pressed to Open All barriers*/
    unsigned char uc_GCPB;      /*Log PB Pressed to clode All barriers*/
    unsigned char uc_ACK;       /*Log ACK PB Pressed*/
    unsigned char uc_SAM;       /*Log SAM PB Pressed*/
    unsigned char uc_ROM;       /*Log ROM PB Pressed*/
    unsigned char uc_MANUAL;    /*Log Manual PB Pressed*/
}PushButton_t;

extern PushButton_t st_Lpso_LogPB;/* Declared for Logging Push Button Event*/

typedef struct 
{
    unsigned char uc_DSS1WrongDir;  /*DSS1 wrong direction detection*/
    unsigned char uc_DSS2WrongDir;  /*DSS2 wrong direction detection*/
    unsigned char uc_DSS3WrongDir;  /*DSS3 wrong direction detection*/
    unsigned char uc_DSS4WrongDir;  /*DSS4 wrong direction detection*/

	unsigned char uc_DSS1RightDir;  /*DSS1 Right direction detection*/
    unsigned char uc_DSS2RightDir;  /*DSS2 Right direction detection*/
	unsigned char uc_DSS3RightDir;  /*DSS3 Right direction detection*/
    unsigned char uc_DSS4RightDir;  /*DSS4 Right direction detection*/

	unsigned char uc_resetDSS1WSSUPWrongDir;/*DSS1-UP flag to reset WSS*/
	unsigned char uc_resetDSS2WSSUPWrongDir;/*DSS2-UP flag to reset WSS*/
	unsigned char uc_resetDSS3WSSUPWrongDir;/*DSS3-UP flag to reset WSS*/
	unsigned char uc_resetDSS4WSSUPWrongDir;/*DSS4-UP flag to reset WSS*/

	unsigned char uc_resetDSS1WSSDNWrongDir;/*DSS1-DN flag to reset WSS*/
	unsigned char uc_resetDSS2WSSDNWrongDir;/*DSS2-DN flag to reset WSS*/
	unsigned char uc_resetDSS3WSSDNWrongDir;/*DSS3-DN flag to reset WSS*/
	unsigned char uc_resetDSS4WSSDNWrongDir;/*DSS4-DN flag to reset WSS*/

	uint32_t ui_DSS1UPWrongDirTimer;/*DSS1-UP Wrong Dir Timer*/
	uint32_t ui_DSS2UPWrongDirTimer;/*DSS2-UP Wrong Dir Timer*/
	uint32_t ui_DSS3UPWrongDirTimer;/*DSS3-UP Wrong Dir Timer*/
	uint32_t ui_DSS4UPWrongDirTimer;/*DSS4-UP Wrong Dir Timer*/

	uint32_t ui_DSS1DNWrongDirTimer;/*DSS1-DN Wrong Dir Timer*/
	uint32_t ui_DSS2DNWrongDirTimer;/*DSS2-DN Wrong Dir Timer*/
	uint32_t ui_DSS3DNWrongDirTimer;/*DSS3-DN Wrong Dir Timer*/
	uint32_t ui_DSS4DNWrongDirTimer;/*DSS4-DN Wrong Dir Timer*/

    
}WSSinput_t;

extern WSSinput_t st_Lpso_Wss;


/*To control all the operations of Lpso module*/
void LpsoModuleControlFunction(void);
/*To give output through data bus*/
void Lpso_OutputControlling( unsigned char,
                             unsigned char);
/*To select the mode of ECM by operator*/
void Lpso_ModeSwitchSelection(void);
/*To control the Mode switch operations by forcing*/
void Lpso_ModeSwitchControl(void);
/*To select the M-Mode as communicted by HHU*/
unsigned char Lpso_MModeSelection(void);
/*To select the Mode by HHU*/
unsigned char Lpso_ModeSelByHHU(unsigned char);
/*To Lit - ON Perticular Mode switch LED*/
void Lpso_ModeSwitchLEDInd(void);
/*To select the Emergency switch.*/
void Lpso_EmergencySwitchfunc(void);
/*To detect the train approach by interface*/

void Lpso_TrainAppDetByInterface(void);

void Lpso_TrainAppDetByElecInterface(void);
/*To detect the train approach by WSS interface*/
void Lpso_TrainAppDetByWSSInterface(void);
/*To detect the train approach by PB*/
void Lpso_TrainAppDetByPB(void);
/*To detect the train approach for Maintanace operation by HHU*/
unsigned char Lpso_TrainAppByHHU(unsigned char);
/*To detect the train Depearture for Maintanace operation by HHU*/
unsigned char Lpso_TrainDepByHHU(unsigned char);
/*To deselect the M - MOde as communicted by HHU*/
unsigned char Lpso_MModeDeselection(unsigned char);
/*To indicate the  train approach LED and train approach Buzzer*/
void Lpso_TrainAppDirAndBuzzorInd(void);
/*To set the flag for Gate closing sequence */
void Lpso_OperationBeforeGC(void);
/*To perform Lever Operations before Gate Close*/
static void Lpso_LeverOpBeforeGC(void);
/*To initate the flasher and bell*/
void Lpso_FlasherBellOpForGC(void);
/*To interlock about RED flasher and BELL*/
void Lpso_IpToInterLockRFAndBell(void);
/*To Contol the barrier closing operation*/
void Lpso_BarrierOpGc(void);
/* To Open the exit barrier on Gate close*/
void Lpso_ExBarrierOpenOnPBinGC(void);
/*To close the opened exit barrier on Gate close*/
void Lpso_ExBarrierCloseOnPBinGC(void);
/*To give input to interlock about Barrier*/
void Lpso_IpToInterLockBarrier(void);
/*To perform Lever operations after Barrier close*/
void Lpso_LeverOpAfterGc(void);
/*To provide reset pulse to wss*/
void Lpso_ResetWss(void);
void Lpso_ResetWss1(void);
/*To detect the train Departure by interface*/
void Lpso_TrainDepDetByInterface(void);
/*To detect the train depearture by PB*/
void Lpso_TrainDepDetByPB(void);
/*To check whter Lx platform is clear to start the opening seq*/
void Lpso_LxPformClrCheckForGO(void);
/*To Indicate the Train passed LED, On Lx platfrom clearance 
  to Complete opening sequence*/
void Lpso_TrPassedLEDOP(void);
/* To Contol the Lever operations before gate open*/
void Lpso_LeverOpBeforeGo(void);
/*To Contol the barrier opening operation*/
void Lpso_BarrierOpG0(void);
/*To initate the flasher and bell*/
void Lpso_FlasherBellOpForGO(void);
/*To Contol the Lever operations after gate open*/
void Lpso_LeverOpAfterGo(void);
/*To LIT - ON the PB LED on pressing any push button*/
void Lpso_PBLedLitOnPBPress(void);
/*To log the events on PB press*/
void Lpso_LogPBPress(void);
/*To log the events on Control Panel PB press*/
void Lpso_LogCPPBPress(void);   
/*To log the events on CTP-UP PB press*/
void Lpso_LogCTPUPPBPress(void);   
/*To log the events on CTP-DN PB press*/
void Lpso_LogCTPDNPBPress(void);    
/*To log the events on RHS Exit GO PB press*/
void Lpso_LogRHSExGOPBPress(void);   
/*To log the events on RHS Exit GC PB press*/
void Lpso_LogRHSExGCPBPress(void);   
/*To log the events on LHS Exit GO PB press*/
void Lpso_LogLHSExGOPBPress(void);    
/* To log the events on LHS Exit GC PB press*/
void Lpso_LogLHSExGCPBPress(void);   
/*To log the events on GO PB press*/
void Lpso_LogGOPBPress(void);  
/*To log the events on GC PB press*/
void Lpso_LogGCPBPress(void);  
/*To log the events on ACK PB press*/
void Lpso_LogACKPBPress(void); 
/* To log the events on SAM PB press*/
void Lpso_LogSAMPBPress(void); 
/* To log the events on ROM PB press*/
void Lpso_LogROMPBPress(void);    
/* To log the events on MANUAL PB press*/
void Lpso_LogMANUALPBPress(void);   
/*To Contol the barrier closing operation*/
void Lpso_LatchRemForBarrier(void);
/*To perform the emergency gate close operation due to 
             approach sensor fail or emergency C position*/
void Lpso_EmGateClose(void);
/*To perform the emergency gate open operation*/
void Lpso_EmGateOpen(void);
/*To initate the flasher and bell*/
void Lpso_EmFlBellOpForGC(void);
/*To Contol the barrier closing operation*/
void Lpso_EmBarrierOpGc(void);
/*To Contol the barrier opening operation*/
void Lpso_EmBarrierOpG0(void);
/*To initate the flasher and bell*/
void Lpso_EmFlBellOpForGO(void);
/*To process yellow flasher failure*/
void Lpso_YFFailProcess(void);
/*To process Red flasher failure*/
void Lpso_RFFailProcess(void);
/*To process Bell failure*/
void Lpso_BellFailProcess(void);
/*To process Entry Barrier failure*/
void Lpso_EnBarrierFailProcess(void);
/*To process Exit Barrier failure*/
void Lpso_ExBarrierFailProcess(void);
/*To process Common Error LED*/
void Lpso_CmnErrProcess(void);
/*To process Error Buzzor */
void Lpso_ErrBuzzProcess(void);
/*To process Approach Sensor fail*/
void Lpso_AppSensorFailProcess(void);
/*To reset the flashers,bell,inputtointerlock(s),
       Train approach and trainpassedLED in Manual Mode Process */
void Lpso_ManualModeProcess(void);
/*To reset the train passed LED if ABC not in Emergency A Position*/
void Lpso_ResetTPLEDOnABCNotInA(void);

/*To withdraw flasher and bell cmd on manual mode*/
static void Lpso_ResetFlasherBell(void);
/*To withdraw barrier cmd on manual mode*/
static void Lpso_ResetBarrier(void);
/*To with draw input to inter lock on manual mode*/
static void Lpso_ManResetIptoInterlock(void);
/*To with draw direction indicators,if cmd is given on manual mode*/
static void Lpso_ManTrAppDirAndBuzzIndReset(void);
/*To with draw Tp LED on manual mode*/
static void Lpso_ManClearTpLED(void);
/*To reset the train approach direction */
static void Lpso_ResetTrainAppDir(void);
/*To Intialize module control functions */
void LpsoIntilizeFunction(void);
/*To Intialize Gate Opeartion structure with default values*/
void InitLpsoGateOpStruct(void);

#ifdef CONFIG_STORE_BATT_BACKUP
	/*To Intialize gate configuration variables with default values*/
	void initLpsoConfigAtStartUpOnly(void);
#endif /*#ifdef CONFIG_STORE_BATT_BACKUP*/

/*To Intialize Gate Fail Opeartion structure with default values*/
void InitLpsoGateFailOpStruct(void);
/*To Intialize Push Button structure with default values*/
void InitLpsoLogPBStruct(void);
/*To detect the train approach from signal cabin*/
void Lpso_ManTrainAppDetFrmSigCabin(void);
/*To detect the train departure from signal cabin*/
void Lpso_ManTrainDepDetFrmSigCabin(void);
/*To process input to interlock for barriers*/
void Lpso_IpToInterLockBarrierHigh(void);
/*To process system mode detection*/
void Lpso_SystemModeDetection(void);
/*To process mode switch failure*/
void Lpso_ModeSwitchFailProcess(void);
/*To process Emergency switch failure*/
void Lpso_EmSwitchFailProcess(void);
/*To process Resetting of WSS on wrong direction occupation*/
void Lpso_ResetWssOnWrongDir(void);
/*To process Resetting of LPM to normal state*/
void Lpso_ResetLPMtoNormalState(void);
/*To process setting of Lx operation flags on LPM restart*/
static void Lpso_setFlagsOnLPMReset(void);
/*To process setting of Lx Lever LPM restart*/
static void Lpso_setLxLeverOnLPMreset(void);
/*To Process Crank Lock*/
void Lpso_CrankLockRelease(void);
/*To Reset Train Approach*/
void Lpso_TrAppResetInSAMandRO(void);
/*To Reset Train Approach flag*/
void Lpso_ResetTrAPPflag(void);
/*To Process barrier operation depending on LxLever*/
void Lpso_BarrierOpenWithLxLever(void);
/*To Process Gate Opening operation depending on LxLever*/
void Lpso_BarrierOpG0OnLxLever(void);
/*To release LxLever Lock*/
void Lpso_ReleaseLxLeverLock(void);

/*New Logics for Mechanical system*/
void InitLpsoWssDirStruct(void);

/*New Logics for Mechanical system*/
void Lpso_wrongDirectionForWSS(void);
void Lpso_setFlagforDSS1WSSUPreset(void);
void Lpso_setFlagforDSS1WSSDNreset(void);
void Lpso_setFlagforDSS2WSSUPreset(void);
void Lpso_setFlagforDSS2WSSDNreset(void);
void Lpso_setFlagforDSS3WSSUPreset(void);
void Lpso_setFlagforDSS3WSSDNreset(void);
void Lpso_setFlagforDSS4WSSUPreset(void);
void Lpso_setFlagforDSS4WSSDNreset(void);



#endif /*LXOPPROCESS_H*/


/*End Of File*/
