#include<pic16f887.h>              //----Include Reg file of Pic18f4550
#include <stdint.h>
#include <stdio.h> 

#define lcd PORTB                   //----Assing PORTD as lcd
 
#define rs PORTDbits.RD5            //----Register Select Pin for Control of LCD
#define rw PORTDbits.RD6           //----Read/Write Pin for Control of LCD
#define en PORTDbits.RD7            //----Enable Pin for Control of LCD
#define _XTAL_FREQ 4000000
 


// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
//-------End of Main Program---------//
 
void LCD_CmdWrite(unsigned char cmd)
{
    lcd = 0xFF;                   
    lcd &= 0x80;                  
    rs = 0;                       
    rw = 1;                       //----Read/Write Pin is High => Read
    en = 0;
    __delay_ms(1);
    en = 1;     //----Low to High to read data from LCD
    if(lcd == 0x80)
    {
        en = 0; __delay_ms(1); en = 1;     //----Low to High to read data from LCD
    }
    
    lcd = cmd;                      //----8-Bit Command is Send to PORTD
    rs = 0;                       //----Register Select Pin is Low => Command Register
    rw = 0;                       //----Read/Write Pin is Low => Write.

    en = 1;                       //----Enable Pin goes high
    __delay_ms(1);                     //----delay of 1ms
    en = 0;                       //----Enable Pin goes Low
}
 
void DWR_LCD(unsigned char dat)
{
    lcd = 0xFF;                   
    lcd &= 0x80;                  
    rs = 0;                       
    rw = 1;                       //----Read/Write Pin is High => Read
    en = 0;
    __delay_ms(1);
    en = 1;     //----Low to High to read data from LCD
    if(lcd == 0x80)
    {
        en = 0; __delay_ms(1); en = 1;     //----Low to High to read data from LCD
    }
    
    lcd = dat;                      //----8-Bit Data is Send to PORTD
    rs = 1;                       //----Register Select Pin is High => Data Register
    rw = 0;                       //----Read/Write Pin is Low => Write.
    
    en = 1;                       //----Enable Pin goes high
    __delay_ms(1);                     //----delay of 1ms
    en = 0;                       //----Enable Pin goes Low
}
 
void LCD_DataWrite(unsigned char *dato)
{
    while(*dato != 0)              //---Check till last data is send
        DWR_LCD(*dato++);          //---Send data to lcd and increment
}
 
void WriteInt_LCD(unsigned char dato){
    
    char output1[3];
    sprintf (output1,"%d",dato);
    LCD_DataWrite(output1);
}

void init_LCD (void)
{
    LCD_CmdWrite(0x38);              //----8-bit data and 16x2 line
    LCD_CmdWrite(0x0E);              //----Cusor Blinking
    LCD_CmdWrite(0x01);              //----Clear LCD
    LCD_CmdWrite(0x06);              //----Increment Cusor
    LCD_CmdWrite(0x80);              //----1st low of 1st row
}