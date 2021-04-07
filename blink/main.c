#include <stdio.h>// C headers
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "xparameters.h"// Xilinx specific headers
#include "xgpio.h"
#include "m3_for_arty.h"// Project specific header
#include "gpio.h"

static XGpio Gpio_Led_DIPSw;
volatile uint32_t msTicks;

void SysTick_Handler (void){
    msTicks++;
}
void Delay(uint32_t dlyTicks){
    uint32_t curTicks;
    curTicks = msTicks;
    while ((msTicks - curTicks) < dlyTicks);
}
int main(){
    //Inicialización de leds
    XGpio_Initialize(&Gpio_Led_DIPSw, XPAR_AXI_GPIO_0_DEVICE_ID);
    XGpio_SetDataDirection(&Gpio_Led_DIPSw, ARTY_A7_LED_CHANNEL, 0xFFFFFFF0);//set como salida
    SysTick_Config(SystemCoreClock/1000); // 'prescaler' of SysTick for 1 ms
    print ("\r\n\t************************************\r\n");
    print ("Ejemplo de diseno tarjeta de desarrollo AVANXE 7 de INTESC\r\n");
    print ("\t Uso de GPIOs, parpadeo de LED \r\n\t\t ver 1.2.6\r\n");
    while(1)//bucle infinito
    {
        XGpio_DiscreteWrite(&Gpio_Led_DIPSw, ARTY_A7_LED_CHANNEL,0x1);//enciende led L14
        Delay(150); //retardo 150 milisegundos
        XGpio_DiscreteWrite(&Gpio_Led_DIPSw, ARTY_A7_LED_CHANNEL, 0x0);//apaga led L14
        Delay(150);//retardo 150 milisegundos
    }
    return 0;
}
