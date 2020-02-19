/*
 * File:   ADC.c
 * Author: Marco
 *
 * Created on 11 de febrero de 2020, 12:36 AM
 */


#include <xc.h>
#include <pic16f887.h>
#include "ADC.h"

void Init_ADC(void) {
    ADCON0bits.ADCS0    = 1;                // clock period (250ns 8MHz; 500ns 4MHz)
    ADCON0bits.ADCS1    = 0;                // clock period (250ns 8MHz; 500ns 4MHz)                         
    ADCON0bits.ADON     = 1;                // Bit de encendido de ADC
    ADCON0bits.GO_DONE  = 1;                // 1 = conversion en proceso ; 0 = completada/no en progreso
    ADCON1bits.ADFM     = 0;    // Justificacion (1 = justificado a la derecha (ADRESL) ; 0 = justificado a la izquierda (ADRESH))
    ADCON1bits.VCFG0    = 0;                // Voltaje de referencia Vss
    ADCON1bits.VCFG1    = 0;                // Voltaje de referencia Vdd
}

void Interrupciones_ADC (void){
    INTCONbits.PEIE = 1; // Interrupcion de perifericos encendida
    PIE1bits.ADIE   = 1; // interrupcion del ADC encendida (Bandera: ADIF)
}

void Canales_ADC (char Canal){
    if (Canal == 8){
                                 //Seleccion de canales                                                Posicion de bits
    ADCON0bits.CHS0 = 0; // canal (0000 ANS0 ; 0001 ANS1 ; 0010 ANS2 ; 0011 ANS3)                 0001
    ADCON0bits.CHS1 = 0; // canal (0100 ANS4 ; 0101 ANS5 ; 0110 ANS6 ; 0111 ANS7)                 0010  
    ADCON0bits.CHS2 = 0; // canal (1000 ANS8 ; 1001 ANS9 ; 1010 ANS10 ; 1011 ANS11)               0100
    ADCON0bits.CHS3 = 1; // canal (1100 ANS12 ; 1101 ANS13; 1110 Cvref ; 1111 Fixed (0.6V))       1000
    }
    if (Canal == 9){
                                 //Seleccion de canales                                                Posicion de bits
    ADCON0bits.CHS0 = 1; // canal (0000 ANS0 ; 0001 ANS1 ; 0010 ANS2 ; 0011 ANS3)                 0001
    ADCON0bits.CHS1 = 0; // canal (0100 ANS4 ; 0101 ANS5 ; 0110 ANS6 ; 0111 ANS7)                 0010  
    ADCON0bits.CHS2 = 0; // canal (1000 ANS8 ; 1001 ANS9 ; 1010 ANS10 ; 1011 ANS11)               0100
    ADCON0bits.CHS3 = 1; // canal (1100 ANS12 ; 1101 ANS13; 1110 Cvref ; 1111 Fixed (0.6V))       1000
    }
    
}
