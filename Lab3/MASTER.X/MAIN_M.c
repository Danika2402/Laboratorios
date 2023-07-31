/*
 * File:   MAIN_M.c
 * Author: HP
 *
 * Created on 26 de julio de 2023, 10:58 AM
 */
//*****************************************************************************
/* Electronica Digital 2 - 2023
 * Laboratorio 3 - SPI MASTER
 * Uso de pantalla LCD y conexión con 2 PICs con SPI
 * 
 * LCD = muestra 3 valores enviados por los slaves, 2 potenciometros y un contador
 * SPI = conexion entre pics
 * 
 * FUNCION: con la configuracion SPI 3 pics se comunican entre si, 2 pics 
 * llamados SLAVES le envian el valor de un potenciometro cada uno y un contador
 * al MAESTRO, que lo muestra en un LCD
*/
//******************************************************************************
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
uint8_t POT1,POT2,cont;
void setup(void);

void main(void) {
    setup();
    while(1){
        PORTCbits.RC2 = 0;       //Slave1 Select
        PORTCbits.RC1 = 1;      //Slave2 Deselect
       __delay_ms(1);
       
       spiWrite(CONT);          //Enviamos un dato que devolvera el contador o
       cont = spiRead();        //el pot del SLAVE1
       
       __delay_ms(1);
       
       PORTCbits.RC2 = 1;       //Slave1 Deselect
       PORTCbits.RC1 = 0;       //Slave2 Select
       __delay_ms(1);
       
       spiWrite(FLAG_SPI);      //Tenemos que enviar un valor cualquiera para 
       POT2 = spiRead();        //iniciar la conexion del maestro con el slave
                                //a pesar que el slave no leera nada
       __delay_ms(1);
       
       PORTCbits.RC2 = 0;       //Slave1 Select
       PORTCbits.RC1 = 1;       //Slave2 Deselect
       __delay_ms(1);
       
       spiWrite(FLAG_SPI);
       POT1 = spiRead();
       
       __delay_ms(1);
       
       PORTCbits.RC2 = 1;       //Slave1 Deselect   (para evitar poblemas con S1)
       PORTCbits.RC1 = 1;       //Slave2 Deselect
       
       centena = CENTENA(POT1);     //Aqui separamos el valor para poder
       decena = DECENA(POT1);       //imprimirlos despues
       unidad = UNIDAD(POT1);
       
       centena += 48;              //por ser idioma ASCII 48 significa 0
       decena += 48;               //de esta forma obtenemos numeros y no palabras
       unidad += 48;
        
       LCD_CLEAR();               //aqui imprimimos para el LCD
       LCD_XY(1,0);
       LCD_STRING("S1:   S2:   S3:");
       LCD_XY(2,0);
       LCD_CHAR(centena);
       LCD_STRING(".");
       LCD_CHAR(decena);
       LCD_CHAR(unidad);
       
       centena = CENTENA(cont);     //Aqui separamos el valor para el contador
       decena = DECENA(cont);       
       unidad = UNIDAD(cont);
       
       centena += 48;              
       decena += 48;               
       unidad += 48;

       LCD_XY(2,6);                 //Imprimimos para LCD
       LCD_CHAR(centena);
       LCD_CHAR(decena);
       LCD_CHAR(unidad);

       
       centena = CENTENA(POT2);     //Aqui separamos el valor para el 
       decena = DECENA(POT2);       // potenciometro del SLAVE2
       unidad = UNIDAD(POT2);
       
       centena += 48;              
       decena += 48;               
       unidad += 48;
       
       LCD_XY(2,11);                //Imprimimos para LCD
       LCD_CHAR(centena);
       LCD_STRING(".");
       LCD_CHAR(decena);
       LCD_CHAR(unidad);
 
    }
    return;
}

void setup(void){
    
    ANSEL = 0x00;
    ANSELH = 0x00;
    
    TRISCbits.TRISC2 = 0;       //Slave Select S1 
    TRISCbits.TRISC1 = 0;       //Slave Select S2
    TRISB = 0x00;
    TRISD = 0x00;
    
    PORTD = 0x00;
    PORTB = 0x00;
    PORTCbits.RC2 = 1;
    PORTCbits.RC1 = 1;
    
    LCD_INIT();
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
}
