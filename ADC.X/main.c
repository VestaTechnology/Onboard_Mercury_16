/* Simple demonstration of ADC use on Mercury16 (PIC16F1947).
 *
 * This application performs continuous conversions and displays of some of the
 * analog channels.
 */

#include <xc.h>
#include <stdio.h>
#include "..\Common\usart.h"
#include "adc.h"

#pragma config FOSC = HS        // Oscillator Selection (HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config LVP = OFF        // High-voltage on MCLR/VPP must be used for programming

/* Main portion of the application.
 * Initialize the board, then continuously display conversion results for the
 * first four channels.
 */
void main()
{
	int result, channel;

	/* Initialize the I/O modules we will be using.
	 */
	init_comms();
        printf("we made it this far");
	init_adc();

	channel = 0;
	while (1)
	{
		result = convert(channel);
		printf("%i\t", result);
		channel = (channel + 1) & 3;
		if (channel == 0) printf("\r\n");
	}
}