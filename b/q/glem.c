/* mill/q/glem.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

/* _mill_q_glem():
*/
u4_noun
_mill_q_glem(u4_milr m, 
             u4_gene hig,
             u4_gene muc)
{
  u4_lane lane = m->lane;

  //  :.
  //    %slon
  //    [%plom hig [%zarb 1] ~]
  //    muc
  //  ==

  return u4_k_trel
    (lane, u4_atom_slon,
           u4_k_qual
            (lane, u4_atom_plom, 
                   hig,
                   u4_k_cell(lane, u4_atom_zarb, u4_noun_1),
                   u4_noun_0),
           muc);
}
