
#include "Header.h"



short int CheckIntegrity(unsigned char *pMsg, short int iLoc, short int iWhich)
{

	
	if (CRCHK == iWhich)
	{
		return(CheckCRC(pMsg, iLoc));
	}
	else if (CHKSUM == iWhich)
	{
		return(CheckCS(pMsg, iLoc));
	}
	else
	{
		return 0;
	}

}


short int CheckCS(unsigned char *pcMsg,short int iCount)
{
	static unsigned char uiCs,k = 0;

	uiCs = Get_CS( 0, pcMsg,iCount);

	k = ( unsigned char ) pcMsg[iCount];
	
	if( k == uiCs ) 	return 1;
	
	return 0;
}

unsigned char Get_CS (int iStart, unsigned char *pcPtr, int iNum)
{
	long lCS = (long) iStart;

	/* while there is more data to process */
	while (iNum-- > 0)
	{
		lCS = lCS + (*pcPtr);
		pcPtr++;
	}

	lCS = lCS % 256;
	return((unsigned char)lCS);
}


