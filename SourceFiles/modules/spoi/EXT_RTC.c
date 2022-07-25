#include "Header.h"			  /* Global Functions & Defines */ 

#define rtc_pin_sel PINSEL1 &=0XFC3FFFFF;// P0.28(24:25) SCL, P0.27(22:23) SDA SELECTED
#define rtc_pin_mode PINMODE1 &=0XFC3FFFFF;// P0.28(24:25) SCL, P0.27(22:23) SDA PULL UP

#define scl_dr_op IODIR0|=0X10000000; // SCL P0.28 DIR OP
#define scl_dr_ip IODIR0&=0XEFFFFFFF; // SCL P0.28 DIR IP
#define scl_1 IOSET0=0X10000000; // SCL P0.28 high
#define scl_0 IOCLR0=0X10000000; // SCL P0.28 low

#define sda_dr_op IODIR0|=0X08000000; // SDA P0.27 DIR OP
#define sda_dr_ip IODIR0&=0XF7FFFFFF; // SDA P0.27 DIR IP
#define sda_1 IOSET0=0X08000000; // SDA P0.27 high
#define sda_0 IOCLR0=0X08000000; // SDA P0.27 low

#define sda_read IO0PIN; // SDA P0.27 DIR IP  P0.24-P0.31
 unsigned int rmin=0,rsec=0,rhour=0,rdate=0,rmonth=0,ryear=0;
/********************************START***********************************************/
	unsigned char convert(unsigned char c)
	{
	c=((c/10)*16)+(c%10);
	return c;
	}
	
/*************Delay*************************/
	void Dely(unsigned int x)
	{
	unsigned int i ;
	for(i=0;i<x*1;i++);	  // DELAY OK 200  WORKING FROM 1
	}

/*************RTC_START*************************/
	unsigned int Rtc_start(void)
		{
		unsigned char busy=0;
		unsigned char notbusy=1;
		sda_dr_ip;	  Dely(30) ;
 		Dely(30) ;	  //busy=sda_read;

  		if(!(IOPIN0&0X08000000))
  		{
    	sda_dr_op;  	busy=0;
		return(busy) ;
  		} 
  		scl_dr_ip;    Dely(30) ;
  		Dely(30) ;    //busy=IOPIN0;
   
   		if(!(IOPIN0&0X10000000))
   		{
    	sda_dr_op; 	busy=0;
		return(busy) ;
   		} 
     	    	  
		Dely(30) ;	  Dely(30) ;
		sda_dr_op;	  Dely(30) ;
		Dely(30) ;	  sda_1;
		Dely(30) ;	  Dely(30) ;
		scl_dr_op;
		Dely(30) ;	  Dely(30) ;
		scl_1;		  Dely(30) ;
		Dely(30) ;	  sda_0;
		Dely(30) ;	  Dely(30) ;

		scl_0;		  Dely(30) ;
		Dely(30) ;

		return(notbusy);
		}

/*************RTC_STOP*************************/
	void Rtc_stop(void)
		{
		scl_dr_op;	Dely(30) ;
 		Dely(30) ;	scl_0;
		Dely(30) ;	Dely(30) ;
		scl_1;		Dely(30) ;
		Dely(30) ;	sda_dr_op;
		sda_0;		Dely(30) ;
		Dely(30) ;	sda_1;
		Dely(30) ;  Dely(30) ;
		}
	 	 
 /****************WRITE RTC***********************************/
 void Write_Rtc(unsigned char dev_addr, unsigned char mem, unsigned char data)
 		{
   		unsigned char write_ack=0;
   		unsigned char flag=0; 
   		//unsigned char prt=0;
  		do
  		{
   		flag=0;     
		//prt=
		Rtc_start();
   		write_ack=Rtc_write(dev_addr);
   		if(write_ack&0X08)
   		{
    		flag=1;  	Rtc_stop();
			write_ack=0;
   		}
 		Dely(30) ;  Dely(30) ;
 		Dely(30) ;	 Dely(30) ;

  		}while(flag == 1);
  		flag=0;	   write_ack=0;
  		Rtc_write(mem);
  		Rtc_write(data);
  		Rtc_stop();
  		Dely(30) ;
 		}

/****************RTC WRITE ,ADDR, MEM, DATA********************/
   	unsigned char Rtc_write(unsigned char write)
 		{
 		unsigned char write_rec=0;
 		unsigned char mask=0X80;
		unsigned char ack_wr=0;
		write_rec= write;

		do{
		 	if(write_rec&mask)
 			{ 
 			Dely(30) ;  Dely(30) ;
 			sda_1;      Dely(30) ;
 			Dely(30) ;	 scl_1;
 			Dely(30) ;	 Dely(30) ;
 			scl_0;      Dely(30) ;
 			Dely(30) ;
 			}
			else
 			{
 			Dely(30) ;	  Dely(30) ;
 			sda_0;		  Dely(30) ;
 			Dely(30) ;	  scl_1;
 			Dely(30) ;	  Dely(30) ;
 		  	scl_0;		  Dely(30) ;
 			Dely(30) ;	 
 			}
		    mask=mask>>1;
		}while(mask>0);
 			write_rec=0;   Dely(30) ;
 			Dely(30) ;		sda_1;
 		    Dely(30) ;     Dely(30) ;
 			scl_1;		    Dely(30) ;
 			Dely(30) ;	    sda_dr_ip;
 			Dely(30) ;	    Dely(30) ;
 			Dely(30) ;	    Dely(30) ;
	
		if((IOPIN0&0X08000000)==0X08000000)
 			ack_wr=0X08;
		else
			ack_wr=0X00;

		Dely(30) ;     Dely(30) ;
 		scl_0;		    Dely(30) ;
 		Dely(30) ;	    sda_dr_op;
 		Dely(30) ;	    Dely(30) ;
 		write=0;

 		return (ack_wr);
 }

  /******************READ RTC*****************/
 	 unsigned char Read_Rtc(unsigned char dev_addr, unsigned char mem)
 		{
 		unsigned char flag=0;
 		unsigned char rtn=0;
 		unsigned char read_ack=0;
 		//unsigned char read_start;
		//printf("\na");
  		do{
  		read_ack=0;     flag=0;
		//read_start=
		Rtc_start();
  		read_ack=Rtc_write(dev_addr);

  		if((read_ack&0X08))
  			{
			Rtc_stop(); 	flag=1;
			read_ack=0;
  			}
	   	}while(flag==1);
		//printf("b");
  		read_ack=0;   flag=0;
		Rtc_write(mem);
  		Rtc_stop();
 		Rtc_start();
  		Rtc_write(dev_addr+1);
  		rtn=Rtc_receive(1);
  		Rtc_stop();
  		dev_addr=0;
  		mem=0;
		//printf("c\n");
  		return(rtn);
 		}

 /************** RTC RECEIVE*********************/

 	unsigned char Rtc_receive(unsigned char ack)
 		{
 		unsigned char ack_rec=0;
 		unsigned char c=0, mask=0X80;
 		//unsigned char comp=0;
		ack_rec=ack;
 	    do{
 			Dely(30) ;		   Dely(30) ;
 			scl_dr_op;		   Dely(30) ;
 			Dely(30) ;		   scl_1;
 			Dely(30) ;        Dely(30) ;
 			sda_dr_ip;		   Dely(30) ;
 			Dely(30) ;		   //comp= sda_read;
 			Dely(30) ;		   Dely(30) ;   // delay();
 			sda_dr_op;		   Dely(30) ;
 			Dely(30) ;		   
 
 		if((IOPIN0&0X08000000))
  			c=c|mask;
			//comp=0;
			scl_dr_op;
  			Dely(30) ;   Dely(30) ;
  			scl_0;	   Dely(30) ;
  			Dely(30) ;   mask=mask>>1;
  			}while(mask>0);
			 //comp=0;
		 if(ack_rec==1)
 			{
 			Dely(30) ;    Dely(30) ;
 			sda_dr_op;	   Dely(30) ;
 			Dely(30) ;	   sda_1;
 			ack_rec=0;	  
 			}
 		else
 			{
  			Dely(30) ;   Dely(30) ;
  			sda_dr_op;   Dely(30) ;
  			Dely(30) ;   sda_0;
 			}
 
 			Dely(30) ;    Dely(30) ;
 			scl_dr_op;    Dely(30) ;
 			Dely(30) ;    scl_1;
 			Dely(30) ;    Dely(30) ;
  			scl_0;        Dely(30) ;
 			Dely(30) ;	   sda_dr_op;
 			Dely(30) ;    Dely(30) ;
 			sda_1;        Dely(30) ;
 			Dely(30) ;
		return (c);
 	 }

 /*************rtc intl*********************/
 	void rtc_intl()
 		{				  
 		rtc_pin_sel ;	  rtc_pin_mode ;
 		sda_dr_op;		  Dely(30) ; 
 		sda_1;			  Dely(30) ;
 		scl_dr_op;		  Dely(30) ;
 		scl_1;			   
 		}
 	
/*************WRITE_EXT_RTC*************************/
void Write_ex_RTC(RTCDateTime_t st_DateTime)
		{	
			Write_Rtc(0xd0,0x00,convert(st_DateTime.ui_RTCSec));
			Write_Rtc(0xd0,0x01,convert(st_DateTime.ui_RTCMin));
			Write_Rtc(0xd0,0x02,convert(st_DateTime.ui_RTCHour)); 
			Write_Rtc(0xd0,0x04,convert(st_DateTime.ui_RTCMday));	
			Write_Rtc(0xd0,0x05,convert(st_DateTime.ui_RTCMon));	
			Write_Rtc(0xd0,0x06,convert(st_DateTime.ui_RTCYear));
		}	
/*****************************************************************************
*
*   NAME	    	:	RTCTimeAndDateUpdate()
*
*   DESCRIPTION	    :	This function used to update(set) the date and time.
*						after receiving the date and time from serial port. 
*
*   PARAMETERS	    :	void
*
*   RETURN VALUE    :	void
*
*****************************************************************************/
