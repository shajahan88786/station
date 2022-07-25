/******************************************************************************
* File Name			: IpReadValid.h
*
* Abstract		    : This file contains the declarations for the routines of 
*					  IpReadValid.c                                                  
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


#ifndef IPREADVALID_H
#define IPREADVALID_H

#define MAX_FIB						2   /* Total FIB Modules */
#define MAX_BUFFER					12  /* Total Buffers of all FIBs */
#define MAX_INPUT_BUFFER			12  /* Max Input Buffers */
#define NO_OF_BUFFERS_OF_EACH_FIB	6   /* No of Buffers of Each FIB Card */

#define TWENTY_SEVEN                27  /* Used for FIB Selection */
#define TWENTY_FOUR                 24  /* Used for Buffer Selection */

#define ONE                         1   /* For Variable Set */
#define ZERO                        0   /* For Variable Reset */
#define FOUR						4
#define EIGHT						8

#define FIB_CARD_SELECTION      0x03        /* For FIB Card Selection */
#define BUFFER_SELECTION        0x07        /* Address Line Buffer Selection */
#define BUFFER_DIRECTION        0x06000000   /* Data Bus and Decoder Enable */
#define FIB_CHK			        0x80800000  /* For FIB Cards Diagnostics */

#define FIB_ONE_CHK      		0x800000    /* For FIB Cards Diagnostics */
#define FIB_TWO_CHK       		0x80000000  /* For FIB Cards Diagnostics */

#define MAX_OUTPUT_BUF  8   /* Total Output Buffers */

/* Configuration Reading From DIP Switches */

typedef struct
{
	unsigned char uc_NoOfGates;         /* Number of Gates */
	unsigned char uc_G1_GateType;       /* Gate-1 Type */
	unsigned char uc_G1_NoOfTracks;     /* Number of Tracks of Gate - 1 */
	unsigned char uc_G1_RHSYF;          /* Existence of RHSYF of Gate-1 */
	unsigned char uc_G1_LHSYF;          /* Existence of LHSYF of Gate-1 */
	unsigned char uc_G1_RHSRF;          /* Existence of RHSRF of Gate-1 */
	unsigned char uc_G1_LHSRF;          /* Existence of LHSRF of Gate-1 */
	unsigned char uc_G1_RHSBell;        /* Existence of RHSBell of Gate-1 */
	unsigned char uc_G1_LHSBell;        /* Existence of LHSBell of Gate-1 */
	unsigned char uc_G1_UPDirIndi;      /* Existence of UPDirInd of Gate - 1*/
	unsigned char uc_G1_DNDirIndi;      /* Existence of DNDirInd of Gate - 1*/
	unsigned char uc_G1_RHSExBarrier;   /* Existence of ExitGate1 of Gate - 1*/
	unsigned char uc_G1_LHSExBarrier;   /* Existence of ExitGate2 of Gate - 1*/
	unsigned char uc_G1_DVRS;           /* Existence of DVRS of Gate - 1*/
    unsigned char uc_G1_EmSwitch;       /* Emergency switch pos*/
	unsigned char uc_SemiAutoMode;		/*Semi Auto Mode*/
    unsigned char uc_RestrictedMode;	/*Restricted Mode*/
    unsigned char uc_ManualMode;		/*Manual Mode*/
	unsigned char uc_DSS1Configinfo;	/* For config DSS-1 data*/
	unsigned char uc_DSS2Configinfo;	/* For config DSS-2 data*/
	unsigned char uc_DSS3Configinfo;	/* For config DSS-3 data*/
	unsigned char uc_DSS4Configinfo;	/* For config DSS-4 data*/
	unsigned char uc_CPsConnected ;		/* For single/ Double CP config Data */
} Config_t;



typedef struct
{
    unsigned char uc_CurInputs[20];/*Array of Current Input*/ 
    unsigned char uc_CurOutputs[10];/*Array of Current output*/
    
}LxGate_t;

/*Declared to Maintaim Current inputs and output*/
extern LxGate_t st_Idrv_LxGate;

extern uint32_t ui_PowerOnTime;/*To Maintain Power ON Time*/
/*Declared to Maintaim Configuration data*/
extern Config_t st_Idrv_CfgInfo;
extern short int si_CfgData[4];/*Array for Storing Config Data*/

/*Asign the flasher and bell config data to data structure*/
void IdrvFlBellsConfigData(void);
/*Asign the primary config data to data structure*/
void IdrvPrimaryConfigData(void);
/*Asign the Mode config data to data structure*/
void IdrvModeConfigData(void);
/*Read the input data from input devices*/
void IdrvInputDataReading(void);
/*Initialize outputs to default values*/
void IdrvOutputDefaultInit(void);
/*Reset the wheel sensing system*/
void SpoiresetTazOnPowerOn(void);
/* validate the input data */
void IdrvInputDataValidation(void);
/*Reload the out put buffers */ 
void IdrvOutputReload(void);
/*New Logics for Mechanical system*/
void IdrvWSSConfigData(void);

#endif /* IPREADVALID_H */


/*End Of File*/

