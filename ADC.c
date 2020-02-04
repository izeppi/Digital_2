/*
 * File:   ADC.c
 * Author: Marco
 * Device: PIC16F887
 * Distribution:
 *  PORTA = salida de contador binario
 *  PORTB = entrada de botones y ADC
 *  PORTC = salida de displays
 *  PORTE = led inidicadora
 * Description:
 *  Este es un sistema ADC que muestra su valor en Hexadecimal en los Displays
 *  y un contador binario que muestra sus valor en el Puerto A. Cuando el valor
 *  del ADC es mayor al del contador binario, el led indicador se enciende.
 * 
 * Created on 2 de febrero de 2020, 04:18 PM
 */

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

#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 4000000

int8_t Boton;
int8_t Valor;

void __interrupt()ISR (void){
    if(INTCONbits.TMR0IE == 1)
    {
        if (PORTEbits.RE0 == 1)
        {
            PORTEbits.RE0 = 0;
            PORTEbits.RE1 = 1;
            INTCONbits.TMR0IE = 0;
        }
        if (PORTEbits.RE0 == 0)
        {
            PORTEbits.RE0 = 1;
            PORTEbits.RE1 = 0;
            INTCONbits.TMR0IE = 0;
        }
    }
    if (INTCONbits.RBIF == 1){
        Boton = 1;
        INTCONbits.RBIF == 0;
    }
    
    if (PIR1bits.ADIF = 1){
        Valor = ADRESH;
    }
}

//ADMF = 0
//ADCON0 = 1
//GO/DONE = 1
//ADCS = 01
//CHS = 1010
//ADON =1

//
void main(void) {
    return;
}
