
#ifndef HAL_RFID_RFID_H_
#define HAL_RFID_RFID_H_

#include "../../MCAL/SPI/SPI.h"
#include "RFID_REG.h"

// Mifare_One card command word                  //DETECTION ONLY
#define PICC_REQIDL 0x26    // find the antenna area does not enter hibernation
#define PICC_REQALL 0x52    // find all the cards antenna area
#define PICC_ANTICOLL 0x93  // anti-collision (return all cards data)
#define PICC_SElECTTAG 0x93 // election card  (return all cards data and select one card)
#define PICC_AUTHENT1A 0x60 // authentication key A (if u have card without serial number it will add serial)
#define PICC_AUTHENT1B 0x61 // authentication key B (if u have card without serial number it will add serial)
#define PICC_READ 0x30      // Read Block  (read all data blocks)
#define PICC_WRITE 0xA0     // write block (write all data blocks if it without serial)
#define PICC_DECREMENT 0xC0 // debit
#define PICC_INCREMENT 0xC1 // recharge
#define PICC_RESTORE 0xC2   // transfer block data to the buffer ()
#define PICC_TRANSFER 0xB0  // save the data in the buffer
#define PICC_HALT 0x50      // Sleep

// command set
#define Idle_CMD 0x00
#define Mem_CMD 0x01
#define GenerateRandomId_CMD 0x02
#define CalcCRC_CMD 0x03
#define Transmit_CMD 0x04
#define NoCmdChange_CMD 0x07
#define Receive_CMD 0x08
#define Transceive_CMD 0x0C
#define Reserved_CMD 0x0D
#define MFAuthent_CMD 0x0E
#define SoftReset_CMD 0x0F

void RFID_INIT();
uint8 DetectCard();
uint8 GetCardId(uint8 *uid);
uint8 getFirmwareVersion();
uint8 ReadReg(uint8 reg);              //  get data frome reg (recive)
void WriteReg(uint8 reg, uint8 value); //  atmega send name of reg and value u want through el spi (transmit)

#endif /* HAL_RFID_RFID_H_ */
