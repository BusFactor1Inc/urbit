/* j/2/need.c
**
** This file is in the public domain.
*/
#include "all.h"
#include "../pit.h"

/* functions
*/
  u2_noun
  j2_mbc(Pit, need)(u2_wire wir_r, u2_noun a)
  {
    return u2_bl_bail(wir_r);
  }
  u2_noun
  j2_mb(Pit, need)(u2_wire wir_r, u2_noun cor)
  {
    u2_noun a, b;

    a = u2_bi_frag(wir_r, 4, cor);
    {
      return j2_mbc(Pit, need)(wir_r, a);
    }
  }

/* structures
*/
  u2_ho_jet 
  j2_mbj(Pit, need)[] = {
    { ".3", j2_mb(Pit, need), u2_yes, u2_none, u2_none },
    { }
  };
