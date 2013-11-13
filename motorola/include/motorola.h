#ifndef MOTOROLA_H_INCLUDED
#define MOTOROLA_H_INCLUDED

/** 
    Frame format:

    n*0x55      (MOTOROLA_PREAMBLE_COUNT*MOTOROLA_PREAMBLE)
    0xff        (1 byte)
    1           (1 byte)
    address     (1 byte)
    command     (1 byte)
    data length (2 byte little endian (LH) format)
    data bytes  (data_length*byte
    crc         (2 byte little endian (LH) format)
*/


#define MOTOROLA_PREAMBLE "preamble.char"
#define MOTOROLA_DEF_PREAMBLE 0x55

#define MOTOROLA_PREAMBLE_COUNTS "preamble.counts"
#define MOTOROLA_DEF_PREAMBLE_COUNTS 1

#define MOTOROLA_MTU "mtu"
#define MOTOROLA_DEF_MTU 32

#define MOTOROLA_FRAME_QUEUE_SIZE "frame-queue.size"
#define MOTOROLA_DEF_FRAME_QUEUE_SIZE 5



#include <motorola.h>


struct adat *MotInit(char *serial_id);

struct adat *MotInitDirect(char *serial_id,
                                           int queue_size, int mtu,
                                           char preamble, int preamble_counts);

void MotReceive(struct adat *data);

int MotSend(struct adat *data,
                         int address, int command,
                         char *buffer, int data_length);


#endif // MOTOROLA_H_INCLUDED
