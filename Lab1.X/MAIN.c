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
#include "ADC.h"
#include "PUSH.h"
#include "TMR.h"
#define _XTAL_FREQ  4000000
#define tmr0_value 244      //3ms

uint8_t unidad, decena;
uint8_t display, POT;

const char tabla[] = {
    0xFC,   //0
    0x60,   //1
    0xDA,   //2
    0xF2,   //3
    0x66,   //4
    0xB6,   //5
    0xBE,   //6
    0xE0,   //7
    0xFE,   //8
    0xF6,   //9
    0xEE,   //A
    0x3E,   //B
    0x9C,   //C
    0x7A,   //D
    0x9E,   //E
    0x8E    //F
};

void setup(void);

void __interrupt() isr (void){
    
    if (RBIF==1){
        if (RB0==0){
            if (RB0==0){
                PORTA++;
            }
        } else if (RB1==0){
            if (RB1==0){
                PORTA--;
            }  
        }
        INTCONbits.RBIF=0;
    }
    else if(T0IF == 1){
        PORTD = 0x00;
        //__delay_us(50); 
        
        if(display == 1){
            RD0 = 1;
            PORTC = tabla[unidad];
            
        }else if(display == 2){
            RD1 = 1;
            PORTC = tabla[decena];
            
        }else if(display == 3){
            display = 0;
        }
        
        ++display;
        INTCONbits.T0IF = 0;
        TMR0 = tmr0_value;
    }
    return;
}

void main(void) {
    setup();
    while(1){
        if (ADCON0bits.GO == 0){
            POT = ADC_READ();
            __delay_us(50); 
            ADCON0bits.GO = 1;
        }
        
        decena = DECENA(POT);
        unidad = UNIDAD(POT);
        
        RB7 = (POT > PORTA) ? 1:0;
    }
}

void setup(void){
    
    ANSEL = 0b00100000;
    ANSELH = 0x00;
    
    TRISA = 0x00;
    TRISB = 0b00000011;
    TRISC = 0x00;
    TRISD = 0x00;

    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    
    //oscilador a 4M Hz
    OSCILLATOR(2);
    /*OSCCONbits.IRCF2 =1;    
    OSCCONbits.IRCF1 =1;
    OSCCONbits.IRCF0 =0;
    OSCCONbits.SCS   =1;*/
    
    //configuracion TMR0
    PRESCALER_TMR0(7);  //1:256
    TMR0 = tmr0_value; 
    
    //Config. PULL UP
    IOC_INT(0b00000011);     //pines 1 y 2 se realizaran la interrupcion
    
    //Config. ADC
    ADC_INIT(5);            //canal 5
    
    ADCON1bits.VCFG0 = 0;   //VDD referencias internas
    ADCON1bits.VCFG1 = 0;   //VSS
    
    ADCON0bits.ADCS0 = 0;   //fosc/32
    ADCON0bits.ADCS1 = 1;

    ADCON1bits.ADFM =0;     //justificado izquierda
    
    ADCON0bits.ADON = 1;    //Habilito modulo ADC 
    __delay_us(50);
    ADCON0bits.GO_nDONE = 1;
    //Config. interrupciones
    
    INTCONbits.GIE  = 1;
    
    INTCONbits.RBIE = 1;    //interrupcion pull up 
    INTCONbits.RBIF = 0;
    INTCONbits.T0IF = 0;    //interrupcion TMR0
    INTCONbits.T0IE = 1;

    unidad = 0; 
    decena = 0;
    display = 0;
    POT = 0;
    
    return;
}