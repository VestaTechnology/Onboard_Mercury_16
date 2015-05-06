/* spi.h
 *
 * Function prototypes for accessing the SPI ports on the PIC16F1947 in master
 * mode.
 */

#ifndef __SPI_H
#define __SPI_H

/* Define labels for SPI clock rate. The number at the end of the first three
 * indicates what the oscillator frequency (Fosc) will be divided by. The last
 * label indicates that the clock will be driven at 1/2 the TMR output rate.
 */
#define SPI_CLOCK_FOSC_4    0
#define SPI_CLOCK_FOSC_16   1
#define SPI_CLOCK_FOSC_64   2
#define SPI_CLOCK_FOSC_TMR2 3


/* Define labels for the different clock modes. The options are whether the
 * clock is idle in the high state or the low state, and when data transitions
 * occur - when the clock goes active to idle (A2I) or idle to active (I2A).
 */
#define SPI_MODE_LO_I2A 0x00
#define SPI_MODE_LO_A2I 0x10
#define SPI_MODE_HI_I2A 0x40
#define SPI_MODE_HI_A2I 0x50
#define SPI_MODE_IDLE_MSK 0x10
#define SPI_MODE_TRAN_MSK 0x40


/* Define labels for the information transfer specification: is data sampled
 * at the middle or the end of the data output time?
 */
#define SPI_INFO_MID 0x00
#define SPI_INFO_END 0x80
#define SPI_INFO_MSK 0x80


/* Define prototypes for the functions implemented.
 */
void OpenSPI(unsigned char clock, unsigned char mode, unsigned char info);
void WriteSPI( unsigned char value);
unsigned char ReadSPI( void );
void OpenSPI2(unsigned char clock, unsigned char mode, unsigned char info);
void WriteSPI2( unsigned char value);
unsigned char ReadSPI2( void );

#endif
