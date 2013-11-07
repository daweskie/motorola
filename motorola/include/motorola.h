#ifndef MOTOROLA_H_INCLUDED
#define MOTOROLA_H_INCLUDED

/*
 * Copyright (C)  2011 Zoltan Zidarics (Zamek)
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/** \file motorola.h
    \brief Motorola frame handler for serial

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

/**
    Config keys for motorola module
*/
#define MOTOROLA_KEY_PREAMBLE "preamble.char"
#define MOTOROLA_DEF_PREAMBLE 0x55

#define MOTOROLA_KEY_PREAMBLE_COUNTS "preamble.counts"
#define MOTOROLA_DEF_PREAMBLE_COUNTS 1

#define MOTOROLA_KEY_MTU "mtu"
#define MOTOROLA_DEF_MTU 32

#define MOTOROLA_KEY_FRAME_QUEUE_SIZE "frame-queue.size"
#define MOTOROLA_DEF_FRAME_QUEUE_SIZE 5


#include <highlevel.h>
#include <motorola.h>
#include <crc.h>
#include <config_common.h>

struct hls_data_t *motorola_init(char *serial_id);

struct hls_data_t *motorola_init_by_direct(char *serial_id,
                                           int queue_size, int mtu,
                                           char preamble, int preamble_counts);

void motorola_receive_char(struct hls_data_t *hls_data);

int motorola_send_frame(struct hls_data_t *hls_data,
                         int address, int command,
                         char *buffer, int data_length);


#endif // MOTOROLA_H_INCLUDED
