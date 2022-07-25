/******************************************************************************
* File Name: RxAndTx.c
*
* File Description: This file contains the routines to receive and transmit 
*                   data. 
*
* Modification History: Ver/Rev      CR        ATR         Remarks
*
* Created by:   PM             23/10/2009
*
* Modified by:  
*
* Compiler/Assembler/Linker: Armcc.Exe V3.1.0.919, Armasm.Exe V3.1.0.919,
*                               ArmLink.Exe V3.1.0.919
*
* Version/Revision: 0.1
*
******************************************************************************/

#include "Header.h"
#undef TXDEBUG
#undef RXDEBUG

/*CRC16 Table*/
const unsigned short int Kus_Crc16Table[16] = {0x0000, 0xCC01, 0xD801, 0x1400,
                                               0xF001, 0x3C00, 0x2800, 0xE401,
	                                           0xA001, 0x6C00, 0x7800, 0xB401, 
                                               0x5000, 0x9C01, 0x8801, 0x4400};

/******************************************************************************
*	File Header    :          RxAndTx.c
*	Procedure Name :          CommReadAndFormMessage
*	Package Name   :          Communication Module
*	Date of creation :        23/10/2009
*	Created by     :          PM
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :   This function Receive packets on Serial port and form 
*					  messages The messages are validated using CRC algorithm.
*					  '$' is considered as the sycronizing byte and END_OF_
*					  MESSAGE represents EOM. This function returs VALID if a 
*					  valid message is recieved else returs as INVALID.
*
*	Allocation	  :	  NIL    
*
*	DR            :   NIL      
*
*	Interfaces	  :		Comm_ComDataReady()
*   Calls               Comm_ComGetByte() 
*                       CommCheckCRC()	
*	                 
*
*	Called by     :    Comm_processTSM()
*                      Comm_processHHU()
*                      Comm_StartUpMCMs()
*                      Comm_processHHUBT()
*                      CommProcessMaster()    
*
*	Input variables  :    
*	Local variables  :     Type                   Name		      comments
*						 
*				  unsigned short int		 us_Port          Port number           
*				unsigned char 			 puc_ReadMsg      Buffer to be filled
*				unsigned short int		 us_MaxSize       Max size of buffer
*
*						
*	Global variables :     Type                   Name		comments
*								
*							--                    None         --
*
*	Output variables :	  
*	Local variables  :     Type                   Name		        comments
*				   
*				unsigned short int		 us_ReturnBytes     No of bytes read   		
*						
*
*	Global variables :     Type                   Name		        comments
*
*						unsigned char  		 puc_ReadMsg        Message Read
*
*	Reference	     :    SRS	  SDR	 SWRS	 DR 
*
*	Derived Requirements  :
*
*	Program Design Language        :        
*						
*	Step1:Check data availability on the port
*	Step2:Read the data from the port and store it in a buffer.
*	Step3:If Start of Message is recieved then store it in a buffer.
*	Step4:If end of message is received remove the CRC data from the message and 
*		compute the CRC for remaining message and compare both CRC's if both 
*		are equal then return number of bytes in a message else ZERO.
*	Step5:If it is not an end of message then store the data in the buffer.
*
******************************************************************************/

unsigned short int CommReadAndFormMessage(unsigned short int us_Port,
                    unsigned char *puc_ReadMsg,unsigned short int us_MaxSize)
{
    static unsigned char suc_RcvStatus = ONE;
    static unsigned char suc_RByte = ZERO;
    static unsigned short int i = ZERO;
    static unsigned short int sus_CRC = ZERO;
    unsigned short int us_ReturnBytes = ZERO;

    /* If data available on port read and store data */

    while(Comm_ComDataReady(us_Port)) 
    {
		CommWatchDogStrobe();
        suc_RByte = Comm_ComGetByte(us_Port); 
		//printf(" %c ",suc_RByte);
        switch(suc_RcvStatus)
        {
            case ONE: /* Receive Start of Message */
                if(START_OF_MESSAGE == suc_RByte)
                {
                    puc_ReadMsg[ZERO] = suc_RByte;
                    i = ONE;
                    suc_RcvStatus = TWO;
                }
            break;
            case TWO: /* Receive body of message or end of message */
                switch(suc_RByte)
                {
                    case END_OF_MESSAGE:
                        sus_CRC = i-TWO;
                        us_ReturnBytes = i;
                        i = ZERO;
                        suc_RcvStatus = ONE;
						if(us_ReturnBytes <= FOUR)
						{
						 	return ZERO;
						}
                        if (CommCheckCRC(puc_ReadMsg,sus_CRC))
                        {
							//printf("CRC OK\n");
                            return us_ReturnBytes;
                        }
                        else
                        {
							//printf("CRC NOK\n");
                            return ZERO;
                        }

                    case START_OF_MESSAGE:
                        puc_ReadMsg[ZERO] = suc_RByte;
                        i = ONE;
                        suc_RcvStatus = TWO;
                    break;

                    case DLE:
                        suc_RcvStatus = THREE;
                    break;

                    default:
                        puc_ReadMsg[i] = suc_RByte;
                        i++;
                    break;
                }
            break;

            case THREE: 
                
                /* Receive body of message specially if $ or & are part of body
                 *  i.e characters escaped with DLE */

                if(START_OF_MESSAGE == suc_RByte || END_OF_MESSAGE == suc_RByte
                                                || DLE == suc_RByte)
                {
                    puc_ReadMsg[i] = suc_RByte;
                    i++;
                }
                suc_RcvStatus = TWO;
            break;

            default:
            break;
        }    /* End of switch*/
            
        /* If receiving invalid message, ZERO message buffer */

        if( i >= us_MaxSize)
        {
            suc_RcvStatus = ONE;
            i = ZERO;
        }
    }	    /* End of While data ready */

    return ZERO;
}	/* End of CommReadAndFormMessage */

/******************************************************************************
*	File Header               RxAndTx.c
*	Procedure Name :          Comm_ComDataReady
*	Package Name   :          Communication Module
*	Date of creation :        23/10/2009 
*	Created by     :           PM
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :     This function checks whether data is available on the 
*						COM port or Not.
*
*	Allocation	  :	   	NIL
*
*	DR            :     NIL    
*	 
*	Interfaces	  :	    None
*	Calls                 
*
*	Called by     :     CommReadAndFormMessage()
*
*	Input variables  :    
*	Local variables  :     Type                     Name		      comments
*							
*						unsigned short int		us_DevNo          Port Number 
*						
*	Global variables :     Type                     Name			  comments
*
*					Buff_t					st_ReadBuf        For In, Out Index	
*
*
*	Output variables :	  
*	Local variables  :     Type                     Name		      comments
*
*				unsigned short int	   us_Comm_IretVal    '1' if data available
*														  '0' if not available
*						
*	Global variables :     Type                     Name		      comments
*	  
*							--                      None                --
*
*	Reference	     :      SRS	  SDR	 SWRS	 DR
*
*	Derived Requirements  :
*
*	Program Design Language        :         
*
*	Step1:Check the availability of data on port if data is available return ONE
*		  else ZERO.
*	 
**********************************************************************************/

unsigned short int Comm_ComDataReady(unsigned short int us_DevNo)
{
	unsigned short int us_Comm_IretVal = ZERO;

	if (st_ReadBuf[us_DevNo].ui_In != st_ReadBuf[us_DevNo].ui_Out)
	{
		us_Comm_IretVal = ONE;
	}
	return us_Comm_IretVal;
}

/******************************************************************************
*	File Header           RxAndTx.c
*	Procedure Name :      Comm_ComGetByte    
*	Package Name   :      Communication Module  
*	Date of creation :     23/10/2009   
*	Created by     :        PM  
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      : This function read the data that available on the COM port.
*
*	Allocation	  :	   NIL  	   
*
*	DR            :    NIL     
*
*	Interfaces	  :		 None	
*	Calls                 
*
*	Called by     :      CommReadAndFormMessage()  
*
*	Input variables  :    
*	Local variables  :     Type                    Name		      comments
*						  
*						 unsigned short int	   us_DevNo       Port Number  
*
*	Global variables :     Type                    Name		      comments
*							
*					Buff_t 	               st_ReadBuf     Data from buffer 
*
*
*	Output variables :	  
*	Local variables  :     Type                    Name		      comments
*						  
*						unsigned char		   uc_Data        Received Data
*
*	Global variables :     Type                    Name		      comments
*
*							--                     None              --
*
*	Reference	     :     SRS	  SDR	 SWRS	 DR
*
*	Derived Requirements  :
*
*	Program Design Language        :         
*
*	Step1:Read the data from the port and save it in varaibale.
*	Step2:If write index is greater than buffer size reset both the read index 
*							   and write index to ZERO.
*
******************************************************************************/

unsigned char Comm_ComGetByte(unsigned short int us_DevNo)
{
    unsigned char uc_Data = ZERO;

    uc_Data = st_ReadBuf[us_DevNo].uc_Buf[st_ReadBuf[us_DevNo].ui_Out++];

    if (st_ReadBuf[us_DevNo].ui_Out >= (RBUF_SIZE))
    {
        st_ReadBuf[us_DevNo].ui_Out = ZERO;
        //st_ReadBuf[us_DevNo].ui_In = ZERO;
        /*memset(&st_ReadBuf[us_DevNo].uc_Buf,ZERO,
                                    sizeof(st_ReadBuf[us_DevNo].uc_Buf));*/
    }

    return uc_Data;
}

/******************************************************************************
*	File Header            RxAndTx.c
*	Procedure Name :       CommTransmitMessage
*	Package Name   :       Communication Module 
*	Date of creation :     23/10/2009   
*	Created by     :        PM  
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :  This function transmits message byte by byte to com port.
*
*	Allocation	  :	  NIL 	    
*
*	DR            :   NIL      
*
*	Interfaces	  :		  Comm_ComSendByte()	
*	Calls                 
*
*	Called by     :       Comm_ProcessSnDDateAndTimeRequestToTSM()
*						  CommSendEventACKTOSDM()
*                         Comm_ProcessSnDDateAndTimeToHHU()
*                         Comm_ProcessAckForLogicConfigDataToHHU()
*                         Comm_SendSDMIDToHHU()
*
*	Input variables  :    
*	Local variables  :     Type                     Name		       comments
*						
*						unsigned short int		s_Port              Port Number     
*			      unsigned char 			   puc_Message  Message to transmit
*				unsigned short int		us_MaxTansmitBytes    Size of data
*				unsigned char			    uc_TypeOfComm      Used for setting
*														randomization technique
*
*	Global variables :     Type                     Name		       comments
*							
*							--	                    None                    --                
*
*	Output variables :	  
*	Local variables  :     Type                     Name		       comments
*	 
*							--	                    None                    --                
*
*						
*	Global variables :     Type                     Name		       comments
*
*							--	                    None                    --  
*
*	Reference	     :     SRS	  SDR	 SWRS	 DR
*
*	Derived Requirements  :
*
*	Program Design Language        :      
*
*	Step1:Transmit message from required port.
*	Step2:If STARTOFMESSAGE or END OF MESSAGE or DLE are available in message 
*		  means transmit DLE from the port.
*
******************************************************************************/

void CommTransmitMessage(unsigned short int us_Port,
                         unsigned char *puc_Message,
                         unsigned short int us_MaxTansmitBytes)
{
   unsigned short int i = ZERO;

    /* Transmit the packet based on the randomization number 
     */
    for(i = ZERO; i <= us_MaxTansmitBytes; i++)
    { 
        if (  (ZERO != i)
            &&(START_OF_MESSAGE == puc_Message[i]))
        {
            Comm_ComSendByte(us_Port,DLE); 
        }
        if (  (i >= ONE) 
                && (i < us_MaxTansmitBytes) 
                && (DLE == puc_Message[i] )
                )
        {
            Comm_ComSendByte(us_Port,DLE); 
        }
        if (  (END_OF_MESSAGE == puc_Message[i]) 
                && (i != us_MaxTansmitBytes)
                )
        {
           Comm_ComSendByte(us_Port,DLE);
        }
     
        Comm_ComSendByte(us_Port, puc_Message[i]); 
    }



    return;
}
	/* End of CommTransmitMessage */

/******************************************************************************
*	File Header              RxAndTx.c
*	Procedure Name :         Comm_ComSendByte   
*	Package Name   :         Communication Module   
*	Date of creation :       23/10/2009   
*	Created by     :         PM  
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :       This function is used to send data to the COM port
*
*	Allocation	  :	   	  NIL 
*
*	DR            :       NIL  
*
*	Interfaces	  :		  None	
*	Calls                 
*
*	Called by     :       CommTransmitMessage() 
*
*	Input variables  :    
*	Local variables  :     Type                   Name		      comments
*				
*						  unsigned short int 	  us_UartNum      Port Number
*						  unsigned char           uc_Data         Data to send
*
*	Global variables :     Type                   Name		      comments
*							
*							--                    None	            --
*
*	Output variables :	  
*	Local variables  :     Type                   Name		      comments
*					 
*							--                    None	            --
*
*	Global variables :     Type                   Name		      comments
*
*							--                    None	            --
*
*	Reference	     :     SRS	  SDR	 SWRS	 DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*	Step1:If transmit holding register is empty then keep the data in 
*         THR register
*
******************************************************************************/

void Comm_ComSendByte(unsigned short int us_UartNum, 
                                unsigned char uc_Data)
{
    if (UART0 == us_UartNum)
    {
        while (!(U0LSR & TRANSMITBIT));
        //{
        U0THR = uc_Data;
        //}
    }
    if (UART1 == us_UartNum)
    {
        while (!(U1LSR & TRANSMITBIT));
        //{
        U1THR = uc_Data;
        //}
    }
    if (UART2 == us_UartNum)
    {
        while (!(U2LSR & TRANSMITBIT));
        //{
        U2THR = uc_Data;
        //}
    }
    if (UART3 == us_UartNum)
    {
        while (!(U3LSR & TRANSMITBIT));
        //{
        U3THR = uc_Data;
        //}
			//printf(" %x|",uc_Data);
    }

    return;
}

/******************************************************************************
*	File Header             RxAndTx.c
*	Procedure Name :        CommComputeCRC
*	Package Name   :        Communication Module
*	Date of creation :      23/10/2009 
*	Created by     :         PM  
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :      This function adds crc value to the message.
*
*	Allocation	  :	   	 NIL  
*
*	DR            :      NIL   
*
*	Interfaces	  :		 CommGetCRC16()	
*	Calls                 
*
*	Called by     :      Cmgt_WriteConfig()
*						 Cmgt_ReadAndValidateConfig()  
*
*	Input variables  :    
*	Local variables  :     Type                    Name		    comments
*					
*						   unsigned char		   puc_Msg      Message
*						   unsigned short int	   us_Count     Count
*
*	Global variables :     Type                    Name		    comments
*							
*							--	                   None            --
*
*	Output variables :	  
*	Local variables  :     Type                    Name		    comments
*
*				  unsigned short int	   sus_RetVal   Computed CRC Value 
*						
*	Global variables :     Type                    Name		    comments
*
*							--	                   None            --
*
*	Reference	     :     SRS	  SDR	 SWRS	 DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*	Step1:Compute the CRC for the given message and append it to that message.
*
******************************************************************************/

unsigned short int CommComputeCRC(unsigned char *puc_Msg,
                                    unsigned short int us_Count)
{
    static unsigned short int sus_Crc = ZERO;
    static unsigned short int sus_RetVal = ZERO;

    sus_Crc = CommGetCRC16( ZERO, puc_Msg, us_Count);
    sus_RetVal = sus_Crc;
    puc_Msg[us_Count+ONE] = (unsigned char) (sus_Crc & HEX_FF);
    sus_Crc = (unsigned short int) (sus_Crc >> EIGHT);
    puc_Msg[us_Count] = (unsigned char) (sus_Crc & HEX_FF);

    return sus_RetVal;
}	/* End of CommComputeCRC */

/******************************************************************************
*	File Header            RxAndTx.c
*	Procedure Name :       CommCheckCRC
*	Package Name   :       Communication Module 
*	Date of creation :      23/10/2009   
*	Created by     :       PM   
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :   This function retrives the crc part of the message wich
*					  is passed as parameter, And caluculates crc value of
*					  remaining message using ComputeCRC function, Checks that
*					  the two crcs are equal or not
*
*	Allocation	  :	  NIL 	    
*
*	DR            :   NIL      
*
*	Interfaces	  :			CommGetCRC16()
*	Calls                 
*
*	Called by     :         CommReadAndFormMessage()
*
*	Input variables  :    
*	Local variables  :     Type                   Name		         comments
*
*						   unsigned char		  puc_Msg            Message
*						   unsigned short int	  us_Count           Count
*
*						
*	Global variables :     Type                   Name		         comments
*
*							--                    None                  -- 
*								
*
*	Output variables :	  
*	Local variables  :     Type                   Name		         comments
*
*				unsigned short int 	  us_RetVal          Status of Comparision
*
*						
*	Global variables :     Type                   Name		         comments
*
*							--                    None                  -- 
*
*	Reference	     :     SRS	  SDR	 SWRS	 DR
*
*	Derived Requirements  :
*
*	Program Design Language        :        
*
*	Step1:Compute the CRC for the given message and compare the computed CRC 
*		 with the CRC in the given message if both are equal then return ONE.                     
*
******************************************************************************/

unsigned short int CommCheckCRC(unsigned char *puc_Msg,
                                        unsigned short int us_Count)
{
    static unsigned short int sus_Crc,sus_CalCrc;
    unsigned short int us_RetVal = ZERO;

    sus_Crc = CommGetCRC16( ZERO, puc_Msg,us_Count);
    sus_CalCrc = ZERO;
    sus_CalCrc = (unsigned short int ) (puc_Msg[us_Count] & HEX_FF);
    sus_CalCrc = (unsigned short int ) (sus_CalCrc << EIGHT);
    sus_CalCrc |= puc_Msg[us_Count + ONE] & HEX_FF;

    if(sus_CalCrc == sus_Crc)
    {
        us_RetVal = ONE;
    }

    return us_RetVal;
}

/******************************************************************************
*	File Header            RxAndTx.c
*	Procedure Name :      CommGetCRC16    
*	Package Name   :      Communication Module   
*	Date of creation :      23/10/2009  
*	Created by     :       PM   
*
*	Modification history
*	+-------------------------------------------------------------------------+
*	|  Revision   |  SPR   |   ATR    |  Date      |     Remarks              |
*	|-------------|-------------------|------------|--------------------------|
*	|     01      |        |          | 23/10/2009 |      Initial Version     |
*	+-------------------------------------------------------------------------+
*
*	Abstract      :  This function caluculates cyclic redudency check(CRC) of 
*					 a given Message.
*
*	Allocation	  :	  NIL 	   
*
*	DR            :   NIL      
*
*	Interfaces	  :		  None	
*	Calls                 
*
*	Called by     :       CommComputeCRC() 
*						  CommCheckCRC() 
*
*	Input variables  :    
*	Local variables  :     Type                   Name		           comments
*
*					unsigned short int	  us_Start             Start
*					unsigned char 		  puc_Ptr              Message Pointer
*				  unsigned short int	  us_Num			   Size of Message
*
*	Global variables :     Type                   Name		           comments
*
*							--	                  None                    --
*
*	Output variables :	  
*	Local variables  :     Type                   Name		           comments
*
*						   unsigned short int     us_Crc      	       Get CRC
*
*						
*	Global variables :     Type                   Name		           comments
*
*							--	                  None                    --
*
*	Reference	     :     SRS	  SDR	 SWRS	 DR
*
*	Derived Requirements  :
*
*	Program Design Language        :       
*
*	 Step1:Compute the CRC for a given message using CRC16 look up table.
*
******************************************************************************/

unsigned short int CommGetCRC16(unsigned short int us_Start,
                            unsigned char *puc_Ptr, unsigned short int us_Num)
{
    unsigned short int us_Crc =  us_Start;
    unsigned short int us_r = ZERO;

    /* while there is more data to process */
    while (us_Num-- > ZERO)
    {
        /* compute checksum of lower four bits of *pcPtr */
        us_r = Kus_Crc16Table[us_Crc & HEX_F];
        us_Crc = (unsigned short int) ((us_Crc >> FOUR) & HEX_FFF);
        us_Crc = (unsigned short int) 
                        (us_Crc ^ us_r ^ Kus_Crc16Table[*puc_Ptr & HEX_F]);

        /* now compute checksum of upper four bits of *pcPtr */
        us_r = Kus_Crc16Table[us_Crc & HEX_F];
        us_Crc =(unsigned short int) ((us_Crc >> FOUR) & HEX_FFF);
        us_Crc =(unsigned short int) 
                (us_Crc ^ us_r ^ Kus_Crc16Table[(*puc_Ptr >> FOUR) & HEX_F]);

        /* next... */
        puc_Ptr++;
    }
    return(us_Crc);
}	/* End of CommGetCRC16 */




/*End Of File*/
extern unsigned char locoPresentFlag  ;
//extern LOCO_NMS_MSG stLocoNmsMsg;
extern STN_NMS_MSG stStnNmsMsg;


void TransmitMessage_NoDle(short int iPort, unsigned char *pszMessage,short int iTBytes)
{
    short int i = 0;

	#ifdef TXDEBUG
	printf("\nTx: A5 C3:%d",iTBytes);
	#endif

//	if( 1 == ( char )ExtractBits(0, 4, &pszMessage[0]))	
	//if( 1 == (pszMessage[0] >> 4))	
	//	stStnNmsMsg.Paketlength =	iTBytes;
//	else
	//	stStnNmsMsg.Paketlength  = 0;


	Comm_ComSendByte(iPort, 0xFF);
	Comm_ComSendByte(iPort, 0xFF);	
	
	Comm_ComSendByte(iPort, SOP1);
	Comm_ComSendByte(iPort, SOP2);

	stStnNmsMsg.Paketlength =	iTBytes;
  	
	for(i = 0; i <= iTBytes; i++)
	{
		Comm_ComSendByte(iPort, pszMessage[i]);
		//printf(" %x.. |",pszMessage[i]);
		stStnNmsMsg.TxStnMessage[i] =pszMessage[i];	
	}

}
