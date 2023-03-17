#ifndef FINGER_PRINT_H
#define FINGER_PRINT_H

#include "../../LIB/Datatypes.h"
#include "FP_Status_Macros.h"
void FP_Init();

/* Detects finger and store the detected finger image in <ImageBuffer> */
uint8 FP_Collect_Image(); // done
// uint8 FP_Upload_Image();  // done
// uint8 FP_Download_Image();
/* Generates 'character_file' from finger_image in <ImageBuffer>  and save it at <char_buffer>[charBuffer_id] -- "charBuffer_id" ranges [1:6] */
uint8 FP_Gen_Char_File(uint8 charBuffer_id); // done
/* Combines character files from <CharBuffer1> and <CharBuffer2>
 * and generate a template which is stroed back in both <CharBuffer1> and <CharBuffer2>. */
uint8 FP_Gen_Template(); // done
// uint8 FP_Upload_Template(uint8 *temp);
// uint8 FP_Download_Template(uint8 *temp);
/* Stores the template of specified buffer <CharBuffer1/CharBuffer2> at the designated location of <Flash library>. */
uint8 FP_Store_Template(uint8 BufferID, uint16 PageID);
// uint8 FP_Read_Template(uint8 *temp);
/* delete (n_temps) templates of Flash library started from (page_id) */
uint8 FP_Delete_Template(uint8 page_id, uint16 n_temps);

// uint8 FP_Empty_Library(void);
// uint8 FP_Match_Templates(uint8 tmp1_id, uint8 tmp2_id);
uint8 FP_Search_Templates(uint8 buffer_id, uint16 starting_page, uint16 n_pages, uint16 *matching_temp_id);

/* ----------- util funcs ------*/
void FP_Save_Finger_Print(uint8 page_id);
uint16 FP_Match_Finger_Print(void);

#endif