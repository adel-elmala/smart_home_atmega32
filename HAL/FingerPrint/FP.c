#include "FP_Private.h"
#include "FP_Interface.h"
#include "../../MCAL/UART/UART_Interface.h"
#include "../../MCAL/TIMER/timer.h"
#include "../LCD/LCD_Interface.h"
#include "../../LIB/Queue/Queue.h"

// UART_Config_t uart_conf_fp = {
//     57600, // uint16 baud_rate;
//     // 9600,                                           // uint16 baud_rate;
//     UART_DISABLE_DOUBLE_TRANSMISSION_SPEED,         // uint8 enable_double_transmission_speed;
//     UART_DISABLE_MULTIPROCESSOR_COMMUNICATION_MODE, // uint8 enable_multiprocessor_mode;
//     UART_DISABLE_RECEIVE_COMPLETE_INTERRUPT,        // uint8 enable_recevie_complete_interrupt;
//     UART_DISABLE_TRANSMIT_COMPLETE_INTERRUPT,       // uint8 enable_transmit_complete_interrupt;
//     UART_DISABLE_DATA_REG_EMPTY_COMPLETE_INTERRUPT, // uint8 enable_data_reg_empty_complete_interrupt;
//     UART_ENABLE_RECEIVER,                           // uint8 enable_receiver;
//     UART_ENABLE_TRANSMITER,                         // uint8 enable_transmiter;
//     UART_8BIT_CHAR_SIZE,                            // uint8 frame_data_bits_size;
//     UART_DISABLE_PARITY,                            // uint8 parity_mode;
//     UART_1_BIT_STOP                                 // uint8 stop_bits_mode;
// };

UART_Config_t uart_conf_fp_async = {
    57600, // uint16 baud_rate;
    // 9600,                                           // uint16 baud_rate;
    UART_DISABLE_DOUBLE_TRANSMISSION_SPEED,         // uint8 enable_double_transmission_speed;
    UART_DISABLE_MULTIPROCESSOR_COMMUNICATION_MODE, // uint8 enable_multiprocessor_mode;
    UART_ENABLE_RECEIVE_COMPLETE_INTERRUPT,         // uint8 enable_recevie_complete_interrupt;
    UART_ENABLE_TRANSMIT_COMPLETE_INTERRUPT,        // uint8 enable_transmit_complete_interrupt;
    UART_DISABLE_DATA_REG_EMPTY_COMPLETE_INTERRUPT, // uint8 enable_data_reg_empty_complete_interrupt;
    UART_ENABLE_RECEIVER,                           // uint8 enable_receiver;
    UART_ENABLE_TRANSMITER,                         // uint8 enable_transmiter;
    UART_8BIT_CHAR_SIZE,                            // uint8 frame_data_bits_size;
    UART_DISABLE_PARITY,                            // uint8 parity_mode;
    UART_1_BIT_STOP                                 // uint8 stop_bits_mode;

};

void FP_Init()
{
    // UART_vInit(uart_conf_fp);
    UART_vInit(uart_conf_fp_async);
    TIMER0_Delay_ms_with_Blocking(200);
}

bool send_packet(FP_Packet_t packet)
{
    // send header
    for (int i = PACKET_HEADER_SIZE - 1; i >= 0; --i) // send high bytes first
        // for (int i = 0; i < PACKET_HEADER_SIZE; ++i)
        UART_vTransmit_poll(packet.header[i]);

    // send_adder
    for (int i = PACKET_ADDER_SIZE - 1; i >= 0; --i)
        UART_vTransmit_poll(packet.adder[i]);

    // send pid
    UART_vTransmit_poll(packet.id);

    // send length
    for (int i = PACKET_LEN_SIZE - 1; i >= 0; --i)
        UART_vTransmit_poll(packet.len[i]);

    // length of the data + (checksum : 2 bytes)
    uint16 p_length = ((uint16)(packet.len[0])) | (((uint16)(packet.len[1])) << 8);

    // length of the data only
    p_length -= PACKET_CHECKSUM_SIZE;

    // send data
    for (int i = 0; i < p_length; ++i)
        UART_vTransmit_poll(packet.content[i]);

    // send checksum
    for (int i = PACKET_CHECKSUM_SIZE - 1; i >= 0; --i)
        UART_vTransmit_poll(packet.checksum[i]);
    return true;
}

bool send_packet_Async(FP_Packet_t packet)
{
    // send header
    for (int i = PACKET_HEADER_SIZE - 1; i >= 0; --i)
        UART_vTransmit_no_poll(packet.header[i]);

    // send_adder
    for (int i = PACKET_ADDER_SIZE - 1; i >= 0; --i)
        UART_vTransmit_no_poll(packet.adder[i]);

    // send pid
    UART_vTransmit_no_poll(packet.id);

    // send length
    for (int i = PACKET_LEN_SIZE - 1; i >= 0; --i)
        UART_vTransmit_no_poll(packet.len[i]);

    // length of the data + (checksum : 2 bytes)
    uint16 p_length = ((uint16)(packet.len[0])) | (((uint16)(packet.len[1])) << 8);

    // length of the data only
    p_length -= PACKET_CHECKSUM_SIZE;

    // send data
    for (int i = 0; i < p_length; ++i)
        UART_vTransmit_no_poll(packet.content[i]);

    // send checksum
    for (int i = PACKET_CHECKSUM_SIZE - 1; i >= 0; --i)
        UART_vTransmit_no_poll(packet.checksum[i]);
    return true;
}
bool receive_packet(FP_Packet_t *packet)
{
    // send header
    for (int i = PACKET_HEADER_SIZE - 1; i >= 0; --i)
        // for (int i = 0; i < PACKET_HEADER_SIZE; ++i)
        packet->header[i] = (uint8)UART_u16Receive_poll();

    // send_adder
    for (int i = PACKET_ADDER_SIZE - 1; i >= 0; --i)
        // for (int i = 0; i < PACKET_ADDER_SIZE; ++i)
        packet->adder[i] = (uint8)UART_u16Receive_poll();

    // send pid
    packet->id = (uint8)UART_u16Receive_poll();

    // send length
    for (int i = PACKET_LEN_SIZE - 1; i >= 0; --i)
        // for (int i = 0; i < PACKET_LEN_SIZE; ++i)
        packet->len[i] = (uint8)UART_u16Receive_poll();

    // length of the data + (checksum : 2 bytes)
    uint16 p_length = ((uint16)(packet->len[0])) | (((uint16)(packet->len[1])) << 8);

    // length of the data only
    p_length -= PACKET_CHECKSUM_SIZE;

    // receive data
    for (int i = 0; i < p_length; ++i)
        // for (int i = p_length - 1; i >= 0; --i)
        packet->content[i] = (uint8)UART_u16Receive_poll();

    // send checksum
    for (int i = PACKET_CHECKSUM_SIZE - 1; i >= 0; --i)
        // for (int i = 0; i < PACKET_CHECKSUM_SIZE; ++i)
        packet->checksum[i] = (uint8)UART_u16Receive_poll();

    return true;
}
bool receive_packet_Async(FP_Packet_t *packet)
{
    // send header
    for (int i = PACKET_HEADER_SIZE - 1; i >= 0; --i)
    {
        uint8 data = (uint8)UART_u16Receive_no_poll();
        if (data != QUEUE_ERROR_EMPTY)
            packet->header[i] = data;
        else
            i++;
    }

    // send_adder
    for (int i = PACKET_ADDER_SIZE - 1; i >= 0; --i)
    {
        uint8 data = (uint8)UART_u16Receive_no_poll();
        if (data != QUEUE_ERROR_EMPTY)
            packet->adder[i] = data;
        else
            i++;
    }

    // send pid
    uint8 pid;
    while ((pid = (uint8)UART_u16Receive_no_poll()) == QUEUE_ERROR_EMPTY)
        ;
    packet->id = pid;

    // send length
    for (int i = PACKET_LEN_SIZE - 1; i >= 0; --i)
    // for (int i = 0; i < PACKET_LEN_SIZE; ++i)
    {
        uint8 data = (uint8)UART_u16Receive_no_poll();
        if (data != QUEUE_ERROR_EMPTY)
            packet->len[i] = data;
        else
            i++;
    }

    // length of the data + (checksum : 2 bytes)
    uint16 p_length = ((uint16)(packet->len[0])) | (((uint16)(packet->len[1])) << 8);

    // length of the data only
    p_length -= PACKET_CHECKSUM_SIZE;

    // receive data

    for (int i = 0; i < p_length; ++i)
    {
        uint8 data = (uint8)UART_u16Receive_no_poll();
        if (data != QUEUE_ERROR_EMPTY)
            packet->content[i] = data;
        else
            i--;
    }

    // send checksum
    for (int i = PACKET_CHECKSUM_SIZE - 1; i >= 0; --i)
    {
        uint8 data = (uint8)UART_u16Receive_no_poll();
        if (data != QUEUE_ERROR_EMPTY)
            packet->checksum[i] = data;
        else
            i++;
    }

    return true;
}
uint16 calculate_checksum(FP_Packet_t packet)
{
    uint16 checksum = 0;
    checksum += packet.id;
    for (int i = 0; i < PACKET_LEN_SIZE; ++i)
        checksum += packet.len[i];

    uint16 p_length = ((uint16)(packet.len[0])) | (((uint16)(packet.len[1])) << 8);
    p_length -= PACKET_CHECKSUM_SIZE;

    for (int i = 0; i < p_length; ++i)
        checksum += packet.content[i];
    return checksum;
}

void fill_packet(FP_Packet_t *packet, uint8 pid, uint16 len, uint8 *data)
{
    (*(uint16 *)(packet->header)) = PACKET_START;
    (*(uint32 *)(packet->adder)) = PACKET_DEFAULT_ADDER;
    packet->id = pid;
    packet->len[0] = (len & 0x00ff);
    packet->len[1] = (len & 0xff00) >> 8;
    for (int i = 0; i < len - PACKET_LEN_SIZE; ++i)
    {
        packet->content[i] = data[i];
    }

    (*((uint16 *)packet->checksum)) = calculate_checksum(*packet);
}

uint8 FP_Verify_Password(uint32 password)
{
    FP_Packet_t vfyPwd_packet = {0};
    FP_Packet_t ack_packet = {0};

    uint8 vfypwd_pid = 0x01;
    uint16 vfypwd_len = 0x0007;
    uint8 vfypwd_content[] = {0x13,
                              (password & 0x000000FF), ((password & 0x0000FF00) >> 8),
                              ((password & 0x00FF0000) >> 16), ((password & 0xFF000000) >> 24)};

    fill_packet(&vfyPwd_packet, vfypwd_pid, vfypwd_len, vfypwd_content);

    // send_packet(vfyPwd_packet);
    send_packet_Async(vfyPwd_packet);

    // receive_packet(&ack_packet);
    receive_packet_Async(&ack_packet);

    return ack_packet.content[0];
}

uint8 FP_Collect_Image()
{
    FP_Packet_t getImg_packet = {0};
    FP_Packet_t ack_packet = {0};

    uint8 getImg_pid = 0x01;
    uint16 getImg_len = 0x0003;
    uint8 getImg_content[] = {0x01};
    fill_packet(&getImg_packet, getImg_pid, getImg_len, getImg_content);
    // send_packet(getImg_packet);
    send_packet_Async(getImg_packet);

    // receive_packet(&ack_packet);
    receive_packet_Async(&ack_packet);
    return ack_packet.content[0];
}

uint8 FP_Upload_Image()
{
    FP_Packet_t getImg_packet = {0};
    FP_Packet_t ack_packet = {0};

    uint8 getImg_pid = 0x01;
    uint16 getImg_len = 0x0003;
    uint8 getImg_content[] = {0x0A};
    fill_packet(&getImg_packet, getImg_pid, getImg_len, getImg_content);
    // send_packet(getImg_packet);
    send_packet_Async(getImg_packet);

    // receive_packet(&ack_packet);
    receive_packet_Async(&ack_packet);
    return ack_packet.content[0];
}

uint8 FP_Gen_Char_File(uint8 charBuffer_id)
{
    FP_Packet_t img2CharFile_packet = {0};
    FP_Packet_t ack_packet = {0};

    uint8 img2CharFile_packet_pid = 0x01;
    uint16 img2CharFile_packet_len = 0x0004;
    uint8 img2CharFile_packet_content[] = {0x02, charBuffer_id};
    fill_packet(&img2CharFile_packet, img2CharFile_packet_pid, img2CharFile_packet_len, img2CharFile_packet_content);
    // send_packet(img2CharFile_packet);
    send_packet_Async(img2CharFile_packet);

    // receive_packet(&ack_packet);
    receive_packet_Async(&ack_packet);
    return ack_packet.content[0];
}

uint8 FP_Gen_Template()
{
    FP_Packet_t gen_temp_packet = {0};
    FP_Packet_t ack_packet = {0};

    uint8 gen_temp_packet_pid = 0x01;
    uint16 gen_temp_packet_len = 0x0003;
    uint8 gen_temp_packet_content[] = {0x05};

    fill_packet(&gen_temp_packet, gen_temp_packet_pid, gen_temp_packet_len, gen_temp_packet_content);

    // send_packet(gen_temp_packet);
    send_packet_Async(gen_temp_packet);

    // receive_packet(&ack_packet);
    receive_packet_Async(&ack_packet);
    return ack_packet.content[0];
}

uint8 FP_Store_Template(uint8 BufferID, uint16 PageID)
{
    FP_Packet_t store_temp_packet = {0};
    FP_Packet_t ack_packet = {0};

    uint8 store_temp_packet_pid = 0x01;
    uint16 store_temp_packet_len = 0x0006;
    uint8 store_temp_packet_content[] = {0x06, BufferID, ((PageID & 0xFF00) >> 8), (PageID & 0x00FF)};

    fill_packet(&store_temp_packet, store_temp_packet_pid, store_temp_packet_len, store_temp_packet_content);

    // send_packet(store_temp_packet);
    send_packet_Async(store_temp_packet);

    // receive_packet(&ack_packet);
    receive_packet_Async(&ack_packet);
    return ack_packet.content[0];
}

uint8 FP_Delete_Template(uint8 page_id, uint16 n_temps)
{
    FP_Packet_t delete_temp_packet = {0};
    FP_Packet_t ack_packet = {0};

    uint8 delete_temp_packet_pid = 0x01;
    uint16 delete_temp_packet_len = 0x0007;
    uint8 delete_temp_packet_content[] = {0x0c, (page_id & 0xFF00) >> 8, (page_id & 0x00FF), (n_temps & 0xFF00) >> 8, (n_temps & 0x00FF)};

    fill_packet(&delete_temp_packet, delete_temp_packet_pid, delete_temp_packet_len, delete_temp_packet_content);

    // send_packet(delete_temp_packet);
    send_packet_Async(delete_temp_packet);

    // receive_packet(&ack_packet);
    receive_packet_Async(&ack_packet);
    return ack_packet.content[0];
}

uint8 FP_Search_Templates(uint8 buffer_id, uint16 starting_page, uint16 n_pages, uint16 *matching_temp_id)
{

    FP_Packet_t search_temps_packet = {0};
    FP_Packet_t ack_packet = {0};

    uint8 search_temps_packet_pid = 0x01;
    uint16 search_temps_packet_len = 0x0008;
    uint8 search_temps_packet_content[] = {0x04, buffer_id, (starting_page & 0xFF00) >> 8, (starting_page & 0x00FF), (n_pages & 0xFF00) >> 8, (n_pages & 0x00FF)};

    fill_packet(&search_temps_packet, search_temps_packet_pid, search_temps_packet_len, search_temps_packet_content);

    // send_packet(search_temps_packet);
    send_packet_Async(search_temps_packet);

    // receive_packet(&ack_packet);
    receive_packet_Async(&ack_packet);
    if (ack_packet.content[0] == ACK_MATCH_FOUND)
        *matching_temp_id = (((uint16)(ack_packet.content[1])) << 8) | (uint16)(ack_packet.content[2]);
    else
        *matching_temp_id = 0;
    return ack_packet.content[0];
}

uint16 FP_Match_Finger_Print(void)
{
    uint8 status;
    uint16 match_id;
    // collect image 1
    while ((status = FP_Collect_Image()) != ACK_FINGER_COLLECTION_SUCCESS)
    {
        lcd_clearAndHome();
        lcd_displayString("collecting 1...");
    }
    status = FP_Gen_Char_File(1);
    if (status == ACK_CHAR_FILE_GEN_COMPLETE)
    {
        lcd_clearAndHome();
        lcd_displayString("Collected: 1/2");

        // collect image 2
        while ((status = FP_Collect_Image()) != ACK_FINGER_COLLECTION_SUCCESS)
        {
            lcd_clearAndHome();
            lcd_displayString("collecting 2...");
        }

        status = FP_Gen_Char_File(2);
        if (status == ACK_CHAR_FILE_GEN_COMPLETE)
        {
            lcd_clearAndHome();
            lcd_displayString("Collected: 2/2");
            status = FP_Gen_Template();
            if (status == ACK_OP_SUCSESS)
            {
                status = FP_Search_Templates(1, 1, 6, &match_id);
            }
            else
            {
                lcd_clearAndHome();
                lcd_displayString("Template Gen. failed ");
            }
        }
        else
        {
            lcd_clearAndHome();
            lcd_displayString("Char file 2 failed ");
        }
    }
    else
    {
        lcd_clearAndHome();
        lcd_displayString("Char file 1 failed ");
    }
    return match_id;
}

void FP_Save_Finger_Print(uint8 page_id)
{
    uint8 status;
    // collect image 1
    while ((status = FP_Collect_Image()) != ACK_FINGER_COLLECTION_SUCCESS)
    {
        lcd_clearAndHome();
        lcd_displayString("collecting 1...");
    }
    status = FP_Gen_Char_File(1);
    if (status == ACK_CHAR_FILE_GEN_COMPLETE)
    {
        lcd_clearAndHome();
        lcd_displayString("Collected: 1/2");

        // collect image 2
        while ((status = FP_Collect_Image()) != ACK_FINGER_COLLECTION_SUCCESS)
        {
            lcd_clearAndHome();
            lcd_displayString("collecting 2...");
        }

        status = FP_Gen_Char_File(2);
        if (status == ACK_CHAR_FILE_GEN_COMPLETE)
        {
            lcd_clearAndHome();
            lcd_displayString("Collected: 2/2");
            status = FP_Gen_Template();
            if (status == ACK_OP_SUCSESS)
            {
                status = FP_Store_Template(1, page_id);
                if (status == ACK_STORAGE_SUCCESS)
                    lcd_displayString("FP Saved");
                else
                {
                    lcd_displayString("storage falied");
                }
                TIMER0_Delay_ms_with_Blocking(2000);
            }
            else
            {
                lcd_clearAndHome();
                lcd_displayString("temp gen failed ");
            }
        }
        else
        {
            lcd_clearAndHome();
            lcd_displayString("Char file 2 failed ");
        }
    }
    else
    {
        lcd_clearAndHome();
        lcd_displayString("Char file 1 failed ");
    }
}