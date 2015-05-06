/* fram.h
 *
 * This file contains definitions used by the FRAM access routines (EEPROM
 * equivalent device) on the Mercury board.
 */

#ifndef __FRAM_H
#define __FRAM_H

/* Define the command set for the FRAM device.
 */
#define EE_WRSR  1
#define EE_WRITE 2
#define EE_READ  3
#define EE_WRDI  4
#define EE_RDSR  5
#define EE_WREN  6

/* Define the status register bits
 */
#define WEL  1
#define BP0  2
#define BP1  3
#define WPEN 7

/* The FRAM is on SSP2. Chip select is active-low.
 * Port D, bit 2 goes to the WP* pin.
 * Port D, bit 3 goes to the HOLD* pin.
 * Port D, bit 7 is the chip select line.
 */
#define EE_WP PORTDbits.RD2
#define EE_HOLD PORTDbits.RD3
#define EE_SELECT PORTDbits.RD7
#define EE_ACTIVE 0
#define EE_IDLE 1


/* Function prototypes
 */
void init_SSP2( void );
void write_FRAM_byte( unsigned char value );
unsigned char read_FRAM_byte( void );
void start_FRAM_write( int address );
void send_FRAM_command( unsigned char command );
void start_FRAM_read( int address );

#endif
