/* 
 * File:   ADC.h
 * Author: Danika Andrino
 * Comments: Configuracion ADC
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADC_H
#define	ADC_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <proc/pic16f887.h>

void ADC_INIT(int c);   //canal inicial
int ADC_READ(); //leer ADRESH del canal 
void ADC_CHANGE_CHANNEL(int c,int b);//cambiar de canal
int ADC_GET_CHANNEL();//en que canal estamos

uint8_t DECENA(char c);
uint8_t UNIDAD(char c);

#endif	/* ADC_H */

