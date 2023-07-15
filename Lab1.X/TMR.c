/*
 * File:   TMR.c
 * Author: HP
 *
 * Created on 15 de julio de 2023, 03:57 PM
 */

#include <stdint.h>
#include <xc.h>
#include "TMR.h"
#define _XTAL_FREQ  4000000

void PRESCALER_TMR0(uint8_t a){
    OPTION_REGbits.T0CS = 0;
    //OPTION_REGbits.PSA = 0; 
    OPTION_REGbits.PS = a; 
}