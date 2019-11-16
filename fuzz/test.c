/**
* @file test.c
* FUZZ_TOOL 1 runs AFL and 2 runs libfuzzer
*
*/

/*======= Includes ==========================================================*/

#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "udp.h"

/*======= Local Macro Definitions ===========================================*/

#ifndef MTU
    #define MTU 65535U
#endif

#ifndef FUZZ_TOOL
    #define FUZZ_TOOL 2
#endif

/*======= Type Definitions ==================================================*/
/*======= Local function prototypes =========================================*/
/*======= Local variable declarations =======================================*/
/*======= Global function implementations ===================================*/
/*======= Local function implementations ====================================*/

#if FUZZ_TOOL == 1

static uint8_t tmp_buffer[MTU];

int main(void)
{
    Udp message;
    
    ssize_t size = read(0, tmp_buffer, sizeof(tmp_buffer));
    if (size <= 0)
    {
        return false;
    }
    uint8_t *buffer;
    buffer = (uint8_t *) malloc(size);
    memcpy(buffer, tmp_buffer, size);
    if ((NULL == buffer) || (1 > (size_t) size))
    {
        return false;
    }

    parseUdpPacket(buffer, (size_t) size, &message);
    free(buffer);
}

#elif FUZZ_TOOL == 2

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    Udp message;
    parseUdpPacket(data, size, &message);
    return 0;
}
#else
    #error "No FUZZ_TOOL assigned"
#endif

