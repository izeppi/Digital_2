/*
 * File:   USART.c
 * Author: Marco
 *
 * Created on 10 de febrero de 2020, 11:39 PM
 */

// TRMT (1 = TSR empty; 0 = TSR full )
#include <xc.h>
#include <pic16f887.h>
#include "USART.h"

void Init_USART (void){
    //INTCONbits.GIE = 1;
    //INTCONbits.PEIE = 1;
    PIE1bits.RCIE = 1;    //RCIF bandera (1 = esta lleno (RCREG); 0 = no esta lleno)
    //PIE1bits.TXIE = 1;    //TXIF bandera (1 = esta lleno (TXREG); 0 = no esta lleno) TSR;TXREG;TRMT;
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 0;
    BAUDCTLbits.BRG16 = 1;
    SPBRG = 25;
    RCSTAbits.SPEN = 1;
    RCSTAbits.CREN = 1;
    TXSTAbits.TXEN = 1; 
    
}

void Envio(char Dato){
    while(TXSTAbits.TRMT == 0){
        
    }
    TXREG = Dato;
}
