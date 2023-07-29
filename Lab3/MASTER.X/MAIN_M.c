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
#define CONT 0xAA
#define _XTAL_FREQ  8000000

uint8_t unidad, decena,centena;
uint8_t unidad1, decena1,centena1;
uint8_t POT1,POT2,cont;
void setup(void);

void main(void) {
    setup();
    while(1){
        PORTCbits.RC2 = 0;       //Slave Select
        PORTCbits.RC1 = 1;
       __delay_ms(10);
       
       spiWrite(FLAG_SPI);
       POT1 = spiRead();
       
       __delay_ms(10);
       
       __delay_ms(10);
       
       spiWrite(CONT);
       cont = spiRead();
       
       __delay_ms(10);
       
       PORTCbits.RC2 = 1;       //Slave Deselect
       PORTCbits.RC1 = 0;
       __delay_ms(1);
       
       spiWrite(FLAG_SPI);
       POT2 = spiRead();
       
       __delay_ms(1);

       
       
       centena = CENTENA(POT1);     //Aqui separamos el valor para poder
       decena = DECENA(POT1);       //imprimirlos despues
       unidad = UNIDAD(POT1);
       
       centena += 48;              //por ser idioma ASCII 48 significa 0
       decena += 48;               //de esta forma obtenemos numeros y no palabras
       unidad += 48;
        
       centena1 = CENTENA(cont);     //Aqui separamos el valor para poder
       decena1 = DECENA(cont);       //imprimirlos despues
       unidad1 = UNIDAD(cont);
       
       centena1 += 48;              //por ser idioma ASCII 48 significa 0
       decena1 += 48;               //de esta forma obtenemos numeros y no palabras
       unidad1 += 48;
       
       LCD_CLEAR();               //aqui imprimimos para el LCD
       LCD_XY(1,0);
       LCD_STRING("S1:   S2:   S3:");
       LCD_XY(2,0);
       LCD_CHAR(centena);
       LCD_STRING(".");
       LCD_CHAR(decena);
       LCD_CHAR(unidad);
       //LCD_STRING("V");
       
       centena1 = CENTENA(cont);     //Aqui separamos el valor para poder
       decena1 = DECENA(cont);       //imprimirlos despues
       unidad1 = UNIDAD(cont);
       
       centena1 += 48;              //por ser idioma ASCII 48 significa 0
       decena1 += 48;               //de esta forma obtenemos numeros y no palabras
       unidad1 += 48;

       LCD_XY(2,6);
       LCD_CHAR(centena1);
       //LCD_STRING(".");
       LCD_CHAR(decena1);
       LCD_CHAR(unidad1);
       //LCD_STRING("V");
       
       centena = CENTENA(POT2);     //Aqui separamos el valor para poder
       decena = DECENA(POT2);       //imprimirlos despues
       unidad = UNIDAD(POT2);
       
       centena += 48;              //por ser idioma ASCII 48 significa 0
       decena += 48;               //de esta forma obtenemos numeros y no palabras
       unidad += 48;
       
       LCD_XY(2,11);
       LCD_CHAR(centena);
       LCD_STRING(".");
       LCD_CHAR(decena);
       LCD_CHAR(unidad);
       //LCD_STRING("V");
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
