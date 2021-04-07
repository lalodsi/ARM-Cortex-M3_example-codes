#include <stdio.h>// C headers
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "xparameters.h"// Xilinx specific headers
#include "xgpio.h"
#include "m3_for_arty.h"// Project specific header
#include "gpio.h"

int main(){
    int i;
    char dataStr[256];

        print("\r\n\t***************************************");
        print("\r\n\tAvanxe 7: Intercambio de información a través de UART");
        print("Ingresa en la terminal un numero de 0 a 255: \r\n\t\t\a")
        i = XUartLite_RecvByte(STDIN_BASEADDRESS);
        sprintf(dataStr, "\r\n\t\t El número ingresado es: %i \r\n", i);
        print(dataStr);
        print("\r\n\t****************Programa Terminado*****************\r\n");

    return 0;
}