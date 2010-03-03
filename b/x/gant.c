/* mill/x/slop.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

/* _mill_slop(): use with changes.
**
**    ved: target : rope == list+(mark [%flat tic=nat vix=mark] [%flet haz=nat])
**    suc: changes: bolt == list+[p=rope q=gene]
**    pex: subject: type
*/
u4_loaf
_mill_x_slop(u4_milr m,
             u4_rope ved,
             u4_bolt suc,
             u4_type pex)
{
  u4_lane lane = m->lane;
  u4_loaf rec;

#if 0
  if ( !u4_n_zero(m->rux) && !u4_n_zero(suc) ) {
    printf("\n");
    u4_err(lane, "slop: ved", ved);
    u4_err(lane, "slop: suc", suc);
    u4_burp(lane, "slop: pex", _mill_dump(m, pex));
  }
#endif

  rec = _mill_look(m, ved, pex);

  if ( u4_n_zero(rec) ) {
    return _mill_fail(m, "slop: broken");
  }
  else {
    u4_type zum = u4_ch(rec);
    u4_form nol = u4_ct(rec);
    u4_noun p_nol, q_nol;
    u4_type p_zum;
    u4_gene q_zum;
    u4_axis ped;

    if ( u4_b_p(nol, u4_noun_0, &p_nol) ) {
      return _mill_salt(m, suc, pex, zum, p_nol);
    }

    else if ( u4_b_pq(nol, u4_noun_3, &p_nol, &q_nol) &&
              u4_b_p(p_nol, u4_noun_0, &ped) &&
              u4_b_pq(zum, u4_atom_hold, &p_zum, &q_zum) )
    {
      u4_type hel = p_zum;
      u4_loaf das = _mill_salt(m, suc, pex, hel, ped);
      u4_type p_das = u4_ch(das);
      u4_form q_das = u4_ct(das);
      u4_noun vew, mig;

      vew = u4_k_trel(lane, u4_atom_hold, p_das, q_zum);
      mig = u4_k_trel(lane, u4_noun_3, q_das, q_nol);

      return u4_k_cell(lane, vew, mig);
    }

    else {
      return _mill_fail(m, "slop: ugly");
    }
  }
}

