/*
 * File:   PUSH.c
 * Author: Danika Andrino
 *
 * Created on 13 de julio de 2023, 05:07 PM
 */

#include <stdint.h>
#include <xc.h>
#include "PUSH.h"

void IOC_INT(uint8_t a){        //configuracion de PULL UPS
                                //de los botones
    //Config. PULL UP
    OPTION_REGbits.nRBPU = 0;
    WPUBbits.WPUB = a;
    IOCBbits.IOCB = a;         
    
}