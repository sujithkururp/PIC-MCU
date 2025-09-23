#include <xc.h>
#include <pic18f4580.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define _XTAL_FREQ 8000000   // Set according to your oscillator

// CONFIG bits (adjust as per your project)
//#pragma config OSC = HS, WDT = OFF, LVP = OFF, PBADEN = OFF

// --- LCD pin mapping ---
#define RS RC0
#define RW RC1
#define E  RC2

// --- RTC I2C address ---
#define RTC_WRITE_ADDR 0xD0
#define RTC_READ_ADDR  0xD1
// --- RTC I2C display address ---
#define I2C_ADDR 0x40   // PCF8574 with A0-A2 = GND
#define BL      0x08    // Backlight ON

// -------- I2C FUNCTIONS ----------
void i2c_idle(void) {
    while ((SSPCON2 & 0x1F) || (SSPSTAT & 0x04));
}

void i2c_start(void) {
    i2c_idle();
    SSPCON2bits.SEN = 1;
}

void i2c_rep_start(void) {
    i2c_idle();
    SSPCON2bits.RSEN = 1;
}

void i2c_stop(void) {
    i2c_idle();
    SSPCON2bits.PEN = 1;
}

void i2c_write(uint8_t data) {
    i2c_idle();
    SSPBUF = data;
    while (SSPSTATbits.BF);
    while (SSPCON2bits.ACKSTAT);
}

uint8_t i2c_read(uint8_t ack) {
    uint8_t data = 0;
    i2c_idle();
    SSPCON2bits.RCEN = 1;
    while (!SSPSTATbits.BF);
    data = SSPBUF;
    SSPCON2bits.ACKDT = ack; // 0=ACK, 1=NACK
    SSPCON2bits.ACKEN = 1;
    while (SSPCON2bits.ACKEN);
    return data;
}

void i2c_init(void) {
    TRISCbits.TRISC3 = 1; // SCL
    TRISCbits.TRISC4 = 1; // SDA
    SSPSTAT = 0x80;       // Slew rate off
    SSPCON1 = 0x28;       // Master mode
    SSPADD  = ((_XTAL_FREQ/4000)/100) - 1; // 100kHz
    SSPCON1bits.SSPEN = 1;
}

// -------- BCD CONVERSION ----------
uint8_t BCDtoDEC(uint8_t val) { return ((val >> 4) * 10) + (val & 0x0F); }
uint8_t DECtoBCD(uint8_t val) { return ((val / 10) << 4) + (val % 10); }

// -------- RTC FUNCTIONS ----------
void RTC_set_time(uint8_t hr, uint8_t min, uint8_t sec) {
    i2c_start();
    i2c_write(RTC_WRITE_ADDR);
    i2c_write(0x00);       // start at seconds
    i2c_write(DECtoBCD(sec));
    i2c_write(DECtoBCD(min));
    i2c_write(DECtoBCD(hr));
    i2c_stop();
}

void RTC_get_time(uint8_t *hr, uint8_t *min, uint8_t *sec) {
    i2c_start();
    i2c_write(RTC_WRITE_ADDR);
    i2c_write(0x00);
    i2c_rep_start();
    i2c_write(RTC_READ_ADDR);
    *sec = BCDtoDEC(i2c_read(0));
    *min = BCDtoDEC(i2c_read(0));
    *hr  = BCDtoDEC(i2c_read(1)); // NACK on last
    i2c_stop();
}

// -------- LCD FUNCTIONS ----------


void lcd_cmd(unsigned char cmd) {
    unsigned char cmd_u = (cmd & 0xF0);
    unsigned char cmd_l = ((cmd << 4) & 0xF0);

    i2c_start();
    i2c_write(I2C_ADDR);

    // Upper nibble
    i2c_write(cmd_u | 0x0C); // EN=1, RS=0
    i2c_write(cmd_u | 0x08); // EN=0, RS=0

    // Lower nibble
    i2c_write(cmd_l | 0x0C); // EN=1, RS=0
    i2c_write(cmd_l | 0x08); // EN=0, RS=0

    i2c_stop();
    __delay_ms(2);
}

void lcd_data(unsigned char data) {
    unsigned char data_u = (data & 0xF0);
    unsigned char data_l = ((data << 4) & 0xF0);

    i2c_start();
    i2c_write(I2C_ADDR);

    // Upper nibble
    i2c_write(data_u | 0x0D ); // EN=1, RS=1
    i2c_write(data_u | 0x09); // EN=0, RS=1

    // Lower nibble
    i2c_write(data_l | 0x0D); // EN=1, RS=1
    i2c_write(data_l | 0x09); // EN=0, RS=1

    i2c_stop();
    __delay_ms(20);
}



void LCD_Init(void) {
    __delay_ms(50);       // Wait LCD power up

    lcd_cmd(0x02);        // Initialize in 4-bit mode
    lcd_cmd(0x28);        // 2 line, 5x8 matrix
    lcd_cmd(0x0C);        // Display ON, Cursor OFF
    lcd_cmd(0x06);        // Entry mode
    lcd_cmd(0x01);        // Clear display
    __delay_ms(20);
}


void lcd_string(const char *s) { while(*s) lcd_data(*s++); }

// -------- MAIN PROGRAM ----------
void main(void) {
    uint8_t hr, min, sec;
    char buffer[17];

    // Init
    
    i2c_init();

    // --- set time once (comment after first run) ---
    RTC_set_time(1, 13, 24);
   // __delay_ms(1000);
    LCD_Init();
    while(1) {
        RTC_get_time(&hr, &min, &sec);
        
        sprintf(buffer,"Time %02u:%02u:%02u",hr,min,sec);
        lcd_cmd(0x80); // First line
        lcd_string(buffer);

        __delay_ms(1000);
    }
}
