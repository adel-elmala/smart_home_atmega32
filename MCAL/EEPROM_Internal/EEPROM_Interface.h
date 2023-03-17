/**
 * @file EEPROM_Interface.h
 * @author Mohamed Elhusseiny
 * @brief  Internal EEPROM Driver Interface file
 * @version 0.1
 * @date 2023-03-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#ifndef         EEPROM_INTERNAL_INTERFACE_H
#define         EEPROM_INTERNAL_INTERFACE_H


typedef enum eeprom_status
{
    EEPROM_WRONG_ADDRESS = 0,
    EEPROM_SET_ADDRESS_OK
}EEPROM_Status_t;
EEPROM_Status_t EEPROM_enuWrite(uint16 EEPROM_Address , uint8 EEPROM_DataSend);
EEPROM_Status_t EEPROM_enuRead(uint16 EEPROM_Address , uint8 *EEPROM_DataRec);

#endif