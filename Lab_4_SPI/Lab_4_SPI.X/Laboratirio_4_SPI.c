/*
 * File:   Laboratirio_4_SPI.c
 * Author: Marco
 *
 * Created on 14 de febrero de 2020, 12:05 PM
 */


#include <xc.h>
#include <stdint.h>
#define _XTAL_FREQ 4000000

void main(void) {
      SSPSTATbits.SMP = 0;
    SSPSTATbits.CKE = 1;
    SSPCONbits.SSPEN = 1;
    SSPCONbits.CKP = 1;
    SSPCONbits.SSPM = 0x0;   // Master = 0000  Slave = 0100
    __delay_ms(2000);
    SSPCONbits.SSPM = 0xF;
}
