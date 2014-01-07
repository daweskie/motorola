/*
 * Copyright (C) 2011 Zoltan Zidarics (Zamek)
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/** \file motorola.c
    \brief Motorola frame handler for serial
*/
#include <stdlib.h>
#include <motorola.h>
#include <serial.h>
#include <macros.h>
#include <crc.h>
#include <config_common.h>
#include <highlevel.h>

#define MOTOROLA_UNKNOWN_ADDRESS -1
#define MOTOROLA_UNKNOWN_COMMAND -1

enum MotoFrameState_t{  // moto prookol struct
    mfs_none,           // none
    mfs_55,             // hex 55
    mfs_1,              // hex 1
    mfs_address,        // address
    mfs_command,        // command
    mfs_data_len_lo,    // data ?
    mfs_data_len_hi,    // data ?
    mfs_data,           // data
    mfs_crc_lo,         // crc ?
    mfs_crc_hi          // crc
};

static struct Motorola_t{                   //
    enum MotoFrameState_t frame_state;      //
    crc_t on_the_fly_crc;                   // szamitott
    crc_t received_crc;                     //  kapott
    unsigned char *temp_buffer;             //
    struct hls_frame_t *current_frame;      //
    char preamble;                          // erorrs
    int preamble_counts;                    // erorr count
    int data_index;                         // data
};

struct hls_data_t *motorola_init_by_direct(char *serial_id, int queue_size,
                                           int mtu, char preamble, int preamble_counts)
{
    struct hls_data_t *result = hls_init(serial_id,
                        motorola_receive_char, motorola_send_frame,
                        queue_size, mtu);
    if (!result)
        return NULL;

    struct Motorola_t *private_data;
    MALLOC(private_data, sizeof(struct motorola_t));
    MALLOC(private_data->temp_buffer,result->mtu);
    private_data->frame_state = mfs_none;
    private_data->preamble = preamble;
    private_data->preamble_counts = preamble_counts;
    result->private_data = private_data;
    return result;
}

struct hls_data_t *motorola_init(char *serial_id)  //data int
{
    char temp[128];
    return motorola_init_by_direct(
            serial_id, cfg_get_int_def(cfg_create_key(serial_id, MOTOROLA_KEY_FRAME_QUEUE_SIZE, temp),
                                       MOTOROLA_DEF_FRAME_QUEUE_SIZE),
                       cfg_get_int_def(cfg_create_key(serial_id, MOTOROLA_KEY_MTU, temp),
                                       MOTOROLA_DEF_MTU),
                       cfg_get_int_def(cfg_create_key(serial_id, MOTOROLA_KEY_PREAMBLE, temp),
                                       MOTOROLA_DEF_PREAMBLE),
                       cfg_get_int_def(cfg_create_key(serial_id, MOTOROLA_KEY_PREAMBLE_COUNTS, temp),
                                        MOTOROLA_DEF_PREAMBLE_COUNTS));
}

static inline struct Motorola_t *extract_private_data(struct hls_data_t *hls_data)
{
    return (struct Motorola_t *) hls_data->private_data;
}

void Motorola_receive_char(struct hls_data_t *hls_data)
{
    #define crc_calc() \
        private_data->on_the_fly_crc = crc_add_byte(private_data->on_the_fly_crc, ch)

    if (! (hls_data && hls_data->private_data) )
        return;

    struct Motorola_t *private_data = extract_private_data(hls_data);
    int num_chars;
    if ( num_chars = (serial_get_char_buffer(
                        hls_data->serial_id, private_data->temp_buffer,
                        hls_data->mtu) <= 0) )
        return;

    unsigned char *cptr=private_data->temp_buffer;
    unsigned char ch;
    for ( ; num_chars > 0; num_chars--) {
        ch = *cptr++;
        switch (private_data->frame_state) {
        case mfs_none :
            if (ch == private_data->preamble)
                private_data->frame_state = mfs_55;

            continue;

        case mfs_55 :
            if (ch == private_data->preamble)
                continue;
            if (ch == 0xff) {
                private_data->frame_state = mfs_1;
                continue;
            }
            break;

        case mfs_1 :
            if (ch==1) {
                private_data->on_the_fly_crc = 0;
                private_data->frame_state = mfs_address;
                ++hls_data->received_frames;
                continue;
            }
            break;

        case mfs_address :
            if (private_data->current_frame) {
                ++hls_data->overruns;
                break;
            }
            crc_calc();
            private_data->current_frame = hls_get_new_frame(hls_data);
            private_data->current_frame->address = ch;
            private_data->frame_state = mfs_command;
            continue;

        case mfs_command :
            crc_calc();
            private_data->current_frame->command = ch;
            private_data->frame_state = mfs_data_len_lo;
            continue;

        case mfs_data_len_lo :
            crc_calc();
            private_data->current_frame->data_length = ch & 0xff;
            private_data->frame_state = mfs_data_len_hi;
            continue;

        case mfs_data_len_hi :
            crc_calc();
            private_data->current_frame->data_length |= (ch & 0xff) << 8;
            private_data->data_index = 0;
            if (private_data->current_frame->data_length >0) {
                if (private_data->current_frame->data_length > hls_data->mtu)
                    break;
                MALLOC(private_data->current_frame->data, private_data->current_frame->data_length);
                private_data->frame_state = mfs_data;
                continue;
            }
            private_data->frame_state = mfs_crc_lo;
            continue;

        case mfs_data :
            crc_calc();
            *(private_data->current_frame->data+private_data->data_index) = ch;
            if (++private_data->data_index >= private_data->current_frame->data_length)
                private_data->frame_state = mfs_crc_lo;
            continue;

        case mfs_crc_lo :
            private_data->received_crc = ch & 0xff;
            private_data->frame_state = mfs_crc_hi;
            continue;

        case mfs_crc_hi :
            private_data->received_crc |= (ch & 0xff) << 8;
            if (crc_check(private_data->on_the_fly_crc, private_data->received_crc)) {
                hls_add_receive_frame(hls_data, private_data->current_frame);
                private_data->frame_state=mfs_none;
                continue;
            }
            break;
        }


    }
    return;
}

int MotoSendFrame(struct hls_data_t *hls_data,                  // keret kuldes (  hls data , cim , commad, buffer ertek , adat hossz , )
                         int address, int command,
                         char *buffer, int data_length)                                 ///define ##  send_ch(ch )  ?????
{
    #define send_ch(ch) \
        crc_add_byte(crc,(ch)); \
        if (serial_send_char(serial_id, (ch)) != EXIT_SUCCESS) \
            return EXIT_FAILURE

    if (!hls_data || address <= MOTOROLA_UNKNOWN_ADDRESS                    // ha nem igaz hls_data vagy a cim NEM ISMERT vagy a buffer ures vagy az adat hossz != buffer hossz
            || (buffer && data_length>0) || (data_length<0 && !buffer))
        return EXIT_FAILURE;                                                  //akkor exit.
    int i;
    char *serial_id = hls_data->serial_id;                                    // serial_id legyen hls_data bol serial_id
    struct motorola_t *private_data = extract_private_data(hls_data);         // motorla_t privat_data pointer erteke legyen extract_privat_data(hls_data)  ???

    for(i=0;i<private_data->preamble_counts;i++)                                //for ameg privat_data problem_counts nagyobb mint i
        if (serial_send_char(serial_id, private_data->preamble)!=EXIT_SUCCESS)  // ha soros karakter kuldes problema nem egyenlo kilepes
            return EXIT_FAILURE;                                                // kulomben kilep

    if (! (serial_send_char(serial_id, 0xff)==EXIT_SUCCESS                      // ha adat ayaonosito  0xff  nem exit && adat azonosito 1 es nem exit  akkor kilep
           && serial_send_char(serial_id, 1)==EXIT_SUCCESS))
        return EXIT_FAILURE;
    crc_t crc=0;                                                                // crc legyen 0
    send_ch(command);                                                           // kuld parapcs
    send_ch(address);                                                           // kuld cim
    char ch = data_length & 0xff;                                               // ch = data hosz es 0xff
    send_ch(ch);                                                                // kuld ch                            elso 8 bit
    ch = (data_length >> 8) & 0xff;                                             // ch = data hosz nagyobb 8 es 0xff
    send_ch(ch);                                                                // send ch                            masidik 8 bit
    if (data_length>0)                                                          // ha adat hossz nagzobb 0
        for (i=0;i<data_length;i++) {                                           // ameg i kisszebb adat hossz addig
            ch = *(buffer+i);                                                   // a ch add a puffer be
            send_ch(ch);                                                        // kuld ch
        }

    return serial_send_char(serial_id, crc & 0xff) == EXIT_SUCCESS              // soroscaracter kuldes -> soros id , crc & 0xff == kilepes
           && serial_send_char(serial_id, (crc >> 8) & 0xff) == EXIT_SUCCESS       // && ha soros caharacter kuldes (soros azonoito crc nagyobb 8 & 0xff) == kilepes
           ? EXIT_SUCCESS : EXIT_FAILURE;                                           // ??????
}
