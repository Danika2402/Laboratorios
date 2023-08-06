/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef I2CS_H
#define	I2CS_H

#include <xc.h> 
#include <stdint.h>
#include <proc/pic16f887.h>
#define _XTAL_FREQ  8000000

void I2C_Master_Init(const unsigned long c);
void I2C_Master_Wait(void);
void I2C_Master_Start(void);
void I2C_Master_RepeatedStart(void);
void I2C_Master_Stop(void);
void I2C_Master_Write(unsigned d);
unsigned short I2C_Master_Read(unsigned short a);
void I2C_Slave_Init(uint8_t address);

#endif	/* I2CS_H */
