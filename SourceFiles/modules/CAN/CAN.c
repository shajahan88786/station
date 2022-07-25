/*----------------------------------------------------------------------------
 * Name:    Can.c
 * Purpose: CAN interface for for LPC23xx with MCB2300
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

#include "Header.h"


canSynch canStatus[2][MAXCANID];
unsigned char canFailStatus[2] = {0,0};


CAN_msg       CAN_TxMsg;                      /* CAN message for sending */
   

canReadStruct canRead;

unsigned int  CAN_TxRdy[2] = {0,0};              /* CAN HW ready to transmit a message */
unsigned int  CAN_RxRdy[2] = {0,0};              /* CAN HW received a message */
//unsigned int  can1set= 0;                            /*  set receive flag */
unsigned char rx_CAN_1[40];
unsigned char rx_CAN_2[40];



//#define  PCLK            24000000                /* Peripheral clock, depends on VPBDIV */

/* Values of bit time register for different baudrates
   NT = Nominal bit time = TSEG1 + TSEG2 + 3
   SP = Sample point     = ((TSEG2 +1) / (TSEG1 + TSEG2 + 3)) * 100%
                                            SAM,  SJW, TSEG1, TSEG2, NT,  SP */
const uint32_t CAN_BIT_TIME[] = {          0, /*             not used             */
                                           0, /*             not used             */
                                           0, /*             not used             */
                                           0, /*             not used             */
                                  0x0001C000, /* 0+1,  3+1,   1+1,   0+1,  4, 75% */
                                           0, /*             not used             */
                                  0x0012C000, /* 0+1,  3+1,   2+1,   1+1,  6, 67% */
                                           0, /*             not used             */
                                  0x0023C000, /* 0+1,  3+1,   3+1,   2+1,  8, 63% */
                                           0, /*             not used             */
                                  0x0025C000, /* 0+1,  3+1,   5+1,   2+1, 10, 70% */
                                           0, /*             not used             */
                                  0x0036C000, /* 0+1,  3+1,   6+1,   3+1, 12, 67% */
                                           0, /*             not used             */
                                           0, /*             not used             */
                                  0x0048C000, /* 0+1,  3+1,   8+1,   4+1, 15, 67% */
                                  0x0049C000, /* 0+1,  3+1,   9+1,   4+1, 16, 69% */
                                };


/*----------------------------------------------------------------------------
  CAN interrupt handler
 *----------------------------------------------------------------------------*/
static void CAN_ISR (void) __irq;

/*----------------------------------------------------------------------------
  configure the requested baudrate.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
static void CAN_cfgBaudrate (uint32_t ctrl, uint32_t baudrate)  {
  CAN_TypeDef *pCAN = (ctrl == 1) ? CAN1 : CAN2; /* select CAN controller */
  uint32_t result = 0;
  uint32_t nominal_time;

  /* Determine which nominal time to use for PCLK and baudrate */
  if (baudrate <= 500000)  {
    nominal_time = 12;
  }  else if (((PCLK / 1000000) % 15) == 0)  {
    nominal_time = 15;
  }  else if (((PCLK / 1000000) % 16) == 0)  {
    nominal_time = 16;
  }  else  {
    nominal_time = 10;
  }

  /* Prepare value appropriate for bit time register */
  result  = (PCLK / nominal_time) / baudrate - 1;
  result &= 0x000003FF;
  result |= CAN_BIT_TIME[nominal_time];

  pCAN->BTR  = result;                           /* Set bit timing */

	//pCAN->BTR = 0x005BC005; //500 kb/s @ 57.6 Mhz 

}


/*----------------------------------------------------------------------------
  setup CAN interface.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
void CAN_setup (uint32_t ctrl)  
{
  CAN_TypeDef *pCAN = (ctrl == 1) ? CAN1 : CAN2; /* select CAN controller */

  if (ctrl == 1) 
	{
    PCONP   |= 1 << 13;                          /* Enable clock for CAN1 */
    //PINSEL0 &= 0xFFFFFFF0;                       /* Reset CAN1 bits */
    //PINSEL0 |= 0x00000005;                       /* Set CAN1 bits to b0101 */
	PINSEL0 |= 0x00000005;
    
    *(&VICVectAddr23) = (unsigned long) CAN_ISR; /* Set interrupt vector for CAN */
    *(&VICVectCntl23) = 1;
    
    VICIntEnable = (1 << 23);                    /* Enable CAN Interrupt */
  } 
	else 
	{
    PCONP   |= 1 << 14;                          /* Enable clock for CAN2 */
    //PINSEL0 &= 0xFFFFF0FF;                       /* Reset CAN2 bits */
    //PINSEL0 |= 0x00000A00;                       /* Set CAN2 bits to b1010 */
	//PINSEL4 |= 0x00014000;
	PINSEL0 |= 0x00000A00;
    
    *(&VICVectAddr23) = (unsigned long) CAN_ISR; /* Set interrupt vector for CAN */
    *(&VICVectCntl23) = 1;
    
    VICIntEnable = (1 << 23);                    /* Enable CAN Interrupt */
  }

  CANAF->AFMR = 3;                               /* By default filter is not used */
  pCAN->MOD   = 1;                               /* Enter reset mode */
  pCAN->IER   = 0;                               /* Disable all interrupts */
  pCAN->GSR   = 0;                               /* Clear status register */
  CAN_cfgBaudrate(ctrl, 500000);                 /* Set bit timing */
  pCAN->IER   = 0x0003;                          /* Enable Tx and Rx interrupt */
}


/*----------------------------------------------------------------------------
  leave initialisation mode.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
void CAN_start (uint32_t ctrl)  {
  CAN_TypeDef *pCAN = (ctrl == 1) ? CAN1 : CAN2; /* select CAN controller */

  pCAN->MOD = 0;                                 /* Enter normal operating mode */
}

/*----------------------------------------------------------------------------
  check if transmit mailbox is empty
 *----------------------------------------------------------------------------*/
void CAN_waitReady (uint32_t ctrl)  {
  CAN_TypeDef *pCAN = (ctrl == 1) ? CAN1 : CAN2; /* select CAN controller */

  while ((pCAN->SR & (1<<2)) == 0);              /* Transmitter ready for transmission */
  CAN_TxRdy[ctrl-1] = 1;
}

/*----------------------------------------------------------------------------
  wite a message to CAN peripheral and transmit it.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
void CAN_wrMsg (uint32_t ctrl, CAN_msg *msg)  {
  CAN_TypeDef *pCAN = (ctrl == 1) ? CAN1 : CAN2; /* select CAN controller */
  uint32_t CANData;
	uint32_t failClock= 0;

	if (1 == canFailStatus[ctrl-1])
	{
		if(!(pCAN->SR & (1<<2)))	
		{			
			return;
		}
		else
		{
			//printf("CAN OK");
			//Comm_1_Trx_integer(ctrl);			
			canFailStatus[ctrl-1] = 0;
		}
	}
	
	failClock = SpoiGetSysTICs();
	
  CANData = (((uint32_t) msg->len) << 16)     & 0x000F0000 | 
            (msg->format == EXTENDED_FORMAT ) * 0x80000000 |
            (msg->type   == REMOTE_FRAME)     * 0x40000000;
	
	
	while(!(pCAN->SR & (1<<2)))/*loop until buffer is ready*/
	{
		if ((((unsigned long)SpoiGetSysTICs() - failClock)) > 100) 	
		{
			printf("\nCAN Fail");
			//Comm_1_Trx_integer(ctrl);			
			canFailStatus[ctrl-1] = 1;
			return;
		}
	}
	//while((pCAN->GSR & (1<<5))){;/*loop until buffer is ready*/}

  //if (pCAN->SR & (1<<2))  {                      /* Transmit buffer 1 free */
    pCAN->TFI1  = CANData;                       /* Write frame informations */
    pCAN->TID1 = msg->id;                        /* Write CAN message identifier */
    pCAN->TDA1 = *(uint32_t *) &msg->data[0];    /* Write first 4 data bytes */
    pCAN->TDB1 = *(uint32_t *) &msg->data[4];    /* Write second 4 data bytes */
  //  pCAN->CMR  = 0x31;                           /* Select Tx1 for Self Tx/Rx */
    pCAN->CMR  = 0x21;                           /* Start transmission without loop-back */
  //}
	//else
	//{
		//	TXcomport1("Not Ready  ");
	//}
}



/*----------------------------------------------------------------------------
  read a message from CAN peripheral and release it.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
void CAN_rdMsg (uint32_t ctrl, CAN_msg *msg)  {
  CAN_TypeDef *pCAN = (ctrl == 1) ? CAN1 : CAN2; /* select CAN controller */
  uint32_t CANData;
		
	msg->canPort = ctrl;
                                                 /* Read frame informations */
  CANData = pCAN->RFS;
  msg->format   = (CANData & 0x80000000) == 0x80000000;
  msg->type     = (CANData & 0x40000000) == 0x40000000;
  msg->len      = ((uint8_t)(CANData >> 16)) & 0x0F;

  msg->id = pCAN->RID;                           /* Read CAN message identifier */
	

  if (msg->type == DATA_FRAME)  {                /* Read the data if received message was DATA FRAME  */ 
    *(uint32_t *) &msg->data[0] = pCAN->RDA;
    *(uint32_t *) &msg->data[4] = pCAN->RDB;
  }
}


/*----------------------------------------------------------------------------
  setup acceptance filter.  CAN controller (1..2)
 *----------------------------------------------------------------------------*/
void CAN_wrFilter (uint32_t ctrl, uint32_t id, uint8_t format)  {
  static int CAN_std_cnt = 0;
  static int CAN_ext_cnt = 0;
         uint32_t buf0, buf1;
         int cnt1, cnt2, bound1;

  /* Acceptance Filter Memory full */
  if ((((CAN_std_cnt + 1) >> 1) + CAN_ext_cnt) >= 512)
    return;                                       /* error: objects full */

  /* Setup Acceptance Filter Configuration 
    Acceptance Filter Mode Register = Off  */                                 
  CANAF->AFMR = 0x00000001;
	//CANAF->AFMR = 0x00000011;

  if (format == STANDARD_FORMAT)  {              /* Add mask for standard identifiers */
    id |= (ctrl-1) << 13;                        /* Add controller number */
    id &= 0x0000F7FF;                            /* Mask out 16-bits of ID */

    /* Move all remaining extended mask entries one place up                 
       if new entry will increase standard ID filters list   */
    if ((CAN_std_cnt & 0x0001) == 0 && CAN_ext_cnt != 0) {
      cnt1   = (CAN_std_cnt >> 1);
      bound1 = CAN_ext_cnt;
      buf0   = CANAF_RAM->mask[cnt1];
      while (bound1--)  {
        cnt1++;
        buf1 = CANAF_RAM->mask[cnt1];
        CANAF_RAM->mask[cnt1] = buf0;
        buf0 = buf1;
      }        
    }

    if (CAN_std_cnt == 0)  {                     /* For entering first  ID */
      CANAF_RAM->mask[0] = 0x0000FFFF | (id << 16);
    }  else if (CAN_std_cnt == 1)  {             /* For entering second ID */
      if ((CANAF_RAM->mask[0] >> 16) > id)
        CANAF_RAM->mask[0] = (CANAF_RAM->mask[0] >> 16) | (id << 16);
      else
        CANAF_RAM->mask[0] = (CANAF_RAM->mask[0] & 0xFFFF0000) | id;
    }  else  {
      /* Find where to insert new ID */
      cnt1 = 0;
      cnt2 = CAN_std_cnt;
      bound1 = (CAN_std_cnt - 1) >> 1;
      while (cnt1 <= bound1)  {                  /* Loop through standard existing IDs */
        if ((CANAF_RAM->mask[cnt1] >> 16) > id)  {
          cnt2 = cnt1 * 2;
          break;
        }
        if ((CANAF_RAM->mask[cnt1] & 0x0000FFFF) > id)  {
          cnt2 = cnt1 * 2 + 1;
          break;
        }
        cnt1++;                                  /* cnt1 = U32 where to insert new ID */
      }                                          /* cnt2 = U16 where to insert new ID */

      if (cnt1 > bound1)  {                      /* Adding ID as last entry */
        if ((CAN_std_cnt & 0x0001) == 0)         /* Even number of IDs exists */
          CANAF_RAM->mask[cnt1]  = 0x0000FFFF | (id << 16);
        else                                     /* Odd  number of IDs exists */
          CANAF_RAM->mask[cnt1]  = (CANAF_RAM->mask[cnt1] & 0xFFFF0000) | id;
      }  else  {
        buf0 = CANAF_RAM->mask[cnt1];            /* Remember current entry */
        if ((cnt2 & 0x0001) == 0)                /* Insert new mask to even address */
          buf1 = (id << 16) | (buf0 >> 16);
        else                                     /* Insert new mask to odd  address */
          buf1 = (buf0 & 0xFFFF0000) | id;
     
        CANAF_RAM->mask[cnt1] = buf1;            /* Insert mask */

        bound1 = CAN_std_cnt >> 1;
        /* Move all remaining standard mask entries one place up */
        while (cnt1 < bound1)  {
          cnt1++;
          buf1  = CANAF_RAM->mask[cnt1];
          CANAF_RAM->mask[cnt1] = (buf1 >> 16) | (buf0 << 16);
          buf0  = buf1;
        }

        if ((CAN_std_cnt & 0x0001) == 0)         /* Even number of IDs exists */
          CANAF_RAM->mask[cnt1] = (CANAF_RAM->mask[cnt1] & 0xFFFF0000) | (0x0000FFFF);
      }
    }
    CAN_std_cnt++;
  }  else  {                                     /* Add mask for extended identifiers */
    id |= (ctrl-1) << 29;                        /* Add controller number */

    cnt1 = ((CAN_std_cnt + 1) >> 1);
    cnt2 = 0;
    while (cnt2 < CAN_ext_cnt)  {                /* Loop through extended existing masks */
      if (CANAF_RAM->mask[cnt1] > id)
        break;
      cnt1++;                                    /* cnt1 = U32 where to insert new mask */
      cnt2++;
    }

    buf0 = CANAF_RAM->mask[cnt1];                /* Remember current entry */
    CANAF_RAM->mask[cnt1] = id;                  /* Insert mask */

    CAN_ext_cnt++;

    bound1 = CAN_ext_cnt - 1;
    /* Move all remaining extended mask entries one place up */
    while (cnt2 < bound1)  {
      cnt1++;
      cnt2++;
      buf1 = CANAF_RAM->mask[cnt1];
      CANAF_RAM->mask[cnt1] = buf0;
      buf0 = buf1;
    }        
  }
  
  /* Calculate std ID start address (buf0) and ext ID start address (buf1) */
  buf0 = ((CAN_std_cnt + 1) >> 1) << 2;
  buf1 = buf0 + (CAN_ext_cnt << 2);

  /* Setup acceptance filter pointers */
  CANAF->SFF_sa     = 0;
  CANAF->SFF_GRP_sa = buf0;
  CANAF->EFF_sa     = buf0;
  CANAF->EFF_GRP_sa = buf1;
  CANAF->ENDofTable = buf1;

  CANAF->AFMR = 0x00000000;                      /* Use acceptance filter */
 //   CANAF->AFMR = 0x00000011; 
}


/*----------------------------------------------------------------------------
  CAN interrupt handler
 *----------------------------------------------------------------------------*/
static void CAN_ISR (void) __irq 
{
	
  if (CAN1->GSR & (1 << 0)) 
	{                    /* CAN Controller #1 meassage is received */
	 
		CAN_rdMsg (1, &canRead.CAN_msg[canRead.In++]);   /*  read the message to end of circular buffer*/
		
		if(CANBUFFSIZE == canRead.In)
			canRead.In = 0;
		
	  
	  CAN1->CMR = (1 << 2);                        /* Release receive buffer */
  
   }

  if (CAN2->GSR & (1 << 0)) {                    /* CAN Controller #2 meassage is received */
	
		//TXcomport1("\n CAN Controller #2 meassage is received ");
		
		CAN_rdMsg (2, &canRead.CAN_msg[canRead.In++]);   /*  read the message to end of circular buffer*/
		
		if(CANBUFFSIZE == canRead.In)
			canRead.In = 0;
	
    CAN2->CMR = (1 << 2);                        /* Release receive buffer */
    
	}			

	CAN1->ICR;                              /* clear interrupts */
  CAN2->ICR;
  VICVectAddr = 0xFFFFFFFF;                      /* Acknowledge Interrupt */
}

/*----------------------------------------------------------------------------
  initialize CAN interface
 *----------------------------------------------------------------------------*/
void can_Init(void)
{

  //CAN_setup (1);                                  /* setup CAN Controller #1 */
  CAN_setup (2);                                  /* setup CAN Controller #2 */
	
  CAN_wrFilter (2, SELF_INFO_PKT, STANDARD_FORMAT);   /* Enable reception of messages 1*/	
  CAN_wrFilter (2, SIG_INFO_PKT, STANDARD_FORMAT);   /* Enable reception of messages 2*/	
  CAN_wrFilter (2, TRN_LEN_PKT, STANDARD_FORMAT);   /* Enable reception of messages 2*/
  CAN_wrFilter (2, LPM_STARTUP, STANDARD_FORMAT);   /* Enable reception of messages 2*/
	CAN_wrFilter (2, SIG_ASPECT, STANDARD_FORMAT);   /* Enable reception of messages 2*/
//CAN_wrFilter (2, HEXFILE_CRCREQ, STANDARD_FORMAT);
	CAN_wrFilter (2, AUTHENTICATION_KEY_ID, STANDARD_FORMAT); 
//	CAN_wrFilter (2, REQ_PKT_ID, STANDARD_FORMAT);
	CAN_wrFilter (2, STATIC_SPEED_PROFILE_PKT, STANDARD_FORMAT);
	if(gucSelfSlot == 4)
	CAN_wrFilter (2, CM1_CM2_STATUSINFO, STANDARD_FORMAT);

	CAN_wrFilter (2, CM2_CM1_RADIO_FAIL, STANDARD_FORMAT); 
  	CAN_wrFilter (2, CM1_CM2_RADIO_FAIL, STANDARD_FORMAT);
	

 // CAN_start (1);                                  /* start CAN Controller #1 */
  CAN_start (2);                                  /* start CAN Controller #2 */

//  CAN_waitReady (1);                              /* wait til tx mbx is empty */
  CAN_waitReady (2);                              /* wait til tx mbx is empty */
  
}

void CAN_transmit (int can_id ,char* datPtr,int len,int seqNo)
{
	char i=0;
	

	CAN_TxMsg.id = can_id; ;     
	

	CAN_TxMsg.data[0] = seqNo;
	for (i = 0; i < len-1; i++) 
	{
		CAN_TxMsg.data[i+1] = *(datPtr+i);	
	} 
	
	  CAN_TxMsg.len = len;                   
    CAN_TxMsg.format = STANDARD_FORMAT;
    CAN_TxMsg.type = DATA_FRAME;         
	
    //CAN_wrMsg (1, &CAN_TxMsg);               /* transmit message */
    CAN_wrMsg (2, &CAN_TxMsg);               /* transmit message */	
}


void sendCanPkts(void *sptr, int size,enum enumCanId canId)
{
	int j = size,seqNo=0;
	char *cptr = sptr;
	
	//printf("Frame ");
		
	while(j > 0)
	{
			
		if(j < 7)
			CAN_transmit(canId,cptr,j+1,seqNo);
		else
			CAN_transmit(canId,cptr,8,seqNo);			
		cptr += 7;
		j-=7;
		seqNo++;
		
	}
}

void TransmitCanPkt(enum enumCanId idetifier)
{
	void *ptr;
	unsigned char size = 0;
	switch((int)idetifier)
	{
	
		case LOCO_INFO_PKT:
			ptr = &stLocMsg;
			size = sizeof(LOCOMSG_t);
			sendCanPkts(ptr,size,idetifier);
			break;
		case LOCO_INFO_PKT_2:
			ptr = &stLocMsg;
			size = sizeof(LOCOMSG_t);
			sendCanPkts(ptr,size,idetifier);
			break;
		case STN_NMS_PKT:
			ptr = &stStnNmsMsg;
			size = sizeof(STN_NMS_MSG);
			sendCanPkts(ptr,size,idetifier);
			//printf("\nNMS PKT size =%d\n",size);
		break;
		case GPS_TIME_PKT:
			//printf("\tTransmitting CAN GPS_TIME_PKT");
			ptr = &stCanGpsInfo;
			size = sizeof(GPS_DATE_TIME_t);
			sendCanPkts(ptr,size,idetifier);
			break;
		case CM2_LPM_GPS_TIME_PKT:
		    ptr = &stCanGpsInfo;
			size = sizeof(GPS_DATE_TIME_t);
			sendCanPkts(ptr,size,idetifier);
			break;	
	  case CM1_CM2_STATUSINFO:
			ptr = &stCanCom1Com2_SwapStatusInfo;
			size = sizeof(stCAN_COM1_COM2_STATUSCHK_t);
			sendCanPkts(ptr,size,idetifier);
			break;
	case LPM_RADIO_MODEM_HEALTH:
			ptr = &RadioModemHealth;
			size = sizeof(RADIOMODEMHEALTH_t);
			sendCanPkts(ptr,size,idetifier);
			//printf("\nRadioModemHealth.ucRadioModemHealth:%d\n",RadioModemHealth.ucRadioModemHealth);
			break;

	case CM2_CM1_RADIO_FAIL :
			ptr = &stCanRadioModemFailStatusTx;
			size = sizeof(CAN_RADIOMODEM_FAIL_STATUS_t);
			//if(T1TC > 50)
			sendCanPkts(ptr,size,idetifier);
			printf("\nRM 2 fail.status sent to com1...\n");
			break;

	case CM1_CM2_RADIO_FAIL :
			ptr = &stCanRadioModemFailStatusTx;
			size = sizeof(CAN_RADIOMODEM_FAIL_STATUS_t);
			//if(T1TC > 50)
			sendCanPkts(ptr,size,idetifier);
			printf("\nRM 1 fail.status sent to com2...\n");
			break;
		
		default:
			break;
		
	}
	
}


unsigned char canDataReady()
{
	int i = 0;
	
	if(canRead.In == canRead.Out)
		return 0;
	
	
	/* for removing duplicates in the buffer */
	for(i = (canRead.Out+1);i<canRead.In;i++)
	{
		if(0 == memcmp(&canRead.CAN_msg[canRead.Out],&canRead.CAN_msg[canRead.In],sizeof(CAN_msg)))
		{
			memset(&canRead.CAN_msg[canRead.Out],0,sizeof(CAN_msg));
			
			canRead.Out++;
			
			break;
			
		}
	}
	
	return 1;
}

void readCanToStructs(void)
{
	unsigned char seqNo,i = 0,j = 0,index = 0,locIndex = 0;
	uint8_t *charPtr = 0;
	
	while(canDataReady())
	{
		CommWatchDogStrobe();
		index = canRead.CAN_msg[canRead.Out].canPort-1;
		
	
				
		switch(canRead.CAN_msg[canRead.Out].id)
		{
					
			case SELF_INFO_PKT:
					charPtr = (uint8_t *)&tempStSelfInfo[index];
					seqNo = canRead.CAN_msg[canRead.Out].data[0];
					if (seqNo==0)
					{
						memset(charPtr,0,sizeof(SELFINFO_t));
						canStatus[index][SELF_INFO_PKT].expSeqNo = 0;
					}
			
					if(seqNo != canStatus[index][SELF_INFO_PKT].expSeqNo)
					{
						memset(charPtr,0,sizeof(SELFINFO_t));
						canStatus[index][SELF_INFO_PKT].expSeqNo = 0;
						
						printf("SELF_INFO_PKT Seq No Mismatch  ");
						break;
					}
			
					charPtr += (7 * seqNo);
				
					for (i = 1; i < canRead.CAN_msg[canRead.Out].len; i++)
					{
						*charPtr = canRead.CAN_msg[canRead.Out].data[i];
						charPtr++;
						
					}
			
					
					if((((canStatus[index][SELF_INFO_PKT].expSeqNo) * 7) 
										+ (canRead.CAN_msg[canRead.Out].len - 1)) >= sizeof(SELFINFO_t))
					{
						
					memcpy(&stSelfInfo,&tempStSelfInfo[index],sizeof(SELFINFO_t));					

						
						canStatus[index][SELF_INFO_PKT].expSeqNo = 0;
						canStatus[index][SELF_INFO_PKT].invalid = 0;	
						#ifdef CANDEBUG
						printf("\nRecieved Self Info: ");
						printf("Stn Id:%d -- Sos: %d",stSelfInfo.stationId,stSelfInfo.ucSos);
						#endif
						
					}
					else
					{
						canStatus[index][SELF_INFO_PKT].invalid = 1;
						canStatus[index][SELF_INFO_PKT].expSeqNo++;
					}
				printf("\n Station self slot : %d\n",stSelfInfo.ucSelfTimeSlot);			
				break;

				case SIG_INFO_PKT:
 					charPtr = (uint8_t *)&tempSigInfo[index];
					seqNo = canRead.CAN_msg[canRead.Out].data[0];
					//printf("************SIG_INFO_PKT Received**************");
					if (seqNo==0)
					{
						memset(charPtr,0,sizeof(SIGINFO_t));
						canStatus[index][SIG_INFO_PKT].expSeqNo = 0;
					}
			
					if(seqNo != canStatus[index][SIG_INFO_PKT].expSeqNo)
					{
						memset(charPtr,0,sizeof(SIGINFO_t));
						canStatus[index][SIG_INFO_PKT].expSeqNo = 0;
						
						printf("Seq No Mismatch  SIG_INFO_PKT Pkt");
						break;
					}
			
					charPtr += (7 * seqNo);
				
					for (i = 1; i < canRead.CAN_msg[canRead.Out].len; i++)
					{
						*charPtr = canRead.CAN_msg[canRead.Out].data[i];
						charPtr++;
						
					}
				   //printf("\nexpSeqNo %d\t len : %d\n",canStatus[index][SIG_INFO_PKT].expSeqNo,canRead.CAN_msg[canRead.Out].len);
					
					if((((canStatus[index][SIG_INFO_PKT].expSeqNo) * 7) 
										+ (canRead.CAN_msg[canRead.Out].len - 1)) >= sizeof(SIGINFO_t))
					{
						locIndex= getLocoIndex(tempSigInfo[index].ulLocoId);

						//printf("\n Loco Id : %d\n",tempSigInfo[index].ulLocoId);

						if(MAX_NO_OF_LOCOS != locIndex)
						{
							memcpy(&siginfo[locIndex],&tempSigInfo[index],sizeof(SIGINFO_t));
//							ucretLocoIndex=0;
//							ucretLocoIndex = formStationPacket(stationPkt,ucretLocoIndex);
//							if(ucretLocoIndex > 0)
//							{
//								ucretLocoIndex = formStationPacket(stationPkt2,ucretLocoIndex);	
//							}	
							sigUpdateTime[locIndex] = SpoiGetSysTICs();
							//printf(" CurSig Asp:%d Next Sig Asp:%d",siginfo[locIndex].ucCurSigAspect,siginfo[locIndex].ucNextSigAspect);
							#ifdef CANDEBUG
							printf("\nRecieved Sig Info: Index:%d ",locIndex);
							printf("%ld ",siginfo[locIndex].ulLocoId);
							printf(" CurSig Asp:%d Next Sig Asp:%d",siginfo[locIndex].ucCurSigAspect,siginfo[locIndex].ucNextSigAspect);
							#endif
						}
						else
						{
							printf("Error No free slot for %ld",tempSigInfo[index].ulLocoId) ;
						}

						
						canStatus[index][SIG_INFO_PKT].expSeqNo = 0;
						canStatus[index][SIG_INFO_PKT].invalid = 0;		
			
					}
					else
					{
						canStatus[index][SIG_INFO_PKT].invalid = 1;
						canStatus[index][SIG_INFO_PKT].expSeqNo++;
					}			
				break;
					
				case TRN_LEN_PKT:	
					charPtr = (uint8_t *)&tempTrnLenInfo[index];
					seqNo = canRead.CAN_msg[canRead.Out].data[0];
					if (seqNo==0)
					{
						memset(charPtr,0,sizeof(TRNLEN_t));
						canStatus[index][TRN_LEN_PKT].expSeqNo = 0;
					}
			
					if(seqNo != canStatus[index][TRN_LEN_PKT].expSeqNo)
					{
						memset(charPtr,0,sizeof(TRNLEN_t));
						canStatus[index][TRN_LEN_PKT].expSeqNo = 0;
						
						printf("TRN_LEN_PKTSeq No Mismatch  ");
						break;
					}
			
					charPtr += (7 * seqNo);
				
					for (i = 1; i < canRead.CAN_msg[canRead.Out].len; i++)
					{
						*charPtr = canRead.CAN_msg[canRead.Out].data[i];
						charPtr++;
						
					}
			
					
					if((((canStatus[index][TRN_LEN_PKT].expSeqNo) * 7) 
										+ (canRead.CAN_msg[canRead.Out].len - 1)) >= sizeof(TRNLEN_t))
					{
						locIndex= getTrnLocoIndex(tempTrnLenInfo[index].ulLocoId);

						if(MAX_TRNLEN_LOCO != locIndex)
						{
							//memcpy(&trnLenInfo[locIndex],&tempTrnLenInfo[index],sizeof(TRNLEN_t));
							updateTrainLenStat(tempTrnLenInfo[index]);
//							ucretLocoIndex=0;
//						ucretLocoIndex = formStationPacket(stationPkt,ucretLocoIndex);
//							if(ucretLocoIndex > 0)
//							{
//								ucretLocoIndex = formStationPacket(stationPkt2,ucretLocoIndex);	
//							}						
							//printf("\nRecieved TRNLEN Info: Index:%d ",locIndex);
							//printf("%ld ",trnLenInfo[locIndex].ulLocoId);
							//printf(" Type:%d ",trnLenInfo[locIndex].ucType);
							//#endif

						}
						else
						{
							;
							//printf("Error No free TRN LEN slot for %ld",tempTrnLenInfo[index].ulLocoId) ;
						}

						
						canStatus[index][TRN_LEN_PKT].expSeqNo = 0;
						canStatus[index][TRN_LEN_PKT].invalid = 0;		
			
					}
					else
					{
						canStatus[index][TRN_LEN_PKT].invalid = 1;
						canStatus[index][TRN_LEN_PKT].expSeqNo++;
					}
					
				break;
					
				case LPM_STARTUP:
//					printf("RecievedLPM_STARTUP\n");
					syncTime = 1;
				break;
				
				case SIG_ASPECT:
					charPtr = (uint8_t *)&tempSigStatus[index];
					seqNo = canRead.CAN_msg[canRead.Out].data[0];
					if (seqNo==0)
					{
						memset(charPtr,0,sizeof(CanSigStatus));
						canStatus[index][SIG_ASPECT].expSeqNo = 0;
					}
			
					if(seqNo != canStatus[index][SIG_ASPECT].expSeqNo)
					{
						memset(charPtr,0,sizeof(CanSigStatus));
						canStatus[index][SIG_ASPECT].expSeqNo = 0;
						
						//printf("SIG_ASPECT Seq No Mismatch  ");
						break;
					}
			
					charPtr += (7 * seqNo);
				
					for (i = 1; i < canRead.CAN_msg[canRead.Out].len; i++)
					{
						*charPtr = canRead.CAN_msg[canRead.Out].data[i];
						charPtr++;
						
					}
			
					
					if((((canStatus[index][SIG_ASPECT].expSeqNo) * 7) 
										+ (canRead.CAN_msg[canRead.Out].len - 1)) >= sizeof(CanSigStatus))
					{
						
					memcpy(&SigStatus,&tempSigStatus[index],sizeof(CanSigStatus));					

						
						canStatus[index][SIG_ASPECT].expSeqNo = 0;
						canStatus[index][SIG_ASPECT].invalid = 0;	
						#ifdef CANDEBUG 
						printf("\nRecieved Signal States: ");
						printf("no Of signals:%d -- Sos: %d",SigStatus.ucNoOfSignal,SigStatus.ucCurSigAsp[3]);
						#endif
						vfnFormAndTransDataLogSigPkt();
						
					}
					else
					{
						canStatus[index][SIG_ASPECT].invalid = 1;
						canStatus[index][SIG_ASPECT].expSeqNo++;
					}			
				break;
        #if 0
				case HEXFILE_CRCREQ:
					charPtr = (uint8_t *)&tempstCanComCrcVal[index];
					seqNo = canRead.CAN_msg[canRead.Out].data[0];
					if (seqNo==0)
					{
						memset(charPtr,0,sizeof(stCAN_HEXFILECRCREQREC_t));
						canStatus[index][HEXFILE_CRCREQ].expSeqNo = 0;
					}
			
					if(seqNo != canStatus[index][HEXFILE_CRCREQ].expSeqNo)
					{
						memset(charPtr,0,sizeof(stCAN_HEXFILECRCREQREC_t));
						canStatus[index][HEXFILE_CRCREQ].expSeqNo = 0;
						
						printf("Seq No Mismatch  ");
						break;
					}
			
					charPtr += (7 * seqNo);
				
					for (i = 1; i < canRead.CAN_msg[canRead.Out].len; i++)
					{
						*charPtr = canRead.CAN_msg[canRead.Out].data[i];
						charPtr++;
						
					}
			
					
					if((((canStatus[index][HEXFILE_CRCREQ].expSeqNo) * 7) 
										+ (canRead.CAN_msg[canRead.Out].len - 1)) >= sizeof(stCAN_HEXFILECRCREQREC_t))
					{
						
					memcpy(&stCanHexCrcvalReqRec,&tempstCanComCrcVal[index],sizeof(stCAN_HEXFILECRCREQREC_t));					

						
						canStatus[index][HEXFILE_CRCREQ].expSeqNo = 0;
						canStatus[index][HEXFILE_CRCREQ].invalid = 0;	
//						#ifdef CANDEBUG 
//						printf("\nRecieved Signal States: ");
//						printf("no Of signals:%d -- Sos: %d",SigStatus.ucNoOfSignal,SigStatus.ucCurSigAsp[3]);
//						#endif
						//vfnFormAndTransDataLogSigPkt();
						
					}
					else
					{
						canStatus[index][HEXFILE_CRCREQ].invalid = 1;
						canStatus[index][HEXFILE_CRCREQ].expSeqNo++;
					}			
				break;	
				
			#endif	
				
				
				
				#if 0
				case TSR_PKT:
					charPtr = (uint8_t *)&tempLandMarkInfo[index];
					seqNo = canRead.CAN_msg[canRead.Out].data[0];
					if (seqNo==0)
					{
						memset(charPtr,0,sizeof(LAND_MARK_PKT_t));
						canStatus[index][TSR_PKT].expSeqNo = 0;
					}
			
					if(seqNo != canStatus[index][TSR_PKT].expSeqNo)
					{
						memset(charPtr,0,sizeof(LAND_MARK_PKT_t));
						canStatus[index][TSR_PKT].expSeqNo = 0;
						
						printf("Seq No Mismatch  ");
						break;
					}
			
					charPtr += (7 * seqNo);
				
					for (i = 1; i < canRead.CAN_msg[canRead.Out].len; i++)
					{
						*charPtr = canRead.CAN_msg[canRead.Out].data[i];
						charPtr++;
						
					}
			
					
					if((((canStatus[index][TSR_PKT].expSeqNo) * 7) 
										+ (canRead.CAN_msg[canRead.Out].len - 1)) >= sizeof(LAND_MARK_PKT_t))
					{
						locIndex= getTsrLocoIndex(tempLandMarkInfo[index].ulLocoId);

						if(MAX_LANDMRK_LOCO != locIndex)
						{
							memcpy(&landMarkInfo[locIndex],&tempTrnLenInfo[index],sizeof(LAND_MARK_PKT_t));
							formLandMarkInfoPkt(locIndex);					
							printf("\nRecieved LANDMARK Info: Index:%d ",locIndex);
							printf("%ld ",trnLenInfo[locIndex].ulLocoId);
							//printf(" Type:%d ",trnLenInfo[locIndex].ucType);

						}
						else
						{
							printf("Error No free LAND_MARK slot for %ld",tempTrnLenInfo[index].ulLocoId) ;
						}

						
						canStatus[index][TSR_PKT].expSeqNo = 0;
						canStatus[index][TSR_PKT].invalid = 0;		
			
					}
					else
					{
						canStatus[index][TSR_PKT].invalid = 1;
						canStatus[index][TSR_PKT].expSeqNo++;
					}			
				break;				
				#endif
					
					case CM1_CM2_STATUSINFO:
			          printf("CM1_CM2\n");
					charPtr = (uint8_t *)&stCanCom1Com2StatusInfo_SwapFillStruct;
					seqNo = canRead.CAN_msg[canRead.Out].data[0];
			
					if(seqNo != canStatus[index][CM1_CM2_STATUSINFO].expSeqNo)
					{
						memset(charPtr,0,sizeof(stCAN_COM1_COM2_STATUSCHK_t));
						canStatus[index][CM1_CM2_STATUSINFO].expSeqNo = 0;
						
						printf("\nSeq No Mismatch CM1_CM2_STATUSINFO");
						break;
					}
			
					charPtr += (7 * seqNo);
				
					for (i = 1; i < canRead.CAN_msg[canRead.Out].len; i++)
					{
						*charPtr = canRead.CAN_msg[canRead.Out].data[i];
						charPtr++;
						
					}
			
					
					if((((canStatus[index][CM1_CM2_STATUSINFO].expSeqNo) * 7) 
										+ (canRead.CAN_msg[canRead.Out].len - 1)) >= sizeof(stCAN_COM1_COM2_STATUSCHK_t))
					{
						
					memcpy(&stCanCom1Com2_SwapStatusInfo,&stCanCom1Com2StatusInfo_SwapFillStruct,sizeof(stCAN_COM1_COM2_STATUSCHK_t));					
														
						
						canStatus[index][CM1_CM2_STATUSINFO].expSeqNo = 0;
						canStatus[index][CM1_CM2_STATUSINFO].invalid = 0;
						
//						processTransmissionToModem();    //putting data on port
//						SpoiPause(TEN_MS);
//						vfnFireRadioPkt();							//actually transmitting data into air
						gucHealthFlag = 1;
						gCommHealthClock = SpoiGetSysTICs();
						#ifdef	CAN_DEBUG
						printf("\nRecieved CM1_CM2_STATUSINFO:");
						#endif	/*#ifdef	CAN_DEBUG*/

					}
					else
					{
						canStatus[index][CM1_CM2_STATUSINFO].invalid = 1;
						canStatus[index][CM1_CM2_STATUSINFO].expSeqNo++;
					}			
					break;
				 	case STATIC_SPEED_PROFILE_PKT:
					charPtr = (uint8_t *)&tempStaticProfileInfo[index];
					seqNo = canRead.CAN_msg[canRead.Out].data[0];
					
					if (seqNo==0)
					{
						memset(charPtr,0,sizeof(STATIC_PROFILE_INFO_t));
						canStatus[index][STATIC_SPEED_PROFILE_PKT].expSeqNo = 0;
					}
					if(seqNo != canStatus[index][STATIC_SPEED_PROFILE_PKT].expSeqNo)
					{
					    
						memset(charPtr,0,sizeof(STATIC_PROFILE_INFO_t));
						canStatus[index][STATIC_SPEED_PROFILE_PKT].expSeqNo = 0;
						
						//printf("Seq No Mismatch  STATIC_SPEED_PROFILE_PKT Pkt");
						break;
					}
			
					charPtr += (7 * seqNo);
				
					for (i = 1; i < canRead.CAN_msg[canRead.Out].len; i++)
					{
						*charPtr = canRead.CAN_msg[canRead.Out].data[i];
						charPtr++;
						
					}
			
					
					if((((canStatus[index][STATIC_SPEED_PROFILE_PKT].expSeqNo) * 7) 
										+ (canRead.CAN_msg[canRead.Out].len - 1)) >= sizeof(STATIC_PROFILE_INFO_t))
					{
						locIndex= getLocoIndex(tempSigInfo[index].ulLocoId);

						if(MAX_NO_OF_LOCOS != locIndex)
						{
							memcpy(&staticProfileInfo,&tempStaticProfileInfo[index],sizeof(STATIC_PROFILE_INFO_t));
							
							//printf("\n .......formStaticTrackProfilePkt......");
							formStaticTrackProfilePkt();
							//gucStaicTrackProfileTransmit = 1;
							
							//sigUpdateTime[locIndex] = SpoiGetSysTICs();
							#ifdef CANDEBUG
							printf("\nRecieved Sig Info: Index:%d ",locIndex);
							printf("%ld ",siginfo[locIndex].ulLocoId);
							printf(" CurSig Asp:%d Next Sig Asp:%d",siginfo[locIndex].ucCurSigAspect,siginfo[locIndex].ucNextSigAspect);
							#endif
						}
						else
						{
							printf("Error No free slot for %ld",tempSigInfo[index].ulLocoId) ;
						}

						
						canStatus[index][STATIC_SPEED_PROFILE_PKT].expSeqNo = 0;
						canStatus[index][STATIC_SPEED_PROFILE_PKT].invalid = 0;		
			
					}
					else
					{
						canStatus[index][STATIC_SPEED_PROFILE_PKT].invalid = 1;
						canStatus[index][STATIC_SPEED_PROFILE_PKT].expSeqNo++;
					}			
				break;
				case AUTHENTICATION_KEY_ID:
				//printf("\nin AUTHENTICATION_KEY_ID...\n ");
				
					charPtr = (uint8_t *)&tempAuthentication_KEY[index];
					seqNo = canRead.CAN_msg[canRead.Out].data[0];
					//printf("seqNo:%d\n",seqNo);
					if (seqNo==0)
					{
						memset(charPtr,0,sizeof(Authentication_KEY_t));
						canStatus[index][AUTHENTICATION_KEY_ID].expSeqNo = 0;
					}
					if(seqNo != canStatus[index][AUTHENTICATION_KEY_ID].expSeqNo)
					{
						memset(charPtr,0,sizeof(Authentication_KEY_t));
						canStatus[index][AUTHENTICATION_KEY_ID].expSeqNo = 0;
						printf("AUTHENTICATION_KEY_ID, Seq No Mismatch  ");
						break;
					}
					charPtr += (7 * seqNo);
					for (i = 1; i < canRead.CAN_msg[canRead.Out].len; i++)
					{
						*charPtr = canRead.CAN_msg[canRead.Out].data[i];
						charPtr++;
					}
					if((((canStatus[index][AUTHENTICATION_KEY_ID].expSeqNo) * 7) 
										+ (canRead.CAN_msg[canRead.Out].len - 1)) >= sizeof(Authentication_KEY_t))
					{
					memcpy(&Authentication_KEY,&tempAuthentication_KEY[index],sizeof(Authentication_KEY_t));					
						canStatus[index][AUTHENTICATION_KEY_ID].expSeqNo = 0;
						canStatus[index][AUTHENTICATION_KEY_ID].invalid = 0;
						//COM_KEY_REQ_FLAG = 1;	
						printf("\nRecieved key Info:\n ");
							//printf("\nMsgType:0x%x\n",Authentication_KEY.MsgType);
							//printf("SrcID:0x%x\n",Authentication_KEY.SrcID);
							//printf("DesID:0x%x\n",Authentication_KEY.DesID);
							//printf("NofKeySets:0x%x\n",Authentication_KEY.NofKeySets);
							printf("Authentication_KEY.KeySet_Vstart:");
							for(j =0; j < 4; j++)
								printf("0x%x ",Authentication_KEY.KeySet_Vstart[j]);
							printf("\n");
							printf("Authentication_KEY.KeySet_Vend:");
							for(j =0; j < 4; j++)
								printf("0x%x ",Authentication_KEY.KeySet_Vend[j]);
							//printf("\n");
//							printf("Authentication_KEY.KeySet[0]:");
//							for(j =0; j < 16; j++)
//								printf("0x%x ",Authentication_KEY.KeySet[0][j]);
//							printf("\n");
//							printf("Authentication_KEY.KeySet[1]:");
//							for(j =0; j < 16; j++)
//								printf("0x%x ",Authentication_KEY.KeySet[1][j]);
//							printf("\n");
					}
					else
					{
						canStatus[index][AUTHENTICATION_KEY_ID].invalid = 1;
						canStatus[index][AUTHENTICATION_KEY_ID].expSeqNo++;
					}
				break;



				case CM2_CM1_RADIO_FAIL:
				
				
					charPtr = (uint8_t *)&stCanRadioModemFailStatusRxFillStruct;
					seqNo = canRead.CAN_msg[canRead.Out].data[0];
					//printf("seqNo:%d\n",seqNo);
					if (seqNo==0)
					{
						memset(charPtr,0,sizeof(CAN_RADIOMODEM_FAIL_STATUS_t));
						canStatus[index][CM2_CM1_RADIO_FAIL].expSeqNo = 0;
					}
					if(seqNo != canStatus[index][CM2_CM1_RADIO_FAIL].expSeqNo)
					{
						memset(charPtr,0,sizeof(CAN_RADIOMODEM_FAIL_STATUS_t));
						canStatus[index][CM2_CM1_RADIO_FAIL].expSeqNo = 0;
						
						break;
					}
					charPtr += (7 * seqNo);
					for (i = 1; i < canRead.CAN_msg[canRead.Out].len; i++)
					{
						*charPtr = canRead.CAN_msg[canRead.Out].data[i];
						charPtr++;
					}
					if((((canStatus[index][CM2_CM1_RADIO_FAIL].expSeqNo) * 7) 
										+ (canRead.CAN_msg[canRead.Out].len - 1)) >= sizeof(CAN_RADIOMODEM_FAIL_STATUS_t))
					{
						memcpy(&stCanRadioModemFailStatusRx,&stCanRadioModemFailStatusRxFillStruct,sizeof(CAN_RADIOMODEM_FAIL_STATUS_t));					
						canStatus[index][CM2_CM1_RADIO_FAIL].expSeqNo = 0;

						printf("\nRadioFailStatus:%d\n",stCanRadioModemFailStatusRx.ucRadioFailStatus);
						//printf("\n*RadioFailStatus:%d\n",stCanRadioModemFailStatusRxFillStruct.ucRadioFailStatus);
							
					}
					else
					{
						canStatus[index][CM2_CM1_RADIO_FAIL].invalid = 1;
						canStatus[index][CM2_CM1_RADIO_FAIL].expSeqNo++;
					}
				break;
				


			case CM1_CM2_RADIO_FAIL:
					charPtr = (uint8_t *)&stCanRadioModemFailStatusRxFillStruct;
					seqNo = canRead.CAN_msg[canRead.Out].data[0];
					//printf("seqNo:%d\n",seqNo);
					if (seqNo==0)
					{
						memset(charPtr,0,sizeof(CAN_RADIOMODEM_FAIL_STATUS_t));
						canStatus[index][CM1_CM2_RADIO_FAIL].expSeqNo = 0;
					}
					if(seqNo != canStatus[index][CM1_CM2_RADIO_FAIL].expSeqNo)
					{
						memset(charPtr,0,sizeof(CAN_RADIOMODEM_FAIL_STATUS_t));
						canStatus[index][CM1_CM2_RADIO_FAIL].expSeqNo = 0;
						
						break;
					}
					charPtr += (7 * seqNo);
					for (i = 1; i < canRead.CAN_msg[canRead.Out].len; i++)
					{
						*charPtr = canRead.CAN_msg[canRead.Out].data[i];
						charPtr++;
					}
					if((((canStatus[index][CM1_CM2_RADIO_FAIL].expSeqNo) * 7) 
										+ (canRead.CAN_msg[canRead.Out].len - 1)) >= sizeof(CAN_RADIOMODEM_FAIL_STATUS_t))
					{
						memcpy(&stCanRadioModemFailStatusRx,&stCanRadioModemFailStatusRxFillStruct,sizeof(CAN_RADIOMODEM_FAIL_STATUS_t));					
						canStatus[index][CM1_CM2_RADIO_FAIL].expSeqNo = 0;

						printf("\nRadioFailStatus:%d\n",stCanRadioModemFailStatusRx.ucRadioFailStatus);
						//printf("\n*RadioFailStatus:%d\n",stCanRadioModemFailStatusRxFillStruct.ucRadioFailStatus);
							
					}
					else
					{
						canStatus[index][CM1_CM2_RADIO_FAIL].invalid = 1;
						canStatus[index][CM1_CM2_RADIO_FAIL].expSeqNo++;
					}
				break;
			
			


				default:
					break;
		}
		memset(&canRead.CAN_msg[canRead.Out],0,sizeof(CAN_msg));
		canRead.Out++;
		if(CANBUFFSIZE == canRead.Out)
			canRead.Out = 0;
			
	}
}


void * getCanData(enum enumCanId idetifier)
{
	#if 0
	if(1 ==	canStatus[0][idetifier].invalid)
		return 0;
	switch((int)idetifier)
	{
		case CANPKT1:
			return &cRecPkt1;


		
		case CANPKT2:
			return &cRecPkt2;			

	}
	#endif	
	return 0;

}




 
