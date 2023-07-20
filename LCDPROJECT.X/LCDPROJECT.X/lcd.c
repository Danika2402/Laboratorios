/*
 * File:   main.c
 * Author: https://microdigisoft.com
 *
 * Created on 9 August, 2020, 5:11 PM
 */
#include < xc.h >
#include "LCD.h"
#define _XTAL_FREQ  20000000UL      //  20MHz

// CONFIG1
#pragma config FOSC = HS      // Oscillator Selection (HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable bit (VCAP pin function disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = OFF         // Low-Voltage Programming Enable (Low-voltage programming enabled)

/*
 *
 */
void Init_LCD(void)
{
    /*  making Pins as output   */
    PORTCbits.RC7  = 0;  //  Enable pin of LCD 
    PORTCbits.RC6  = 0;  //  RS pin of LCD 
    PORTD     = 0;       //  DATA pin FOR LCD 8bits  port D as output   
    TRISD   = 0;         // Direction for Port D
    TRISCbits.TRISC7    = 0;//Direction for Port C bit 7 EN
    TRISCbits.TRISC6       = 0; // Direction for Port C 6 Rs Pin
   __delay_ms(10);          /*  10ms delay   */
   /*   writing commands for initialization of LCD  */
   Lcd_Cmd(0x38);  //  Functions Set as Given in Datasheet 
   Lcd_Cmd(0x0F);  //  Display ON; Cursor ON; Blink ON     
   Lcd_Cmd(0x06);  //  Display Shifting OFF                
   Lcd_Clear();   //  Clear Display                       
}   



void Lcd_Clear(void)
{
    Lcd_Cmd(0x01);         //  Clear Screen command    
    __delay_ms(3);                                           
}

void Lcd_Port(void)
{
  // toggling Enable PIN is must for data to be displayed on screen
    PORTCbits.RC7 = 1;
    __delay_us(200);
    PORTCbits.RC7 = 0;
    __delay_us(200);
}



void Lcd_Cmd(unsigned char Cmd)
{
    PORTCbits.RC6   = 0;        // For command RS must be low (0)     
    PORTD  = Cmd;      //  write Command to data pins of LCD    

    Lcd_Port();
}



void Lcd_Write_Char(unsigned char Data)
{
    PORTCbits.RC6  = 1;        //  For data RS must be high (1)    
    PORTD = Data;     //  write data to data bus of LCD   
    Lcd_Port();
}

void Lcd_Write_String(const char *String)
{
    while(*String)
    {
        Lcd_Write_Char(*String++);   // Display data until string ends 
    }
}



unsigned char Lcd_Set_Cursor(unsigned char Address)
{
    //  valid addresses are for line one 0x80 and line two are 0xC0   
    if ((Address >= 0x80 && Address <= 0xA8) || (Address >= 0xC0 && Address <= 0xE8))
    {
       Lcd_Cmd(Address);
        return 1;
    }
    else
        return 0;
}

int main() {

    Init_LCD(); // start LCD 

    while(1)
    {
        Lcd_Clear();
        __delay_ms(100);           
        Lcd_Set_Cursor(0x80);
        Lcd_Write_String("  Welcome  ");
        Lcd_Set_Cursor(0xC0);
        Lcd_Write_String(" Microdigisoft ");
        __delay_ms(500);           //  1 Second Delay.
    }
    return 0;           
}

