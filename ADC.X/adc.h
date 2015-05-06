/* ADC.H
 *
 * Definitions required for simple A/D interface on PIC16F1947.
 */

#ifndef __ADC_H
#define __ADC_H

/* Function prototypes
 */
void init_adc();
int convert(int channel);

#endif // __ADC_H
