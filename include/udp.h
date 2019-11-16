#ifndef _udp_H_
#define _udp_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
* @file udp.h
*
* Description
*
*/

/*======= Includes ==========================================================*/

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>


/*======= Public macro definitions ==========================================*/
/*======= Type Definitions and declarations =================================*/

typedef struct UdpStruct {
    uint16_t    srcPort;
    uint16_t    destPort;
    uint16_t    length;
    uint16_t    checksum;
    uint8_t     lastByte;   // To "demonstrate" potential memory mistakes
} Udp;

/*======= Public variable declarations ======================================*/
/*======= Public function declarations ======================================*/

bool parseUdpPacket(const uint8_t *data, size_t size, Udp *message);

#ifdef __cplusplus
}
#endif

#endif /* _udp_H_ */
