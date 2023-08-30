#ifndef __DS3231_H
#define	__DS3231_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <pic16f887.h>
#include <stdint.h>

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 8000000
#endif

int SEG;
int MIN;
int HOR;
int DAY;
int MOTH;
int YEAR;

void DS3231_Init();
void DS3231_Read();
uint8_t Bcd_to_Dec(uint8_t bcd);
uint8_t Dec_to_Bcd(uint8_t dec);


#endif	/* __I2C_H */
