/*
 * File:   LCD.c
 * Author: HP
 *
 * Created on 19 de julio de 2023, 02:23 PM
 */

#include <stdint.h>
#include <xc.h>
#include "LCD.h"
#define _XTAL_FREQ  8000000

void LCD_PORT8(char a){
    LCD_PORT = a;
}
void LCD_COM8(char a){
    RS_PIN = 0;
    LCD_PORT8(a);
    E_PIN = 1;
    __delay_ms(5);
    E_PIN = 0;
}
void LCD_CLEAR8(void){
    LCD_PORT8(0);
    LCD_PORT8(1); 
}
void LCD_XY8(char x, char y){
    if(x == 1)
	  LCD_COM8(0x80 + y);
	else if(x == 2)
		LCD_COM8(0xC0 + y);
}
void LCD_INIT8(void){
    LCD_PORT8(0x00);
	RS_PIN = 0;
	__delay_ms(25);
	///////////// Reset process from datasheet /////////
    LCD_COM8(0x30);
  __delay_ms(5);
    LCD_COM8(0x30);
      __delay_ms(15);
    LCD_COM8(0x30);
    /////////////////////////////////////////////////////
    LCD_COM8(0x38);    //function set
    LCD_COM8(0x0C);    //display on,cursor off,blink off
    LCD_COM8(0x01);    //clear display
    LCD_COM8(0x06);    //entry mode, set increment
}
void LCD_CHAR8(char a){
    RS_PIN = 1;             // => RS = 1
    LCD_PORT8(a);    //Data transfer
    E_PIN  = 1;             // => E = 1
   __delay_ms(4);
    E_PIN  = 0;
}
void LCD_STRING8(char *a){
    int i;
	for(i=0;a[i]!='\0';i++)
	 LCD_CHAR8(a[i]);
}
void LCD_RIGHT8(void){
    LCD_COM8(0x1C);
}
void LCD_LEFT8(void){
    LCD_COM8(0x18);
}
/*
void LCD_PORT4(char a){
    if (a & 1)
        D4 = 1;
    else
        D4 = 0;

    if (a & 2)
        D5 = 1;
    else
        D5 = 0;

    if (a & 4)
        D6 = 1;
    else
        D6 = 0;

    if (a & 8)
        D7 = 1;
    else
        D7 = 0;
}
void LCD_COM4(char a){
    RS_PIN = 0;
    LCD_PORT4(a);
    E_PIN = 1;
    __delay_ms(4);
    E_PIN = 0;
}
void LCD_CLEAR4(void){
    LCD_PORT4(0);
    LCD_PORT4(1);    
}

void LCD_XY4(char x, char y){
    char temp,z,q;
    if(x == 1){
        temp = 0x80 + y - 1;
        z = temp >> 4;
        q = temp & 0x0F;
        LCD_COM4(z);
        LCD_COM4(q);
    }else if (x == 2){
        temp = 0xC0 + y - 1;
        z = temp >> 4;
        q = temp & 0x0F;
        LCD_COM4(z);
        LCD_COM4(q);
    }
}
void LCD_INIT4(void){
    LCD_PORT4(0x00);
    __delay_ms(20);
    LCD_COM4(0x03);
    __delay_ms(5);
    LCD_COM4(0x03);
    __delay_ms(11);
    LCD_COM4(0x03);
    /////////////////////////////////////////////////////
    LCD_COM4(0x02);
    LCD_COM4(0x02);
    LCD_COM4(0x08);
    LCD_COM4(0x00);
    LCD_COM4(0x0C);
    LCD_COM4(0x00);
    LCD_COM4(0x06);
}
void LCD_CHAR4(char a){
    char temp, y;
    temp = a & 0x0F;
    y = a & 0xF0;
    RS_PIN = 1; // => RS = 1
    LCD_PORT4(y >> 4); //Data transfer
    E_PIN = 1;
    __delay_us(40);
    E_PIN = 0;
    LCD_PORT4(temp);
    E_PIN = 1;
    __delay_us(40);
    E_PIN = 0;
}
void LCD_STRING4(char *a){
    int i;
    for (i = 0; a[i] != '\0'; i++)
        LCD_CHAR4(a[i]);
}
void LCD_RIGHT4(void){
    LCD_COM4(0x01);
    LCD_COM4(0x0C);
}
void LCD_LEFT4(void){
    LCD_COM4(0x01);
    LCD_COM4(0x08);
}
*/