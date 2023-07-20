/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef LCD_H
#define	LCD_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <proc/pic16f887.h>
#define _XTAL_FREQ  4000000

void LCD_INIT4(void);
void LCD_COM4(unsigned char dato);
void LCD_XY4(unsigned char x, unsigned char y);
void LCD_CADENA4(const char *dato);
void LCD_DATA4(char data);
/*
void LCD_INIT8(void);
void LCD_COM8(unsigned char dato);
void LCD_XY8(unsigned char x, unsigned char y);
void LCD_CADENA8(const char *dato);
void LCD_DATA8(char data);
*/
#define LCD_PORT PORTD
#define LCD_TRIS TRISD

#define RS_PIN  PORTCbits.RC0
#define RS_TRIS TRISCbits.TRISC0

#define RW_PIN  PORTCbits.RC1
#define RW_TRIS TRISCbits.TRISC1

#define E_PIN   PORTCbits.RC2
#define E_TRIS  TRISCbits.TRISC2

#endif	/* LCD_H */

