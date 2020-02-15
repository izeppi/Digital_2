/*
 * File:   SPI.c
 * Author: Marco
 *
 * Created on 14 de febrero de 2020, 11:07 AM
 */


#include <xc.h>
#include <stdint.h>


void init_SPI (uint8_t selector){
    SSPSTATbits.SMP = 0;
    SSPSTATbits.CKE = 1;
    SSPCONbits.SSPEN = 1;
    SSPCONbits.CKP = 1;
    SSPCONbits.SSPM = selector;   // Master = 0000  Slave = 0100
            
         
}  