/* fram.c
 *
 * This file contains the routines that provide access to the FM25W256 FRAM
 * (EEPROM equivalent device) on the Mercury board.
 */

#include <xc.h>
#include "fram.h"
#include "../common/spi.h"


/* Initialize the SSP2 channel
 */
void init_SSP2( void )
{
	OpenSPI2(SPI_CLOCK_FOSC_4, SPI_MODE_LO_A2I, SPI_INFO_MID);
	TRISD &= 0x73;		/* RD7, RD3, and RD2 are control signals for FRAM */
}


/* Send one byte via the SSP2 port.
 * We don't use the WriteSPI2 routine because we want to wait until the write
 * has completed.
 */
void write_FRAM_byte( unsigned char value )
{
	SSP2BUF = value;
	while (!PIR4bits.SSP2IF)
		;
	PIR4bits.SSP2IF = 0;
}


/* Receive one byte via the SSP2 port.
 * We don't use the ReadSPI2 routine because we need to perform a dummy write
 * not related to the last actual write.
 */
unsigned char read_FRAM_byte()
{
	unsigned char result;

	write_FRAM_byte(0xFF);		/* Send a dummy byte */
	result = SSP2BUF;			/* Get the return value */
	return result;
}


/* Open a write transaction at a specified register address.
 */
void start_FRAM_write( int address )
{
	EE_HOLD = EE_IDLE;
	EE_WP = EE_IDLE;
	EE_SELECT = EE_ACTIVE;
	write_FRAM_byte(EE_WRITE);			/* Tell the chip we're writing to it */
	write_FRAM_byte(address >> 8);		/* Send high byte of address */
	write_FRAM_byte(address & 0xFF);	/* Send low byte of address */
}


/* Send a single-byte command to the FRAM.
 */
void send_FRAM_command( unsigned char command )
{
	EE_SELECT = EE_ACTIVE;
	write_FRAM_byte(command);
	EE_SELECT = EE_IDLE;
}


/* Open a read transaction at the specified register address.
 */
void start_FRAM_read( int address )
{
	EE_SELECT = EE_ACTIVE;
	write_FRAM_byte(EE_READ);			/* Tell the chip we're reading from it */
	write_FRAM_byte(address >> 8);		/* Send high byte of address */
	write_FRAM_byte(address & 0xFF);	/* Send low byte of address */
}


