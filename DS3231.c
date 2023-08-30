#include "DS3231.h"
#include "I2C.h"

void DS3231_Init(){
    //Minutos 
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x01);
        I2C_Master_Write(Dec_to_Bcd(47));
        I2C_Master_Stop();
    //Segundos 
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x00);
        I2C_Master_Write(Dec_to_Bcd(0));
        I2C_Master_Stop();
    //Hora    
         I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x02);
        I2C_Master_Write(Dec_to_Bcd(13));
        I2C_Master_Stop();
    //Dia
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x04);
        I2C_Master_Write(Dec_to_Bcd(30));
        I2C_Master_Stop();
    //MES    
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x05);
        I2C_Master_Write(Dec_to_Bcd(8));
        I2C_Master_Stop();
     //AÑO   
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x06);
        I2C_Master_Write(Dec_to_Bcd(23));
        I2C_Master_Stop();
        
        __delay_ms(10);
}

void DS3231_Read(){
       I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x00);
        I2C_Master_Stop();
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x00);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        SEG = Bcd_to_Dec(I2C_Master_Read(0));
        I2C_Master_Stop();
        __delay_ms(10);
        
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x01);
        I2C_Master_Stop();
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x01);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        MIN = Bcd_to_Dec(I2C_Master_Read(0));
        I2C_Master_Stop();
        __delay_ms(10);
        
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x02);
        I2C_Master_Stop();
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x02);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        HOR = Bcd_to_Dec(I2C_Master_Read(0));
        I2C_Master_Stop();
        __delay_ms(10);
        
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x04);
        I2C_Master_Stop();
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x04);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        DAY = Bcd_to_Dec(I2C_Master_Read(0));
        I2C_Master_Stop();
        __delay_ms(10);
        
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x05);
        I2C_Master_Stop();
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x05);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        MOTH = Bcd_to_Dec(I2C_Master_Read(0));
        I2C_Master_Stop();
        __delay_ms(10);
        
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x06);
        I2C_Master_Stop();
        I2C_Master_Start();
        I2C_Master_Write(0xD0);
        I2C_Master_Write(0x06);
        I2C_Master_RepeatedStart();
        I2C_Master_Write(0xD1);
        YEAR = Bcd_to_Dec(I2C_Master_Read(0));
        I2C_Master_Stop();
        __delay_ms(10);
}

uint8_t Bcd_to_Dec(uint8_t bcd){                            //Función para pasar números de bcd a decimal
    uint8_t dec;                                            //Variable para guardar valor
    dec = ((bcd>>4)*10)+(bcd & 0b00001111);                 //Hacer un corrimiento de bits y sumar con la unidad
    return dec;                                             //Retornar valor
}

uint8_t Dec_to_Bcd(uint8_t dec) {
    return ((dec / 10) << 4) | (dec % 10);
}