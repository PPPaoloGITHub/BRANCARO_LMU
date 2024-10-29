/**
 *  @file       EEPROM24LC512.c
 *  @brief      Driver for 24LC512 EEPROM with I2C Serial Interface
 *
 *  @details    ---
 *
 *  $Header: 	ver 1.0 Paolo Parrino
 *
 *  @copyright  *****  Copyright BRANCARO Industries.  All rights reserved - CONFIDENTIAL  *****
 */

/**
 * *****************************************  DESCRIPTION  ****************************************
 * The 24LC512 EEPROM is an I2C device with a capacity of 512Kb (64KB) and requires the use of
 * specific commands to read and write data. The driver is designed to be compatible with any 
 * microcontroller that supports I2C to manage the EEPROM via a standard I2C interface.
 * 
 * MAIN FUNCTIONS:
 * 1) Initialization: EEPROM24LC512__Initialize() initializes the module.
 * 
 * 2) Handler every 25ms: EEPROM24LC512__Handler25ms() manage repetitive task in the module
 *
 * 2) Write: EEPROM24LC512WriteByte() writes a single byte to the EEPROM.
 *    For more bytes, you can use the EEPROM24LC512WritePage() function (up to 128 bytes per page).
 *
 * 3) Read: EEPROM24LC512ReadByte() reads a single byte. The EEPROM24LC512ReadBytes() function allows 
 *    multiple bytes to be read consecutively.
 *
 * 4) Waiting for write completion: EEPROM24LC512WaitForWrite() waits for the EEPROM to complete a
 *    write operation before proceeding to other operations.
 *
 * NOTE:
 * The 24LC512 EEPROM supports pages of 128 bytes, so you need to make sure that you do not exceed 
 * this limit during paged write operations
 * 
 * USAGE EXAMPLE:
 * void EEPROM24LC512__Handler25ms(void)
 * {
 *    //    static uint8 readData = 0x88;
 * //    static uint8 cntErr = 0;
 *     static uint8 oneTimeOnly = 0;
 *     
 *     static uint8 dataBuffer[] = 
 *     {
 *       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
 *       0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11,
 *       0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
 *       0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
 *       0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44,
 *       0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
 *       0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66,
 *       0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77,
 *       0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
 *       0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99, 0x99,
 *       0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
 *       0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB,
 *       0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 
 *       0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD, 0xDD,
 *       0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,
 *       0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, 0xF8
 *     };
 *     static uint8 readBuffer[128];
 *     uint8 k;
 *     uint8 cnt = 0;
 *     
 *     oneTimeOnly++;
 *     
 *   // TEST write - Read one Byte in EEPROM
 * //    if(oneTimeOnly == 10)
 * //    {
 * //        readData = 0;
 * //        printf("Write a byte in EEPROM\r\n");
 * //        // Write the byte 0x42 ('B') at 0x0008 EEPROM address
 * //        EEPROM24LC512_Interf.WriteByte(0x0008, 0x42);
 * //    }
 * //    else if(oneTimeOnly == 11)
 * //    {
 * //        printf("Read a byte in EEPROM\r\n");
 * //         // Read The byte at 0x0008 address
 * //        EEPROM24LC512_Interf.ReadByte(0x0008, &readData);
 * //    }
 * //    else if(oneTimeOnly == 12)
 * //    {
 * //        // Waiting for I2C module is free
 * //        while(EEPROM24LC512_Interf.IsI2CBusy() == true);
 * //        
 * //        if(readData != 0x42)
 * //        {
 * //            cntErr ++;
 * //        }
 * //        printf("EEPROM data: %d\r\nError Counter: %d\r\n\r\n", readData, cntErr);
 * //    }
 * //    else
 * //    {
 * //        //do nothing
 * //    }
 *   
 *   // TEST write - Read more Bytes (max a page 128 Bytes) in EEPROM
 *     if(oneTimeOnly == 10)
 *     {
 *         readData = 0;
 *         printf("\r\n\r\nWrite a page in EEPROM done\r\n");
 *         // Write the dataBuffer starting from 0x0080 EEPROM address
 *         EEPROM24LC512_Interf.WritePage(0x0080, dataBuffer, 128);
 *     }
 *     else if(oneTimeOnly == 14)
 *     {
 *         printf("Read a page in EEPROM done\r\n");
 *          // Read page starting from 0x0080 address
 *         EEPROM24LC512_Interf.ReadBytes(0x0080, readBuffer, 128);
 *     }
 *     else if(oneTimeOnly == 18)
 *     {
 *         // Waiting for I2C module is free
 *         while(EEPROM24LC512_Interf.IsI2CBusy() == true);
 *         
 *         printf("EEPROM data page:\r\n");
 *         for(k = 0; k < 128; k++)
 *         {
 *             printf(", 0x%x", readBuffer[k]);
 *             if(cnt++ >= 7 )
 *             {
 *                 cnt = 0;
 *                 printf("\r\n");
 *             }
 *         }
 *     }
 *     else
 *     {
 *         //do nothing
 *     }
 * 
 */ 



//-------------------------------------- Include Files ----------------------------------------------------------------
#include <stdio.h>

#include "../../ProductLibraryInclude/EEPROM24LC512.h"


//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- PRIVATE (Variables, Constants & Defines) -------------------------------------
static uint8 WriteBuffer[132];
static uint8 ReadBuffer[2];


//-------------------------------------- PRIVATE (Function Prototypes) ------------------------------------------------
static bool  EEPROM24LC512WriteByte(uint16 memoryAddr, uint8 data);
static bool  EEPROM24LC512WritePage(uint16 memoryAddr, uint8 *data, uint16 length);
static bool  EEPROM24LC512ReadByte (uint16 memoryAddr, uint8 *data);
static bool  EEPROM24LC512ReadBytes(uint16 memoryAddr, uint8 *buffer, uint16 length);
static bool  EEPROM24LC512IsI2CBusy(void);


const struct EEPROM24LC512_INTRFACE_STRUCT EEPROM24LC512_Interf =
{
    .Initialize = &EEPROM24LC512__Initialize,
    .Handler5ms = &EEPROM24LC512__Handler25ms,
    .WriteByte  = &EEPROM24LC512WriteByte,
    .WritePage  = &EEPROM24LC512WritePage,
    .ReadByte   = &EEPROM24LC512ReadByte,
    .ReadBytes  = &EEPROM24LC512ReadBytes,
    .IsI2CBusy  = &EEPROM24LC512IsI2CBusy,
};


//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  This function initializes the EEPROM 24LC512 module
  *
  * @param  None
  * @retval None
  * @note	None
  */
void EEPROM24LC512__Initialize(void)
{
    /* Set I2C Clock frequency at 400KHz */
    /* EEPROM 24LC512 has Max Clock Frequency = 400KHz */
    struct I2C_TRANSFER_SETUP tempVar;
    
    tempVar.clkSpeed = 400000UL;
    I2C1_Host.TransferSetup(&tempVar, 0);
}

/**
  * @brief  EEPROM 24LC512 module handler. It manages all the module functionalities
  *
  * @param  None
  * @retval None
  * @note	call this function in the task every 25ms
  */
void EEPROM24LC512__Handler25ms(void)
{

}


//=====================================================================================================================
//-------------------------------------- Private Functions ------------------------------------------------------------
//=====================================================================================================================
/**
  * @brief  It writes a single byte to the specified memory address
  *
  * @param  [in] memoryAddr: I2C device address in range [0x0000 - 0xFFFF]
  *         [in] data:       byte to be written in EEPROM
  * 
  * @retval true:       the request was placed successfully and the bus activity was initiated
  * false:              the request fails, if there was already a transfer in progress
  *                     when this function was called
  * @note	None
  */
static bool  EEPROM24LC512WriteByte(uint16 memoryAddr, uint8 data)
{
    bool retVal;
     
    // Waiting for I2C module is free
    while(EEPROM_I2CIsBusy() == true);
        
    WriteBuffer[0] = HIBYTE_WORD(memoryAddr);
    WriteBuffer[1] = LOBYTE_WORD(memoryAddr);
    WriteBuffer[2] = data;
    retVal = EEPROM_I2CWrite(EEPROM24LC512_I2C_ADDRESS, WriteBuffer, 3);
     
    return retVal;
}

/**
  * @brief  It writes multiple bytes, in sequence, started from the specified memory address   
  *
  * @param  [in] memoryAddr: I2C device address in range [0x0000 - 0xFFFF]
  *         [in] data:       pointer to the buffer to be written in EEPROM
  *         [in] dataLength: bytes to write length
  * 
  * @retval true:       the request was placed successfully and the bus activity was initiated
  *         false:      the request fails, if there was already a transfer in progress
  *                     when this function was called
  * 
  * @note	EEPROM 24LC512 has maximum 128 bytes per page, so, 'length' parameter has to be less than 128!
  *         ==> Page write operations are limited to writing bytes within a single physical page,  <==
  *         regardless of the number of bytes actually being written. Physical page boundaries start at
  *         addresses that are integer multiples of the page buffer size (or ?page size?) and end at 
  *         addresses that are integer multiples of [page size ? 1]. If a Page Write command attempts to write
  *         across a physical page boundary, the result is that the data wraps around to the beginning of
  *         the current page (overwriting data previously stored there), instead of being written to the 
  *         next page as might be expected. It is therefore necessary for the application software to 
  *         prevent page write operations that would attempt to cross a page boundary.
  */
static bool  EEPROM24LC512WritePage(uint16 memoryAddr, uint8 *data, uint16 dataLength)
{
    bool retVal;
    uint8 k;
    
    /* EEPROM 24LC512 has maximum 128 bytes per page */
    if(dataLength > EEPROM24LC512_MAX_BYTE_PER_PAGE)
    {
        retVal = FALSE;
    }
    else
    {
        // Waiting for I2C module is free
        while(EEPROM24LC512_Interf.IsI2CBusy() == true);
        
        WriteBuffer[0] = HIBYTE_WORD(memoryAddr);
        WriteBuffer[1] = LOBYTE_WORD(memoryAddr);
        
        for(k = 0; k < dataLength; k++)
        {
            WriteBuffer[k+2] = *(data + k);
        }
        retVal = EEPROM_I2CWrite(EEPROM24LC512_I2C_ADDRESS, WriteBuffer, (dataLength + 2));   // + 2 because memory address are 2 bytes
    }
    
    return retVal;
}

/**
  * @brief  It reads a single byte from the specified memory address. 
  *
  * @param  [in]  memoryAddr: I2C device address in range [0x0000 - 0xFFFF]
  *         [out] data:       pointer to source data buffer that contains the read data into EEPROM
   * 
  * @retval true:       the request was placed successfully and the bus activity was initiated
  *         false:      the request fails, if there was already a transfer in progress
  *                     when this function was called
  * @note	None
  */
static bool EEPROM24LC512ReadByte(uint16 memoryAddr, uint8 *data)
{
    bool retVal;
    
    // Waiting for I2C module is free
    while(EEPROM24LC512_Interf.IsI2CBusy() == true);
    
    // Sending the EEPROM address from which you want to read 
    ReadBuffer[0] = HIBYTE_WORD(memoryAddr);
    ReadBuffer[1] = LOBYTE_WORD(memoryAddr);
    retVal = EEPROM_I2CWrite(EEPROM24LC512_I2C_ADDRESS, ReadBuffer, 2);
    
    if(retVal == true)
    {    
        // Waiting for I2C module is free
        while(EEPROM24LC512_Interf.IsI2CBusy() == true);
        // Reads the byte at the memory address requested before
        retVal = EEPROM_I2CRead(EEPROM24LC512_I2C_ADDRESS, data, 1);
    }
    else
    {
        retVal = false;
    }
     
    return retVal;
}

/**
  * @brief  It reads multiple bytes, in sequence, started from the specified memory address 
  *
  * @param  [in]  memoryAddr: I2C device address in range [0x0000 - 0xFFFF]
  *         [out] buffer:     pointer to the source data buffer that will receive the data read into EEPROM
  *         [in] length:      bytes to read length
  * 
  * @retval true:       the request was placed successfully and the bus activity was initiated
  *         false:      the request fails, if there was already a transfer in progress
  *                     when this function was called
  * @note	None
  */
static bool  EEPROM24LC512ReadBytes(uint16 memoryAddr, uint8 *buffer, uint16 dataLength)
{
    bool retVal;
    
    // Waiting for I2C module is free
    while(EEPROM24LC512_Interf.IsI2CBusy() == true);
    
    // Sending the EEPROM address from which you want to read 
    ReadBuffer[0] = HIBYTE_WORD(memoryAddr);
    ReadBuffer[1] = LOBYTE_WORD(memoryAddr);
    retVal = EEPROM_I2CWrite(EEPROM24LC512_I2C_ADDRESS, ReadBuffer, 2);
    
    if(retVal == true)
    {    
        // Waiting for I2C module is free
        while(EEPROM24LC512_Interf.IsI2CBusy() == true);
        // Reads the bytes starting from the memory address requested before
        retVal = EEPROM_I2CRead(EEPROM24LC512_I2C_ADDRESS, buffer, dataLength);
    }
    else
    {
        retVal = false;
    }

    return retVal;
}

/**
  * @brief  This function returns true if the I2C module is busy with 
  *         a transfer. The application can use this function to check if I2C 
  *         module is busy before calling any of the data transfer functions. 
  *         The library does not allow a data transfer operation if another 
  *         transfer  operation is already in progress.
  *  
  * @param  None
  * 
  * @retval I2C module status:
  *         true:  Busy
  *         false: Not Busy
  * 
  * @note	None
  */
static bool EEPROM24LC512IsI2CBusy(void)
{
    bool retVal;
    
    retVal = EEPROM_I2CIsBusy();
    
    return retVal;
}

