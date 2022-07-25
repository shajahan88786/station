/******************************************************************************
* File Name: version.h
*
* File Description: This file contains the declarations for the routines  of 
*                   version.c
*
* Modification History: Ver/Rev      CR        ATR         Remarks
*
* Created by:   
*
* Modified by:  
*
* Compiler/Assembler/Linker: Armcc.Exe V3.1.0.919, Armasm.Exe V3.1.0.919,
*                               ArmLink.Exe V3.1.0.919
*
* Version/Revision: 0.1
*
******************************************************************************/

#ifndef VERSION_H
#define VERSION_H

/*To Maintain Main Version of Build*/
#define MAIN_VERSION 1
/*To Maintain Sub Version of Build*/
#define SUB_VERSION 0

#define ONE		 1
#define TWO		 2
#define TEN		 10
#define TWENTY	 20
#define TWENTYFIVE	 25

typedef struct 
{
    unsigned int ui_Sec;       /* Second value - [0,59]           */
    unsigned int ui_Min;       /* Minute value - [0,59]           */
    unsigned int ui_Hour;      /* Hour value - [0,23]             */
    unsigned int ui_Day;       /* Day of the month value - [1,31] */
    char uc_Month[4];          /* Month value - [Jan,Feb...Dec]   */
    unsigned int ui_Year;      /* Year value - [0,4095]           */	
}BuildDateTime_t;

extern BuildDateTime_t st_BuildDateTime;/*To Maintain Build Date and Time*/

/* To Maintain Build Date and Time */
void verBuildDateTime(void);



#endif/*VERSION_H*/


/*End Of File*/


