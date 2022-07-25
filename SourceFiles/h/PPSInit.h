#ifndef PPSInit_H
#define PPSInit_H

#define EINT0		0x00000001
#define EINT1		0x00000002
#define EINT2		0x00000004
#define EINT3		0x00000008

#define EINT0_EDGE	0x00000001
#define EINT1_EDGE	0x00000002
#define EINT2_EDGE	0x00000004
#define EINT3_EDGE	0x00000008

#define EINT0_RISING	0x00000001
#define EINT1_RISING	0x00000002
#define EINT2_RISING	0x00000004
#define EINT3_RISING	0x00000008

#define EINT0_PINSEL		0x00100000	/*21 and 20 Pins are setting to 0x01*/
#define EINT1_PINSEL		0x00400000	/*23 and 22 Pins are setting to 0x01*/
#define EINT2_PINSEL		0x01000000	/*25 and 24 Pins are setting to 0x01*/
#define EINT3_PINSEL		0x04000000	/*27 and 26 Pins are setting to 0x01*/

#define VIC_EINT0_BIT14_DISABLE	0x00004000
#define VIC_EINT1_BIT15_DISABLE	0x00008000
#define VIC_EINT2_BIT16_DISABLE	0x00010000
#define VIC_EINT3_BIT17_DISABLE	0x00020000

#define VIC_EINT0_BIT14_ENABLE	0x00004000
#define VIC_EINT1_BIT15_ENABLE	0x00008000
#define VIC_EINT2_BIT16_ENABLE	0x00010000
#define VIC_EINT3_BIT17_ENABLE	0x00020000


void EINTInit(void);

//void EINT3_Handler (void) __irq ;
void EINT1_Handler (void) __irq ; 
void EINT2_Handler (void) __irq ;
#endif /* PPSInit_H */

