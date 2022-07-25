

#ifndef __CHECKSUM_H__
#define __CHECKSUM_H__


short int CheckCS(unsigned char *pcMsg,short int iCount);
unsigned char Get_CS (int iStart, unsigned char *pcPtr, int iNum);

short int CheckIntegrity(unsigned char *pMsg, short int iLoc, short int iWhich);

#endif /*#ifndef __CHECKSUM_H__*/

