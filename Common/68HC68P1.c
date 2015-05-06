#include <xc.h>
#include "68HC68P1.h"
#include "spi.h"

/* VAST Addressing using the bottom 4 bits of Port D compared 
 * with the equalizer on board.
 */
void set_Vaddress(char add)
{
	/* The OR 0x80 ensures EEPROM CS isn't enabled while using 
	 * VAST address. */
	PORTD = add | 0x80; 
}

/* Initializes vast communication on Port D with SPI I/O at
 * Port Number dependent on address jumpers.  Port value can be found
 * in Vesta Basic Manual under RLYOPTO Address Jumpers Port column.
 */
void init_V4RLYOPTO(char port)
{
	char dummy;
	TRISD = 0x70; //make the 4 lowest bits outputs for VA0-3
	set_Vaddress(NULL_ADDRESS);
	OpenSPI2(SPI_CLOCK_FOSC_64,SPI_MODE_HI_I2A,SPI_INFO_END);
	set_Vaddress((port & 0x3C) >> 2); //enable passed VAST address
	/* Control byte; passing data to direction register. */ 
	WriteSPI2((port<<6)|IO_DIRECTION|IO_WRITE|FORMAT_DATA|0);
	dummy = ReadSPI2();
	/* Set D7-D4 outputs, D3-D0 inputs */
	WriteSPI2(0xF0); 
	dummy = ReadSPI2();
	set_Vaddress(NULL_ADDRESS); //disable passed VAST address
}

/* Initializes vast communication on Port D with V8OPTORLY at a
 * Port dependent on address jumpers.  Pass either the Opto Port 
 * or the Relay Port for the jumper configuration.  Port values 
 * can be found in Vesta Basic Manual under RLYOPTO Address 
 * Jumpers Port column.
 */
void init_V8RLYOPTO(char port)
{
	port &= 0xFE; //make port start with opto port number
	char dummy;
	TRISD = 0x70; //make the 4 lowest bits outputs for VA0-3
	set_Vaddress(NULL_ADDRESS);
	OpenSPI2(SPI_CLOCK_FOSC_64,SPI_MODE_HI_I2A,SPI_INFO_END);
	set_Vaddress((port & 0x3C) >> 2); //enable passed VAST address

	/* Initialize the SPI I/O port connected to the opto isolated
	 * inputs as inputs. Control byte; passing data to direction 
	 * register. */ 
	WriteSPI2((port<<6)|IO_DIRECTION|IO_WRITE|FORMAT_DATA|0);
	dummy = ReadSPI2();
	WriteSPI2(0); //Set pins as inputs.
	dummy = ReadSPI2();

	set_Vaddress(NULL_ADDRESS); //disable passed VAST address
	port += 1; //make port relay port number 
	set_Vaddress((port & 0x3C) >> 2); //enable passed VAST address

	/* Initialize the SPI I/O port connected to the relays as 
	 * ouputs. Control byte; passing data to direction register. */
	WriteSPI2((port<<6)|IO_DIRECTION|IO_WRITE|FORMAT_DATA|0);
	dummy = ReadSPI2();
	WriteSPI2(0xFF); //Set pins as outputs.
	dummy = ReadSPI2();

	set_Vaddress(NULL_ADDRESS); //disable passed VAST address
}

/* Sets the relay address passed as num.  The first WriteSPI2 is the
 * control byte, the second is the set if 1 mask. num variable is 
 * used to get the VAST address, the chip ID bits, and make the mask 
 * to set a single relay.
 */
void VSET(short num)
{
	char vaddr, dummy;
	vaddr = (num & 0x01FF) >> 5;
	set_Vaddress(vaddr); //enable passed VAST address
	/* 8-bit I/O Control byte to apply mask to data register. */
	WriteSPI2(((num&0x0018)<<3)|IO_DATA|IO_WRITE|FORMAT_1_MASK|0);
	dummy = ReadSPI2();
	/* A mask with only one bit set */
	WriteSPI2(1 << (num &0x0007)); //shift a bit according to the rly address
	dummy = ReadSPI2();
	set_Vaddress(NULL_ADDRESS); //disable passed VAST address
}

/* Clears the relay address passed as num.  The first WriteSPI2 is the
 * control byte, the second is the clear if 1 mask.  num variable is 
 * used to get the VAST address, the chip ID bits, and make the mask 
 * to clear a specific relay.
 */
void VRESET(short num)
{
	char vaddr, dummy;
	vaddr = (num & 0x01FF) >> 5;
	set_Vaddress(vaddr); //enable passed VAST address
	/* 8-bit I/O Control byte to apply mask to data register. */
	WriteSPI2(((num&0x0018)<<3)|IO_DATA|IO_WRITE|FORMAT_0_MASK|0);
	dummy = ReadSPI2();
	/* A mask with only one bit set */
	WriteSPI2(1 << (num &0x0007)); //shift a bit according to the rly address
	dummy = ReadSPI2();
	set_Vaddress(NULL_ADDRESS); //disable passed VAST address
}

/* Reads one bit from the SPI I/O.  The first WriteSPI2 is the control byte to 
 * tell the SPI I/O we're reading from it, the second is arbitrary
 * since we're reading. num variable is used to get the VAST address, 
 * the the chip ID bits, and as a mask for the returned value.
 */
char VTEST(short num)
{
	char vaddr, result;
	vaddr = (num & 0x01FF) >> 5;
	set_Vaddress(vaddr); //enable passed VAST address
	WriteSPI2(((num&0x0018)<<3)|IO_DATA|IO_READ|0);
	result = ReadSPI2();
	WriteSPI2(0x00); //write XX, doesn't matter what
	result = ReadSPI2();
	set_Vaddress(NULL_ADDRESS); //disable passed VAST address
	/* Store the value of the opto input in result */
	if (result & (1 << (num & 7)))    result = 1;
	else    result = 0;
	return result;
}

/* Reads an SPI I/O at port.  The first WriteSPI2, the control byte, 
 * tells the SPI I/O we're reading from it, the second is arbitrary
 * since we're reading. port variable is used to get the VAST address, 
 * and the the chip ID bits of the SPI I/O you want to read from.
 */
char VINP(char port)
{
	char vaddr, result;
	vaddr = ((port & 0x3C) >> 2);
	set_Vaddress(vaddr); //enable passed VAST address
	/* I/O Control byte, read from the data register. */
	WriteSPI2(((port&0x03)<<6)|IO_DATA|IO_READ|0);
	result = ReadSPI2();
	WriteSPI2(0x00); //write XX, doesn't matter what
	result = ReadSPI2();
	set_Vaddress(NULL_ADDRESS); //disable passed VAST address
	return result;
}

/* Writes a byte, passed as bite, to the SPI I/O specified by prt.
 * The first WriteSPI2 is the control byte, the second transfers 
 * the data.  prt is used to get the VAST address and the chip
 * ID bits.  bite holds the bit pattern you want set at the output 
 * of the SPI I/O.
 */
void VOUT(char port, char bite)
{
	char vaddr, dummy;
	vaddr = ((port & 0x3C) >> 2);
	set_Vaddress(vaddr); //enable passed VAST address
	/* I/O Control byte, write a byte to the data register. */
	WriteSPI2(((port&0x03)<<6)|IO_DATA|IO_WRITE|FORMAT_DATA|0);
	dummy = ReadSPI2();
	/* Pass bite as the data byte */
	WriteSPI2(bite);
	dummy = ReadSPI2();
	set_Vaddress(NULL_ADDRESS); //disable passed VAST address
}