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
#include "USART.h"

#define _XTAL_FREQ  8000000
//#define tmr0_value 244      //3ms
uint8_t POT;
char cont;
uint8_t unidad, decena,centena;
char old_pot;

void setup(void);

void main(void) {
    //unsigned int a;
    setup();
    while(1){
        old_pot = POT;
        POT = ADC_READ();
        /*if (ADCON0bits.GO == 0){
            POT= ADRESH;           
            ADCON0bits.GO = 1;
        }*/
        centena = CENTENA(POT);
        decena = DECENA(POT);
        unidad = UNIDAD(POT);
        
        centena += 48;
        decena += 48;
        unidad += 48;
        
        cont = USART_READ();
        
        if(cont == '+'){
            PORTA++;
        }else if(cont == '-'){
            PORTA--;
        }
        
        if(old_pot != POT){
            USART_WRITE("\n\r+ Aumentar contador\n\r");
            USART_WRITE("- Disminuir contador\n\r");
            USART_WRITE("Voltaje de POT:");
            USART_CHAR(centena);
            USART_WRITE(".");
            USART_CHAR(decena);
            USART_CHAR(unidad);
            USART_WRITE("\n\r\n\r");
        }
        
        LCD_CLEAR8();
        LCD_XY8(1,1);
        LCD_STRING8("POT");
        LCD_XY8(2,1);
        LCD_CHAR8(centena);
        LCD_STRING8(".");
        LCD_CHAR8(decena);
        LCD_CHAR8(unidad);
        LCD_STRING8("V");
        
        centena = CENTENA(PORTA);
        decena = DECENA(PORTA);
        unidad = UNIDAD(PORTA);
        
        centena += 48;
        decena += 48;
        unidad += 48;
        
        LCD_XY8(1,10);
        LCD_STRING8("CPU:");
        LCD_XY8(2,10);
        LCD_CHAR8(centena);
        LCD_STRING8(".");
        LCD_CHAR8(decena);
        LCD_CHAR8(unidad);
        LCD_STRING8("V");
        
    }
    return;
}

void setup(void){
    
    ANSEL =  0b00100000;     //activo canal 5
    ANSELH = 0x00;
    
    TRISA = 0x00;
    TRISD = 0x00;
    TRISC = 0b10000000;
    
    PORTA = 0x00;
    PORTD = 0x00;
    PORTC = 0X00;
    //oscilador a 8M Hz
    OSCILLATOR(1);
    
    //Config. ADC
    ADC_INIT(5);            //canal 5
    
    ADCON1bits.VCFG0 = 0;   //VDD referencias internas
    ADCON1bits.VCFG1 = 0;   //VSS
    
    ADCON0bits.ADCS0 = 0;   //fosc/32
    ADCON0bits.ADCS1 = 1;

    ADCON1bits.ADFM =0;     //justificado izquierda
    
    ADCON0bits.ADON = 1;    //Habilito modulo ADC 
    __delay_us(50);
    ADCON0bits.GO_nDONE = 0;
    
    LCD_INIT8();
    USART_INIT(9600);
    return;
}