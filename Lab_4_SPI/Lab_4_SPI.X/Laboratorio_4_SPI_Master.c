/*
 * File:   Laboratorio_3.c
 * Author: Marco 
 *
 * Created on 11 de febrero de 2020, 01:16 AM
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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include <pic16f887.h>
#include <stdio.h>
#include "USART.h"
#include "SPI.h"
#define _XTAL_FREQ 4000000

uint8_t  Contador = 0;
uint8_t Pot_1 = 0;
uint8_t Pot_2 = 0;


void __interrupt()ISR (void){
    if (PIR1bits.RCIF == 1){
        Contador = RCREG;
}


void Configuracion(void);

void main(void) {
    Configuracion();
    Envio_SPI (1);
    __delay_ms(100);
    
    while(1){
        Recibo_SPI(Pot_1);  //Recibo valor del Pot 1 
        __delay_ms(100);
        Envio_SPI(2);      // Envio el # del Pot 2
        __delay_ms(100);
        Recibo_SPI(Pot_2); //Recibo valor del Pot 2
        __delay_ms(100);
        Envio_SPI(1)       // Envio el # del Pot 1
        __delay_ms(100);
        Envio (Pot_1);      // UART pot 1
        Envio (Pot_2);     // UART pot 2
        PORTA = Contador;
    }
}


void Configuracion(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    PORTA = 0;
    INTCONbits.GIE = 1;
    Init_USART();
    init_SPI(0101,1); 
}