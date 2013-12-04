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

/** \file
    \brief
*/

#include <stdlib.h>
#include <macros.h>
#include <highlevel.h>

static struct hls_frame_t *alloc_frame(int data_length)
{
    struct hls_frame_t *frame;
    MALLOC(frame, sizeof(struct hls_frame_t));
    frame->address = 0;
    frame->address = 0;
    frame->data_length = 0;
    frame->valid = 0;
    MALLOC(frame->data, data_length);
    return frame;
}

struct hls_data_t *hls_init(char *serial_id,
                            hls_receive_char_handler_t receive_char_handler,
                            hls_send_packet_handler_t send_packet_handler,
                            int max_frames,int mtu)
{
    struct hls_data_t *hls_data;
    if (! (receive_char_handler
           && send_packet_handler
           && max_frames
           && mtu) )
        return NULL;

    MALLOC(hls_data, sizeof(struct hls_data_t));
    hls_data->receive_char_handler = receive_char_handler;
    hls_data->send_packet_handler = send_packet_handler;
    hls_data->max_frames = max_frames;
    hls_data->mtu = mtu;
    hls_data->serial_id = serial_id;
    hls_data->error_frames = 0;
    hls_data->overruns = 0;
    hls_data->received_frames = 0;
    hls_data->transmitted_frames = 0;
    TAILQ_INIT(&hls_data->frame_queue);
    TAILQ_INIT(&hls_data->frame_pool);
    int i;
    for (i=0;i<max_frames;i++)
        TAILQ_INSERT_TAIL(&hls_data->frame_pool,  alloc_frame(mtu), next);
    return hls_data;
}

int hls_close(struct hls_data_t *hls_data)
{
    if (hls_data)
        serial_close(hls_data->serial_id);
    return EXIT_SUCCESS;
}

struct hls_frame_t *hls_get_next_frame(struct hls_data_t *hls_data)
{
    if (!hls_data )
        return NULL;

    struct hls_frame_t *result=hls_data->frame_queue.tqh_first;
    TAILQ_REMOVE(&hls_data->frame_queue, result, next);
    return result;
}

int hls_send_frame(struct hls_data_t *hls_data, int address,
                   int command, char *buffer, int buffer_length)
{
    if (!(hls_data && hls_data->send_packet_handler) )
        return EXIT_FAILURE;
    return hls_data->send_packet_handler(hls_data, address, command, buffer, buffer_length);
}

int hls_add_receive_frame(struct hls_data_t *hls_data,
                          struct hls_frame_t *frame)
{
    if (! (hls_data && frame))
        return EXIT_FAILURE;

    TAILQ_INSERT_HEAD(&hls_data->frame_queue, frame, next);
    return EXIT_SUCCESS;
}

struct hls_frame_t *hls_get_new_frame(struct hls_data_t *hls_data)
{
    struct hls_frame_t *result;
    if (!hls_data || TAILQ_EMPTY(&hls_data->frame_pool))
        return NULL;

    result=hls_data->frame_pool.tqh_first;
    TAILQ_REMOVE(&hls_data->frame_pool, result, next);
    if (result) {
        result->address=0;
        result->command=0;
        result->valid=0;
    }
    return result;
}

void hls_reinstate_frame(struct hls_data_t *hls_data,
                     struct hls_frame_t *frame)
{
    if (!(hls_data && frame) )
        return;
    TAILQ_INSERT_TAIL(&hls_data->frame_pool, frame,  next);
}
