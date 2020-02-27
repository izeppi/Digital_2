/*
 * File:   I2C_Master.c
 * Author: Marco
 *
 * Created on 25 de febrero de 2020, 11:30 PM
 */

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

#include <xc.h>
#include <stdint.h>
#include<stdio.h>
#include <pic16f887.h>
#include "I2C.h"
#include "LCD.h"

#define _XTAL_FREQ 4000000

uint8_t val;
char valor[16];

void Configuracion(void);

void main(void) {
    Configuracion();
    LCD_CmdWrite(0xC0);
    LCD_DataWrite(" S1    S2    S3 ");
    while(1){
        I2C_Master_Start();
        I2C_Master_Write(0x51);
        val = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(10);   
        
        LCD_CmdWrite(0x80);
        sprintf(valor, "%.3d", val);
        LCD_DataWrite(valor);
        
    }
}

void Configuracion (void){
    TRISB = 0;
    TRISD = 0;
    I2C_Master_Init(100000);       // Inicializar Comuncación I2C
    init_LCD(); 
}