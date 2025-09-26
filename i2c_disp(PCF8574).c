#include <xc.h>
#define _XTAL_FREQ 2000000

// ================= I2C ===================
void i2c_init() {
    SSPCON1 = 0x28;    // I2C Master mode
    SSPCON2 = 0x00;
    SSPSTAT = 0x00;
    SSPADD  = 4;       // 100kHz @ Fosc=2MHz
}

void i2c_start() {
    SEN = 1;
    while (SEN);
}
void i2c_stop() {
    PEN = 1;
    while (PEN);
}
void i2c_write(unsigned char data) {
    while (SSPSTATbits.BF);   // wait buffer empty
    SSPBUF = data;            // load data
    while (!PIR1bits.SSPIF);  // wait transfer complete
    PIR1bits.SSPIF = 0;       // clear flag
    while (SSPCON2 & 0x1F);   // wait for idle
}

// ================= LCD over I2C ===================
#define I2C_ADDR 0x40   // PCF8574 with A0-A2 = GND
#define BL      0x08    // Backlight ON

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

void lcd_disp(const char *str) {
    while (*str) {
        lcd_data(*str++);
    }
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

// ================= MAIN ===================
void main(void) {
    i2c_init();
    LCD_Init();

    lcd_cmd(0x80);        // Line 1, pos 0
    lcd_disp("sujith");
    lcd_cmd(0xc0);
    lcd_disp("hellow");

    while (1);
}
