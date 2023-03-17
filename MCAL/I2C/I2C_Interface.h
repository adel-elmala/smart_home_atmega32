/**
 * @file I2C_Interface.h
 * @author Mohamed Elhusseiny
 * @brief 
 * @version 0.2
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef     I2C_INTERFACE_H
#define     I2C_INTERFACE_H



/**************************************************************************************************/
/**************************************************************************************************/
/***************************************** Version 0.2 ********************************************/
/**************************************************************************************************/
/**************************************************************************************************/

#define     OLED_ADDRESS            0x78
#define     READ                    1
#define     WRITE                   0

/**
 * @brief Master Important Status
 * 
 */
#define     I2C_START_ACK           0x08        /* Start Condition has been transmitted */
#define     I2C_R_START_ACK         0x10        /* Repeated Start Condition has been transmitted */
#define     I2C_MT_SLA_W_ACK        0x18        /* Master Transmit Address with Write Option & Ack Recived From Slave */
#define     I2C_MT_DATA_ACK         0x28        /* Master Transmit Data &  Slave Ack Recived */

/**
 * @brief Not Used Stauts
 * 
 */
#define     I2C_MT_SLA_R_ACK        0x40        /* Master Transmit Address with Read Option & Ack Recived From Slave */
#define     I2C_MR_DATA_ACK         0x48        /* Master Recive Data &  Slave Ack Recived */
#define     I2C_SR_DATA_ACK         0x80

typedef enum
{
    I2C_OK = 0,
    I2C_SC_ERROR,
    I2C_RSC_ERROR,
    I2C_MT_SLA_R_ERROR,
    I2C_MT_SLA_W_ERROR,
    I2C_MT_DATA_ERROR,
    I2C_MR_DATA_ERROR,
    I2C_SR_DATA_ERROR
}I2C_ErrorState_t;

void I2C_vInit(void);
I2C_ErrorState_t I2C_enuStartTransmission(void);
I2C_ErrorState_t I2C_enuSendSalveAdd(uint8 SalveAddress);
I2C_ErrorState_t I2C_enuSendSlaveRamAdd(uint8 SalveAddress);
I2C_ErrorState_t I2C_enuSendSlaveData(uint8 Data);
I2C_ErrorState_t I2C_enuRestartTransmission(void);
uint8 I2C_enuReadOneByte(void);
int I2C_enuReadMoreByte(void);
void I2C_vStopTransmission(void);

void I2C_Write(uint8 Address , uint8 Data);
uint8 I2C_Read(uint8 Address);






















/**************************************************************************************************/
/**************************************************************************************************/
/***************************************** Version 0.2 ********************************************/
/**************************************************************************************************/
/**************************************************************************************************/



typedef enum
{
    I2C_SEND_ADDRESS_WITH_WRITE,
    I2C_SEND_ADDRESS_WITH_READ
}I2C_Send_Add_WR_t;

typedef enum
{
    I2C_MASTER_SEND_DATA,
    I2C_MASTER_RECIVE_DATA
}I2C_Data_SR_Option_t;




/**************************************************************************************************/
/**************************************************************************************************/
/******************************************** I2C APIs ********************************************/
/**************************************************************************************************/
/**************************************************************************************************/

/**
 * @brief The Init Function will do the following Initialization to Master I2C.
 *        1- Set Prescaller value for TWSR Reg.
 *        2- Set Bit rate on TWBR Reg based on SCL_FREQ "Pre define value" , will add the option to make it select from user
 *        3- Enable Ack for Master 
 *        4- Enable I2C
 */
void I2C_Master_vInit(void);


/**
 * @brief The Init Function will do the following Initialization to Slave I2C.
 *        1- Set Prescaller value for TWSR Reg.
 *        2- Set Bit rate on TWBR Reg based on SCL_FREQ "Pre define value" , will add the option to make it select from user
 *        3- Enable Ack for Master
 *        4- Set Address in TWAR Reg
 *        5- Enable I2C
 * 
 * @param I2C_Address Slave Address
 */
void I2C_Slave_vInit(uint8 I2C_Address);


/**
 * @brief This Function use to send start condition. 
 * 
 * @return I2C_ErrorState_t Result State after sending start condition {I2C_SC_ERROR , I2C_OK}.
 */
I2C_ErrorState_t I2C_Master_enuSendSC(void);


/**
 * @brief This Function use to send repeated start condition. 
 * 
 * @return I2C_ErrorState_t Result State after sending Repeated start condition {I2C_RSC_ERROR , I2C_OK}.
 */
I2C_ErrorState_t I2C_Master_enuSendRSC(void);


/**
 * @brief Using this function after start condition or repeated SC to Target Slave with it's Address
 *        and use Option W or R to know the slave if you need to read data or send data.
 * 
 * @param I2C_Address Address of the slave 
 * @param WR_Option   Write or Read option from the slave 
 * @return I2C_ErrorState_t 
 */
I2C_ErrorState_t I2C_Master_enuSendSlaveAddress_WR(uint8 I2C_Address , I2C_Send_Add_WR_t WR_Option);


/**
 * @brief After Recive Ack from the slave as it address was correct send you need to use this function to 
 *        send or recive Data to/from Slave. 
 * 
 * @param I2C_Data   Data needed to send/recive.
 * @param DataOption Data option determine if you want to recive or send data.
 * @return I2C_ErrorState_t 
 */
I2C_ErrorState_t I2C_Master_enuData_SR(uint8 *I2C_Data , I2C_Data_SR_Option_t DataOption);


/**
 * @brief Send Stop Condition
 * 
 */
void I2C_Master_vSendStopCond(void);


/**
 * @brief Wait for any transmitting to done
 * 
 */
void I2C_Slave_vListen(void);


/**
 * @brief use to return data that was send by master
 * 
 * @param I2C_Data Pointer to save this data
 * @return I2C_ErrorState_t 
 */
I2C_ErrorState_t I2C_Slave_enuReadu8Data(uint8 *I2C_Data);


I2C_ErrorState_t I2C_Master_enuData_S(uint8 I2C_Data);
I2C_ErrorState_t I2C_Master_enuData_R(uint8 *I2C_Data);

#endif