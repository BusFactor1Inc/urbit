/* mill/x/cast.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

/* _mill_x_cast()::
*/
u4_wire
_mill_x_cast(u4_milr m, 
             u4_gene fes,
             u4_gene rum, 
             u4_type tip)
{
  u4_lane lane = m->lane;
  u4_type maf  = _mill_play(m, fes, tip);
  u4_wire kib  = _mill_make(m, rum, tip);

  if ( _mill_nest(m, u4_ch(kib), maf) ) {
    return u4_k_cell(lane, maf, u4_ct(kib));
  }
  else {
    u4_burp(lane, "cast: maf", _mill_dump(m, maf));
    u4_burp(lane, "cast: kib", _mill_dump(m, u4_ch(kib)));

    return _mill_fail(m, "type mismatch");
  }
}
