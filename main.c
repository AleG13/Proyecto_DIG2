#pragma config FOSC = INTRC_CLKOUT// Oscillator Selection bits (INTOSC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "stdio.h"
#include <string.h>
#include "I2C.h"
#include "DS3231.h"
#include "MPU6050.h"
#include <stdlib.h>
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 8000000
int datai2c;
char bufferTemp[4];
int TemperatureValue;
uint8_t HumidityValue;

void __interrupt() isr(void){
    
}

void setup(void);

//*****************************************************************************
// Código Principal
//*****************************************************************************
void main(void) {
   setup();
   MPU6050_Init(); 
    while(1){
        
    DS3231_Read(); 
    __delay_ms(200);
    //MPU6050_Read();
    __delay_ms(200);
    
    //LECTURA DE TEMPERATURA
//    I2C_Master_Start();
//    I2C_Master_Write(0x80);
//    I2C_Master_Write(PORTA);
//    I2C_Master_Stop();
//    __delay_ms(200);
//       
//    I2C_Master_Start();
//    I2C_Master_Write(0x81);
//    TemperatureValue = I2C_Master_Read(0);
//    I2C_Master_Stop();
//    __delay_ms(200);
//    PORTA++; 
    

    //ENVIAR DATOS A LA LCD, POR MEDIO DE UN PIC ESCLAVO
        I2C_Master_Start();
        I2C_Master_Write(0x50);
        I2C_Master_Write(SEG);
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0xA1);
        datai2c = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
          I2C_Master_Start();
        I2C_Master_Write(0x50);
        I2C_Master_Write(MIN);
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0xA1);
        datai2c = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
          I2C_Master_Start();
        I2C_Master_Write(0x50);
        I2C_Master_Write(HOR);
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0xA1);
        datai2c = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);
        
          I2C_Master_Start();
        I2C_Master_Write(0x50);
        I2C_Master_Write(24);
        I2C_Master_Stop();
        __delay_ms(200);
        
        I2C_Master_Start();
        I2C_Master_Write(0xA1);
        datai2c = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(200);

    }
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    // Configuración del oscilador
    OSCCONbits.IRCF =   0b0111; //8MHz
    OSCCONbits.SCS = 1;
    ANSEL = 0;
    ANSELH = 0;
    TRISC2 = 0;
    TRISCbits.TRISC1 = 0;
    TRISCbits.TRISC2 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;
    TRISD = 0; 
    PORTD = 0;
    PORTB = 0;
    PORTCbits.RC4 = 1;  
    PORTCbits.RC3 = 1;
    I2C_Master_Init(100000);
    INTCONbits.PEIE = 1; 
    PIE1bits.ADIE = 1; 
    ADCON0bits.GO = 0; 
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
}
