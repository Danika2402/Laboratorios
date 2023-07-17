/* 
 * File:    TMR.h   
 * Author: Danika Andrino
 * Comments: Configuracion TMR0
 * Revision history:    16/07/2023
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TMR0_H
#define	TMR0_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <proc/pic16f887.h>

void OSCILLATOR(uint8_t c);
void PRESCALER_TMR0(int c);
//void TMR1
//void TMR2

#endif	/* TMR0_H */

