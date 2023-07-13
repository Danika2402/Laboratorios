/*
 * File:   MAIN.c
 * Author: Danika
 *
 * Created on 12 de julio de 2023, 07:38 PM
 */
//*****************************************************************************
/*
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

void setup(void);

void __interrupt() isr (void){
    
    if (RBIF==1){
        if (RB0==0){
            PORTA++;
            
        } else if (RB1==0){
            PORTA--;
        }
        INTCONbits.RBIF=0;
    }
}

void main(void) {
    setup();
    while(1){
        
    }
}

void setup(void){
    
    ANSEL = 0x00;
    ANSELH = 0x00;
    
    TRISA = 0x00;
    TRISB = 0b00000011;

    PORTA = 0x00;
    PORTB = 0x00;
    
    //Config. PULL UP
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB0 = 1;
    WPUBbits.WPUB1 = 1;
    
    IOCBbits.IOCB0 = 1;         //pines 1 y 2 se realizaran la interrupcion
    IOCBbits.IOCB1 = 1;
    
    //Config. interrupciones
    INTCONbits.GIE  = 1;
    
    INTCONbits.RBIE = 1;    //interrupcion pull up 
    INTCONbits.RBIF = 0;
}