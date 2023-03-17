/**
 * @file EEPROM_Prog.c
 * @author Mohamed Elhusseiny
 * @brief  Internal EEPROM driver implementation
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../../LIB/Datatypes.h"
#include "../../LIB/Calcbit.h"
#include "./EEPROM_Interface.h"
#include "./EEPROM_Reg.h"



EEPROM_Status_t EEPROM_enuWrite(uint16 EEPROM_Address , uint8 EEPROM_DataSend)
{
    if(EEPROM_Address >= 0 && EEPROM_Address <= 1023)
    {
        while(GETBIT(EECR_REG , EEWE));                 // What about the first time ?
        EEAR_REG = EEPROM_Address;
        EEDR_REG = EEPROM_DataSend;
        SETBIT(EECR_REG , EEMWE);
        SETBIT(EECR_REG , EEWE);
    }
    else
    {
        return EEPROM_WRONG_ADDRESS;
    }
    return EEPROM_SET_ADDRESS_OK;
}


EEPROM_Status_t EEPROM_enuRead(uint16 EEPROM_Address , uint8 *EEPROM_DataRec)
{
    if(EEPROM_Address >= 0 && EEPROM_Address <= 1023)
    {
        while(GETBIT(EECR_REG , EEWE));                 // What about the first time ?
        EEAR_REG = EEPROM_Address;
        SETBIT(EECR_REG , EERE);
        *EEPROM_DataRec = EEDR_REG;
    }
    else
    {
        return EEPROM_WRONG_ADDRESS;
    }
    return EEPROM_SET_ADDRESS_OK;
}
