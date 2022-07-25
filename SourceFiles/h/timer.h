#ifndef	TIMER_H
#define TIMER_H

#define F0_TO_FS 13
#define FS_TO_F0 26

//#define TIMER1_PCONP 	0x0004	/* For Timer 0 */
//#define T1_PCLK_DIV		(143)	/* to test 20% error */
 #define T1_PCLK_DIV		(144)
extern unsigned long timerClk;
extern uint32_t gCommHealthClock;

void timer1Init(void);
void timer2Init(void);
void timer3Init(void);
static void TIMER1_ISR (void) __irq; 
static void TIMER2_ISR (void) __irq;
static void TIMER3_ISR (void) __irq; 
void loadTimer1MR0(unsigned long ticks);
 void loadTimer1MR1(unsigned long ticks);
  void loadTimer1MR2(unsigned long ticks);
	void loadTimer1MR3(unsigned long ticks);
	void loadTimer2MR0(unsigned long ticks);
	void loadTimer2MR1(unsigned long ticks);
	void loadTimer2MR2(unsigned long ticks);
	void loadTimer2MR3(unsigned long ticks);
	void loadTimer3MR1(unsigned long ticks);
	void loadTimer3MR2(unsigned long ticks) ;
	void loadTimer3MR3(unsigned long ticks);
	void loadTimer3MR0(unsigned long ticks);
	void configTimers(unsigned char ucSelfTimeSlot);
	void FrquncyShift_F0ToFS(void);
	void FrquncyShift_FSToF0(void);
	void configSlotControlPkt(void);
	void ConfigEmergencyPkt(void);
#endif /*#define _TIMER_H__*/
