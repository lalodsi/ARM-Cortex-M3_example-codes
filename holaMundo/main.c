#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Xilinx specific headers
#include "xparameters.h"
#include "xgpio.h"

// Project specific header
#include "m3_for_arty.h"
#include "gpio.h"
#include "uart.h"
#include "spi.h"

/*******************************************************************/
static XGpio Gpio_Led_DIPSw;   /* The driver instance for GPIO Device 0 */
static XGpio Gpio_RGBLed_PB;   /* The driver instance for GPIO Device 1 */
static XGpio Gpio_DAPLink;     /* The driver instance for the DAPLink GPIO */

int main (void)
{


    // Initialise the UART
    InitialiseUART();


#ifndef SIM_BUILD
    // Use Xilinx version print command
    print ("***********Avanxe 7*************\r\n");
    print ("Primer Prueba con la placa \r\n");
    print ("Use DIP switches and push buttons to\r\ncontrol LEDS\r\n");
    print (" Version 1.0\r\n");
    print ("************************************\r\n");
#else
    print ( debugStr );
#endif

    // Main loop.  Handle LEDs and switches via interrupt
    while ( 1 )
    {
        /* Main loop. Wait for interrupts to occur */
        if ( CheckUARTRxBytes() != 0 )
            print ("x");

        volatile uint32_t gpio_dip_switches;

        // Read dip switches, change LEDs to match
        gpio_dip_switches = XGpio_DiscreteRead(&Gpio_Led_DIPSw, ARTY_A7_DIP_CHANNEL);   // Capture DIP status
        XGpio_DiscreteWrite(&Gpio_Led_DIPSw, ARTY_A7_LED_CHANNEL, gpio_dip_switches);   // Set LEDs Mitad derecha 0*AAAAAAAA
        XGpio_DiscreteWrite(&Gpio_Led_DIPSw, ARTY_A7_LED_CHANNEL, gpio_dip_switches); //YO
    
        // Clear interrupt from GPIO
        XGpio_InterruptClear(&Gpio_Led_DIPSw, XGPIO_IR_MASK);
        // Clear interrupt in NVIC
        NVIC_ClearPendingIRQ(GPIO0_IRQn);

  }
}

