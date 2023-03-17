#ifndef FP_STATUS_MACROS_H
#define FP_STATUS_MACROS_H

/* verify password ack macros */
#define ACK_CORRECT_PASSWORD 0x00
#define ACK_ERROR_RECEIVING 0x01
#define ACK_WRONG_PASSWORD 0x13

/* collect finger ack macros */
#define ACK_FINGER_COLLECTION_SUCCESS 0x00
#define ACK_ERROR_RECEIVING 0x01
#define ACK_CANNOT_FIND_FINGER 0x02
#define ACK_FAILED_TO_COLLECT_FINGER 0x03

/* generate char file ack macros */
#define ACK_CHAR_FILE_GEN_COMPLETE 0x00
#define ACK_ERROR_RECEIVING 0x01
#define ACK_FAILED_OVER_DISORDERLY_FP_IMG 0x06
#define ACK_FAILED_OVER_SMALLNESS_FP_IMG 0x07
#define ACK_FAILED_LACK_OF_PRIMARY_IMG 0x15

/* generate template ack macros */
#define ACK_OP_SUCSESS 0x00
#define ACK_ERROR_RECEIVING 0x01
#define ACK_FAILED_TO_COMBINE_CHAR_FILES 0x0a

/* store template ack macros */
#define ACK_STORAGE_SUCCESS 0x00
#define ACK_ERROR_RECEIVING 0x01
#define ACK_ERROR_PAGEID_BEYOND_FINGER_LIB 0x0b
#define ACK_ERROR_WRITING_FLASH 0x18

/* delete template ack macros */
#define ACK_DELETE_SUCCESS 0x00
#define ACK_ERROR_RECEIVING 0x01
#define ACK_FAILED_TO_DELETE_TEMPLATE 0x10

/* search templates ack macros */
#define ACK_MATCH_FOUND 0x00
#define ACK_ERROR_RECEIVING 0x01
#define ACK_NO_MATCH_FOUND 0x09

#endif