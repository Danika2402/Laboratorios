/*
 * File:   MAIN_S.c
 * Author: HP
 *
 * Created on 2 de agosto de 2023, 03:02 PM
 */
//******************************************************************************
/* Electronica Digital 2 - 2023
 * Laboratorio 4 - I2C SLAVE
 * Comunicacion I2C usando 2 PICs, un RTC DS1307 (Tiny RTC I2C module) o 
 * el DS3231, un LCD 2x16 y un Potenciometro(SLAVE)
 * 
 * I2C = comunicacion con PIC MASTER
 * ADC = leer potenciometro
 * 
 * FUNCION: con I2C, se comunica con el PIC MASTER, donde se envia los
 * valores de un potenciometro, que luego son imprimidos y mostrados en 
 * una pantalla LCD.
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
#include "I2CS.h"
#include "ADC.h"

#define _XTAL_FREQ  8000000
uint8_t z;
uint8_t POT;
void setup(void);

void __interrupt() isr(void){
   if(PIR1bits.SSPIF == 1){ 
        SSPCONbits.CKP = 0;
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            z = SSPBUF;                 // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;       // Clear the overflow flag
            SSPCONbits.WCOL = 0;        // Clear the collision bit
            SSPCONbits.CKP = 1;         // Enables SCL (Clock)
        }
        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            //__delay_us(7);
            z = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            //__delay_us(2);
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepción se complete
            PORTD = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepción
            __delay_us(250);
            
        }else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;                 //Envio de la varialbe POT al MASTER
            BF = 0;                     
            SSPBUF = POT;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        }
        PIR1bits.SSPIF = 0;    
    }
}

void main(void) {
    setup();
    while(1){
        POT = ADC_READ();   //lectura del potenciometro
    }
    return;
}

void setup(void){
    //oscilador a 8M Hz
    OSCILLATOR(1);
    
    ANSEL =  0b00100000;
    ANSELH = 0x00;
    
    //Config. ADC
    ADC_INIT(5);            //canal 5
    I2C_Slave_Init(0x80);   
}
