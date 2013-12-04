#ifndef HIGHLEVEL_H_INCLUDED
#define HIGHLEVEL_H_INCLUDED

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
/** \file highlevel.h
    \brief High level serial handler prototype


*/

#include <serial.h>
#include <sys/queue.h>

struct hls_data_t;

typedef void hls_receive_char_handler_t(struct hls_data_t *hls_data);

typedef int hls_send_packet_handler_t(struct hls_data_t *hls_data,
                int address, int command, char *buffer, int data_length);


/**
    General frame format
*/
struct hls_frame_t {
    int address;
    int command;
    int data_length;
    char *data;
    int valid;
    TAILQ_ENTRY(hls_frame_t) next;
};

struct hls_data_t {
    /** name of serial channel */
    char *serial_id;
    /** receive character and assemble a frame */
    hls_receive_char_handler_t *receive_char_handler;
    /** send a frame to a serial channel */
    hls_send_packet_handler_t *send_packet_handler;
    /** max received frames queue size */
    int max_frames;
    /** max data bytes of a frame */
    int mtu;
    /** total received frames counts */
    int received_frames;
    /** total transmitted frames counts */
    int transmitted_frames;
    /** total error frames counts */
    int error_frames;
    /** total overruns counts */
    int overruns;
    /** valid frames queue */
    TAILQ_HEAD(queuehead, hls_frame_t) frame_queue;
    /** unused frames pool queue */
    TAILQ_HEAD(poolhead, hls_frame_t) frame_pool;
    /** each frame handler modules can save private data */
    void *private_data;
};

/**
    initialize high level serial module
    \param serial_id name of serial channel to use
    \param receive_char_handler address of a function to specialized receive chars
    \param send_packet_handler address of a function to send a frame
    \param max_frames receive frames queue size
    \param mtu max data bytes size of a frame
*/
struct hls_data_t *hls_init(char *serial_id,
                            hls_receive_char_handler_t receive_char_handler,
                            hls_send_packet_handler_t send_packet_handler,
                            int max_frames,int mtu);

/**
    close a high level serial module
    \param hls_data
    \return EXIT_SUCCESS or EXIT_FAILURE
*/
int hls_close(struct hls_data_t *hls_data);

int hls_add_receive_frame(struct hls_data_t *hls_data,
                          struct hls_frame_t *frame);

/**

*/
struct hls_frame_t *hls_get_next_frame(struct hls_data_t *hls_data);

int hls_send_frame(struct hls_data_t *hls_data,
                   int address, int command, char *buffer, int buffer_length);

struct hls_frame_t *hls_get_new_frame(struct hls_data_t *hls_data);

void hls_reinstate_frame(struct hls_data_t *hls_data, struct hls_frame_t *frame);

#endif // HIGHLEVEL_H_INCLUDED
