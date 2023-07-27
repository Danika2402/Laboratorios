/*
 * File:   MAIN_M.c
 * Author: HP
 *
 * Created on 26 de julio de 2023, 10:58 AM
 */
//*****************************************************************************
/* Electronica Digital 2 - 2023
 * Laboratorio 3 - SPI
 * 
*/
//*****************************************************************************
#pragma config  FOSC    = INTRC_NOCLKOUT
#pragma config  WDTE    = OFF
#pragma config  PWRTE   = OFF
#pragma config  MCLRE   = OFF
#pragma config  CP      = OFF
#pragma config  CPD     = OFF
#pragma config  BOREN   = OFF
#pragma config  IESO    = OFF
#pragma config  FCMEN   = OFF
#pragma config  LVP     = OFF

#pragma config  BOR4V   = BOR40V
#pragma config  WRT     = OFF

#include <stdint.h>
#include <xc.h>
#include "LCD.h"
#include "SPIM.h"
#define FLAG_SPI 0xFF
#define _XTAL_FREQ  8000000

void setup(void);

void main(void) {
    setup();
    while(1){
        PORTCbits.RC2 = 0;       //Slave Select
       __delay_ms(1);
       
       spiWrite(FLAG_SPI);
       PORTD = spiRead();
       
       __delay_ms(1);
       PORTCbits.RC2 = 1;       //Slave Deselect 
       
       //__delay_ms(250);
       //PORTB++;
    }
    return;
}

void setup(void){
    
    ANSEL = 0;
    ANSELH = 0;
    
    TRISCbits.TRISC2 = 0;
    TRISB = 0;
    TRISD = 0;
    
    PORTB = 0;
    PORTD = 0;
    PORTCbits.RC2 = 1;
    
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
}
