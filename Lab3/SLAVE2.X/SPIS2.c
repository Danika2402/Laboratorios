/*
 * File:   SPIS2.c
 * Author: HP
 *
 * Created on 27 de julio de 2023, 01:09 PM
 */

#include <stdint.h>
#include <xc.h>
#include "SPIS2.h"
#define _XTAL_FREQ  8000000

void spiInit(Spi_Type sType, Spi_Data_Sample sDataSample, Spi_Clock_Idle sClockIdle, Spi_Transmit_Edge sTransmitEdge)
{
    TRISC5 = 0;
    if(sType & 0b00000100) //If Slave Mode
    {
        SSPSTAT = sTransmitEdge;
        TRISC3 = 1;
    }
    else              //If Master Mode
    {
        SSPSTAT = sDataSample | sTransmitEdge;
        TRISC3 = 0;
    }
    
    SSPCON = sType | sClockIdle;
}

/*static void spiReceiveWait()
{
    while ( !SSPSTATbits.BF ); // Wait for Data Receive complete
}*/

void spiWrite(char dat)  //Write data to SPI bus
{
    SSPBUF = dat;
}

/*unsigned spiDataReady(void) //Check whether the data is ready to read
{
    if(SSPSTATbits.BF)
        return 1;
    else
        return 0;
}*/

/*char spiRead(void) //REad the received data
{
    spiReceiveWait();        // wait until the all bits receive
    return(SSPBUF); // read the received data from the buffer
}*/