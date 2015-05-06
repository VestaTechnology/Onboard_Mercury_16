/* Blinky
 *
 * File:   main.c
 * Author: Production
 *
 * Created on August 7, 2014, 12:01 PM
 * A project to blink LED1 on Mercury and print Hello Win7 to a terminal
 * via USB cable at 38400 BAUD
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "../Common/usart.h"

#pragma config FOSC = HS        // Oscillator Selection (HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config LVP = OFF        // High-voltage on MCLR/VPP must be used for programming

#define LED PORTCbits.RC3
/*
 * 
 */
int main() {
    init_comms();

    long wait;
    TRISC = 0;
    LED = 0;
    printf("%cc",0x1B);         // Reset COM Terminal
    
    while(1) {
        printf("Hello World!\r\n");
        for (wait=100000; wait>0; wait--);
        LED = !(LED);
   }

    return (EXIT_SUCCESS);
}

