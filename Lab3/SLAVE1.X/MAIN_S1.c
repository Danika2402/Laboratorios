/*
 * File:   MAIN_S1.c
 * Author: HP
 *
 * Created on 26 de julio de 2023, 01:04 PM
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
#include "SPIS1.h"
#include "ADC.h"

#define _XTAL_FREQ  8000000

//uint8_t POT;
void setup(void);

void __interrupt() isr(void){
    if(PIR1bits.SSPIF == 1){
        //PORTD = spiRead();
        spiWrite(PORTD);
        PIR1bits.SSPIF = 0;
    }
}

void main(void) {
    setup();
    while(1){

        /*ADCON0bits.GO_nDONE = 1;
        __delay_us(10);
       while( ADCON0bits.GO_nDONE == 1);*/
       PORTD = ADC_READ(); 
        
        
    }
    return;
}

void setup(void){
    //oscilador a 8M Hz
    OSCILLATOR(1);
    
    ANSEL =  0b00100000;
    ANSELH = 0;
    
    TRISB = 0;  //salidas
    TRISD = 0;  //salidas
    
    PORTB = 0;
    PORTD = 0;
    
    //Config. ADC
    ADC_INIT(5);            //canal 5
       
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    
    TRISAbits.TRISA5 = 1;       // Slave Select
    
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
 }
