#ifndef FP_PRIVATE_H
#define FP_PRIVATE_H
#include "../../LIB/Datatypes.h"

#define FP_PACKET_CONTENT_MAX_SIZE 256

#define PACKET_START 0xEF01
#define PACKET_DEFAULT_ADDER 0xFFFFFFFF

#define PACKET_PID_COMMAND 0x01
#define PACKET_PID_DATA 0x02
#define PACKET_PID_ACK 0x07
#define PACKET_PID_END 0x08

#define PACKET_HEADER_SIZE 2
#define PACKET_ADDER_SIZE 4
#define PACKET_LEN_SIZE 2
#define PACKET_CHECKSUM_SIZE 2

// low bytes are stored first in the arrays
typedef struct FP_Packet
{
    uint8 header[PACKET_HEADER_SIZE];
    uint8 adder[PACKET_ADDER_SIZE];
    uint8 id;
    uint8 len[PACKET_LEN_SIZE];
    uint8 content[FP_PACKET_CONTENT_MAX_SIZE]; // data should be stored in big endian style (high bytes first)
    uint8 checksum[PACKET_CHECKSUM_SIZE];
} FP_Packet_t;

// void FP_Init();
bool send_packet(FP_Packet_t packet);
bool receive_packet(FP_Packet_t *packet);
uint16 calculate_checksum(FP_Packet_t packet);

void send_array(uint8 *packet, uint8 packet_size);

uint8 FP_Verify_Password(uint32 password);

void fill_packet(FP_Packet_t *packet, uint8 pid, uint16 len, uint8 *data);

#endif