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

void LCD_PORT(char a);
void LCD_COM(char a);
void LCD_CLEAR(void);
void LCD_XY(char x, char y);
void LCD_INIT(void);
void LCD_CHAR(char a);
void LCD_STRING(char *a);
//void LCD_RIGHT(void);
//void LCD_LEFT(void);

#define LCD_PORT PORTD
#define RS_PIN RC0
#define E_PIN RC1

#endif	/* LCD_H */
