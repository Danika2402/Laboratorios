/*
 * File:   MAIN_M.c
 * Author: HP
 *
 * Created on 2 de agosto de 2023, 03:00 PM
 */
//*****************************************************************************
/* Electronica Digital 2 - 2023
 * Laboratorio 4 - I2C MASTER
 * 
 * 
 * 
 * FUNCION: 
*/
//******************************************************************************
#pragma config  FOSC    = INTRC_NOCLKOUT
#pragma config  WDTE    = OFF
#pragma config  PWRTE   = OFF
#pragma config  MCLRE   = OFF
#pragma config  CP      = OFF
#pragma config  CPD     = OFF
#pragma config  BOREN   = OFF
#pragma config  IESO    = OFF
#pragma config  FCMEN   = OFF
#pragma config  LVP     = OFF

#pragma config  BOR4V   = BOR40V
#pragma config  WRT     = OFF

#include <stdint.h>
#include <xc.h>
#include "LCD.h"
#include "I2CM.h"

#define PUSH1 RB0
#define PUSH2 RB1
#define _XTAL_FREQ  8000000

void setup(void);
uint8_t POT;
uint8_t unidad, decena,centena;

uint8_t seg,min,hora;
uint8_t dia,mes,year;

uint8_t select,parametro,p;

void RTC_PRINT(uint8_t Val);
void CONFIGURAR(char x, char y);
unsigned short RTC_READ(unsigned I2C,unsigned d);
void RTC_WRITE(unsigned I2C,unsigned d,char parametro);

uint8_t DECIMAL_BCD(uint8_t num);
uint8_t BCD_DECIMAL(uint8_t num);

void Parpadeo(void);

void __interrupt() isr(void){
    if (INTCONbits.RBIF==1){               //Interrupciones de botones en PORTB con PULL UP
        if (PUSH1==0){
            select++;
            PORTA++;
            __delay_ms(10);
        } else if (PUSH2==0){     //RB1 decrementa PORTA
            if(select != 0)
                parametro++;
        }
        if(select >5)
            select = 0;
        
        if(select == 1 && parametro >23){       //horas
            parametro = 0;
        }else if(select == 2 && parametro >59){ //minutos
            parametro = 0;
        }else if(select == 3 && parametro >12){ //meses
            parametro = 1;
        }else if(select == 4 && parametro >99){ //años
            parametro = 0;
        }
        INTCONbits.RBIF=0;
    }
}

void main(void) {
    setup();
    while(1){
        
        I2C_Master_Start();
        I2C_Master_Write(0x81);
        POT = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(10);
       
        if(select !=0){
            
            if(select == 1){
                if(!PUSH1){
                    parametro = BCD_DECIMAL(hora);
                    __delay_ms(10);
                }
                hora = DECIMAL_BCD(parametro);
                CONFIGURAR(1,8);
            }
            if(select == 2){
                if(!PUSH1){
                    parametro = BCD_DECIMAL(min);
                    __delay_ms(10);
                }
                min = DECIMAL_BCD(parametro);
                CONFIGURAR(1,11);
            }
            if(select == 3){
                if(!PUSH1){
                    parametro = BCD_DECIMAL(mes);
                    __delay_ms(10);
                }
                mes = DECIMAL_BCD(parametro);
                CONFIGURAR(2,9);
            }
            if(select == 4){
                if(!PUSH1){
                    parametro = BCD_DECIMAL(year);
                    __delay_ms(10);
                }
                year = DECIMAL_BCD(parametro);
                CONFIGURAR(2,14);
            }
            
            if(select == 5){
                RTC_WRITE(0xD0,0x02,hora);
                RTC_WRITE(0xD0,0x01,min);
                RTC_WRITE(0xD0,0x05,mes);
                RTC_WRITE(0xD0,0x06,year);
                RTC_WRITE(0xD0,0x00,0x00);
                select = 0;
            }
            
            
        }else {
        
        seg = RTC_READ(0xD0,0x00);
        min = RTC_READ(0xD0,0x01);
        hora = RTC_READ(0xD0,0x02);
        dia = RTC_READ(0xD0,0x04);
        mes = RTC_READ(0xD0,0x05);
        year = RTC_READ(0xD0,0x06); 
        }
        //LCD******************************************************************
        centena = CENTENA(POT);     //Aqui separamos el valor para poder
        decena = DECENA(POT);       //imprimirlos despues
        unidad = UNIDAD(POT);
       
        centena += '0';              //por ser idioma ASCII 48 significa 0
        decena += '0';               //de esta forma obtenemos numeros y no palabras
        unidad += '0';
        
        //POTENCIOMETRO
        LCD_CLEAR();               //aqui imprimimos para el LCD
        LCD_XY(1,0);
        LCD_STRING("S1:");
        LCD_XY(2,0);
        LCD_CHAR(centena);
        LCD_STRING(".");
        LCD_CHAR(decena);
        LCD_CHAR(unidad);
        
        //HORAS
        LCD_XY(1,8);
        RTC_PRINT(hora);
        LCD_STRING(":");
        
        //MINUTOS
        RTC_PRINT(min);
        LCD_STRING(":");
        
        //SEGUNDOS
        RTC_PRINT(seg);
        
        //DIA
        LCD_XY(2,6);
        RTC_PRINT(dia);
        LCD_STRING("/");
                
        //MES
        RTC_PRINT(mes);
        LCD_STRING("/");
        
        //AÑO
        LCD_STRING("20");
        RTC_PRINT(year);
    }
    return;
}

void setup(void){
    //oscilador a 8M Hz
    OSCILLATOR(1);
    
    
    ANSEL = 0x00;
    ANSELH = 0x00;

    TRISD = 0x00;
    PORTD = 0x00;
    TRISE = 0x00;
    PORTE = 0x00;
    
    TRISB = 0b00000011;     //RB1 y RB0 entradas
    PORTB = 0x00;
    
    PORTA = 0x00;
    TRISA = 0x00;
    
    //Config. PULL UP
    IOC_INT(0b00000011);     //pines 1 y 2 se realizaran la interrupcion
    
    POT = 0;
    unidad = 0;
    decena = 0;
    centena = 0;
    
    seg = 0;
    min = 0;
    hora=0 ;
    dia = 0;
    mes = 0;
    year=0;

    LCD_INIT();
    I2C_Master_Init(100000);        // Inicializar Comuncación I2C
    
}

void RTC_PRINT (uint8_t Val){
    char s10,s;
    
    s10 = (uint8_t)((Val >>4)) + '0';
    s = (uint8_t)((Val & 0x0f)) + '0';
    
    LCD_CHAR(s10);
    LCD_CHAR(s);

}

unsigned short RTC_READ(unsigned I2C,unsigned d){
    unsigned short RTC;
    
    I2C_Master_Start();
    I2C_Master_Write(I2C);
    I2C_Master_Write(d);
    I2C_Master_Stop();
    __delay_ms(10);
       
    I2C_Master_Start();
    I2C_Master_Write(I2C + 0x01);
    RTC = I2C_Master_Read(0);
    I2C_Master_Stop();
    __delay_ms(10);

    return RTC;
}

void CONFIGURAR(char x, char y){
    LCD_XY(x,y);
    LCD_STRING("  ");
    Parpadeo();
}

void Parpadeo(void){
    uint8_t j = 0;
    while(j>100 && PUSH1 && PUSH2){
        j++;
        __delay_ms(50);
    }
}


uint8_t DECIMAL_BCD(uint8_t num){
    return (((num/10)<<4) + (num % 10));
}

uint8_t BCD_DECIMAL(uint8_t num){
    return ((num >> 4)*10 + (num & 0x0f));
}


void RTC_WRITE(unsigned I2C,unsigned d,char parametro){
    
    I2C_Master_Start();
    I2C_Master_Write(I2C);
    I2C_Master_Write(d);
    I2C_Master_Write(parametro);
    I2C_Master_Stop();
    __delay_ms(20);
    
}
 