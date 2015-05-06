/* ADC.C
 * Simple interface to A/D on PIC16F1947.
 * Not generic; specific to example app.
 */

#include <xc.h>

/* Initialize the module (or, at least the part we'll be using.
 */
void init_adc()
{
	TRISA  = 0x0F;		// Set A.0-3 as input
	ANSELA = 0x0F;		// A.0-3 configured as analog
	ADCON1 = 0xC0;		// Right-justified, Fosc/4, Vdd+, Vss-
}


/* Produce a conversion result on the specified channel.
 */
int convert(int channel)
{
	int result;

	// Set channel and turn A/D module on
	ADCON0 = (channel << 2) | 1;
	for (result = 0; result < 250; result++)
		;			// Minor delay for setup
	ADGO = 1;		// Start conversion
	while (ADGO)
		continue;	// Wait for done
	result = ADRES;
	return result;
}

