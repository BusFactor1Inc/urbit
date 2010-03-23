/* mill/nest.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

  /** Forward declarations.
  **/
    static u4_t _nest_main(u4_milr, u4_bag, u4_rail, u4_mold, u4_mold);


/* _nest_flat(): true iff [meg gan] is flat.
*/
static u4_t
_nest_flat(u4_milr m,
           u4_bag  hax,
           u4_rail meg,
           u4_mold gan)
{
  u4_lane lane = m->lane;
  u4_noun p_gan, q_gan;

  // %atom
  //
  if ( u4_n_eq(u4_atom_atom, gan) ) {
    return u4_true;
  }

  // %blot
  //
  else if ( u4_n_eq(u4_atom_blot, gan) ) {
    return u4_true;
  }

  // %blur
  //
  else if ( u4_n_eq(u4_atom_blur, gan) ) {
    return u4_false;
  }

  // [%cell p=mold q=mold]
  //
  else if ( u4_b_pq(gan, u4_atom_cell, &p_gan, &q_gan) ) {
    return u4_false;
  }

  // [%cone p=mold q=bush+[term mold]]
  // [%dome p=mold q=bush+[term mold]]
  //
  else if ( u4_b_pq(gan, u4_atom_cone, &p_gan, &q_gan) ||
            u4_b_pq(gan, u4_atom_dome, &p_gan, &q_gan) ) {
    return u4_false;
  }

  // [%cube p=noun]
  // 
  else if ( u4_b_p(gan, u4_atom_cube, &p_gan) ) {
    if ( u4_n_atom(p_gan) ) {
      return u4_true;
    }
    else return u4_false;
  }

  // [%face p=mark q=mold]
  //
  if ( u4_b_pq(gan, u4_atom_face, &p_gan, &q_gan) ) {
    return _nest_flat(m, hax, meg, q_gan);
  }

  // [%fork p=mold q=mold]
  //
  else if ( u4_b_pq(gan, u4_atom_fork, &p_gan, &q_gan) ) {
    return ( (_mill_cull(m, meg, p_gan) || _nest_flat(m, hax, meg, p_gan)) &&
             (_mill_cull(m, meg, q_gan) || _nest_flat(m, hax, meg, q_gan)) );
  }

  // [%fuse p=mold q=mold]
  //
  else if ( u4_b_pq(gan, u4_atom_fuse, &p_gan, &q_gan) ) {
    return _nest_flat(m, hax, meg, p_gan) ||
           _nest_flat(m, hax, u4_k_cell(lane, p_gan, meg), q_gan);
  }

  // [%hold p=mold q=gene]
  //
  else if ( u4_b_pq(gan, u4_atom_hold, &p_gan, &q_gan) ) {
    u4_noun dit = u4_k_cell(lane, meg, gan);

    if ( u4_bag_in(dit, hax) ) {
      return 1;
    } else {
      return _nest_flat(m, u4_bag_add(lane, dit, hax), 
                           meg, 
                           _mill_repo(m, p_gan, q_gan));
    }
  }
  else return u4_trip;
}

/* _nest_deep(): true iff [meg gan] is deep (known non-atomic).
*/
static u4_t
_nest_deep(u4_milr m,
           u4_bag  hax,
           u4_rail meg,
           u4_mold gan)
{
  u4_lane lane = m->lane;
  u4_noun p_gan, q_gan;

  // %atom
  //
  if ( u4_n_eq(u4_atom_atom, gan) ) {
    return u4_false;
  }

  // %blot
  //
  else if ( u4_n_eq(u4_atom_blot, gan) ) {
    return u4_true;
  }

  // %blur
  //
  else if ( u4_n_eq(u4_atom_blur, gan) ) {
    return u4_false;
  }

  // [%cell p=mold q=mold]
  //
  else if ( u4_b_pq(gan, u4_atom_cell, &p_gan, &q_gan) ) {
    return u4_true;
  }

  // [%cone p=mold q=bush+[term mold]]
  // [%dome p=mold q=bush+[term mold]]
  //
  else if ( u4_b_pq(gan, u4_atom_cone, &p_gan, &q_gan) ||
            u4_b_pq(gan, u4_atom_dome, &p_gan, &q_gan) ) {
    return u4_true;
  }

  // [%cube p=noun]
  // 
  else if ( u4_b_p(gan, u4_atom_cube, &p_gan) ) {
    if ( u4_n_atom(p_gan) ) {
      return u4_false;
    }
    else return u4_true;
  }

  // [%face p=mark q=mold]
  //
  if ( u4_b_pq(gan, u4_atom_face, &p_gan, &q_gan) ) {
    return _nest_deep(m, hax, meg, q_gan);
  }

  // [%fork p=mold q=mold]
  //
  else if ( u4_b_pq(gan, u4_atom_fork, &p_gan, &q_gan) ) {
    return ( (_mill_cull(m, meg, p_gan) || _nest_deep(m, hax, meg, p_gan)) &&
             (_mill_cull(m, meg, q_gan) || _nest_deep(m, hax, meg, q_gan)) );
  }

  // [%fuse p=mold q=mold]
  //
  else if ( u4_b_pq(gan, u4_atom_fuse, &p_gan, &q_gan) ) {
    return _nest_deep(m, hax, meg, p_gan) ||
           _nest_deep(m, hax, u4_k_cell(lane, p_gan, meg), q_gan);
  }

  // [%hold p=mold q=gene]
  //
  else if ( u4_b_pq(gan, u4_atom_hold, &p_gan, &q_gan) ) {
    u4_noun dit = u4_k_cell(lane, meg, gan);

    if ( u4_bag_in(dit, hax) ) {
      return 1;
    } else {
      return _nest_deep(m, u4_bag_add(lane, dit, hax), 
                           meg, 
                           _mill_repo(m, p_gan, q_gan));
    }
  }
  else return u4_trip;
}

/* _nest_rock(): congruence for atomic constant.
*/
static u4_t
_nest_rock(u4_milr m,
           u4_bag  hax,
           u4_noun p_typ,
           u4_rail meg,
           u4_mold gan)
{
  u4_lane lane = m->lane;
  u4_noun p_gan, q_gan;

  // %atom
  //
  if ( u4_n_eq(u4_atom_atom, gan) ) {
    return u4_false;
  }

  // %blot
  //
  else if ( u4_n_eq(u4_atom_blot, gan) ) {
    return u4_true;
  }

  // %blur
  //
  else if ( u4_n_eq(u4_atom_blur, gan) ) {
    return u4_false;
  }

  // [%cell p=mold q=mold]
  //
  else if ( u4_b_pq(gan, u4_atom_cell, &p_gan, &q_gan) ) {
    return u4_false;
  }

  // [%cone p=mold q=bush+[term mold]]
  // [%dome p=mold q=bush+[term mold]]
  //
  else if ( u4_b_pq(gan, u4_atom_cone, &p_gan, &q_gan) ||
            u4_b_pq(gan, u4_atom_dome, &p_gan, &q_gan) ) {
    return u4_false;
  }

  // [%cube p=noun]
  // 
  else if ( u4_b_p(gan, u4_atom_cube, &p_gan) ) {
    return u4_n_eq(p_typ, p_gan);
  }

  // [%face p=mark q=mold]
  //
  if ( u4_b_pq(gan, u4_atom_face, &p_gan, &q_gan) ) {
    return _nest_rock(m, hax, p_typ, meg, q_gan);
  }

  // [%fork p=mold q=mold]
  //
  else if ( u4_b_pq(gan, u4_atom_fork, &p_gan, &q_gan) ) {
    return ( ( _mill_cull(m, meg, p_gan) || 
               _nest_rock(m, hax, p_typ, meg, p_gan) ) &&
             ( _mill_cull(m, meg, q_gan) || 
               _nest_rock(m, hax, p_typ, meg, q_gan) ) );
  }

  // [%fuse p=mold q=mold]
  //
  else if ( u4_b_pq(gan, u4_atom_fuse, &p_gan, &q_gan) ) {
    return _nest_rock(m, hax, p_typ, meg, p_gan) ||
           _nest_rock(m, hax, p_typ, u4_k_cell(lane, p_gan, meg), q_gan);
  }

  // [%hold p=mold q=gene]
  //
  else if ( u4_b_pq(gan, u4_atom_hold, &p_gan, &q_gan) ) {
    u4_noun dit = u4_k_cell(lane, meg, gan);

    if ( u4_bag_in(dit, hax) ) {
      return 1;
    } else {
      return _nest_rock(m, u4_bag_add(lane, dit, hax), 
                           p_typ,
                           meg, 
                           _mill_repo(m, p_gan, q_gan));
    }
  }
  else return u4_trip;
}

/* _nest_cell(): congruence for cell.
*/
static u4_t
_nest_cell(u4_milr m,
           u4_bag  gil,
           u4_mold p_typ,
           u4_mold q_typ,
           u4_rail meg,
           u4_mold gan)
{
  if ( !_nest_deep(m, u4_noun_0, meg, gan) ) {
    return u4_false;
  }
  else {
    u4_noun p_gan = _mill_peek(m, u4_noun_2, meg, gan);
    u4_noun q_gan = _mill_peek(m, u4_noun_3, meg, gan);
    u4_rail p_meg = _mill_slip(m, u4_noun_2, meg);
    u4_rail q_meg = _mill_slip(m, u4_noun_3, meg);

    return _nest_main(m, gil, p_meg, p_gan, p_typ) &&
           _nest_main(m, gil, q_meg, q_gan, q_typ);
  }
}

/* _nest_cone(): congruence for cone or dome.
*/
static u4_t
_nest_cone(u4_milr m,
           u4_bag  gil,
           u4_bag  hax,
           u4_mold p_typ,
           u4_noun q_typ,
           u4_rail meg,
           u4_mold gan)
{
  u4_lane lane = m->lane;
  u4_noun p_gan, q_gan;

  // %atom
  //
  if ( u4_n_eq(u4_atom_atom, gan) ) {
    return u4_false;
  }

  // %blot
  //
  else if ( u4_n_eq(u4_atom_blot, gan) ) {
    return u4_true;
  }

  // %blur
  //
  else if ( u4_n_eq(u4_atom_blur, gan) ) {
    return u4_false;
  }

  // [%cell p=mold q=mold]
  //
  else if ( u4_b_pq(gan, u4_atom_cell, &p_gan, &q_gan) ) {
    return u4_false;
  }

  // [%cone p=mold q=bush+[term mold]]
  // [%dome p=mold q=bush+[term mold]]
  //
  else if ( u4_b_pq(gan, u4_atom_cone, &p_gan, &q_gan)  ||
            u4_b_pq(gan, u4_atom_dome, &p_gan, &q_gan) ) {
    return _nest_main(m, gil, _mill_slip(m, u4_noun_2, meg), p_gan, p_typ) &&
           u4_n_eq(q_typ, q_gan);
  }

  // [%cube p=noun]
  // 
  else if ( u4_b_p(gan, u4_atom_cube, &p_gan) ) {
    return u4_false;
  }

  // [%face p=mark q=mold]
  //
  if ( u4_b_pq(gan, u4_atom_face, &p_gan, &q_gan) ) {
    return _nest_cone(m, gil, hax, p_typ, q_typ, meg, q_gan);
  }

  // [%fork p=mold q=mold]
  //
  else if ( u4_b_pq(gan, u4_atom_fork, &p_gan, &q_gan) ) {
    return ( ( _mill_cull(m, meg, p_gan) || 
               _nest_cone(m, gil, hax, p_typ, q_typ, meg, p_gan) ) &&
             ( _mill_cull(m, meg, q_gan) || 
               _nest_cone(m, gil, hax, p_typ, q_typ, meg, q_gan) ) );
  }

  // [%fuse p=mold q=mold]
  //
  else if ( u4_b_pq(gan, u4_atom_fuse, &p_gan, &q_gan) ) {
    return _nest_cone(m, gil, hax, p_typ, q_typ, meg, p_gan) ||
           _nest_cone(m, gil, hax, p_typ, 
                                   q_typ, 
                                   u4_k_cell(lane, p_gan, meg), 
                                   q_gan);
  }

  // [%hold p=mold q=gene]
  //
  else if ( u4_b_pq(gan, u4_atom_hold, &p_gan, &q_gan) ) {
    u4_noun dit = u4_k_cell(lane, meg, gan);

    if ( u4_bag_in(dit, hax) ) {
      return 1;
    } else {
      return _nest_cone(m, gil, u4_bag_add(lane, dit, hax), 
                                p_typ,
                                q_typ, 
                                meg, 
                                _mill_repo(m, p_gan, q_gan));
    }
  }
  else return u4_trip;
}

/* _nest_fork_row(): congruence for each.
*/
static u4_t
_nest_fork_row(u4_milr m,
               u4_bag  gil,
               u4_rail meg,
               u4_mold i_vig,
               u4_log  lec)
{
  while ( !u4_n_zero(lec) ) {
    u4_mold i_lec = u4_ch(lec);
    {
      if ( _nest_main(m, gil, meg, i_vig, i_lec) ) {
        return 1;
      }
    }
    lec = u4_ct(lec);
  }
  return 0;
}

/* _nest_fork_end(): congruence across.
*/
static u4_t
_nest_fork_end(u4_milr m,
               u4_bag  gil,
               u4_rail meg,
               u4_log  vig,
               u4_log  lec)
{
  while ( !u4_n_zero(vig) ) {
    u4_mold i_vig = u4_ch(vig);
    {
      if ( !_nest_fork_row(m, gil, meg, i_vig, lec) ) {
        return 0;
      }
      vig = u4_ct(vig);
    }
  }
  return 1;
}

/* _nest_fork_list(): accumulate fork-tree leaves.
*/
static u4_log
_nest_fork_list(u4_milr m,
                u4_log  hoc,
                u4_bag  lut,
                u4_rail zab,
                u4_mold gav)
{
  u4_lane lane = m->lane;
  u4_noun p_gav, q_gav;

  if ( u4_n_atom(gav) || 
       u4_b_pq(gav,  u4_atom_cell, &p_gav, &q_gav) ||
       u4_b_pq(gav,  u4_atom_cone, &p_gav, &q_gav) ||
       u4_b_pq(gav,  u4_atom_dome, &p_gav, &q_gav) ||
       u4_b_p(gav,   u4_atom_cube, &p_gav) ||
       u4_b_pq(gav,  u4_atom_fuse, &p_gav, &q_gav) )
  {
    return u4_k_cell(lane, gav, hoc);
  }
  else if ( u4_b_pq(gav, u4_atom_face, &p_gav, &q_gav) ) {
    return _nest_fork_list(m, hoc, lut, zab, q_gav);
  }
  else if ( u4_b_pq(gav, u4_atom_fork, &p_gav, &q_gav) ) {
    if ( _mill_cull(m, zab, p_gav) ) {
      return _nest_fork_list(m, hoc, lut, zab, q_gav);
    }
    else if ( _mill_cull(m, zab, q_gav) ) {
      return _nest_fork_list(m, hoc, lut, zab, p_gav);
    }
    else {
      return _nest_fork_list
        (m, _nest_fork_list(m, hoc, lut, zab, p_gav), lut, zab, q_gav);
    }
  }
  else if ( u4_b_pq(gav, u4_atom_hold, &p_gav, &q_gav) ) {
    if ( u4_bag_in(gav, lut) ) {
      return hoc;
    }
    else {
      lut = u4_bag_add(lane, gav, lut);

      return _nest_fork_list(m, hoc, lut, zab, _mill_repo(m, p_gav, q_gav));
    }
  }
  else return u4_trip;
}

/* _nest_fork(): nest a fork tree.
*/
static u4_t
_nest_fork(u4_milr m,
           u4_bag  gil,
           u4_bag  hax,
           u4_rail meg,
           u4_mold gan,
           u4_log  lec)
{
  u4_lane lane = m->lane;
  u4_noun p_gan, q_gan;

  if ( u4_n_eq(u4_atom_atom, gan) ||
       u4_n_eq(u4_atom_blot, gan) ||
       u4_n_eq(u4_atom_blur, gan) ||
       u4_b_pq(gan, u4_atom_cell, 0, 0) ||
       u4_b_pq(gan, u4_atom_cone, 0, 0) ||
       u4_b_pq(gan, u4_atom_dome, 0, 0) ||
       u4_b_p(gan, u4_atom_cube, 0) )
  {
    return _nest_fork_end
      (m, gil, meg, u4_k_cell(lane, gan, u4_noun_0), lec);
  }

  else if ( u4_b_pq(gan, u4_atom_face, &p_gan, &q_gan) ) {
    return _nest_fork(m, gil, hax, meg, q_gan, lec);
  }

  // [%fuse p=mold q=mold]
  //
  else if ( u4_b_pq(gan, u4_atom_fuse, &p_gan, &q_gan) ) {
    return _nest_fork(m, gil, hax, meg, p_gan, lec) ||
           _nest_fork(m, gil, hax, u4_k_cell(lane, p_gan, meg), q_gan, lec);
  }

  // [%fork p=mold q=mold]
  //
  else if ( u4_b_pq(gan, u4_atom_fork, 0, 0) ) {
    return _nest_fork_end
      (m, gil, meg, _nest_fork_list(m, u4_noun_0, u4_noun_0, meg, gan), lec);
  }

  // [%hold p=mold q=gene]
  //
  else if ( u4_b_pq(gan, u4_atom_hold, &p_gan, &q_gan) ) {
    u4_noun dit = u4_k_cell(lane, meg, gan);

    if ( u4_bag_in(dit, hax) ) {
      return 1;
    } 
    else {
      gan = _mill_repo(m, p_gan, q_gan);
      hax = u4_bag_add(lane, dit, hax);

      return _nest_fork(m, gil, hax, meg, gan, lec);
    }
  }
  else return u4_trip;
}

/* _nest_loop(): innards of _nest_main().
*/
static u4_t
_nest_loop(u4_milr m,
           u4_bag  gil,
           u4_rail meg,
           u4_mold gan,
           u4_mold typ)
{
  u4_lane lane = m->lane;
  u4_noun p_typ, q_typ;

  // %atom
  // 
  if ( u4_n_eq(u4_atom_atom, typ) ) {
    return _nest_flat(m, u4_noun_0, meg, gan);
  }

  // %blot
  //
  else if ( u4_n_eq(u4_atom_blot, typ) ) {
    return 0;
  }

  // %blur
  //
  else if ( u4_n_eq(u4_atom_blur, typ) ) {
    return 1;
  }

  // [%cell p=mold q=mold]
  //
  else if ( u4_b_pq(typ, u4_atom_cell, &p_typ, &q_typ) ) {
    return _nest_cell(m, gil, p_typ, q_typ, meg, gan);
  }

  // [%cone p=mold q=bush+[term mold]]
  // [%dome p=mold q=bush+[term mold]]
  //
  else if ( u4_b_pq(typ, u4_atom_cone, &p_typ, &q_typ) || 
            u4_b_pq(typ, u4_atom_dome, &p_typ, &q_typ) ) {
    return _nest_cone(m, gil, u4_noun_0, p_typ, q_typ, meg, gan);
  }

  // [%cube p=noun]
  // 
  else if ( u4_b_p(typ, u4_atom_cube, &p_typ) ) {
    if ( u4_n_cell(p_typ) ) {
      return _nest_main(m, gil, meg, gan, _mill_reap(m, typ));
    }
    else {
      return _nest_rock(m, u4_noun_0, p_typ, meg, gan);
    }
  }

  // [%face p=mark q=mold]
  //
  if ( u4_b_pq(typ, u4_atom_face, &p_typ, &q_typ) ) {
    return _nest_main(m, gil, meg, gan, q_typ);
  }

  // [%fork p=mold q=mold]
  //
  else if ( u4_b_pq(typ, u4_atom_fork, 0, 0) ) {
    u4_log lec = _nest_fork_list(m, u4_noun_0, u4_noun_0, u4_noun_0, typ);

    return _nest_fork(m, gil, u4_noun_0, meg, gan, lec);
  }

  // [%fuse p=mold q=mold]
  //
  else if ( u4_b_pq(typ, u4_atom_fuse, &p_typ, &q_typ) ) {
    return _nest_main(m, gil, meg, gan, p_typ) &&
           _nest_main(m, gil, meg, gan, q_typ);
  }

  // [%hold p=mold q=gene]
  //
  else if ( u4_b_pq(typ, u4_atom_hold, &p_typ, &q_typ) ) {
    return _nest_main(m, gil, meg, gan, _mill_repo(m, p_typ, q_typ));
  }

  else {
    u4_burp(lane, "typ", _mill_dump(m, typ));
    return u4_trip;
  }
}

/* _nest_main(): geometric congruence, with loop control (gil).
*/
static u4_t
_nest_main(u4_milr m,
           u4_bag  gil,
           u4_rail meg,
           u4_mold gan,
           u4_mold typ)
{
  u4_lane lane = m->lane;

  if ( u4_n_eq(gan, typ) ) {
    return 1;
  }
  else {
    u4_noun res = u4_k_trel(lane, meg, gan, typ);

    if ( u4_bag_in(res, gil) ) {
      return 1;
    }
    else if ( u4_n_zero(gil) ) {
      u4_nopt zod = u4_tab_get(res, m->vus);

      if ( zod != u4_bull ) {
        return u4_n_zero(zod);
      }
      else {
        u4_t t_zod = _nest_loop(m, u4_bag_add(lane, res, gil), meg, gan, typ);

        zod = (t_zod ? u4_noun_0 : u4_noun_1);

        m->vus = u4_tab_add(m->lane, res, zod, m->vus);
        return t_zod;
      }
    }
    else {
      return _nest_loop(m, u4_bag_add(lane, res, gil), meg, gan, typ);
    }
  }
}

/* _mill_nest(): test geometric congruence.
**
**    [gan] is geometrically congruent with [typ] iff 
**    every noun in [gan] is also in [typ].  Ie: [gan] <: mold.
*/
u4_t
_mill_nest(u4_milr m,
           u4_mold gan,
           u4_mold typ)
{
  return _mill_null(m, gan) || _nest_main(m, u4_noun_0, u4_noun_0, gan, typ);
}
