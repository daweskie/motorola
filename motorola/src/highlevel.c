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

static struct keret *lok_keret(int adat_hossz)
{
    struct keret *hl_keret;
    MALLOC(hl_keret, sizeof(struct keret));
    hl_keret->cim = 0;
    hl_keret->cim = 0;
    hl_keret->adat_hossz = 0;
    hl_keret->ervenyesseg = 0;
    MALLOC(hl_keret->anyag, adat_hossz);
    return hl_keret;
}

struct adat *Init(char *soros_azonosito,
                            hl_fogadott_karakter fogadott_karakter_k,
                            hl_elkuldott_karakter kuldott_karakter_k,
                            int max_keret,int mtu)
{
    struct adat *hl_adat;
    if (! (fogadott_karakter_k && kuldott_karakter_k && max_keret && mtu) )

        return NULL;

    MALLOC(hl_adat, sizeof(struct adat));
    hl_adat->fogadott_karakter_k = fogadott_karakter_k;
    hl_adat->kuldott_karakter_k = kuldott_karakter_k;
    hl_adat->max_keret = max_keret;
    hl_adat->mtu = mtu;
    hl_adat->soros_azonosito = soros_azonosito;
    hl_adat->hibas_keret = 0;
    hl_adat->tul_cs = 0;
    hl_adat->be_keret = 0;
    hl_adat->ki_keret = 0;
    TAILQ_INIT(&hl_adat->frame_queue);
    TAILQ_INIT(&hl_adat->frame_pool);
    int i;
    for (i=0;i<max_keret;i++)
        TAILQ_INSERT_TAIL(&hl_adat->frame_pool, lok_keret(mtu), next);
    return hl_adat;
}

/**int bezar(struct adat *hl_adat)
{
    if (hl_adat)
        // ? serial_close(hl_adat->soros_azonosito);
    return EXIT_SUCCESS;
}
*/

struct keret *kovetkezokeret(struct adat *hl_adat)
{
    if (!hl_adat )
        return NULL;


    struct keret *result=hl_adat->frame_queue.tqh_first;
    TAILQ_REMOVE(&hl_adat->frame_queue, result, next);

    return result;

}

int keretkuldesstruct adat *hl_adat, int cim, int parancs char *buff, int buff_hossz)
{
    if (!(hl_adat && hl_adat->kuldott_karakter_k) )

        return EXIT_FAILURE;

    return hl_adat->kuldott_karakter_k(hl_adat, cim, parancs buff, buff_hossz);
}

int hozzaadfogadottkeret(struct adat *hl_adat, struct keret *hl_keret)
{
    if (! (hl_adat && hl_keret))

        return EXIT_FAILURE;

    TAILQ_INSERT_HEAD(&hl_adat->frame_queue, hl_keret, next);

    return EXIT_SUCCESS;
}

struct keret *hls_get_new_frame(struct adat *hl_adat)
{
    struct keret *result;

    if (!hl_adat || TAILQ_EMPTY(&hl_adat->frame_pool))
        return NULL;


    result=hl_adat->frame_pool.tqh_first;
    TAILQ_REMOVE(&hl_adat->frame_pool, result, next);
    if (result) {
        result->cim=0;
        result->command=0;
        result->ervenyesseg=0;
    }

    return result;

}

void visszakeret(struct adat *hl_adat, struct keret *hl_keret)
{
    if (!(hl_adat && hl_keret) )

        return;

    TAILQ_INSERT_TAIL(&hls_ ->frame_pool, hl_keret,  next);
}
