/* DAC test
 *
 * Generates a sawtooth waveform on the DACOUT pin (J6.8)
 */

#include <xc.h>
#include <stdio.h>
#include "..\common\usart.h"

#pragma config FOSC = HS        // Oscillator Selection (HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config LVP = OFF        // High-voltage on MCLR/VPP must be used for programming

void main (void)
{
	int x;

	// Configure DAC: Enabled, positive reference in Low-Power state,
	// DAC voltage on DACOUT pin, positive source is Vdd, negative
	// source is Vss.
	DACCON0 = 0xE0;
	for (;;)
	{
		// Generate a sawtooth waveform
		for (x = 0; x < 32; x++)
		{
			DACCON1 = x;
		}
		for (x = 31; x >= 0; x--)
		{
			DACCON1 = x;
		}
	}
}
