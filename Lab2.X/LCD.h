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
#define _XTAL_FREQ  8000000

void LCD_PORT4(char a);
void LCD_COM4(char a);
void LCD_CLEAR4(void);
void LCD_XY4(char x, char y);
void LCD_INIT4(void);
void LCD_CHAR4(char a);
void LCD_STRING4(char *a);
void LCD_RIGHT4(void);
void LCD_LEFT4(void);
/*
void LCD_INIT4(void);
void LCD_COM4(char dato);
void LCD_XY4(char x, char y);
void LCD_CADENA4( char *dato);
void LCD_DATA4(char data);*/
/*
void LCD_INIT8(void);
void LCD_COM8(unsigned char dato);
void LCD_XY8(unsigned char x, unsigned char y);
void LCD_CADENA8(const char *dato);
void LCD_DATA8(char data);
*/

#define RS_PIN PORTDbits.RD2
#define E_PIN PORTDbits.RD3
#define D4 PORTDbits.RD4
#define D5 PORTDbits.RD5
#define D6 PORTDbits.RD6
#define D7 PORTDbits.RD7

//#define E_TRIS  TRISCbits.TRISC2

#endif	/* LCD_H */

