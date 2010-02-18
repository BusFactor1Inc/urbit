/* mill/q/clet.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

/* _mill_q_clet():
*/
u4_noun
_mill_q_clet(u4_milr m, 
             u4_mark han,
             u4_gene dur,
             u4_gene leb)
{
  u4_lane lane = m->lane;

  //  :*
  //    %grat
  //    [%slon [han leb] [%% [%slet 1]] ~]
  //    dur
  //  ==
  
  return u4_k_trel
    (lane, u4_atom_grat,
           u4_k_qual
            (lane, u4_atom_slon,
                   u4_k_cell(lane, han, leb),
                   u4_k_cell(lane, u4_noun_0, 
                                   u4_k_cell(lane, u4_atom_slet, u4_noun_1)),
                   u4_noun_0),
          dur);
}
