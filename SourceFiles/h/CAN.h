/*----------------------------------------------------------------------------
 * Name:    CAN.h
 * Purpose: CAN interface for LPC23xx
 * Version: V1.00
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------
 * History:
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/

#ifndef _CAN_H_
#define _CAN_H_

#include <string.h>
#include <stdint.h>                           /* Include standard types */
#include "realtimeclk.h"

#define STANDARD_FORMAT  0
#define EXTENDED_FORMAT  1

#define DATA_FRAME       0
#define REMOTE_FRAME     1


#define CANBUFFSIZE		32


/*enumerated dataType for can ID*/
enum enumCanId
{	
			SELF_INFO_PKT = 1,
								SIG_INFO_PKT,
				
								TRN_LEN_PKT,
								LOCO_INFO_PKT,
								GPS_TIME_PKT = 5,
								LPM_STARTUP,
								SIG_ASPECT,
								S2S_INFO_PKT,
								INPUT_BUF_PKT,
								LPM_SYNC,
								COMM_SYNC,
								RIU_PKT,
	             				STN_NMS_PKT,
	                     CM1_CM2_STATUSINFO,
	                     LOCO_INFO_PKT_2,
	                     STATIC_SPEED_PROFILE_PKT,
						 AUTHENTICATION_KEY_ID,
						 LPM_RADIO_MODEM_HEALTH,	  //sid
						 CM2_LPM_GPS_TIME_PKT,
						 CM2_CM1_RADIO_FAIL,
						 CM1_CM2_RADIO_FAIL,

	            				  MAXCANID
			
};


typedef struct  {
  unsigned int   id;                    /* 29 bit identifier */
  unsigned char  data[8];               /* Data field */
  unsigned char  len;                   /* Length of data field in bytes */
  unsigned char  format;                /* 0 - STANDARD, 1- EXTENDED IDENTIFIER */
  unsigned char  type;                  /* 0 - DATA FRAME, 1 - REMOTE FRAME */
	unsigned char	 canPort;
} CAN_msg;

/* Functions defined in module CAN.c */
void CAN_setup         (uint32_t ctrl);
void CAN_start         (uint32_t ctrl);
void CAN_waitReady     (uint32_t ctrl);
void CAN_wrMsg         (uint32_t ctrl, CAN_msg *msg);
void CAN_rdMsg         (uint32_t ctrl, CAN_msg *msg);
void CAN_wrFilter      (uint32_t ctrl, uint32_t id, uint8_t filter_type);


extern CAN_msg       CAN_TxMsg;      /* CAN messge for sending */
                           

extern unsigned int  CAN_TxRdy[2];      /* CAN HW ready to transmit a message */
extern unsigned int  CAN_RxRdy[2];      /* CAN HW received a message */


/******************************************************************************/
/*                  CAN Specific Peripheral registers structures              */
/******************************************************************************/

/*- IO definitions define access restrictions to peripheral registers --------*/
#define     __I     volatile const            /* 'read only'    permissions   */
#define     __O     volatile                  /* 'write only'   permissions   */
#define     __IO    volatile                  /* 'read / write' permissions   */

/*- Controller Area Network (CAN) --------------------------------------------*/
typedef struct
{
  __IO uint32_t mask[512];              /* ID Masks                           */
} CANAF_RAM_TypeDef;

typedef struct                          /* Acceptance Filter Registers        */
{
  __IO uint32_t AFMR;
  __IO uint32_t SFF_sa;
  __IO uint32_t SFF_GRP_sa;
  __IO uint32_t EFF_sa;
  __IO uint32_t EFF_GRP_sa;
  __IO uint32_t ENDofTable;
  __I  uint32_t LUTerrAd;
  __I  uint32_t LUTerr;
} CANAF_TypeDef;

typedef struct                          /* Central Registers                  */
{
  __I  uint32_t CANTxSR;
  __I  uint32_t CANRxSR;
  __I  uint32_t CANMSR;
} CANCR_TypeDef;

typedef struct                          /* Controller Registers               */
{
  __IO uint32_t MOD;
  __O  uint32_t CMR;
  __IO uint32_t GSR;
  __I  uint32_t ICR;
  __IO uint32_t IER;
  __IO uint32_t BTR;
  __IO uint32_t EWL;
  __I  uint32_t SR;
  __IO uint32_t RFS;
  __IO uint32_t RID;
  __IO uint32_t RDA;
  __IO uint32_t RDB;
  __IO uint32_t TFI1;
  __IO uint32_t TID1;
  __IO uint32_t TDA1;
  __IO uint32_t TDB1;
  __IO uint32_t TFI2;
  __IO uint32_t TID2;
  __IO uint32_t TDA2;
  __IO uint32_t TDB2;
  __IO uint32_t TFI3;
  __IO uint32_t TID3;
  __IO uint32_t TDA3;
  __IO uint32_t TDB3;
} CAN_TypeDef;


/******************************************************************************/
/*                           CAN memory map                                   */
/******************************************************************************/

#define CANAF_RAM_BASE        (0xE0038000)
#define CANAF_BASE            (CAN_ACCEPT_BASE_ADDR)
#define CANCR_BASE            (CAN_CENTRAL_BASE_ADDR)
#define CAN1_BASE             (CAN1_BASE_ADDR)
#define CAN2_BASE             (CAN2_BASE_ADDR)

/******************************************************************************/
/*                         Peripheral declaration                             */
/******************************************************************************/

#define CANAF_RAM             ((CANAF_RAM_TypeDef *) CANAF_RAM_BASE)
#define CANAF                 ((    CANAF_TypeDef *)     CANAF_BASE)
#define CANCR                 ((    CANCR_TypeDef *)     CANCR_BASE)
#define CAN1                  ((      CAN_TypeDef *)      CAN1_BASE)
#define CAN2                  ((      CAN_TypeDef *)      CAN2_BASE)


typedef struct
{
	unsigned char invalid;
	unsigned char expSeqNo;
	void * strPtr;
}canSynch;

extern canSynch canStatus[2][MAXCANID];


/* can functions */

void can_Init(void);
void CAN_transmit (int can_id ,char* datPtr,int len,int seqNo);

void readCanMsgs(void);
void sendCanPkts(void * ,int, enum enumCanId );
void readCanToStructs(void);
void TransmitCanPkt(enum enumCanId);
void * getCanData(enum enumCanId);




extern RTCDateTime_t st_CanDateTime;

/*
#define CANPKT1 1
#define CANPKT2	3
*/
#pragma pack(1)


extern int intr;

typedef struct 
{
	unsigned char canId;
	unsigned char canData[8];
}canBuf;

typedef struct
{
	CAN_msg CAN_msg[CANBUFFSIZE];
	unsigned char In;
	unsigned char Out;
}canReadStruct;

extern canReadStruct canRead;

#pragma pack(4)

#endif // _CAN_H_
