#ifndef TWI_PRIVATE_H
#define TWI_PRIVATE_H

#define TWI_READ 1
#define TWI_WRITE 0
/* ------- Status codes ------- */
/* master transmit status codes */
#define START (0x08)
#define REPEATED_START (0x10)
#define MT_SLA_ACK (0x18)
#define MT_SLA_NACK (0x20)
#define MT_DATA_ACK (0x28)
#define MT_DATA_NACK (0x30)
#define MT_ARBITRATION_LOST (0x38)
/* master recieve status codes */
#define MR_SLA_ACK (0x40)
#define MR_SLA_NACK (0x48)
#define MR_DATA_ACK (0x50)
#define MR_DATA_NACK (0x58)

/* slave transmit status codes */
/* slave recieve status codes */

#define SR_SLA_ACK (0x60)
#define SR_GCALL_SLA_ACK (0x70)
#define SR_ARBT_SLA_ACK (0x68)
#define SR_DATA_ACK (0x80)
#define SR_GCALL_DATA_ACK (0x90)

#define SR_DATA_NACK (0x88)
#define SR_GCALL_DATA_NACK (0x98)
/* ------------------------ */

/* ------- Error codes ------- */
/* master transmit error codes */
#define TWI_SUCESS 0
#define MT_START_ERROR 1
#define MT_SLA_ERROR 2
#define MT_DATA_ERROR 3

/* master recieve error codes */
#define MR_SLA_ERROR 4
#define MR_DATA_ERROR 5
/* slave recieve error codes */
#define SR_SLA_ERROR 6

/* ------------------------ */
#endif