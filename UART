//UART TRANSMISSION


#include <xc.h>
#define _XTAL_FREQ 2000000
void main(void) {
    
    TRISCbits.TRISC6=0;
    TRISCbits.TRISC7=1;
    //TRIC=0X80;//TO GET THE PORTC6 OUTPUT AND PORTC7 INPUT
    TXSTA=0X24;//SET TX REGISTER 
    RCSTA=0X90;//SET RC REGISTER
    BAUDCON=0X00;
    
    SPBRG=129;//FOR TO GET THE 9600 BAUD RATE WE GET THE VALUE USING THE EQUATION
    while(1)
    {
        while(!TXIF);
        TXREG='F';
        __delay_ms(1000);
    }
  
    return;
}



//uart receiver and transmit code


void main(void) {
    
    TRISCbits.TRISC6=0;
    TRISCbits.TRISC7=1;
    //TRIC=0X80;//TO GET THE PORTC6 OUTPUT AND PORTC7 INPUT
    TXSTA=0X24;//SET TX REGISTER 
    RCSTA=0X90;//SET RC REGISTER
    BAUDCON=0X00;
    
    SPBRG=129;//FOR TO GET THE 9600 BAUD RATE WE GET THE VALUE USING THE EQUATION
    while(1)
    {
        while(!RCIF);//when ever the rcreg full the rcif is high then exit the loop
        char data=RCREG;
       // __delay_ms(1000);  
   
        while(!TXIF);//when ever the tcreg register is full then txif is low and exit the loop but 
        TXREG=data;
      
        
    }
  
    return;
}



//transmit string two method

#include <xc.h>
#define _XTAL_FREQ 2000000



void display(unsigned char *str ){
        while(*str)
        {
            while(!TXIF);
            TXREG=(*str++);
        }
    }

void main(void) {
    
    TRISCbits.TRISC6=0;
    TRISCbits.TRISC7=1;
    //TRIC=0X80;//TO GET THE PORTC6 OUTPUT AND PORTC7 INPUT
    TXSTA=0X24;//SET TX REGISTER 
    RCSTA=0X90;//SET RC REGISTER
    BAUDCON=0X00;
    
    SPBRG=129;//FOR TO GET THE 9600 BAUD RATE WE GET THE VALUE USING THE EQUATION
    //while(1)
    //{
//        while(!RCIF);//when ever the rcreg full the rcif is high then exit the loop
//        char data=RCREG;
       // __delay_ms(1000);  
   
       //when ever the tcreg register is full then txif is low and exit the loop but 
        
    
    display("sujith\r");
    __delay_ms(2000);
    
    
//        char name[8]="sujith";
//        for(int i=0;i<8;i++){
//            while(!TXIF);
//            TXREG=name[i];
//        }
        
        //while(1);
        
   // }
  
    return;
}


/// // STRING OF INPUT FROM THE KEYBOARD AND TRANSMIT USING UART


#include <xc.h>
#define _XTAL_FREQ 2000000



void display(unsigned char *str ){
        while(*str)
        {
            while(!TXIF);
            TXREG=(*str++);
        }
    }

void main(void) {
    
    TRISCbits.TRISC6=0;
    TRISCbits.TRISC7=1;
    //TRIC=0X80;//TO GET THE PORTC6 OUTPUT AND PORTC7 INPUT
    TXSTA=0X24;//SET TX REGISTER 
    RCSTA=0X90;//SET RC REGISTER
    BAUDCON=0X00;
    char data[10];
    int i=0;
    
    SPBRG=129;//FOR TO GET THE 9600 BAUD RATE WE GET THE VALUE USING THE EQUATION
    while(1)
    {
      //for(int i=0;i<10;i++){
       while(!RCIF);//when ever the rcreg full the rcif is high then exit the loop
       char ch=RCREG;
       if(ch=='\r'){
           
            data[i]='\0';
            display(data);
           //break;
           i=0;
       }
       else {
       data[i]=RCREG;
       i++;
       //}
      }
       
       
      
        
   }
  
    return;
}


//buffer is full when the size of the string is grater than 10 characters

#include <xc.h>
#define _XTAL_FREQ 2000000



void display(unsigned char *str ){
        while(*str)
        {
            while(!TXIF);
            TXREG=(*str++);
        }
    }

void main(void) {
    
    TRISCbits.TRISC6=0;
    TRISCbits.TRISC7=1;
    //TRIC=0X80;//TO GET THE PORTC6 OUTPUT AND PORTC7 INPUT
    TXSTA=0X24;//SET TX REGISTER 
    RCSTA=0X90;//SET RC REGISTER
    BAUDCON=0X00;
    char data[10];
    int i=0;
    
    SPBRG=129;//FOR TO GET THE 9600 BAUD RATE WE GET THE VALUE USING THE EQUATION
    while(1)
    {
      //for(int i=0;i<10;i++){
       while(!RCIF);//when ever the rcreg full the rcif is high then exit the loop
       char ch=RCREG;
       if(ch=='\r'){
           
            data[i]='\0';
            display(data);
           break;
           //i=0;
       }
       else if(i==9){
           display("buffer is full");
           break;
       }
       else {
       data[i]=RCREG;
       i++;
       //}
      }
       
       
      
        
   }
  
    return;
}



//adc value is sending using UART


#include <xc.h>
#include<stdio.h>
#define _XTAL_FREQ 2000000


void display(unsigned char *str ){
        while(*str)
        {
            while(!TXIF);
            TXREG=(*str++);
        }
    }

void main(void) {
    char buffer[15];
    
    TRISA=0X01;
    ADCON0=0X01;
    ADCON1=0X0E;
    ADCON2=0XA6;
    
    
    TRISC=0x80;
    //TRISCbits.TRISC7=1;
    //TRIC=0X80;//TO GET THE PORTC6 OUTPUT AND PORTC7 INPUT
    TXSTA=0X24;//SET TX REGISTER 
    RCSTA=0X90;//SET RC REGISTER
    BAUDCON=0X00;
    
    SPBRG=129;
    while(1){
        
       ADCON0 |=(1<<1);
       while(ADCON0 & (1<<1));
       int ADC_value =ADRESL;
       ADC_value |=ADRESH<<8;
       sprintf(buffer,"%d\r",ADC_value);
       display(buffer);
      
       
    }
    
    return;
}



// UART ADC VALUE DISPLAY

#include <xc.h>
#include<stdio.h>
#define _XTAL_FREQ 2000000


void display(unsigned char *str ){
        while(*str)
        {
            while(!TXIF);
            TXREG=(*str++);
        }
    }

void main(void) {
    char buffer[15];
    
    TRISA=0X01;
    ADCON0=0X01;
    ADCON1=0X0E;
    ADCON2=0XA6;
    TRISD=0X00;
    
    
    TRISC=0x80;
    //TRISCbits.TRISC7=1;
    //TRIC=0X80;//TO GET THE PORTC6 OUTPUT AND PORTC7 INPUT
    TXSTA=0X24;//SET TX REGISTER 
    RCSTA=0X90;//SET RC REGISTER
    BAUDCON=0X00;
    
    SPBRG=129;
    while(1){
        
       ADCON0 |=(1<<1);
       while(ADCON0 & (1<<1));
       int ADC_value =ADRESL;
       ADC_value |=ADRESH<<8;
       sprintf(buffer,"%d\r",ADC_value);
       display(buffer);
       if(ADC_value<=200){
       PORTD=0x01;}
       else if((ADC_value>200) && (ADC_value<=400)){
       PORTD=0x02;} 
       else if((ADC_value>400) && (ADC_value<=600)){
       PORTD=0x04;} 
       else if((ADC_value>600) && (ADC_value<=800)){
       PORTD=0x08;} 
       else if((ADC_value>800) && (ADC_value<=1000)){
       PORTD=0x10;} 
    }
    
    return;
}

