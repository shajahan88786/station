/******************************************************************************
* File Name			: Communication.h
*
* Abstract		    : This file contains the MACRO and function protype for      
*					communication pertaining to active and S&D microcontroller.    
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

#ifndef COMMUNICATION_H
#define COMMUNICATION_H


#define DELAY_ACK_TRANSMISSION  THIRTY_MS

#define TIMEOUT_STARTUP_SETTING	(uint32_t)(2*TWO_SEC)

#define ONE					1
#define TWO					2
#define THREE				3
#define FOUR				4
#define FIVE				5
#define SIX					6
#define SEVEN				7
#define EIGHT				8
#define NINE				9
#define TEN					10
#define ELEVEN				11
#define TWELVE				12
#define THIRTEEN			13
#define FOURTEEN			14
#define FIFTEEN				15
#define SIXTEEN				16
#define SEVENTEEN			17
#define EIGHTEEN			18
#define NINETEEN			19
#define TWENTY				20
#define TWENTY_ONE			21
#define TWENTY_TWO			22
#define TWENTY_THREE		23
#define TWENTY_FOUR			24
#define TWENTY_FIVE			25
#define TWENTY_SIX			26
#define TWENTY_SEVEN		27
#define TWENTY_EIGHT		28
#define TWENTY_NINE			29
#define THIRTY				30
#define THIRTY_ONE			31
#define FIFTY				50

#define ONE_BYTE			8
#define TWO_BYTE			16
#define THREE_BYTE			24
#define FOUR_BYTE			32

#define TWELVE_BYTE			96

/* Event Loging Macros */

#define EVENT_CODE                          1
#define FAIL_CODE                           2
#define IMP_EVENT_CODE                      3
#define MBIT_EVENT							4
#define MBIT_FAIL							5
#define CONFIG_EVENT                        6
#define IPDEV_STATUS						9


enum Fail_Log
{
         ON_ALL_RHS_YF_OK = ONE,                        /* 1 */   /* Logging Yellow Flasher ON Status */  
         ON_SINGLE_RHS_YF_FAIL_ON_POST,                 /* 2 */                  
         ON_ALL_RHS_YF_FAIL_ON_POST,                    /* 3 */                  
         ON_1OR2_RHS_YF_FAIL_ON_CANTI,                  /* 4 */                  
         ON_3OR4_RHS_YF_FAIL_ON_CANTI,                  /* 5 */                  
         ON_1OR2AND3OR4_RHS_YF_FAIL_ON_EACH_PAIR,       /* 6 */                  
         ON_3AND4_RHS_YF_FAIL_IN_PAIR,                  /* 7 */                     
         ON_1AND2_RHS_YF_FAIL_IN_PAIR,                  /* 8 */                  
         ON_3AND4AND1OR2_RHS_YF_FAIL_ON_CANTI,          /* 9 */                  
         ON_1AND2AND3OR4_RHS_YF_FAIL_ON_CANTI,          /* 10 */                 
         ON_ALL_RHS_YF_FAIL_ON_CANTI,                   /* 11 */                 
         OFF_ALL_RHS_YF_OK,                             /* 12 */                 
         OFF_SINGLE_RHS_YF_FAIL_ON_POST,                /* 13 */                 
         OFF_ALL_RHS_YF_FAIL_ON_POST,                   /* 14 */                 
         OFF_1OR2_RHS_YF_FAIL_ON_CANTI,                 /* 15 */                 
         OFF_3OR4_RHS_YF_FAIL_ON_CANTI,                 /* 16 */                 
         OFF_1OR2AND3OR4_RHS_YF_FAIL_ON_EACH_PAIR,      /* 17 */                 
         OFF_3AND4_RHS_YF_FAIL_IN_PAIR,                 /* 18 */                 
         OFF_1AND2_RHS_YF_FAIL_IN_PAIR,                 /* 19 */                 
         OFF_3AND4AND1OR2_RHS_YF_FAIL_ON_CANTI,         /* 20 */                 
         OFF_1AND2AND3OR4_RHS_YF_FAIL_ON_CANTI,         /* 21 */                 
         OFF_ALL_RHS_YF_FAIL_ON_CANTI,                  /* 22 */                 
         ON_ALL_LHS_YF_OK,	                            /* 23 */                 
         ON_SINGLE_LHS_YF_FAIL_ON_POST,                 /* 24 */                 
         ON_ALL_LHS_YF_FAIL_ON_POST,                    /* 25 */                 
         ON_1OR2_LHS_YF_FAIL_ON_CANTI,                  /* 26 */                 
         ON_3OR4_LHS_YF_FAIL_ON_CANTI,                  /* 27 */                 
         ON_1OR2AND3OR4_LHS_YF_FAIL_ON_EACH_PAIR,       /* 28 */                 
         ON_3AND4_LHS_YF_FAIL_IN_PAIR,                  /* 29 */                 
         ON_1AND2_LHS_YF_FAIL_IN_PAIR,                  /* 30 */                 
         ON_3AND4AND1OR2_LHS_YF_FAIL_ON_CANTI,          /* 31 */                 
         ON_1AND2AND3OR4_LHS_YF_FAIL_ON_CANTI,          /* 32 */                 
         ON_ALL_LHS_YF_FAIL_ON_CANTI,                   /* 33 */                 
         OFF_ALL_LHS_YF_OK,	                            /* 34 */                 
         OFF_SINGLE_LHS_YF_FAIL_ON_POST,                /* 35 */                 
         OFF_ALL_LHS_YF_FAIL_ON_POST,                   /* 36 */                 
         OFF_1OR2_LHS_YF_FAIL_ON_CANTI,                 /* 37 */                 
         OFF_3OR4_LHS_YF_FAIL_ON_CANTI,                 /* 38 */                 
         OFF_1OR2AND3OR4_LHS_YF_FAIL_ON_EACH_PAIR,      /* 39 */                 
         OFF_3AND4_LHS_YF_FAIL_IN_PAIR,                 /* 40 */                 
         OFF_1AND2_LHS_YF_FAIL_IN_PAIR,                 /* 41 */                 
         OFF_3AND4AND1OR2_LHS_YF_FAIL_ON_CANTI,         /* 42 */                 
         OFF_1AND2AND3OR4_LHS_YF_FAIL_ON_CANTI,         /* 43 */                 
         OFF_ALL_LHS_YF_FAIL_ON_CANTI,                  /* 44 */                 
         ON_ALL_RHS_RF_OK,	                    	    /* 45 */                 
         ON_SINGLE_RHS_RF_FAIL_ON_POST,          	    /* 46 */                
         ON_ALL_RHS_RF_FAIL_ON_POST,                    /* 47 */                 
         ON_1OR2_RHS_RF_FAIL_ON_CANTI,                  /* 48 */                 
         ON_3OR4_RHS_RF_FAIL_ON_CANTI,                  /* 49 */                 
         ON_1OR2AND3OR4_RHS_RF_FAIL_ON_EACH_PAIR,       /* 50 */                 
         ON_3AND4_RHS_RF_FAIL_IN_PAIR,                  /* 51 */                 
         ON_1AND2_RHS_RF_FAIL_IN_PAIR,                  /* 52 */                 
         ON_3AND4AND1OR2_RHS_RF_FAIL_ON_CANTI,          /* 53 */                 
         ON_1AND2AND3OR4_RHS_RF_FAIL_ON_CANTI,          /* 54 */                 
         ON_ALL_RHS_RF_FAIL_ON_CANTI,                   /* 55 */                 
         OFF_ALL_RHS_RF_OK,	                            /* 56 */                 
         OFF_SINGLE_RHS_RF_FAIL_ON_POST,                /* 57 */                 
         OFF_ALL_RHS_RF_FAIL_ON_POST,                   /* 58 */                 
         OFF_1OR2_RHS_RF_FAIL_ON_CANTI,                 /* 59 */                 
         OFF_3OR4_RHS_RF_FAIL_ON_CANTI,                 /* 60 */                 
         OFF_1OR2AND3OR4_RHS_RF_FAIL_ON_EACH_PAIR,      /* 61 */                 
         OFF_3AND4_RHS_RF_FAIL_IN_PAIR,                 /* 62 */                 
         OFF_1AND2_RHS_RF_FAIL_IN_PAIR,                 /* 63 */                 
         OFF_3AND4AND1OR2_RHS_RF_FAIL_ON_CANTI,         /* 64 */                 
         OFF_1AND2AND3OR4_RHS_RF_FAIL_ON_CANTI,         /* 65 */                 
         OFF_ALL_RHS_RF_FAIL_ON_CANTI,                  /* 66 */                 
         ON_ALL_LHS_RF_OK,	                            /* 67 */                 
         ON_SINGLE_LHS_RF_FAIL_ON_POST,                 /* 68 */                 
         ON_ALL_LHS_RF_FAIL_ON_POST,                    /* 69 */                 
         ON_1OR2_LHS_RF_FAIL_ON_CANTI,                  /* 70 */                 
         ON_3OR4_LHS_RF_FAIL_ON_CANTI,                  /* 71 */                 
         ON_1OR2AND3OR4_LHS_RF_FAIL_ON_EACH_PAIR,       /* 72 */                 
         ON_3AND4_LHS_RF_FAIL_IN_PAIR,                  /* 73 */                 
         ON_1AND2_LHS_RF_FAIL_IN_PAIR,                  /* 74 */                 
         ON_3AND4AND1OR2_LHS_RF_FAIL_ON_CANTI,          /* 75 */                 
         ON_1AND2AND3OR4_LHS_RF_FAIL_ON_CANTI,          /* 76 */                 
         ON_ALL_LHS_RF_FAIL_ON_CANTI,                   /* 77 */                 
         OFF_ALL_LHS_RF_OK,	                            /* 78 */                 
         OFF_SINGLE_LHS_RF_FAIL_ON_POST,                /* 79 */                 
         OFF_ALL_LHS_RF_FAIL_ON_POST,                   /* 80 */                 
         OFF_1OR2_LHS_RF_FAIL_ON_CANTI,                 /* 81 */                 
         OFF_3OR4_LHS_RF_FAIL_ON_CANTI,                 /* 82 */                 
         OFF_1OR2AND3OR4_LHS_RF_FAIL_ON_EACH_PAIR,      /* 83 */                 
         OFF_3AND4_LHS_RF_FAIL_IN_PAIR,                 /* 84 */                 
         OFF_1AND2_LHS_RF_FAIL_IN_PAIR,                 /* 85 */                 
         OFF_3AND4AND1OR2_LHS_RF_FAIL_ON_CANTI,         /* 86 */                 
         OFF_1AND2AND3OR4_LHS_RF_FAIL_ON_CANTI,         /* 87 */                 
         OFF_ALL_LHS_RF_FAIL_ON_CANTI,                  /* 88 */                 
         RHS_BELL_ON_NOK,    						    /* 89 */                
         RHS_BELL_ON_OK,     						    /* 90 */                
         RHS_BELL_OFF_NOK,    						    /* 91 */                 
         RHS_BELL_OFF_OK,    						    /* 92 */                 
         LHS_BELL_ON_NOK,    						    /* 93 */                
         LHS_BELL_ON_OK,     						    /* 94 */                
         LHS_BELL_OFF_NOK,    						    /* 95 */                 
         LHS_BELL_OFF_OK,     						    /* 96 */                 
         UP_DIR_ON_RHS_LHS_OK,							/* 97 */  
         UP_DIR_ON_RHS_FAIL,							/* 98 */  
         UP_DIR_ON_LHS_FAIL,							/* 99 */  
         UP_DIR_ON_RHS_LHS_FAIL,						/* 100 */ 
         UP_DIR_OFF_RHS_LHS_OK,							/* 101 */ 
         UP_DIR_OFF_RHS_FAIL,							/* 102 */ 
         UP_DIR_OFF_LHS_FAIL,							/* 103 */ 
         UP_DIR_OFF_RHS_LHS_FAIL,						/* 104 */ 
         DN_DIR_ON_RHS_LHS_OK,							/* 105 */ 
         DN_DIR_ON_RHS_FAIL,							/* 106 */ 
         DN_DIR_ON_LHS_FAIL,							/* 107 */ 
         DN_DIR_ON_RHS_LHS_FAIL,						/* 108 */ 
         DN_DIR_OFF_RHS_LHS_OK,							/* 109 */ 
         DN_DIR_OFF_RHS_FAIL,							/* 110 */ 
         DN_DIR_OFF_LHS_FAIL,							/* 111 */ 
         DN_DIR_OFF_RHS_LHS_FAIL,						/* 112 */ 
         RHS_EN_CL_CLSENSOR_NOK,                        /* 113 */                
         RHS_EN_CL_CLSENSOR_OK,                         /* 114 */                
         RHS_EN_CL_OPSENSOR_NOK,                        /* 115 */                
         RHS_EN_CL_OPSENSOR_OK,                         /* 116 */                
         RHS_EN_OPE_CLSENSOR_NOK,                       /* 117 */                
         RHS_EN_OPE_CLSENSOR_OK,                        /* 118 */                
         RHS_EN_OPE_OPESENSOR_NOK,                      /* 119 */                
         RHS_EN_OPE_OPESENSOR_OK,                       /* 120 */                
         LHS_EN_CL_CLSENSOR_NOK,                        /* 121 */                
         LHS_EN_CL_CLSENSOR_OK,                         /* 122 */                
         LHS_EN_CL_OPSENSOR_NOK,                        /* 123 */                
         LHS_EN_CL_OPSENSOR_OK,                         /* 124 */                
         LHS_EN_OPE_CLSENSOR_NOK,                       /* 125 */                
         LHS_EN_OPE_CLSENSOR_OK,                        /* 126 */                
         LHS_EN_OPE_OPSENSOR_NOK,                       /* 127 */                
         LHS_EN_OPE_OPSENSOR_OK,                        /* 128 */                
         RHS_EX_CL_CLSENSOR_NOK,                        /* 129 */                
         RHS_EX_CL_CLSENSOR_OK,                         /* 130 */                
         RHS_EX_CL_OPSENSOR_NOK,                        /* 131 */                
         RHS_EX_CL_OPSENSOR_OK,                         /* 132 */                
         RHS_EX_OPE_CLSENSOR_NOK,                       /* 133 */                
         RHS_EX_OPE_CLSENSOR_OK,                        /* 134 */                
         RHS_EX_OPE_OPSENSOR_NOK,                       /* 135 */                
         RHS_EX_OPE_OPSENSOR_OK,                        /* 136 */                
         LHS_EX_CL_CLSENSOR_NOK,                        /* 137 */                
         LHS_EX_CL_CLSENSOR_OK,                         /* 138 */                
         LHS_EX_CL_OPSENSOR_NOK,                        /* 139 */                
         LHS_EX_CL_OPSENSOR_OK,                         /* 140 */                
         LHS_EX_OPE_CLSENSOR_NOK,                       /* 141 */                
         LHS_EX_OPE_CLSENSOR_OK,                        /* 142 */                
         LHS_EX_OPE_OPSENSOR_NOK,                       /* 143 */                
         LHS_EX_OPE_OPSENSOR_OK,                        /* 144 */                
         RHS_ENTRY_CRANK_REMOVED,                       /* 145 */                
         RHS_ENTRY_CRANK_INSERTED,                      /* 146 */                
         LHS_ENTRY_CRANK_REMOVED,                       /* 147 */                
         LHS_ENTRY_CRANK_INSERTED,                      /* 148 */                
         RHS_EXIT_CRANK_REMOVED,                        /* 149 */                
         RHS_EXIT_CRANK_INSERTED,                       /* 150 */                
         LHS_EXIT_CRANK_REMOVED,                        /* 151 */                
         LHS_EXIT_CRANK_INSERTED,                       /* 152 */                
         APPROACH_SENSOR_FAIL,                          /* 153 */                
         APPROACH_SENSOR_RECOVERED,                     /* 154 */                
         BATT_LOW_DETECTED,                             /* 155 */                
         BATT_RECOVERED,                                /* 156 */                
         AC_MAINS_PS_NOK,                               /* 157 */                
         AC_MAINS_PS_OK,                                /* 158 */                
         DVRS_HEALTH_NOK,                               /* 159 */                
         DVRS_HEALTH_OK,                                /* 160 */  
         MODE_SWITCH_ERROR,                             /* 161 */                
         MODE_SWITCH_RECOVERED,                         /* 162 */                
         EMR_SWITCH_ERROR,                              /* 163 */                
         EMR_SWITCH_RECOVERED,                          /* 164 */                
         FIB1_LPM1_NOT_OK,                              /* 165 */         
         FIB1_LPM1_OK,                     	            /* 166 */                
         FIB2_LPM1_NOT_OK,                              /* 167 */               
         FIB2_LPM1_OK,                     	            /* 168 */               
         FIB3_LPM1_NOT_OK,                              /* 169 */               
         FIB3_LPM1_OK,                     	            /* 170 */         
         LXLEVER_ERROR,                                 /* 171 */               
         LXLEVER_RECOVERED,                             /* 172 */               
         SIGNALLEVER_ERROR,                             /* 173 */               
         SIGNALLEVER_RECOVERED,                         /* 174 */ 
         CRANK_SAFE,                                    /* 175 */
         CRANK_NOT_SAFE,                                /* 176 */
         INPUT_READING_FAIL,                           /* 177 */
		 CRANK_NOT_SAFE_FAIL,							/* 178 */
         BATTERY_CHARGER_NOK,                           /* 179 */
         BATTERY_CHARGER_OK,                            /* 180 */
		 FIB1_LPM2_NOT_OK,                              /* 181 */         
         FIB1_LPM2_OK,                     	            /* 182 */                
         FIB2_LPM2_NOT_OK,                              /* 183 */               
         FIB2_LPM2_OK,                     	            /* 184 */               
         FIB3_LPM2_NOT_OK,                              /* 185 */               
         FIB3_LPM2_OK,                     	            /* 186 */  
		 FIB1_LPM3_NOT_OK,                              /* 187 */                
         FIB1_LPM3_OK,                     	            /* 188 */                
         FIB2_LPM3_NOT_OK,                              /* 189 */               
         FIB2_LPM3_OK,                     	            /* 190 */               
         FIB3_LPM3_NOT_OK,                              /* 191 */               
         FIB3_LPM3_OK,                     	            /* 192 */			
         CSM_CARD_NOT_OK,                                /* 193 */
         AXM_CARD_NOT_OK,		                         /* 194 */
		 CSM_CARD_OK,									 /* 195 */
         AXM_CARD_OK,								     /* 196 */
		 CSM_AUX_CARD_NOT_OK,							/* 197 */
		 CSM_AUX_CARD_OK,								/* 198 */
		 SSR_CARD_NOT_OK,								/* 199 */
		 SSR_CARD_OK									/* 200 */
 };                                                  

enum Event_Log
{
    YF_ON_COMMAND = ONE,                /* 1 */ 
    YF_OFF_COMMAND,                     /* 2 */ 
    RF_ON_COMMAND,                      /* 3 */ 
    RF_OFF_COMMAND,                     /* 4 */ 
    BELL_ON_COMMAND,                    /* 5 */ 
    BELL_OFF_COMMAND,                   /* 6 */ 
    UP_DIR_INDI_ON_COMMAND,             /* 7 */ 
    UP_DIR_INDI_OFF_COMMAND,            /* 8 */ 
    DN_DIR_INDI_ON_COMMAND,             /* 9 */ 
    DN_DIR_INDI_OFF_COMMAND,            /* 10 */                                
    RHS_EN_BARRIER_CLOSE_ON,            /* 11 */
    LHS_EN_BARRIER_CLOSE_ON,            /* 12 */ 
    RHS_EX_BARRIER_CLOSE_ON,            /* 13 */
    LHS_EX_BARRIER_CLOSE_ON,            /* 14 */
    RHS_EN_BARRIER_OPEN_ON,             /* 15 */
    LHS_EN_BARRIER_OPEN_ON,             /* 16 */
    RHS_EX_BARRIER_OPEN_ON,             /* 17 */
    LHS_EX_BARRIER_OPEN_ON,             /* 18 */
    DVRS_ON_COMMAND,                    /* 19 */
    DVRS_OFF_COMMAND,                   /* 20 */                                
    IP_TO_INTERLOCK_FLASHER_BELL_GREEN, /* 21 */
    IP_TO_INTERLOCK_FLASHER_BELL_OFF,   /* 22 */ 
    IP_TO_INTERLOCK_FLASHER_BELL_RED,   /* 23 */
    IP_TO_INLK_BARRIER_GREEN,           /* 24 */
    IP_TO_INLK_BARRIER_RED,             /* 25 */
    UP_TRAIN_APP_DETECTED,              /* 26 */
    DN_TRAIN_APP_DETECTED,              /* 27 */
    TRAIN_APP_DETECTED_BY_PB,           /* 28 */
    MAN_TRAIN_APP_DET_FROM_SIG_CAB,     /* 29 */
    TRAN_APP_BUZZER_CMD_ON,             /* 30 */
    UP_TRAIN_DEP_DETECTED,              /* 31 */
    DN_TRAIN_DEP_DETECTED,              /* 32 */    		                            
    TRAIN_DEP_DETECTED_BY_PB,		    /* 33 */
    MAN_TRAIN_DEP_DET_FROM_SIG_CAB,     /* 34 */
    TRAN_APP_BUZZER_CMD_OFF,            /* 35 */
    LX_LEVER_LOCKED,                    /* 36 */
    LX_LEVER_LOCK_RELEASED,             /* 37 */
    LX_LEVER_NORMAL,	                /* 38 */
    LX_LEVER_REVERSE,                   /* 39 */
    SIGNAL_LEVER_LOCKED,                /* 40 */
    SIGNAL_LEVER_LOCK_RELEASED,         /* 41 */      
    SIGNAL_LEVER_NORMAL,                /* 42 */
    SIGNAL_LEVER_REVERSE,               /* 43 */
    TRAIN_PASSED_LED_OFF,               /* 44 */ 
    TRAIN_PASSED_LED_ON,                /* 45 */
    RESET_CMD_TO_WSS_UP,                /* 46 */
    RESET_CMD_TO_WSS_DN,                /* 47 */
    EM_SWITCH_A_POS,                    /* 48 */
    EM_SWITCH_B_POS,                    /* 49 */
    EM_SWITCH_C_POS,                    /* 50 */
    LOG_MANUAL_MODE,                    /* 51 */
    LOG_RES_OP_MODE,                    /* 52 */
    LOG_SEMI_AUTO_MODE,                 /* 53 */
    COMMON_ERROR_ON,                    /* 54 */
    COMMON_ERROR_OFF,                   /* 55 */
    ERROR_BUZZER_ON,                    /* 56 */
    ERROR_BUZZER_OFF,                   /* 57 */                                 
    PB_ACK_LED_ON,		  			    /* 58 */
    PB_ACK_LED_OFF,		  			    /* 59 */
    CP_ENABLED,			  			    /* 60 */
    CP_DISABLED,			   			/* 61 */
    CTP_UP_PRESSED,		   			    /* 62 */
    CTP_DN_PRESSED,					    /* 63 */
    EX_GO_RHS_PRESSED,		 		    /* 64 */
    EX_GC_RHS_PRESSED,		  		    /* 65 */
    EX_GO_LHS_PRESSED,		   		    /* 66 */
    EX_GC_LHS_PRESSED,	                /* 67 */	   		
    GO_PB_PRESSED,		  		        /* 68 */
    GC_PB_PRESSED,		  		        /* 69 */
    ACK_PB_PRESSED,		 		        /* 70 */
    SAM_PB_PRESSED,		 		        /* 71 */
    ROM_PB_PRESSED,		 		        /* 72 */
    MANUAL_PB_PRESSED,		 		    /* 73 */
    TIME_UPDATION_FROM_MASTER,          /* 74 */
	CRANK_LOCK_RELEASED,                /* 75 */
    CRANK_LOCK_LOCKED,                  /* 76 */
	MANUAL_MODE_RHS_YF_ON,			    /* 77 */
	MANUAL_MODE_RHS_YF_OFF,			    /* 78 */
	MANUAL_MODE_RHS_RF_ON,			    /* 79 */
	MANUAL_MODE_RHS_RF_OFF,			    /* 80 */
	MANUAL_MODE_LHS_YF_ON,			    /* 81 */
	MANUAL_MODE_LHS_YF_OFF,			    /* 82 */
	MANUAL_MODE_LHS_RF_ON,			    /* 83 */
	MANUAL_MODE_LHS_RF_OFF,			    /* 84 */
	MANUAL_MODE_RHS_BELL_ON,		    /* 85 */
	MANUAL_MODE_RHS_BELL_OFF,			/* 86 */
	MANUAL_MODE_LHS_BELL_ON,		    /* 87 */
	MANUAL_MODE_LHS_BELL_OFF,		    /* 88 */
	MANUAL_MODE_UP_DIR_ON,			    /* 89 */
	MANUAL_MODE_UP_DIR_OFF,			    /* 90 */
	MANUAL_MODE_DN_DIR_ON,			    /* 91 */
	MANUAL_MODE_DN_DIR_OFF,			    /* 92 */
	MANUAL_MODE_LXLEVER_REVERSE,	    /* 93 */
	MANUAL_MODE_LXLEVER_NORMAL,		    /* 94 */
	MANUAL_MODE_SIGNALLEVER_REVERSE,    /* 95 */
	MANUAL_MODE_SIGNALLEVER_NORMAL,	    /* 96 */
	MANUAL_MODE_RHS_ENTRY_CLOSED,	    /* 97 */
	MANUAL_MODE_RHS_ENTRY_OPENED,	    /* 98 */
	MANUAL_MODE_RHS_EXIT_CLOSED,	    /* 99 */
	MANUAL_MODE_RHS_EXIT_OPENED,	    /* 100 */
	MANUAL_MODE_LHS_ENTRY_CLOSED,	    /* 101 */
	MANUAL_MODE_LHS_ENTRY_OPENED,	    /* 102 */
	MANUAL_MODE_LHS_EXIT_CLOSED,	    /* 103 */
	MANUAL_MODE_LHS_EXIT_OPENED,	    /* 104 */
	VLM_OUTPUT_FLASHERANDBELL_ON,	    /* 105 */
	VLM_OUTPUT_FLASHERANDBELL_OFF,	    /* 106 */
	VLM_OUTPUT_ENTRYBARRIER_CLOSED,     /* 107 */
	VLM_OUTPUT_ENTRYBARRIER_OPENED,	    /* 108 */
	VLM_OUTPUT_LXLEVER_LOCKED,		    /* 109 */
	VLM_OUTPUT_LXLEVER_RELEASEED,	    /* 110 */
	VLM_OUTPUT_SIGNALLEVER_LOCKED,	    /* 111 */
	VLM_OUTPUT_SIGNALLEVER_RELEASEED,   /* 112 */
	VLM_OUTPUT_INPUT1INTERLOCK_HIGH,    /* 113 */
	VLM_OUTPUT_INPUT1INTERLOCK_LOW,	    /* 114 */
	VLM_OUTPUT_INPUT2INTERLOCK_HIGH,    /* 115 */
	VLM_OUTPUT_INPUT2INTERLOCK_LOW,	    /* 116 */
	LOG_SEMI_AUTO_MODE_DETECTED,		/* 117 */  
	LOG_MANUAL_MODE_DETECTED,			/* 118 */  
	LOG_RES_OP_MODE_DETECTED,    		/* 119 */ 
    UP_DIR_TRAIN_PASSED_LED_ON,			/* 120 */
	DN_DIR_TRAIN_PASSED_LED_ON			/* 121 */
};                                      

enum Imp_Event_Log
{
    HHU_MAINT_MODE = 1,                     /* 1 */ 
    HHU_SEMI_AUTO_MODE,                     /* 2 */ 
    HHU_RES_OP_MODE,                        /* 3 */ 
    HHU_MANUAL_MODE,                        /* 4 */ 
    HHU_MODE_SWITCH_ERROR,                  /* 5 */ 
    HHU_UP_TRAIN_APP_SIMULATED,             /* 6 */ 
    HHU_DN_TRAIN_APP_SIMULATED,             /* 7 */ 
    HHU_UP_TRAIN_DEP_SIMULATED,             /* 8 */ 
    HHU_DN_TRAIN_DEP_SIMULATED,             /* 9 */ 
    HHU_DESELECT_MAINTMODE                  /* 10 */ 
};                                          

/*Function type for communication between S&D to Active MicroControllers */
#define ACTIVEDATETIME			 0x01	/* Set Active Date & Time*/
#define ACTIVECFG				 0x02	/* Set Active CFG */
#define EVENTREQUEST			 0x03	/* Event Request */
#define MMODESELECT				 0x04	/* M-MODE Selection */
#define SEMIMODE				 0x05	/* Semi Auto Mode */
#define RESTRICTEDMODE			 0x06	/* Restricted Mode */
#define MANUALMODE				 0x07	/* Manual Mode */
#define TRAPDETECTION			 0x08	/* Train Approach (TA) */
#define TRDPDETECTION			 0x09	/* Train Departure (TD) */
#define FIELDDEVICES			 0x10	/* Field Devices */
#define MMODEDESELECT			 0x11	/* M-Mode Deselected */
#define MODECGECKCONFIG			 0x12	/* MODE Check for Configuration */
#define EVENTACKTOACTIVE		 0x13	/* ACK for event packet reception */
#define ACKFORBROADCAST			 0x14	/* ACK for Broadcast packet reception */
#define CONFIGDATAREQ			 0x15   /* Configuration data request */
#define ECM_PARTIAL_FAIL		 0x16	/* ECM Partial Fail */
#define ECM_NO_PARTIAL_FAIL		 0x17	/* NO ECM Partial Fail */
#define BROADCASTDATETIME		 0x18	/* Date & TIme Broadcast Pkt */



/*Function type for communication between Active to S&D MicroControllers */
#define ACKDATETIME				 0x21	/* ACK for Date & Time */
#define ACKACTIVECFG			 0x22	/* ACK for Set Active CFG */
#define ACKNODATA				 0x23	/* Event Requestz */
#define ACKDATA					 0x24	/* M-MODE Selection */
#define ACKMODESELECT			 0x25	/* Semi Auto Mode */
#define ACKSEMIMODE				 0x26	/* Semi Auto Mode */
#define ACKRESTRICTMODE			 0x27	/* Restricted Mode */
#define ACKMANUALMODE			 0x28	/* Manual Mode */
#define ACKTRAPDETECTION		 0x29	/* Train Approach (TA)*/
#define ACKTRDPDETECTION		 0x30	/* Train Departure (TD) */
#define ACKFIELDDEVICES			 0x31	/* Field Devices */
#define ACKMMODEDESELECT		 0x32	/* M-Mode Deselected by HHU*/
#define ACKMODECGECKCONFIG		 0x33	/* MODE Check for Configuration*/
//#define ACKMMODEDESELECTTR	 0x34	/* M-MODE Deselected By train*/
#define ACKCONFIGDATAREQ         0x34	/* Configuration Data ACK*/
#define ACK_ECM_PARTIAL_FAIL     0x35	/*ACK for ECM Partial Fail*/





/* Sub Type for M-Mode Processing */



#define FLSANDBELLSON		1
#define FLSANDBELLSOFF		2

//#define YELLOWFLON			1   /*Yellow Flasher ON*/
//#define YELLOWFLOFF			2   /*Yellow Flasher OFF*/

//#define REDFLON				23   /*Red Flasher ON*/
//#define REDFLOFF			24   /*Red Flasher OFF*/

//#define BELLON				25   /*Bell ON*/
//#define BELLOFF				26   /*Bell OFF*/



#define DIRINDICATORON		3   /*Direction Indicators ON*/
#define DIRINDICATOROFF		4   /*Direction Indicators OFF*/
#define ENBARRIEROPEN   	5   /*Entry Barrier Open*/
#define ENBARRIERCLOSE		6   /*Entry Barrier Close*/
#define EXBARRIEROPEN   	7   /*Exit Barrier Open*/
#define EXBARRIERCLOSE		8   /*Exit Barrier Close*/
#define INPUTDEVICES		9   /*Input Devices*/

#define DEFAULT_ID			4

#define WATCHDOG_STROBE_PIN   0x1000000       /* P4.24 for Watchdog Strobe */

#define CHANNEL_HEALTH_PIN    0x00004000      /* P0.14 for Channel Fail */

#define WDT_CHANGE_OVER       (THIRTY_MS)	/*Change Over Duration*/

#define MAX_EVENTS			  100	/*Max Number Of Events*/
#define MAX_COMM_TYPE         20	/*No of Field Devices*/

extern unsigned char guc_CommSNDID;     /* S&D Microcontroller Id */
extern unsigned char guc_CommDateTimeUpadted; /* Used for Date time updation */

extern unsigned char guc_CommMCMID;     /* For Self MCM Id */

extern unsigned char guc_CommType;    /* Field device comm type */
extern unsigned char guc_SubFunctionType; /* Sub type revcd from S&D */
extern short int si_PowerOn;

typedef struct 
{
    unsigned char uc_TimeUpdated;   /* Date And Time Updated From S&D */
    unsigned char uc_StartUpdated;  /* On Startup Date And Time Updated From S&D */
    uint32_t ui_TimeClk;            /* Clock For Acknowledgement of Date And Time*/
}TimeUpdate_t;

/*Declared for Maintain Time updation From SND*/ 
extern TimeUpdate_t st_Comm_TimeUpdation; 

/* Structure used for Broadcast Message Reply to S&D */
typedef struct 
{
    unsigned char uc_FunctionType; /*Function type*/
    unsigned char uc_RequestReceived;/*Recieved Request*/
    unsigned char uc_TransmitCount;/*Transmit count*/
    short int si_Status;/*Status*/
} BroadcastMsg_t;

/*Declared to maintain transmitting message status*/
extern BroadcastMsg_t st_Comm_BroadcastMsg[MAX_COMM_TYPE];

/* Structure used to maintain Events */
typedef struct
{
	unsigned int ui_Milli_Sec;/*Milli Second*/
	unsigned int ui_Sec;/*Seconds*/
	unsigned int ui_Min;/*Minutes*/
	unsigned int ui_Hour;/*Hours*/


	unsigned int ui_Day;/*Day*/
	unsigned int ui_Mon;/*Month*/
	unsigned int ui_Year;/*Year*/
		
	unsigned char uc_EventCode;/*Event Code*/
	unsigned long ui_EventNum;/*Event Number*/
}EventStruct_t;

/*Declared To Maintain Event Information*/ 
extern 	EventStruct_t st_EventInfo[MAX_EVENTS];

/* To Maintain Read Index and Write Index for reading and writing data*/ 
extern unsigned char guc_ReadIndex,guc_WriteIndex;

extern uint32_t sui_RetransmitTime;/*Packet Retransmission Time*/

/*Function protype for Packet reception from S&D
 */
void CommProcessMaster(unsigned char);
/*This function form the ACK for Date and Time after checking RTC status*/
void CommDateTimeACK(void);
/*This function process the data receive from S&D microcontroller*/
static void Comm_ProcessMasterData(unsigned char *);
/*This function Upadate the Date and Time of Self Microcontroller*/
static void Comm_UpdateDateAndTime(unsigned char *);
/*This function receive the configuration parameter from 
  HHU thru S&D microcontroller*/
static unsigned char Comm_UpdateCfgParams(unsigned char *, unsigned char, unsigned char );
/*This function recv the request for Event logging*/
static void Comm_RespToEvntFail(unsigned char,unsigned char);
/*This function process the request for Filed device processing*/
static void Comm_FieldDevices(unsigned char);
/*This function used for reading the RTC status and from the packet
  for S&D tregarding the last data and time updatipn status.*/
static void Comm_ProcessTimeStatusUpdation(void);
/*This function form and transmit the event packet based on 
  the sequence*/
void CommTransmitEvent(void);
/*This function form and transmit the ACK for Field Devices*/
void CommFieldDeviceStatus(unsigned char uc_SubSytemType);
/* prototype for ACK to S&D */
static unsigned char Comm_FormACKOperationMode(unsigned char *,
                                               unsigned char,
                                               unsigned char);
/*This function form the ACK for M-Mode deselection*/                                             
static unsigned char Comm_FormACKMModeDeselection(unsigned char *,
                                                  unsigned char);
/*This function form the ACK for Date and Time updation*/
static unsigned char Comm_FormAckDateTime(unsigned char *,unsigned char);
/*This function form the ACK packet for configuration mode*/
static unsigned char Comm_FormAckConfigModeStatus(unsigned char *,
                                                  unsigned char);
/*This function form the ACK for Train approach*/                                                  
static unsigned char Comm_FormACKTrainApproach(unsigned char *,
                                               unsigned char);
/*This function form the ACK for Train Departure*/
static unsigned char Comm_FormACKTrainDeparture(unsigned char *,
                                                unsigned char);
/*This function form the ACK for M-Mode selection*/
static unsigned char Comm_FormACKMModeSelection(unsigned char *,
                                                unsigned char);
/*This function form the ACK for configuration in Active*/
static unsigned char Comm_FormAckConfig(unsigned char *, unsigned char );
/*This function initialize the watchdog timer*/
static unsigned char Comm_FormAckNoData(unsigned char *);
/*This function form the packet and transmit the event logs*/
static unsigned char Comm_FormAckDateLog(unsigned char *);
/*This function form ACK packet for Field Devices*/
static unsigned char Comm_FormAckFieldDevice(unsigned char *,
                                             unsigned char);
/*This function get the self MCM Id.*/
void CommMCMSelection(void);
/*This function sends watchdog strobe signal.*/
void CommWatchDogStrobe(void);
/*This function fills the structure for event logging*/
void CommEventLog(unsigned char, unsigned int);
/*This function initializes the Event Info Structure*/
void CommInitEventStruct(void);
/*This function form and transmit the event packet based on 
  the sequence.*/
void CommTransmitBroadcastPacket(void);
/*This function form and transmit the event packet based on 
  the sequence.*/
void CommResetBroadcastSructure(void);

/* For Sending Channel Health as OK*/
void CommChanHealth(void);
/*This function is to transmit ack for the confiuration 
  data request */
unsigned char Comm_FormAckConfigDataReq(unsigned char *);
/*This function is to transmit ack for the partial fail */
unsigned char Comm_FormAckEcmPartialfail(unsigned char *);
/*This function is to Extract Date And Time From Events Request Packet */
void Comm_ExtractDateAndTimeFromEventsRequestPacket(unsigned char *);

void Comm_StartUpSetting(void);
void Comm_StartUpData(unsigned char * puc_MasterMessage );
void Comm_StartUpDateAndTime(unsigned char *puc_TimeStamp, unsigned char uc_FuncType);
#endif /* COMMUNICATION_H */

/*End Of File*/

