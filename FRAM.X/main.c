/* FRAM test
 */

#include <xc.h>
#include <stdio.h>
#include "..\Common\usart.h"
#include "fram.h"

#pragma config FOSC = HS        // Oscillator Selection (HS Oscillator, High-speed crystal/resonator connected between OSC1 and OSC2 pins)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config LVP = OFF        // High-voltage on MCLR/VPP must be used for programming

/* A place to hold the values. The size of the array is arbitrary.
 */
unsigned char values[10];


/* Here is the code for the application itself.
 */
void main( void )
{
	int reg;
	unsigned char value, x;

	init_comms();						/* Initialize serial communications */
	init_SSP2();						/* Initialize the synchronous serial port */
        printf("%cc",0x1B);                                     /* Reset COM Terminal */

	/* The test involves modifying the first 10 bytes of the FRAM and reading them back
	 * to verify the write. Because we don't want to write the same data all the time,
	 * we'll use the variable 'x' to contain a value that will be added to the register
	 * address to produce the data value that is to be written to a register during
	 * each write cycle.
	 */
	x = 0;
	for (;;)
	{
		/* The general format of a read is:
		 * 1) start the READ transaction at a particular register address,
		 * 2) read one or more consecutive registers, and
		 * 3) close the transaction.
		 *
		 * We could have read each register in a separate transaction, but
		 * we do them in a single transaction to show that it can be done.
		 */
		start_FRAM_read(0);
		for (reg = 0; reg < 10; reg++)
		{
			values[reg] = read_FRAM_byte();
		}
		EE_SELECT = EE_IDLE;

		/* Now that the registers have been read, print their values.
		 */
		for (reg = 0; reg < 10; reg++)
		{
			printf("%02x   ", values[reg]);
		}
		printf("\r\n");

		/* Now write new values into the registers. As with the read transaction,
		 * we do the writes in a single transaction rather than separate writes
		 * for each read. Note that the call to enable writes must be performed
		 * prior to each write transaction.
		 */
		send_FRAM_command(EE_WREN);
		start_FRAM_write(0);
		for (reg = 0; reg < 10; reg++)
		{
			write_FRAM_byte(reg + x);
		}
		EE_SELECT = EE_IDLE;

		/* Bump the base value prior to the next set of writes.
		 */
		x++;
	}
}