#ifndef __INITTCAS_H_
#define __INITTCAS_H_


#define	VIC_INTERRUPT_PRIORITY_ZERO		0x00000000
#define	VIC_INTERRUPT_PRIORITY_ONE		0x00000001
#define	VIC_INTERRUPT_PRIORITY_TWO		0x00000002
#define	VIC_INTERRUPT_PRIORITY_THREE	0x00000003
#define	VIC_INTERRUPT_PRIORITY_FOUR		0x00000004
#define	VIC_INTERRUPT_PRIORITY_FIVE		0x00000005
#define	VIC_INTERRUPT_PRIORITY_SIX		0x00000006
#define	VIC_INTERRUPT_PRIORITY_SEVEN	0x00000007
#define	VIC_INTERRUPT_PRIORITY_EIGHT	0x00000008
#define	VIC_INTERRUPT_PRIORITY_NINE		0x00000009
#define	VIC_INTERRUPT_PRIORITY_TEN		0x0000000a
#define	VIC_INTERRUPT_PRIORITY_ELEVEN	0x0000000b
#define	VIC_INTERRUPT_PRIORITY_TWELVE	0x0000000c
#define	VIC_INTERRUPT_PRIORITY_THIRTEEN	0x0000000d
#define	VIC_INTERRUPT_PRIORITY_FOURTEEN	0x0000000e
#define	VIC_INTERRUPT_PRIORITY_FIFTEEN	0x0000000f

void spoiInitializeTcasHardware(void);
void InitHardware(void);
void InitialiseSpeedoInfo(void);


#endif /*__INITTCAS_H_ */
