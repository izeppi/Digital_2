/*
 * File:   Juego_Carrera.c
 * Author: HP
 *
 * Created on 23 de enero de 2020, 02:20 AM
 */


#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 4000000
 //CONFIGURACION 
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

// DEFINICION DE VARIABLES
int8_t inicio = 3;
int8_t Ganador = 0;
uint8_t Valor = 0;
uint8_t Regreso = 0;

void Semaforo (void);
void Juego (void);
void Contador_Decadas(void);
void Display (void);
void Configuracion (void);

//PROGRAMA PRINCIPAL
void main(void) {
    Configuracion();
    while (1){
        if(PORTDbits.RD3 == 0){
            __delay_ms (1);
            PORTA = 0;
            PORTB = 0;
            PORTDbits.RD7 = 0;
            PORTDbits.RD6 = 0;
            inicio = 3;
            Ganador = 0;
            if (PORTDbits.RD3 == 1){
                Semaforo();
                Juego(); 
            }
        }
    }
}

void Semaforo (void) {
    while (inicio >= 0){
        Valor = inicio;
        Contador_Decadas();
        PORTE = Regreso;
        Display ();
        inicio--;
        __delay_ms(1000);
    }
    PORTC = 0;
    PORTE = 0;
}

void Juego (void){
    PORTAbits.RA0 = 1;
    PORTBbits.RB0 = 1;
    while (Ganador == 0){  
        if (PORTDbits.RD0 == 0){
            __delay_ms(10);
            if (PORTDbits.RD0 == 1){
                PORTA = PORTA*2;
            }
        }
            
        if (PORTDbits.RD2 == 0){
            __delay_ms(10);
            if (PORTDbits.RD2 == 1){
                PORTB = PORTB*2;
            }
        }
        
        if (PORTB == 128){
            PORTDbits.RD7 = 1;
            Valor = 2;
            Display ();
            Ganador = 1;
            break;
        }
        if (PORTA == 128){
            PORTDbits.RD6= 1;
            Valor = 1;
            Display ();
            Ganador = 1;
            break;
        }
        
    }
}

void Contador_Decadas(void){
    if (Valor == 0){
        Regreso = 0b00000111;  
    }
    if (Valor == 1){
        Regreso = 0b00000001;
    }
    if (Valor == 2){
        Regreso = 0b00000010;
    }
    if (Valor == 3){
        Regreso = 0b00000100;
    }
}

void Display (void){
    if (Valor == 0){
        PORTC = 0b11101110;
    }
    if (Valor == 1){
        PORTC = 0b00101000;
    }
    if (Valor == 2){
        PORTC = 0b11001101;
    }
    if (Valor == 3){
        PORTC = 0b01101101;   
    }
}

void Configuracion (void){
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISE = 0;
    TRISDbits.TRISD0 = 1;
    TRISDbits.TRISD2 = 1;
    TRISDbits.TRISD3 = 1;
    TRISDbits.TRISD7 = 0;
    TRISDbits.TRISD6 = 0;
    PORTDbits.RD7 = 0;
    PORTDbits.RD6 = 0;
    ANSEL = 0;
    ANSELH = 0;
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTE = 0;
}