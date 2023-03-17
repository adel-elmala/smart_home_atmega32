#include "EEPROM_Interface.h"
#include "EEPROM_REG.h"
#include "../GIE/GIE_Interface.h"
#include "../GIE/GIE_REG.h"

void EEPROM_Write_Byte(uint8 byte, uint16 eeprom_address)
{
    uint8 temp = SREG;
    cli();
    /* Wait for completion of previous write */
    while (EECR & (1 << EECR_EEWE))
        ;
    /* Set up address and data registers */
    EEAR = eeprom_address;
    EEDR = byte;
    /* Write logical one to EEMWE */
    EECR |= (1 << EECR_EEMWE);
    /* Start eeprom write by setting EEWE */
    EECR |= (1 << EECR_EEWE);
    SREG = temp;
}

void EEPROM_Write_Buffer(uint8 *buffer, uint16 buffer_size, uint16 eeprom_address)
{
    for (int i = 0; i < buffer_size; ++i)
        EEPROM_Write_Byte(buffer[i], eeprom_address + i);
}

uint8 EEPROM_Read_Byte(uint16 eeprom_address)
{
    uint8 temp = SREG;
    cli();
    /* Wait for completion of previous write */
    while (EECR & (1 << EECR_EEWE))
        ;
    /* Set up address register */
    EEAR = eeprom_address;
    /* Start eeprom read by writing EERE */
    EECR |= (1 << EECR_EERE);

    uint8 byte = EEDR;
    SREG = temp;
    /* Return data from data register */
    return byte;
}
void EEPROM_Read_Buffer(uint8 *buffer, uint16 buffer_size, uint16 eeprom_address)
{
    for (int i = 0; i < buffer_size; ++i)
        buffer[i] = EEPROM_Read_Byte(eeprom_address + i);
}
