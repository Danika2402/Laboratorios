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


#define _XTAL_FREQ  8000000
//#define tmr0_value 244      //3ms
uint8_t POT;
uint8_t unidad, decena,centena;

void setup(void);

void main(void) {
    //unsigned int a;
    setup();
    while(1){
        
        POT = ADC_READ();
        centena = (uint8_t)((POT*1.9607)/100);
        decena = (uint8_t)((POT*1.9607) - centena*100)/10;
        unidad = (uint8_t)((POT*1.9607) - centena*100 - decena*10);
        
        centena += 48;
        decena += 48;
        unidad += 48;
        
        LCD_CLEAR4();
        LCD_XY4(1,1);
        LCD_STRING4("POTENCIOMETRO");
        LCD_XY4(2,1);
        LCD_CHAR4(centena);
        LCD_STRING4(".");
        LCD_CHAR4(decena);
        LCD_CHAR4(unidad);
        
        /*LCD_CLEAR4();
        LCD_XY4(1,1);
        LCD_STRING4("LCD Library for");
        LCD_XY4(2,1);
        LCD_STRING4("MPLAB XC8");
        __delay_ms(2000);
        LCD_CLEAR4();
        LCD_XY4(1,1);
        LCD_STRING4("Developed By");
        LCD_XY4(2,1);
        LCD_STRING4("electroSome");
        __delay_ms(2000);
        LCD_CLEAR4();
        LCD_XY4(1,1);
        LCD_STRING4("www.electroSome.com");

        for(a=0;a<15;a++)
        {
            __delay_ms(300);
            LCD_LEFT4();
        }

        for(a=0;a<15;a++)
        {
            __delay_ms(300);
            LCD_RIGHT4();
        }

        LCD_CLEAR4();
        LCD_XY4(2,1);
        LCD_CHAR4('H');
        LCD_CHAR4('o');
        LCD_CHAR4('l');
        LCD_CHAR4('a');
        LCD_XY4(1,1);
        LCD_STRING4("Hola Mundo");
        __delay_ms(2000);*/

    }
    return;
}

void setup(void){
    
    ANSEL =  0b00100000;     //activo canal 5
    ANSELH = 0x00;
    
    //TRISA = 0x00;
    TRISD = 0x00;
    
    
    //PORTA = 0x00;
    //PORTC = 0x00;
    PORTD = 0x00;
    
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
    ADCON0bits.GO_nDONE = 1;
    
    LCD_INIT4();
    return;
}