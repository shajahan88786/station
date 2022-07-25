
#ifndef __CRC_H__
#define __CRC_H__


unsigned short int GetCRC16 (short int,unsigned char *, short int);
unsigned short int ComputeCRC(unsigned char *, short int);
short int CheckCRC(unsigned char *, short int);
#endif
