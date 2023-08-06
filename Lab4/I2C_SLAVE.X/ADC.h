/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */
#ifndef ADC_H
#define	ADC_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <proc/pic16f887.h>

void OSCILLATOR(uint8_t f);             //Oscillador

//void IOC_INT(uint8_t a);

void ADC_INIT(uint8_t c);                   //canal inicial
unsigned char ADC_READ(void);                         //leer ADRESH del canal 
//void ADC_CHANGE_CHANNEL(uint8_t c,uint8_t b);   //cambiar de canal
//int ADC_GET_CHANNEL();                  //en que canal estamos

//uint8_t DECENA(unsigned char c);        //Funciones para ir separando
//uint8_t UNIDAD(unsigned char c);        //cada valor
//uint8_t CENTENA(unsigned char c);

#endif	/* ADC_H */
