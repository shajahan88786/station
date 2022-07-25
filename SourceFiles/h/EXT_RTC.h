#ifndef EXT_RTC_H_
#define EXT_RTC_H_

void Rtc_intl(void);
unsigned int Rtc_start(void);
void Rtc_stop(void);
unsigned char Rtc_write_addr(unsigned char);


void Write_Rtc(unsigned char, unsigned char, unsigned char);
unsigned char Rtc_write(unsigned char);
unsigned char Read_Rtc(unsigned char, unsigned char);
unsigned char Rtc_receive(unsigned char );
void rtc_intl(void);
void Write_ex_RTC(RTCDateTime_t st_DateTime);
void Read_ex_RTC(void);
		  
unsigned char convert(unsigned char c);
void Dely(unsigned int x);

#endif
