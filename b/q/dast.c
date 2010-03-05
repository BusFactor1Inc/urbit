/* mill/q/dast.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

/* _mill_q_dast():
*/
u4_noun
_mill_q_dast(u4_milr m, 
             u4_noun das)
{
  u4_lane lane = m->lane;

  //  ?-  das
  //    -   ~       [%rock %1]
  //    -   [i t]   [%quiz i.das [%rock %0] $(das t.das)]
  //  ==
  
  if ( u4_n_zero(das) ) {
    return u4_k_cell(lane, u4_atom_rock, u4_noun_1);
  }
  else {
    return u4_k_qual
      (lane,
       u4_atom_quiz,
       u4_ch(das),
       u4_k_cell(lane, u4_atom_rock, u4_noun_0),
       _mill_q_dast(m, u4_ct(das)));
  }
}
