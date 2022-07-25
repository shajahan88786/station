#include "Header.h"

const unsigned short int ulCrc16Table[16] = {0x0000, 0xCC01, 0xD801, 0x1400,
											 0xF001, 0x3C00, 0x2800, 0xE401,
											 0xA001, 0x6C00, 0x7800, 0xB401, 
											 0x5000, 0x9C01, 0x8801, 0x4400 };



unsigned short int GetCRC16 (short int iStart,unsigned char *pcPtr, short int iNum)
{
    unsigned short int uiCrc = (unsigned short int ) iStart;
    short int r;

    /* while there is more data to process */
	while (iNum-- > 0)
    {
	/* compute checksum of lower four bits of *pcPtr */
	r = ulCrc16Table[uiCrc & 0xF];
	uiCrc = (unsigned short int) ((uiCrc >> 4) & 0x0FFF);
	uiCrc = (unsigned short int) (uiCrc ^ r ^ ulCrc16Table[*pcPtr & 0xF]);

	/* now compute checksum of upper four bits of *pcPtr */
	r = ulCrc16Table[uiCrc & 0xF];
	uiCrc =(unsigned short int) ((uiCrc >> 4) & 0x0FFF);
	uiCrc =(unsigned short int) (uiCrc ^ r ^ ulCrc16Table[(*pcPtr >> 4) & 0xF]);

	/* next... */
	pcPtr++;
    }
    return(uiCrc);
}



unsigned short int ComputeCRC(unsigned char *pcMsg, short int iCount)
{
    static unsigned short int uiCrc,k;
	uiCrc = GetCRC16( 0, pcMsg, iCount);
    k=uiCrc;
    pcMsg[iCount+1] = (char) (uiCrc & 0x00ff);
    uiCrc =(unsigned short int) (uiCrc >> 8);
    pcMsg[iCount] = (char) (uiCrc & 0x00ff);
    return k;
}



short int CheckCRC(unsigned char *pcMsg,short int iCount)
{
    static unsigned short int uiCrc,k = 0;
	short int retVal = 0;

	uiCrc = GetCRC16( 0, pcMsg,iCount);
    k = (unsigned short int ) (pcMsg[iCount] & 0xff);
    k = (unsigned short int ) (k<<8);
    k |= pcMsg[iCount+1] & 0xff;

	if(k == uiCrc)
	{
		retVal = 1;
	}
	printf("\nCalculated CRC : %x\n",uiCrc);
	printf("\nExtracted CRC : %x\n",k);
    return retVal;
}


