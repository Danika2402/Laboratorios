/*
 * File:   LCD.h
 * Author: https://microdigisoft.com
 *
 * Created on 9 August, 2020, 5:11 PM
 */
 

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif
#define FirstLine   0x80
#define SecondLine  0xC0

/*----------------------------------------------------------------------------*/

    /*  Functions for LCD   */

    void Init_LCD(void);
    void Lcd_Clear(void);
    void Lcd_Port(void);
    void Lcd_Cmd(unsigned char Cmd);
    void Lcd_Write_Char(unsigned char Data);
    void Lcd_Write_String(const char *String);
    unsigned char Lcd_Set_Cursor(unsigned char Address);
#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

      
