/* mill/peek.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

/* _peek_main(): peek, with gil.
*/
u4_type
_peek_main(u4_milr m,
           u4_axis axe,
           u4_bag  gil,
           u4_rail bar,
           u4_type tip)
{
  u4_lane lane = m->lane;
  u4_axis sud  = u4_op_tip(axe);
  u4_axis hec  = u4_op_tap(lane, axe);
  u4_noun p_tip, q_tip;

  if ( u4_n_eq(u4_noun_1, axe) ) {
    return tip;
  }
  else {
    // %atom
    // 
    if ( u4_n_eq(u4_atom_atom, tip) ) {
      return u4_atom_blot;
    }
    
    // %blot
    //
    else if ( u4_n_eq(u4_atom_blot, tip) ) {
      return u4_atom_blot;
    }

    // %blur
    //
    else if ( u4_n_eq(u4_atom_blur, tip) ) {
      return u4_atom_blur;
    }

    // <%crib p={list ~[(term) (type)]}>
    //
    else if ( u4_b_p(tip, u4_atom_crib, &p_tip) ) {
      u4_noun ip_tip = u4_ch(p_tip);
      u4_type qip_tip = u4_ct(ip_tip);
      u4_noun tp_tip = u4_ct(p_tip);

      if ( u4_n_zero(tp_tip) ) {
        return _peek_main(m, axe, gil, bar, qip_tip);
      }
      else {
        u4_type gan;

        if ( u4_n_eq(u4_noun_2, sud) ) {
          gan = qip_tip;
        }
        else gan = u4_k_cell(lane, u4_atom_crib, tp_tip);

        return _peek_main(m, hec, u4_noun_0, _mill_slip(m, sud, bar), gan);
      }
    }

    // <%cell p=(type) q=(type)>
    //
    else if ( u4_b_pq(tip, u4_atom_cell, &p_tip, &q_tip) ) {
      u4_type gan;

      if ( u4_n_eq(u4_noun_2, sud) ) {
        gan = p_tip;
      }
      else gan = q_tip;

      return _peek_main(m, hec, u4_noun_0, _mill_slip(m, sud, bar), gan);
    }

    // <%cone p=(type) q={bush term type}>
    //
    else if ( u4_b_pq(tip, u4_atom_cone, &p_tip, &q_tip) ) {
      if ( u4_n_eq(u4_noun_2, sud) ) {
        return _peek_main(m, hec, u4_noun_0, _mill_slip(m, sud, bar), p_tip); 
      }
      else return u4_atom_blur;
    }

    // <%cube p=*>
    // 
    else if ( u4_b_p(tip, u4_atom_cube, &p_tip) ) {
      if ( u4_n_atom(p_tip) ) {
        return u4_atom_blot;
      }
      else return _peek_main(m, axe, gil, bar, _mill_reap(m, tip));
    }

    // <%fork p=(type) q=(type)>
    //
    else if ( u4_b_pq(tip, u4_atom_fork, &p_tip, &q_tip) ) {
      if ( _mill_cull(m, bar, p_tip) ) {
        return _peek_main(m, axe, gil, bar, q_tip);
      } 
      else if ( _mill_cull(m, bar, q_tip) ) {
        return _peek_main(m, axe, gil, bar, p_tip);
      }
      else return _mill_eith
        (m, _peek_main(m, axe, gil, bar, p_tip),
            _peek_main(m, axe, gil, bar, q_tip));
    }

    // <%fuse p=(type) q=(type)>
    //
    else if ( u4_b_pq(tip, u4_atom_fuse, &p_tip, &q_tip) ) {
      return _mill_both
        (m, _peek_main(m, axe, gil, bar, p_tip),
            _peek_main(m, axe, gil, u4_k_cell(lane, p_tip, bar), q_tip));
    }

    // <%gate p=(type) q=(gene)>
    //
    else if ( u4_b_pq(tip, u4_atom_gate, &p_tip, &q_tip) ) {
      if ( u4_bag_in(tip, gil) ) {
        return u4_atom_blot;
      }
      else return _peek_main(m, axe, gil, bar, _mill_repo(m, p_tip, q_tip));
    }

    // [%wing p=axis q=type]
    //
    else if ( u4_b_pq(tip, u4_atom_wing, &p_tip, &q_tip) ) {
      if ( u4_n_eq(sud, u4_op_tip(p_tip)) ) {
        u4_type gan = _mill_sail(m, u4_op_tap(lane, p_tip), q_tip);

        return _peek_main(m, hec, u4_noun_0, _mill_slip(m, sud, bar), gan);
      }
      else return u4_atom_blur;
    }

    else return u4_trip;
  }
}

/* _mill_peek(): cut a railed type.
*/
u4_type
_mill_peek(u4_milr m,
           u4_axis axe,
           u4_rail bar,
           u4_type tip)
{
  return _peek_main(m, axe, u4_noun_0, bar, tip);
}
