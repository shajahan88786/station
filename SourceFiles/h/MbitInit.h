/******************************************************************************
* File Name			: MBit.h
*
* Abstract		    : This file contains the declarations for feedback checking 
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


#ifndef MBITINIT_H
#define MBITINIT_H


/* Prior to checking the feedback (FB) of Flashers (FL)
 * it shall have an initial delay of around 500ms.
 */
#define INITIAL_DELAY_FLFB	HALF_SEC

/* Prior to checking the feedback (FB) of Direction Indicator (DI) 
 * it shall have an initial delay of around 500ms.
 */
#define INITIAL_DELAY_DIFB	HALF_SEC


#define ONE					1
#define TWO					2
#define THREE				3
#define FOUR				4
#define FIVE				5
#define SIX					6
#define SEVEN				7
#define EIGHT				8
#define EIGHTEEN			18

typedef struct 
{
    unsigned char uc_MModeStatus;             /*To detect M-Mode*/
    unsigned char uc_TrAppUPByHHU;            /*To detect UP Train App M-Mode*/
    unsigned char uc_TrAppDNByHHU;            /*To detect DN Train App M-Mode*/
    unsigned char uc_TrDepUPByHHU;            /*To detect UP Train Dep M-Mode*/
    unsigned char uc_TrDepDNByHHU;            /*To detect DN Train Dep M-Mode*/

    unsigned char uc_RealTrAppInUp;           /*Real UP Train in M-Mode*/
    unsigned char uc_RealTrAppInDn;           /*Real UP Train in M-Mode*/

    unsigned char uc_EnBarrierClose;          /*Entry Barrier Maint close op*/                              
    unsigned char uc_EnBarrierOpen;           /*Entry Barrier Maint open op*/                              
    unsigned char uc_ExBarrierClose;          /*Exit Barrier  Maint close op*/                                
    unsigned char uc_ExBarrierOpen;           /*Exit Barrier  Maint open op*/                                
    unsigned char uc_YFRFBellOn ;             /*YF,RF and Bell Maint ON op*/                              
    unsigned char uc_YFRFBelloff ;            /*YF,RF and Bell Maint op*/                              
    unsigned char uc_DirOn;                   /*Dir Maint ON op*/                              
    unsigned char uc_DirOff;                  /*Dir Maint OFF op*/                              
    unsigned char uc_IpDev;                   /*Input dev */                              
    
  
    unsigned int ui_YFRFBellOnStatus;    /*YF,RF,Bell ON status*/                  
    unsigned int ui_YFRFBellOffStatus;   /*YF,RF,Bell OFF status*/                  
    unsigned int ui_DirIndOnStatus;      /*DIR 0N status*/        
    unsigned int ui_DirIndOffStatus;     /*DIR OFF status*/        
    unsigned int ui_EnCloseStatus;       /*Entry Barrier Status*/  
    unsigned int ui_EnOpenStatus;       /*Entry Barrier Status*/  
    unsigned int ui_ExCloseStatus;        /*Exit Barrier status*/      
    unsigned int ui_ExOpenStatus;        /*Exit Barrier status*/      
    unsigned int ul_IpDevStatus;       /*All input device Staus*/  
	   

    
    unsigned char uc_FlAndBellSet; /* Flasher And Bell CMD Status */
    unsigned char uc_DirSet;        /* Direction Indicator CMD status*/
    unsigned char uc_EnBarrierSet; /* Entry Barrier CMD status*/
    unsigned char uc_ExBarrierSet; /* Exit Barrier CMD status */

    uint32_t ui_DirFBTime;      /* Direction Indicator FB check time */
    uint32_t ui_YFRFBellFBTime; /* Flasher and Bell FB check time */
    uint32_t ui_EnBarrierTime;  /* Entry Barrier FB check time */
    uint32_t ui_ExBarrierTime;  /* Exit Barrier FB check time */
    
    unsigned char uc_TrainAppInUPLED; /*Tarin Approach In UP LED Inicator*/
    unsigned char uc_TrainAppInDNLED;/*Tarin Approach In DOWN LED Inicator*/


} Maintanance_t;                             

extern Maintanance_t st_Ofds_MaintOp; /* Declared for Maintanace Operations*/

typedef struct  
{
    unsigned char uc_RHSYFONStatus; /* RHS YF Fail */
    unsigned char uc_LHSYFONStatus; /* LHS YF Fail */
    unsigned char uc_RHSRFONStatus; /* RHS RF Fail */
    unsigned char uc_LHSRFONStatus; /* LHS RF Fail */
    unsigned char uc_RHSBellONStatus; /* RHS Bell Fail */
    unsigned char uc_LHSBellONStatus; /* LHS Bell Fail */

    unsigned char uc_RHSUPDirIndiONStatus; /* For UP Dir Indicator ON Fail */
    unsigned char uc_LHSUPDirIndiONStatus; /* For UP Dir Indicator ON Fail */
    unsigned char uc_RHSDNDirIndiONStatus; /* For DN Dir Indicator ON Fail */
    unsigned char uc_LHSDNDirIndiONStatus; /* For DN Dir Indicator ON Fail */

    unsigned char uc_RHSYFOFFStatus; /* RHS YF OFF Fail */
    unsigned char uc_LHSYFOFFStatus; /* LHS YF OFF Fail */
    unsigned char uc_RHSRFOFFStatus; /* RHS RF OFF Fail */
    unsigned char uc_LHSRFOFFStatus; /* LHS RF OFF Fail */
    unsigned char uc_RHSBellOFFStatus; /* RHS Bell OFF Fail */
    unsigned char uc_LHSBellOFFStatus; /* LHS Bell OFF Fail */

     unsigned char uc_RHSUPDirIndiOFFStatus; /* For UP Dir Indicator OFF Fail */
    unsigned char uc_LHSUPDirIndiOFFStatus; /* For UP Dir Indicator OFF Fail */
    unsigned char uc_RHSDNDirIndiOFFStatus; /* For DN Dir Indicator OFF Fail */
    unsigned char uc_LHSDNDirIndiOFFStatus; /* For DN Dir Indicator OFF Fail */

    
    unsigned char uc_RHSEnCloseStatus; /*RHS Entry Close Barrier Fail*/
    unsigned char uc_RHSExCloseStatus; /*RHS Exit Close Barrier Fail*/
    unsigned char uc_LHSEnCloseStatus; /*LHS Entry Close Barrier Fail*/
    unsigned char uc_LHSExCloseStatus; /*LHS Exit Close Barrier Fail*/
    unsigned char uc_RHSEnOpenStatus; /*RHS Entry Open Barrier Fail*/
    unsigned char uc_RHSExOpenStatus; /*RHS Exit Open Barrier Fail*/
    unsigned char uc_LHSEnOpenStatus; /*LHS Entry Open Barrier Fail*/ 
    unsigned char uc_LHSExOpenStatus; /*LHS Exit Open Barrier Fail*/

    unsigned char uc_RHSEnClCloseSensor; /*RHS En Close sensor Fail in close */
    unsigned char uc_RHSEnClOpenSensor;/*RHS En Open sensor Fail in close */
    unsigned char uc_LHSEnClCloseSensor;/*LHS En Close sensor Fail in close */
    unsigned char uc_LHSEnClOpenSensor;/*LHS En Open sensor Fail in close */
    unsigned char uc_RHSEnOpeCloseSensor;/*RHS En Close sensor Fail in Open */
    unsigned char uc_RHSEnOpeOpenSensor;/*RHS En Open sensor Fail in Open */
    unsigned char uc_LHSEnOpeCloseSensor;/*LHS En Close sensor Fail in Open */
    unsigned char uc_LHSEnOpeOpenSensor;/*LHS En Open sensor Fail in Open */

    unsigned char uc_RHSExClCloseSensor;/*RHS Ex Close sensor Fail in close */
    unsigned char uc_RHSExClOpenSensor;/*RHS Ex open sensor Fail in close */
    unsigned char uc_LHSExClCloseSensor;/*LHS Ex Close sensor Fail in close */
    unsigned char uc_LHSExClOpenSensor;/*LHS Ex open sensor Fail in close */
    unsigned char uc_RHSExOpeCloseSensor;/*RHS Ex Close sensor Fail in open */
    unsigned char uc_RHSExOpeOpenSensor;/*RHS Ex open sensor Fail in open */
    unsigned char uc_LHSExOpeCloseSensor;/*LHS Ex Close sensor Fail in open */
    unsigned char uc_LHSExOpeOpenSensor;/*LHS Ex open sensor Fail in open */


} MbitGate_t;

extern MbitGate_t st_Ofds_MbitGateFB; /*Declared for Maintenance of subsystems*/

extern unsigned char guc_OfdsFldDevType;/*For Storing Field Device Type*/

/*To Perform Maintenance operation of LXCS*/
void OfdsMbit(void);
/*To Perform Flasher Bell ON Commend on M-Bit request*/
void Ofds_FlasherBellON(void);
/*To Perform Flasher Bell OFF Commend on M-Bit request*/
void Ofds_FlasherBellOFF(void);
/*To Perform Direction Indicator ON Commend on M-Bit request*/
void Ofds_DirIndiON(void);
/*To Perform Direction Indicator OFF Commend on M-Bit request*/
void Ofds_DirIndiOFF(void);
/*To Perform Entry Barrier Open Command on M-Bit request*/
void Ofds_EnBarrierOpen(void);
/*To Perform Entry Barrier Close Command on M-Bit request*/
void Ofds_EnBarrierClose(void);
/*To Perform Exit Barrier Open Command on M-Bit request*/
void Ofds_ExBarrierOpen(void);
/*To Perform Exit Barrier Close Command on M-Bit request*/
void Ofds_ExBarrierClose(void);
/*To Perform operations on Input devices on M-Bit request*/
void Ofds_Inputdevices(void);
/*To Perform Bit stuffing for Entry Barrier Close FB on M-Bit request*/
void Ofds_EnBarrierClFBitStuffing(void);
/*To Perform Bit stuffing for Entry Barrier Open FB on M-Bit request*/
void Ofds_EnBarrierOPFBitStuffing(void);
/*To Perform Bit stuffing for Exit Barrier Open FB on M-Bit request*/
void Ofds_ExBarrierClFBitStuffing(void);
/*To Perform Bit stuffing for Exit Barrier Open FB on M-Bit request*/
void Ofds_ExBarrierOPFBitStuffing(void);
/*To Perform Bit stuffing for Direction Indication ON FB on M-Bit request*/
void Ofds_DIRIndiONBitStuffing(void);
/*To Perform Bit stuffing for Direction Indication OFF FB on M-Bit request*/
void Ofds_DIRIndiOFFBitStuffing(void);
/*To Perform Bit stuffing for YF RF Bell ON FB on M-Bit request*/
void Ofds_YFRFBellONBitStuffing(void);
/*To Perform Bit stuffing for YF RF Bell OFF FB on M-Bit request*/
void Ofds_YFRFBellOFFBitStuffing(void);
/*To Contol the entry barrier closing operation*/
void Ofds_EnBarrierCloseCmd(void);
/*To Contol the entry barrier opening operation*/
void Ofds_EnBarrierOpenCmd(void);
/*To Open the exit barrier on Gate close */
void Ofds_ExBarrierOpenCmd(void);
/*To Open the exit barrier on Gate close*/
void Ofds_ExBarrierCloseCmd(void);
/*To switch ON Direction Indicators*/
void Ofds_DirIndicatorON(void);
/*To switch OFF Direction Indicators*/
void Ofds_DirIndicatorOFF(void);
/*To initate the flasher and bell*/
void Ofds_FlasherBellOpForONCmd(void);
/*To deactivate the flasher and bell*/
void Ofds_FlasherBellOpForOFFCmd(void);
/*To detect Failure of RHS Yellow ON Flashers*/
void Ofds_RHSYFONFailureDetection(void);
/*To detect Failure of RHS Yellow OFF Flashers*/
void Ofds_RHSYFOFFFailureDetection(void);
/*To detect Failure of LHS Yellow ON Flashers*/
void Ofds_LHSYFONFailureDetection(void);
/*To detect Failure of LHS Yellow OFF Flashers*/
void Ofds_LHSYFOFFFailureDetection(void);
/*To detect Failure of RHS Red ON Flashers*/
void Ofds_RHSRFONFailureDetection(void);
/*To detect Failure of RHS Red OFF Flashers*/
void Ofds_RHSRFOFFFailureDetection(void);
/*To detect Failure of LHS Red ON Flashers*/
void Ofds_LHSRFONFailureDetection(void);
/*To detect Failure of LHS Red OFF Flashers*/
void Ofds_LHSRFOFFFailureDetection(void);
/*To detect Failure of RHS Bell*/
void Ofds_RHSBellFeedbackCheck(void);
/*To detect Failure of LHS Bell*/
void Ofds_LHSBellFeedbackCheck(void);
/*To detect UP Direction Indicator failures.*/
void Ofds_UPDirIndiFBCheck(void);
/*To detect DN Direction Indicator failures.*/
void Ofds_DNDirIndiFBCheck(void);
/*To checks RHS Entry Barrier feedback while closing.*/
void Ofds_RHSEnCloseBarrierFBCheck(void);
/*To checks LHS Entry Barrier feedback while closing.*/
void Ofds_LHSEnCloseBarrierFBCheck(void);
/*To checks RHS Entry Barrier feedback while opening.*/
void Ofds_RHSEnOpenBarrierFBCheck(void);
/*To checks LHS Entry Barrier feedback while opening.*/
void Ofds_LHSEnOpenBarrierFBCheck(void);
/*To checks RHS Exit Barrier feedback while closing.*/
void Ofds_RHSExCloseBarrierFBCheck(void);
/*To checks LHS Exit Barrier feedback while closing.*/
void Ofds_LHSExCloseBarrierFBCheck(void);
/*To checks RHS Exit Barrier feedback while opening.*/
void Ofds_RHSExOpenBarrierFBCheck(void);
/*To checks LHS Exit Barrier feedback while opening.*/
void Ofds_LHSExOpenBarrierFBCheck(void);
/*To detect Failure of RHS single Yellow ON Flashers*/
 void Ofds_RHSSingleFlOnPostYFONFailDetection(void);
/*To detect Failure of RHS Both Yellow ON Flashers*/
 void Ofds_RHSBothFlOnPostYFONFailDetection(void);
/*To detect Failure of RHS Yellow ON Flashers*/
 void Ofds_RHSFlOnCantiYFONFailDetection(void);
/*To detect Failure of RHS single Yellow OFF Flashers*/
 void Ofds_RHSSingleFlOnPostYFOFFFailDetection(void);
/*To detect Failure of RHS Both Yellow OFF Flashers*/
 void Ofds_RHSBothFlOnPostYFOFFFailDetection(void);
/*To detect Failure of RHS Yellow OFF Flashers*/
 void Ofds_RHSFlOnCantiYFOFFFailDetection(void);
/*To detect Failure of LHS single Yellow ON Flashers*/
 void Ofds_LHSSingleFlOnPostYFONFailDetection(void);
/*To detect Failure of LHS Both Yellow ON Flashers*/
 void Ofds_LHSBothFlOnPostYFONFailDetection(void);
/*To detect Failure of LHS single Yellow OFF Flashers*/
 void Ofds_LHSSingleFlOnPostYFOFFFailDetection(void);
/*To detect Failure of LHS Both Yellow OFF Flashers*/
 void Ofds_LHSBothFlOnPostYFOFFFailDetection(void);
/*To detect Failure of LHS Yellow OFF Flashers*/
 void Ofds_LHSFlOnCantiYFOFFFailDetection(void);
/*To detect Failure of RHS single Red ON Flashers*/
 void Ofds_RHSSingleFlOnPostRFONFailDetection(void);
/*To detect Failure of RHS Both Red ON Flashers*/
 void Ofds_RHSBothFlOnPostRFONFailDetection(void);
/*To detect Failure of RHS Red ON Flashers*/
 void Ofds_RHSFlOnCantiRFONFailDetection(void);
/*To detect Failure of RHS both Red OFF Flashers*/
 void Ofds_RHSBothFlOnPostRFOFFFailDetection(void);
/*To detect Failure of RHS single Red OFF Flashers*/
 void Ofds_RHSSingleFlOnPostRFOFFFailDetection(void);
/*To detect Failure of RHS Red OFF Flashers*/
 void Ofds_RHSFlOnCantiRFOFFFailDetection(void);
/*To detect Failure of LHS single Red ON Flashers*/
 void Ofds_LHSSingleFlOnPostRFONFailDetection(void);
/*To detect Failure of LHS Yellow ON Flashers.*/
 void Ofds_LHSFlOnCantiYFONFailDetection(void);
/*To detect Failure of LHS Both Red ON Flashers*/
 void Ofds_LHSBothFlOnPostRFONFailDetection(void);
/*To detect Failure of LHS red ON Flashers.*/
 void Ofds_LHSFlOnCantiRFONFailDetection(void);
/*To detect Failure of LHS single red OFF Flashers.*/
 void Ofds_LHSSingleFlOnPostRFOFFFailDetection(void);
/*To detect Failure of LHS both red OFF Flashers*/
 void Ofds_LHSBothFlOnPostRFOFFFailDetection(void);
/*To detect Failure of LHS Yellow OFF Flashers.*/
 void Ofds_LHSFlOnCantiRFOFFFailDetection(void);
/*This is to send the status of input devices to HHU 
  through S n D*/
 void Ofds_InputDevBitStuffing(void);
/*This function Intilizes MbitGate Struct to default values*/
void InitMbitGateStruct(void);
/*This function Intilizes MbitMaintanance Struct to default values*/
void InitMBitMaintananceStruct(void);
/*This function calls the structure initialisation function*/
void MBitStructInitialzeFunc(void);



#endif /* MBIT_H */

/*End Of File*/

