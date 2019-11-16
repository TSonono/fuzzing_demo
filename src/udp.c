/**
* @file udp.c
*
* Description
*
*/

/*======= Includes ==========================================================*/

#include "udp.h"

/*======= Local Macro Definitions ===========================================*/

#define SHIFT_FOR_16 8
#define UDP_HEADER_SIZE 8

/*======= Type Definitions ==================================================*/
/*======= Local function prototypes =========================================*/

static uint16_t concatTwoBytes(uint8_t byte1, uint8_t byte2);

/*======= Local variable declarations =======================================*/
/*======= Global function implementations ===================================*/

bool parseUdpPacket(const uint8_t *data, size_t size, Udp *message)
{
    if (NULL == data || NULL == message || size < UDP_HEADER_SIZE)  // What happens if we remove this check
    {
        return false;
    }

    message->srcPort = concatTwoBytes(data[0], data[1]);
    message->destPort = concatTwoBytes(data[2], data[3]);
    message->length = concatTwoBytes(data[4], data[5]);
    message->checksum = concatTwoBytes(data[6], data[7]);

    if(0 != message->checksum)
    {
        return false;
    }

    if(size != message->length) // What happens if we remove this check
    {
        return false;
    }
    message->lastByte= *(data + message->length - 1); // What happens if we remove -1

    return true;
}

/*======= Local function implementations ====================================*/

// Big endian
static uint16_t concatTwoBytes(uint8_t byte1, uint8_t byte2)
{
    return ((uint16_t) byte1 << SHIFT_FOR_16) | byte2;
}

