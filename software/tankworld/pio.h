#ifndef PIO_H
#define PIO_H


#include <system.h>
#include <alt_types.h>
#include <stdio.h>

void setLED(int LED);
void clearLED(int LED);
void printSignedHex0(signed char value);
void printSignedHex1(signed char value);

#endif /*PIO_H*/
