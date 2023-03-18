/*
 * RFID.c
 *
 *  Created on: Mar 12, 2023
 *      Author: dell
 */

#include "RFID.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/DIO/DIO_REG.h"
#include "../../MCAL/TIMER/timer.h"
#include "../../MCAL/SPI/SPI.h"

#include <util/delay.h>

uint8 ReadReg(uint8 reg)
{
    uint8 data;
    clearbit(PORTB_R, SS);
    SPI_DATA_RW(((reg << 1) & 0x7E) | 0x80);
    data = SPI_DATA_RW(0x00);
    setbit(PORTB_R, SS);

    return data;
}

void ReadRegMulti(uint8 reg, uint8 count, uint8 *values)
{
    count++;
    uint8 out[30] = {0};
    uint8 in[30] = {0};
    clearbit(PORTB_R, SS);
    for (int i = 0; i < count - 1; i++)
    {
        out[i] = (uint8)(0x80 | ((reg << 1) & 0x7E));
        SPI_DATA_RW(out[i]);
    }
    out[count] = 0x00;
    SPI_DATA_RW(out[count]);
    setbit(PORTB_R, SS);
    for (int i = 0; i < count; i++)
    {
        values[i] = in[i + 1];
    }
}

void WriteReg(uint8 reg, uint8 value)
{
    clearbit(PORTB_R, SS);
    SPI_DATA_RW((reg << 1) & 0x7E);
    SPI_DATA_RW(value);
    setbit(PORTB_R, SS);
}

void WriteRegMulti(uint8 reg, uint8 count, uint8 *values)
{
    count++;
    uint8 out[30] = {0};
    out[0] = (uint8)((reg << 1) & 0x7E);
    clearbit(PORTB_R, SS);
    SPI_DATA_RW(out[0]);
    for (int i = 1; i < count; i++)
    {
        out[i] = values[i - 1];
        SPI_DATA_RW(out[i]);
    }
    setbit(PORTB_R, SS);
}
void ClearBitMask(uint8 reg, uint8 mask)
{
    uint8 tmp = ReadReg(reg);
    WriteReg(reg, tmp & (~mask));
}

void SetBitMask(uint8 reg, uint8 mask)
{
    uint8 tmp = ReadReg(reg);
    WriteReg(reg, tmp | mask);
}

void Reset()
{
    WriteReg(CommandReg, SoftReset_CMD);
    _delay_ms(50);
    while (ReadReg(CommandReg) & 0x08)
        ;
}

uint8 calculate_crc(uint8 *data, int length, uint8 *result)
{
    WriteReg(CommandReg, Idle_CMD);
    WriteReg(DivIrqReg, 0x04);
    SetBitMask(FIFOLevelReg, 0x80);
    WriteRegMulti(FIFODataReg, length, data);
    WriteReg(CommandReg, CalcCRC_CMD);
    int i = 5000;
    uint8 n;
    while (1)
    {
        n = ReadReg(DivIrqReg);
        if (n & 0x04)
        {
            break;
        }
        if (--i == 0)
        {
            return 0;
        }
    }
    WriteReg(CommandReg, Idle_CMD);
    result[0] = ReadReg(CRCResultReg_2);
    result[1] = ReadReg(CRCResultReg_1);
    return 1;
}

uint8 Communicate(uint8 command, uint8 *sendData, uint8 sendLen, uint8 *backData, uint8 *backLen, uint8 *validBits, uint8 checkCRC)
{
    uint8 waitIRq = 0, n, _validBits = 0;

    uint8 bitFraming = (uint8)(validBits ? *validBits : 0);
    if (command == Transceive_CMD)
    {
        waitIRq = 0x30;
    }
    else if (command == MFAuthent_CMD)
    {
        waitIRq = 0x10;
    }
    WriteReg(CommandReg, Idle_CMD);
    WriteReg(ComIrqReg, 0x7F);
    SetBitMask(FIFOLevelReg, 0x80);
    // WriteRegMulti(FIFODataReg, sendLen, sendData);
    for (uint8 i = 0; i < sendLen; i++)
    {
        WriteReg(FIFODataReg, sendData[i]);
    }
    WriteReg(BitFramingReg, bitFraming);
    WriteReg(CommandReg, command);
    if (command == Transceive_CMD)
    {
        SetBitMask(BitFramingReg, 0x80);
    }
    for (int i = 2000; i > 0;)
    {
        n = ReadReg(ComIrqReg);
        if (n & waitIRq)
        {
            break;
        }
        if (n & 0x01)
        {
            return 0;
        }
        if (--i == 0)
        {
            return 0;
        }
    }
    uint8 errorRegValue = ReadReg(ErrorReg);
    if (errorRegValue & 0x13)
    {
        return 0;
    }

    if (backData && backLen)
    {
        n = ReadReg(FIFOLevelReg);
        if (n > *backLen || n == 0)
        {
            return 0;
        }
        *backLen = n;
        // ReadRegMulti(FIFODataReg, n, backData);
        for (uint8 i = 0; i < n; i++)
        {
            backData[i] = ReadReg(FIFODataReg);
        }
        _validBits = (uint8)(ReadReg(ControlReg) & 0x07);
        if (validBits)
        {
            *validBits = _validBits;
        }
    }
    if (errorRegValue & 0x08)
    {
        return 0;
    }
    if (backData && backLen && checkCRC)
    {
        uint8 controlBuffer[2];
        if (!calculate_crc(&backData[0], (uint8)(*backLen - 2), &controlBuffer[0]))
        {
            return 0;
        }
        if ((backData[*backLen - 2] != controlBuffer[0]) || (backData[*backLen - 1] != controlBuffer[1]))
        {
            return 0;
        }
    }
    return 1;
}

void RFID_INIT()
{
    WriteReg(TModeReg, 0x80);
    WriteReg(TPrescalerReg, 0x9A);
    WriteReg(TReloadReg_1, 0x03);
    WriteReg(TReloadReg_2, 0xE8);
    WriteReg(TxASKReg, 0x40);
    WriteReg(ModeReg, 0x3D);
    uint8 value = ReadReg(TxControlReg);
    if ((value & 0x03) != 0x03)
    {
        SetBitMask(TxControlReg, 0x03);
    }
}

uint8 DetectCard()
{
    uint8 buffer[2];
    uint8 len = sizeof(buffer);
    uint8 validBits = 7;
    ClearBitMask(CollReg, 0x80);
    uint8 command[1] = {0x26};
    // Transceive_CMD:transmit and recive comm & command==0x26 & length of command arrary & back data(buffer) & length of back data & validBits & crc erorr
    if (!Communicate(Transceive_CMD, command, 1, buffer, &len, &validBits, 0))
    {
        // wait until some card
        // DIO_vWritePin(PORTA, PIN6, HIGH);
        // TIMER0_Delay_ms_with_Blocking(500);
        // DIO_vWritePin(PORTA, PIN6, LOW);
        // TIMER0_Delay_ms_with_Blocking(500);
        return 0;
    }
    if (len != 2 || validBits != 0)
    {
        return 0;
    }
    return 1;
}

uint8 getFirmwareVersion()
{
    return ReadReg(VersionReg); // to get type of card version
}

uint8 GetCardId(uint8 *uid)
{
    uint8 buffer[9];
    uint8 backLen = 9;
    ClearBitMask(CollReg, 0x80);
    WriteReg(BitFramingReg, 0);
    buffer[0] = 0x93;
    buffer[1] = 0x20;
    if (!Communicate(Transceive_CMD, buffer, (uint8)2, buffer, &backLen, 0, 0))
    {
        return 0;
    }
    for (uint8 i = 0; i < 4; i++)
    {
        uid[i] = buffer[i];
    }
    return 1;
}
