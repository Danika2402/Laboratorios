/*
 * File:   LCD.c
 * Author: HP
 *
 * Created on 19 de julio de 2023, 02:23 PM
 */

#include <stdint.h>
#include <xc.h>
#include "LCD.h"
#define _XTAL_FREQ  4000000

void LCD_INIT4(void){
    LCD_PORT = LCD_PORT & 0xf0; //limpiar puerto
    LCD_TRIS &= 0xf0;           //salidas, solo primeros 4 bits
    
    RS_TRIS = 0;                //pines como salida
    RW_TRIS = 0;
    E_TRIS = 0;
    
    RS_PIN = 0;                 //estados iniciales
    RW_PIN = 0;
    E_PIN = 0;
    
    __delay_ms(15);             //segun datasheet
    LCD_COM4(0x30);    
    __delay_ms(5);               
    LCD_COM4(0x30);
    __delay_us(100);
    LCD_COM4(0x32);
    __delay_us(100);
    
    //configuracion 4 bits
    __delay_us(100);
    LCD_COM4(0x28);
    __delay_us(100);
    LCD_COM4(0x08);
    __delay_us(100);
    LCD_COM4(0x0f);
    __delay_us(100);
    LCD_COM4(0x01);     //que incremente y no se mueva
    __delay_us(100);
    LCD_COM4(0x04);
    __delay_us(100);
    
    __delay_us(100);
    LCD_COM4(0x06);           //display
    LCD_COM4(0x0C);           //que incremente y no se mueva
    
    return;
}
void LCD_COM4(unsigned char cmd){
    LCD_PORT &= 0xf0;
    LCD_TRIS &= 0xf0;                 //modo comando
    
    LCD_PORT = LCD_PORT | ((cmd>>4)& 0x0f);
    /*  30  = 0011 0000
     * >>4  = 0000 0011
     * &0f  = 0000 1111
     * -> + significativo 3
     */
    
    RW_PIN = 0;                 //modo escritura
    RS_PIN = 0;                 //modo comando
    __delay_us(10);
    E_PIN = 1;                  //habilito LCD
    __delay_us(10);
    E_PIN = 0;                  //deshabilito LCD
    
    //-> -significativo 0
    LCD_PORT &= 0xf0;
    LCD_PORT |= cmd & 0x0f;
    
    __delay_us(10);
    E_PIN = 1;                  //habilito LCD
    __delay_us(10);
    E_PIN = 0;                  //deshabilito LCD
    
    LCD_TRIS |= 0x0f;
    
    return;
}
void LCD_XY4(unsigned char x, unsigned char y){
    if(x>0){
        LCD_COM4(0xC0 + y);
    }
    else{
        LCD_COM4(0x80 + y);
    }
    return;
    
}
void LCD_CADENA4(const char *dato){
    while(*dato){
        __delay_us(100);
        LCD_DATA4(*dato);
        dato++;
    }
    return;
}
void LCD_DATA4(char data){
    __delay_us(100);
    
    LCD_PORT &= 0xf0;
    LCD_TRIS &= 0xf0;
    
    LCD_PORT = LCD_PORT | ((data>>4) & 0x0f);
    //Configuración
    RW_PIN = 0;     //Modo Escritura
    RS_PIN = 1;     //Modo Caracter
    __delay_us(10); 
    E_PIN = 1;      //Habilita LCD
    __delay_us(10);
    E_PIN = 0;      //Deshabilita LCD
    
    LCD_PORT &= 0xf0;
    LCD_PORT |= data & 0x0f;
    
    __delay_us(10); 
    E_PIN = 1;      //Habilita LCD
    __delay_us(10);
    E_PIN = 0;      //Deshabilita LCD
    
    LCD_TRIS |= 0x0f;
    return;
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
    
    __delay_ms(16);             //segun datasheet
    LCD_COM8(0b00110000);    
    __delay_ms(5);               
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
    
    return;
}

void LCD_COM8(unsigned char dato){
    LCD_PORT = dato;
    RS_PIN = 0;                 //modo comando
    RW_PIN = 0;                 //modo escritura
    __delay_us(10);
    E_PIN = 1;                  //habilito LCD
    __delay_us(10);
    E_PIN = 0;                  //deshabilito LCD
    
    return;
}

void LCD_XY8(unsigned char x, unsigned char y){
    if(x>0){
        LCD_COM8(0xC0 + y);
    }
    else{
        LCD_COM8(0x80 + y);
    }
    return;
}

void LCD_CADENA8(const char *dato){
    while(*dato){
        __delay_us(100);
        LCD_DATA8(*dato);
        dato++;
    }
    return;
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