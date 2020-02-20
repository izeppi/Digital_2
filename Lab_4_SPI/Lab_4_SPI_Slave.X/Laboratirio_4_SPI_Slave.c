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
#include "ADC.h"
#include "SPI.h"
#define _XTAL_FREQ 4000000

void Configuracion(void);
int Pot_1 = 0;
int Pot_2 = 0;
int b = 0;
int ADC_Sel = 1;



void __interrupt() ISR(void){
   if(SSPIF == 1){
        ADC_Sel = spiRead();
        if (ADC_Sel == 1){
           spiWrite(Pot_1); 
        }else {
            spiWrite(Pot_2); 
        }
        SSPIF = 0;
    }
    if(ADIF){
        b++;
        if (b%2==1){
            Canales_ADC(0);
            Pot_1 = ADRESH;
        }
        if (b%2 == 0){
            Canales_ADC(3);
            Pot_2 = ADRESH;
        }
        ADCON0bits.GO_DONE = 1;
        ADIF = 0;
    }
}


void main(void) {
    Configuracion();
    while(1){

    }
    return;
}


void Configuracion(void){
    ANSEL = 0B11111111;
    ANSELH = 0;
    TRISB = 0;
    TRISA = 0B11111111;   
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    Init_ADC();
   
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);

}