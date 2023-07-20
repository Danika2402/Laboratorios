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
/*
void LCD_INIT8(void){
    LCD_PORT = LCD_PORT & 0x00; //limpiar puerto
    LCD_TRIS = 0x00;            //salidas
    
    RS_TRIS = 0;                //pines como salida
    RW_TRIS = 0;
    E_TRIS = 0;
    
    RS_PIN = 0;                 //estados iniciales
    RW_PIN = 0;
    E_PIN = 0;
    
    __delay_ms(15);             //segun datasheet
    LCD_COM8(0b00110000);    
    __delay_ms(4.1);               
    LCD_COM8(0b00110000);
    __delay_us(100);
    LCD_COM8(0b00110000);
    __delay_us(100);
    
    //configuracion 8 bits
    LCD_COM8(0b00111000);
    __delay_us(100);
    LCD_COM8(0b00001000);
    __delay_us(100);
    LCD_COM8(0b00000001);
    __delay_us(100);
    LCD_COM8(0b00000100);     //que incremente y no se mueva
    __delay_us(100);
    __delay_us(100);
    LCD_COM8(0x06);           //display
    LCD_COM8(0x0C);           //que incremente y no se mueva
    
    //return;
}

void LCD_COM8(unsigned char dato){
    LCD_PORT = dato;
    RS_PIN = 0;                 //modo comando
    RW_PIN = 0;                 //modo escritura
    __delay_us(10);
    E_PIN = 1;                  //habilito LCD
    __delay_us(10);
    E_PIN = 0;                  //deshabilito LCD
    
    //return;
}

void LCD_XY8(unsigned char x, unsigned char y){
    if(x>0){
        LCD_COM8(0xC0 + y);
    }
    else{
        LCD_COM8(0x80 + y);
    }
    //return;
}

void LCD_CADENA8(const char *dato){
    while(*dato){
        __delay_us(100);
        LCD_DATA8(*dato);
        dato++;
    }
    //return;
}
void LCD_DATA8(char data){
    __delay_us(100);
    
    LCD_PORT = data;
    //Configuración
    RW_PIN = 0;     //Modo Escritura
    RS_PIN = 1;     //Modo Caracter
    __delay_us(10); 
    E_PIN = 1;      //Habilita LCD
    __delay_us(10);
    E_PIN = 0;      //Deshabilita LCD
    
    return;
}*/