/* 68HC68P1.h
 * 
 * Function prototypes and definitions for controling the V4RLYOPTO 
 * and V8RLYOPTO. To communicate with the 68HC68P1 on board send 
 * a control byte and a data byte.  The definitions in this file 
 * are used to generate the command byte.
 */

#ifndef __68HC68P1_H
#define __68HC68P1_H

/* Define the null address where no VAST periphial is enabled.
 */
#define NULL_ADDRESS 0x0F

/* Define labels for register select on SPI I/O port.  Data
 * writes data to the port and Direction allows you to configure
 * input or output.
 */
#define IO_DATA 		(0<<5)
#define IO_DIRECTION	(1<<5)

/* Define labels to read or write with the SPI I/O port.
 * Read when data is being transfered from the SPI I/O.
 * Write when the SPI I/O is receiving data.
 */
#define IO_READ		(0<<4)
#define IO_WRITE	(1<<4)

/* Defines labels for Data Format.  Format Data writes the data
 * byte following the control byte to selected register. 0 mask
 * causes the 1 bits in the data byte to clear the corresponding
 * register flip-flops.  1 mask sets the corresponding flip-flops.
 */
#define FORMAT_DATA		(0<<2)
#define FORMAT_0_MASK	(2<<2)
#define FORMAT_1_MASK	(3<<2)

/* Defines labels for Compare Function.  Compare Function is used
 * when I/O pins are inputs. As outputs the compare flag (LSB of 
 * MISO control byte) is always set. O looks for at least 1 non-
 * match between port and data byte. 1 looks for all match, 2 for
 * all non-match and 3 for at least 1 match.
 */
#define COMP_1_NoMATCH		0
#define COMP_ALL_MATCH		1
#define COMP_ALL_NoMATCH	2
#define COMP_1_MATCH		3

#define _XTAL_FREQ 32000000

/* Function Prototypes */
void set_Vaddress(char add);
void init_V4RLYOPTO(char port);
void init_V8RLYOPTO(char port);
void VSET(short num);
void VRESET(short num);
char VTEST(short num);
char VINP(char port);
void VOUT(char port, char bite);


#endif