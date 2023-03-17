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


#ifndef         EEPROM_INTERNAL_REG_H
#define         EEPROM_INTERNAL_REG_H

#define         EEARH_REG       *((volatile uint8 *) 0x3F)
#define         EEARL_REG       *((volatile uint8 *) 0x3E)
#define         EEDR_REG       *((volatile uint8 *) 0x3D)
#define         EECR_REG       *((volatile uint8 *) 0X3C)
#define         EEAR_REG       *((volatile uint16 *) 0x3E)

/**
 * @brief Pins Name of EECR Register
 */
#define         EERIE       3
#define         EEMWE       2
#define         EEWE        1
#define         EERE        0





#endif