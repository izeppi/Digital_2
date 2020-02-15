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
#include "LCD.h"
#include "USART.h"
#define _XTAL_FREQ 4000000
 
void Envio(char Lol);
void FloatDec(float Variable,uint8_t Selector );

unsigned char Pot_1 = 0;
unsigned char Pot_2 = 0;
int8_t b = 0;
int8_t Sel_ADC = 1;
unsigned char Counter = 1;
char output1[8];
float f1;
uint8_t Decenas;
uint8_t Unidades;
uint8_t Dec_1 = 0;
float Uni_1 = 0;
uint8_t Dec_2 = 0;
float Uni_2 = 0;
float tempU = 0;

float f2;

void __interrupt()ISR (void){
    if (PIR1bits.ADIF == 1)
    {
        b++;
        if(b%2 == 1){
            Canales_ADC(8);
            Pot_1 = ADRESH;
        }
        if (b%2 == 0){
            Canales_ADC(9);
            Pot_2 = ADRESH;
        }
      ADCON0bits.GO_DONE = 1;
      PIR1bits.ADIF = 0;
    }
    if (PIR1bits.RCIF == 1){
        Sel_ADC = RCREG;
        if(Sel_ADC == 43){
            Counter++;
        }else if(Sel_ADC == 45){
            Counter--;
        }
    }
}

void Configuracion(void);

void main()
{
    Configuracion();
    
    LCD_DataWrite(" S1    S2    S3 ");
    while (1){
      //  entero = (int) floatVar; //7.5678  7   0.5678  56.78 
        f1 = (((float)Pot_1 * 5) / 255);
        f2 = (((float)Pot_2 * 5) / 255);
        FloatDec(f1,0);
        FloatDec(f2,1);
        LCD_CmdWrite(0xC0);
        WriteInt_LCD(Dec_1);
        LCD_DataWrite(".");
        if(Uni_1 < 10){
            WriteInt_LCD(0);
        }
        WriteInt_LCD(Uni_1);
        LCD_DataWrite("V ");
        
        
        WriteInt_LCD(Dec_2);
        LCD_DataWrite(".");
        if(Uni_2 < 10){
            WriteInt_LCD(0);
        }
        WriteInt_LCD(Uni_2);
        LCD_DataWrite("V ");
        
        WriteInt_LCD(Counter);
        LCD_DataWrite("  ");
        
        //sprintf (output1,"%d.%dV %d.%dV %d",Dec_1,Uni_1,Dec_2,Uni_2, Counter);
        
        Envio(Pot_2);
        Envio(Pot_1);
        
        
    }
    
}


void Envio(char Lol){
    while(TXSTAbits.TRMT == 0){
        
    }
    TXREG = Lol;
}


void Configuracion(void){
    TRISA = 0;
    TRISC = 0b10000000;
    Init_ADC();
    INTCONbits.GIE = 1;
//    INTCONbits.PEIE = 1;
//    PIE1bits.RCIE = 1;
    Interrupciones_ADC();
    init_LCD(); 
    Init_USART();
}



void FloatDec(float Variable,uint8_t Selector ){
    Decenas = (int)Variable;
    tempU = Variable - Decenas;
    tempU = tempU * 100;
    Unidades = (int)tempU;
    if(Selector){
        Dec_1 = Decenas;
        Uni_1 = Unidades;
    }else{
        Dec_2 = Decenas;
        Uni_2 = Unidades;
    }
}