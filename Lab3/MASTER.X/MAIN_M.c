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
        PORTCbits.RC1 = 1;
       __delay_ms(1);
       
       spiWrite(FLAG_SPI);
       PORTB = spiRead();
       
       __delay_ms(1);
       PORTCbits.RC2 = 1;       //Slave Deselect
       PORTCbits.RC1 = 0;
       __delay_ms(1);
       
       spiWrite(FLAG_SPI);
       PORTD = spiRead();
       
       __delay_ms(1);

    }
    return;
}

void setup(void){
    
    ANSEL = 0x00;
    ANSELH = 0x00;
    
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC1 = 0;
    TRISB = 0x00;
    TRISD = 0x00;
    
    PORTD = 0x00;
    PORTB = 0x00;
    PORTCbits.RC2 = 1;
    PORTCbits.RC1 = 1;
    
    LCD_INIT();
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
}
