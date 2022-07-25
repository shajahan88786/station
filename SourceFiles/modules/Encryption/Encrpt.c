#include "Header.h"

//unsigned short RS = 0x1234;
/*
unsigned char gucKA[16][16] = {0x2B7E151628AED2A6ABF7158809CF4F3C,
								0xA0FAFE1788542CB123A339392A6C7605,
								0xF2C295F27A96B9435935807A7359F67F,
								0x3D80477D4716FE3E1E237E446D7A883B,
								0xEF44A541A8525B7FB671253BDB0BAD00,
								0xD4D1C6F87C839D87CAF2B8BC11F915BC,
								0x6D88A37A110B3EFDDBF98641CA0093FD,
								0x4E54F70E5F5FC9F384A64FB24EA6DC4F,
								0xEAD27321B58DBAD2312BF5607F8D292F,
								0xAC7766F319FADC2128D12941575C006E,
								0xEF44A541A8525B7FB671253BDB0BAD00,
								0xD4D1C6F87C839D87CAF2B8BC11F915BC,
								0x6D88A37A110B3EFDDBF98641CA0093FD,
								0x4E54F70E5F5FC9F384A64FB24EA6DC4F,
								0xEAD27321B58DBAD2312BF5607F8D292F,
								0XD014F9A8C9EE2589E13F0CC8B6630CA6};   */

uint64_t gucKA[16][2] = {{0x2B7E151628AED2A6,0xABF7158809CF4F3C},
						 {0xA0FAFE1788542CB1,0x23A339392A6C7605},
						 {0xF2C295F27A96B943,0x5935807A7359F67F},
						 {0x3D80477D4716FE3E,0x1E237E446D7A883B},
						 {0xEF44A541A8525B7F,0xB671253BDB0BAD00},
						 {0xD4D1C6F87C839D87,0xCAF2B8BC11F915BC},
						 {0x6D88A37A110B3EFD,0xDBF98641CA0093FD},
						 {0x4E54F70E5F5FC9F3,0x84A64FB24EA6DC4F},
						 {0xEAD27321B58DBAD2,0x312BF5607F8D292F},
						 {0xAC7766F319FADC21,0x28D12941575C006E},
						 {0xEF44A541A8525B7F,0xB671253BDB0BAD00},
						 {0xD4D1C6F87C839D87,0xCAF2B8BC11F915BC},
						 {0x6D88A37A110B3EFD,0xDBF98641CA0093FD},
						 {0x4E54F70E5F5FC9F3,0x84A64FB24EA6DC4F},
						 {0xEAD27321B58DBAD2,0x312BF5607F8D292F},
						 {0XD014F9A8C9EE2589,0xE13F0CC8B6630CA6}};


static void BlockCopy(unsigned char* output, unsigned char* input)
{
  unsigned int i;
  for (i=0;i<KEYLEN;++i)
  {
    output[i] = input[i];
  }
}

static unsigned char getSBoxValue(unsigned char num)
{
  return sbox[num];
}

static void XorWithIv(unsigned char* buf)
{
  unsigned char i;
  for(i = 0; i < KEYLEN; ++i)
  {
    buf[i] ^= Iv[i];
  }
}

static void AddRoundKey(unsigned char round)
{
  unsigned char i,j;
  for(i=0;i<4;++i)
  {
    for(j = 0; j < 4; ++j)
    {
      (*state)[i][j] ^= RoundKey[round * Nb * 4 + i * Nb + j];
    }
  }
}

static void SubBytes(void)
{
  unsigned char i, j;
  for(i = 0; i < 4; ++i)
  {
    for(j = 0; j < 4; ++j)
    {
      (*state)[j][i] = getSBoxValue((*state)[j][i]);
    }
  }
}

static void ShiftRows(void)
{
  unsigned char temp;

  // Rotate first row 1 columns to left  
  temp           = (*state)[0][1];
  (*state)[0][1] = (*state)[1][1];
  (*state)[1][1] = (*state)[2][1];
  (*state)[2][1] = (*state)[3][1];
  (*state)[3][1] = temp;

  // Rotate second row 2 columns to left  
  temp           = (*state)[0][2];
  (*state)[0][2] = (*state)[2][2];
  (*state)[2][2] = temp;

  temp       = (*state)[1][2];
  (*state)[1][2] = (*state)[3][2];
  (*state)[3][2] = temp;

  // Rotate third row 3 columns to left
  temp       = (*state)[0][3];
  (*state)[0][3] = (*state)[3][3];
  (*state)[3][3] = (*state)[2][3];
  (*state)[2][3] = (*state)[1][3];
  (*state)[1][3] = temp;
}

static unsigned char xtime(unsigned char x)
{
  return ((x<<1) ^ (((x>>7) & 1) * 0x1b));
}

static void MixColumns(void)
{
  unsigned char i;
  unsigned char Tmp,Tm,t;
  for(i = 0; i < 4; ++i)
  {  
    t   = (*state)[i][0];
    Tmp = (*state)[i][0] ^ (*state)[i][1] ^ (*state)[i][2] ^ (*state)[i][3] ;
    Tm  = (*state)[i][0] ^ (*state)[i][1] ; Tm = xtime(Tm);  (*state)[i][0] ^= Tm ^ Tmp ;
    Tm  = (*state)[i][1] ^ (*state)[i][2] ; Tm = xtime(Tm);  (*state)[i][1] ^= Tm ^ Tmp ;
    Tm  = (*state)[i][2] ^ (*state)[i][3] ; Tm = xtime(Tm);  (*state)[i][2] ^= Tm ^ Tmp ;
    Tm  = (*state)[i][3] ^ t ;        Tm = xtime(Tm);  (*state)[i][3] ^= Tm ^ Tmp ;
  }
}

static void Cipher(void)
{
  unsigned char round = 0;

  // Add the First round key to the state before starting the rounds.
  AddRoundKey(0); 
  
  // There will be Nr rounds.
  // The first Nr-1 rounds are identical.
  // These Nr-1 rounds are executed in the loop below.
  for(round = 1; round < Nr; ++round)
  {
    SubBytes();
    ShiftRows();
    MixColumns();
    AddRoundKey(round);
  }
  
  // The last round is given below.
  // The MixColumns function is not here in the last round.
  SubBytes();
  ShiftRows();
  AddRoundKey(Nr);
}

static void KeyExpansion(void)
{
  unsigned int i, j, k;
  unsigned char tempa[4]; // Used for the column/row operations
  
  // The first round key is the key itself.
  for(i = 0; i < Nk; ++i)
  {
    RoundKey[(i * 4) + 0] = Key[(i * 4) + 0];
    RoundKey[(i * 4) + 1] = Key[(i * 4) + 1];
    RoundKey[(i * 4) + 2] = Key[(i * 4) + 2];
    RoundKey[(i * 4) + 3] = Key[(i * 4) + 3];
  }

  // All other round keys are found from the previous round keys.
  for(; (i < (Nb * (Nr + 1))); ++i)
  {
    for(j = 0; j < 4; ++j)
    {
      tempa[j]=RoundKey[(i-1) * 4 + j];
    }
    if (i % Nk == 0)
    {
      // This function rotates the 4 bytes in a word to the left once.
      // [a0,a1,a2,a3] becomes [a1,a2,a3,a0]

      // Function RotWord()
      
        k = tempa[0];
        tempa[0] = tempa[1];
        tempa[1] = tempa[2];
        tempa[2] = tempa[3];
        tempa[3] = k;
      

      // SubWord() is a function that takes a four-byte input word and 
      // applies the S-box to each of the four bytes to produce an output word.

      // Function Subword()
      
        tempa[0] = getSBoxValue(tempa[0]);
        tempa[1] = getSBoxValue(tempa[1]);
        tempa[2] = getSBoxValue(tempa[2]);
        tempa[3] = getSBoxValue(tempa[3]);
     
      tempa[0] =  tempa[0] ^ Rcon[i/Nk];
    }
    else if (Nk > 6 && i % Nk == 4)
    {
      // Function Subword()
     
        tempa[0] = getSBoxValue(tempa[0]);
        tempa[1] = getSBoxValue(tempa[1]);
        tempa[2] = getSBoxValue(tempa[2]);
        tempa[3] = getSBoxValue(tempa[3]);
     
    }
    RoundKey[i * 4 + 0] = RoundKey[(i - Nk) * 4 + 0] ^ tempa[0];
    RoundKey[i * 4 + 1] = RoundKey[(i - Nk) * 4 + 1] ^ tempa[1];
    RoundKey[i * 4 + 2] = RoundKey[(i - Nk) * 4 + 2] ^ tempa[2];
    RoundKey[i * 4 + 3] = RoundKey[(i - Nk) * 4 + 3] ^ tempa[3];
  }
}

void AES128_CBC_encrypt_buffer(unsigned char* output, unsigned char* input, unsigned int length, const unsigned char* key, const unsigned char* iv)
{
  unsigned int i;
  unsigned int remainders = length % KEYLEN; /* Remaining bytes in the last non-full block */

  BlockCopy(output, input);
  state = (state_t*)output;
 // Skip the key expansion if key is passed as 0
  if(0 != key)
  {
    Key = key;
    KeyExpansion();
  }


  if(iv != 0)
  {
    Iv = (unsigned char*)iv;
  }

  for(i = 0; i < length; i += KEYLEN)
  {
    XorWithIv(input);
    BlockCopy(output, input);
    state = (state_t*)output;
    Cipher();
    Iv = output;
    input += KEYLEN;
    output += KEYLEN;
  }

  if(remainders)
  {
    BlockCopy(output, input);
    memset(output + remainders, 0, KEYLEN - remainders); /* add 0-padding */
    state = (state_t*)output;
    Cipher();
  }
}
#if 0
void ComputeRandom16Byte(unsigned short RS, unsigned short RL, unsigned char *Dest)
{
	uint64_t R1 = 0, R2 = 0;
	unsigned int SL = 0, LS = 0;
	unsigned char i = 0, j = 0, k = 0;

/* R1 = (RS | RL) | (RS | RL) 			where ‘|’ means concatenation operator
   R2 = (RL | RS) | (RL | RS) 
   R	= (R1 | R2)
*/

	SL = RS;
	SL = ((SL << 16) | RL);
	
	LS = RL;
	LS = ((LS << 16) | RS);

	R1 = SL;
	R1 = ((R1 << 32) | SL);
	
	R2 = LS;
	R2 = ((R2 << 32) | LS);
	
	for(i=16,j=7; i>0; i--,j--)
	{
		if(0 == k)
			Dest[i-1] = ((R1 >> (j*8)) & 0xFF);
		else if(1 == k)
			Dest[i-1] = ((R2 >> (j*8)) & 0xFF);
		else { ; }
		
		if(0 == j)
		{
			j = 8;
			k = 1;
		}
	}
}
#endif

void ComputeRandom16Byte(unsigned short RS, unsigned short RL, unsigned char *R)
{
	unsigned char i = 0;

/* R1 = (RS | RL) | (RS | RL) 			where ‘|’ means concatenation operator
   R2 = (RL | RS) | (RL | RS) 
   R	= (R1 | R2)
*/
	
	for(i=0; i<8; i++)
	{
		if(i<4)
		{
			if(0 == (i%2))
			{
				R[2*i] = RS;
				R[(2*i)+1] = RS>>8;
			}
			else
			{
				R[2*i] = RL;
				R[(2*i)+1] = RL>>8;
			}
		}
		else
		{
			if(0 == (i%2))
			{
				R[2*i] = RL;
				R[(2*i)+1] = RL>>8;
			}
			else
			{
				R[2*i] = RS;
				R[(2*i)+1] = RS>>8;
			}
		}
	}
}


unsigned char ComputeAuthenticKeyIndex(unsigned long ulLocoID)
{
//	unsigned char ucnumdig = 0;
	unsigned int temp=0, RLoco=0;
	unsigned short  RStn=0;
//	unsigned int id =0, iddigcnt=0;
//	unsigned char i = 0;
	
	RStn = stSelfInfo.stationId;
	RLoco = ulLocoID;
	
	temp = ((RStn + RLoco)%16);
	
//	printf("-------- STNID %d LOCOID %d Ka index : %d -----------\n",RStn,RLoco,temp);
	
	return temp;
}

unsigned short int ComputeMAC_Code(unsigned char *pcMsg,unsigned char ucStartByte,
									unsigned char ucEndByte, unsigned short RL,
											unsigned long ulLocoID)
{
	unsigned char Ka[16] = {0,}, Ks[16] = {0,}, R[16] = {0,};
	unsigned char KaIndex = 0, i = 0,ucByte = ucStartByte;
	unsigned char InitVect[16] = {0, }, Ciphertxt[16] = {0, }, InputMsgBlock[16] = {0, };
	unsigned short MAC_CODE = 0;
	unsigned short RS = 0;

//	printf("\n\n\n*************************************************************\n");

	for(i = 0; i< MAX_NO_OF_LOCOS;	i++) 
		if(ulLocoID == siginfo[i].ulLocoId)
			break;
	RS = siginfo[i].usSTNRandomNmbr;
	ComputeRandom16Byte(RS, RL, R);
	KaIndex = ((stSelfInfo.stationId+ulLocoID)%2);
//	KaIndex = ComputeAuthenticKeyIndex(ulLocoID);

	//k=0;
//	for(i=0; i<2; i++)
//	{
//		for(j=0; j<8;j++)
//		{
//			Ka[k] = ((gucKA[KaIndex][i] >> ((7-j)*8)) & 0xFF);
//		 	k++;
//		}
//	}
		//printf("...KaIndex:%d....\n",KaIndex);
		for(i=0 ; i<16 ;i++)
		{
			Ka[i] = Authentication_KEY.KeySet[KaIndex][i];
			//printf("0x%2x ",Ka[i]);
		}
	printf("\n");
		
	AES128_CBC_encrypt_buffer(Ks, R, 16, Ka, InitVect);			// Ks = AES(Ka, R)

//	printf("\nRandom Numbers: RS = %x\t\t RL = %x\n",RS,RL);
//	printf("\nSession Key:");
//	for(i=0; i<16; i++)
//		printf(" %x",Ks[i]);
//	printf("\n");
	memset(InputMsgBlock,0,16);	

	i=0;
	if(0 != ucStartByte)
	{
		for(i=0; i<10; i++)
		{
			InputMsgBlock[i] = pcMsg[i];
		}
	}		
	ucByte = ucStartByte;

	while(ucByte <= ucEndByte)
	{
		CommWatchDogStrobe();
//		printf("\nucByte : %d\t\tucEndByte : %d\n",ucByte,ucEndByte); 

		memset(Ciphertxt,0,16);

	   	for(; i<16; i++)
		{
			if(ucByte <= ucEndByte)
			{
				InputMsgBlock[i] = pcMsg[ucByte];
				ucByte++;
			}
			else 
				InputMsgBlock[i] = 0;
		}

		AES128_CBC_encrypt_buffer(Ciphertxt,InputMsgBlock,16, Ks, InitVect);
   		BlockCopy(Ks, Ciphertxt);

//		printf("\nMessage Block :");
//		for(i=0; i<16; i++)
//			printf(" %x",InputMsgBlock[i]);
//		printf("\n");

//		printf("\nCipher Text :");
//		for(i=0; i<16; i++)
//			printf(" %x",Ciphertxt[i]);
//		printf("\n");
		
		memset(InputMsgBlock,0,16);	
		i=0;
	}

//	printf("\nFinal Cipher Text:");
//	for(i=0; i<16; i++)
//		printf(" %x",Ciphertxt[i]);	
//	printf("\n");

	MAC_CODE = GetCRC16(0,Ciphertxt, 16);

	printf("\t\tGenerated MAC_CODE : %x\n",MAC_CODE);
//	printf("\n*************************************************************\n\n");
	return MAC_CODE;
}

unsigned char CheckMAC(unsigned char *pcReadMsg, unsigned char iNrepBytes)
{
	unsigned short MAC_CODE = 0x0000, RL = 0x0000;
	unsigned long LocoID = 0;
	unsigned char i = 0;

	LocoID	= ExtractBits(4,17,&pcReadMsg[3]);
	printf("Loco Id : %d\n",LocoID);
	for(i=0; i<MAX_NO_OF_LOCOS; i++)
	{
//		printf("ulLocoId [%d] : %d\n",i,siginfo[i].ulLocoId);
		if(LocoID == siginfo[i].ulLocoId)
		{
			RL = siginfo[i].usLocoRandomNumbr;
			break;
		}		
	}
	if(i == MAX_NO_OF_LOCOS)
	{
		printf("\nLOCO INFO NOT AVAILABLE IN MAIN MODULE\n");
		return 0;
	}

	MAC_CODE = 	pcReadMsg[iNrepBytes-3];
	MAC_CODE = 	(((MAC_CODE << 8) & 0xFF00) | pcReadMsg[iNrepBytes-2]);

	printf("\nReceived MAC_CODE : %x",MAC_CODE);

	if(MAC_CODE == ComputeMAC_Code(pcReadMsg,0,iNrepBytes-4,RL,LocoID))
		return 1;
	else
		return 0;

}

