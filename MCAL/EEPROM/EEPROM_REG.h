#ifndef EEPROM_REG_H
#define EEPROM_REG_H

/* The EEPROM Address Register – EEARH and EEARL */
#define EEARH (*((volatile uint8 *)(0x3F)))
#define EEARL (*((volatile uint8 *)(0x3E)))
#define EEAR (*((volatile uint16 *)(0x3E)))
/* The EEPROM Data Register – EEDR */
#define EEDR (*((volatile uint8 *)(0x3D)))

/* The EEPROM Control Register – EECR */
#define EECR (*((volatile uint8 *)(0x3C)))

#define EECR_EERIE 3
#define EECR_EEMWE 2
#define EECR_EEWE 1
#define EECR_EERE 0

#endif