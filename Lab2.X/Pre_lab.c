/*
 * File:   Pre_lab.c
 * Author: Danika Andrino
 *
 * Created on 19 de julio de 2023, 02:03 PM
 */
//*****************************************************************************
/* Electronica Digital 2 - 2023
 * Laboratorio 2 - LCD
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
#include "ADC.h"

#define _XTAL_FREQ  4000000
//#define tmr0_value 244      //3ms



void setup(void);

void main(void) {
    setup();
    while(1){
        PORTA = ADC_READ();
        
        LCD_XY4(16,1);
        LCD_CADENA4("HOLA MUNDO");
        //LCD_XY4(1,0);
        //LCD_CADENA4("M");
        //__delay_us(100);
    }
    return;
}

void setup(void){
    
    ANSEL =  0b00100000;     //activo canal 5
    ANSELH = 0x00;
    
    TRISA = 0x00;
    TRISC = 0x00;
    TRISD = 0x00;
    
    PORTA = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    
    //oscilador a 4M Hz
    OSCILLATOR(2);
    
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
    
    LCD_INIT4();
    return;
}