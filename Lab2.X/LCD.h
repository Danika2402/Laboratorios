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
//#define _XTAL_FREQ  8000000
/*
void LCD_PORT4(char a);
void LCD_COM4(char a);
void LCD_CLEAR4(void);
void LCD_XY4(char x, char y);
void LCD_INIT4(void);
void LCD_CHAR4(char a);
void LCD_STRING4(char *a);
void LCD_RIGHT4(void);
void LCD_LEFT4(void);*/

void LCD_PORT8(char a);
void LCD_COM8(char a);
void LCD_CLEAR8(void);
void LCD_XY8(char x, char y);
void LCD_INIT8(void);
void LCD_CHAR8(char a);
void LCD_STRING8(char *a);
void LCD_RIGHT8(void);
void LCD_LEFT8(void);

#define LCD_PORT PORTD
#define RS_PIN RC0
#define E_PIN RC1

#endif	/* LCD_H */

