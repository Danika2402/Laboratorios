/*
 * File:   LCD.c
 * Author: HP
 *
 * Created on 26 de julio de 2023, 11:00 AM
 */

#include <stdint.h>
#include <xc.h>
#include "LCD.h"
#define _XTAL_FREQ  8000000

uint8_t CENTENA(unsigned char c){    //se separa el bit mas significativo   
    c = (uint8_t)((c*1.9607)/100);
    return c;
}
uint8_t DECENA(unsigned char c){         //se separa el bit medio significativo
    c = (uint8_t)((c*1.9607) - CENTENA(c)*100)/10;
    return c;
}

uint8_t UNIDAD(unsigned char c){         // se separa el bit menos significativo
    c = (uint8_t)((c*1.9607) - CENTENA(c)*100 - DECENA(c)*10);
    return c;
}

void LCD_PORT(char a){
    PORT = a;
}
void LCD_COM(char a){
    RS_PIN = 0;
    LCD_PORT(a);
    E_PIN = 1;
    __delay_ms(5);
    E_PIN = 0;
}
void LCD_CLEAR(void){
    LCD_PORT(0);
    LCD_PORT(1); 
}
void LCD_XY(char x, char y){
    if(x == 1)
        LCD_COM(0x80 + y);
	else if(x == 2)
        LCD_COM(0xC0 + y);
}
void LCD_INIT(void){
    LCD_PORT(0x00);
	RS_PIN = 0;
	__delay_ms(25);
	///////////// Reset process from datasheet /////////
    LCD_COM(0x30);
  __delay_ms(5);
    LCD_COM(0x30);
      __delay_ms(15);
    LCD_COM(0x30);
    /////////////////////////////////////////////////////
    LCD_COM(0x38);    //function set
    LCD_COM(0x0C);    //display on,cursor off,blink off
    LCD_COM(0x01);    //clear display
    LCD_COM(0x06);    //entry mode, set increment
}
void LCD_CHAR(char a){
    RS_PIN = 1;             // => RS = 1
    LCD_PORT(a);    //Data transfer
    E_PIN  = 1;             // => E = 1
   __delay_ms(4);
    E_PIN  = 0;
}
void LCD_STRING(char *a){
    int i;
	for(i=0;a[i]!='\0';i++)
	 LCD_CHAR(a[i]);
}
/*void LCD_RIGHT(void){
    LCD_COM(0x1C);
}
void LCD_LEFT(void){
    LCD_COM(0x18);
}*/
