/* watt/open.c
**
** This file is in the public domain.
*/
#include "u4/all.h"

#define _open_p(stem) \
  if ( u4_b_p(gen, u4_atom_##stem, &p_gen) ) { \
    return _open_in_##stem(p, p_gen); \
  }

#define _open_pq(stem) \
  if ( u4_b_pq(gen, u4_atom_##stem, &p_gen, &q_gen) ) { \
    return _open_in_##stem(p, p_gen, q_gen); \
  }

#define _open_pqr(stem) \
  if ( u4_b_pqr(gen, u4_atom_##stem, &p_gen, &q_gen, &r_gen) ) {\
    return _open_in_##stem(p, p_gen, q_gen, r_gen); \
  }

#define _open_pqrs(stem) \
  if ( u4_b_pqrs(gen, u4_atom_##stem, &p_gen, &q_gen, &r_gen, &s_gen) ) {\
    return _open_in_##stem(p, p_gen, q_gen, r_gen, s_gen); \
  }

#define _open_do_p(stem)  \
  static u4_gene _open_in_##stem \
    (u4_crow p, u4_noun p_gen)

#define _open_do_pq(stem)  \
  static u4_gene _open_in_##stem \
    (u4_crow p, u4_noun p_gen, u4_noun q_gen)

#define _open_do_pqr(stem)  \
  static u4_gene _open_in_##stem \
    (u4_crow p, u4_noun p_gen, u4_noun q_gen, u4_noun r_gen)

#define _open_do_pqrs(stem)  \
  static u4_gene _open_in_##stem \
    (u4_crow p, u4_noun p_gen, u4_noun q_gen, u4_noun r_gen, u4_noun s_gen)

/* mast:open:crow
*/
  static u4_gene
  _open_mast(u4_crow, u4_gene);

  static u4_gene 
  _open_mast_fix(u4_crow p,
                 u4_gene gen,
                 u4_axis axe)
  {
    u4_lane lan = p->lan;
    u4_noun p_gen, q_gen;

    if ( u4_b_pq(gen, u4_atom_cast, &p_gen, &q_gen) ) {
      return _open_mast_fix(p, p_gen, axe);
    }
    else if ( u4_b_pq(gen, u4_atom_twix, &p_gen, &q_gen) ) {
      return u4_kt
        (lan, 
         u4_atom_twix,
         _open_mast_fix(p, p_gen, u4_op_peg(lan, axe, u4_noun_2)),
         _open_mast_fix(p, q_gen, u4_op_peg(lan, axe, u4_noun_3)));
    }
    else if ( u4_b_pq(gen, u4_atom_velt, &p_gen, &q_gen) ) {
      u4_tool ryx = u4_kc(lan, u4_atom_frag, axe);

      return u4_kt
        (lan, 
         u4_atom_flac,
         u4_kt(lan, 
               u4_atom_mack, 
               u4_blip,
               u4_kl
                (lan,
                 u4_kc
                  (lan, 
                   ryx,
                   u4_kq
                    (lan, u4_atom_mong, _open_mast(p, q_gen), ryx, u4_nul)))),
         _open_mast_fix(p, p_gen, axe));
    }
    else if ( u4_b_pq(gen, u4_atom_bran, &p_gen, &q_gen) ) {
      return u4_kt
        (lan, u4_atom_bran, p_gen, _open_mast_fix(p, q_gen, axe));
    }
    else if ( u4_b_p(gen, u4_atom_teck, &p_gen) ) {
      return u4_kq
        (lan, u4_atom_mong,
              p_gen,
              u4_kc(lan, u4_atom_frag, axe),
              u4_nul);
    }
    if ( u4_b_pq(gen, u4_atom_pock, &p_gen, &q_gen) ) {
      return _open_mast_fix(p, q_gen, axe);
    } 
    else {
      u4_gene bog = _crow_open(p, gen);

      if ( !u4_n_eq(gen, bog) ) {
        return _open_mast_fix(p, bog, axe);
      }
      else {
        u4_tool ryx = u4_kc(lan, u4_atom_frag, axe);

        return u4_kt
          (lan,
           u4_atom_gram, 
           u4_kt(lan, u4_atom_plin, gen, ryx), 
           ryx);
      }
    }
  }
static u4_gene
_open_mast(u4_crow p,
           u4_gene gen)
{
  u4_lane lan = p->lan;
  u4_noun p_gen, q_gen;

  if ( u4_b_pq(gen, u4_atom_cast, &p_gen, &q_gen) ) {
    return u4_kt
      (lan,
       u4_atom_gant,
       u4_kt(lan, u4_atom_wost, u4_atom_mave, q_gen),
       u4_kc(lan, u4_atom_lome, _open_mast_fix(p, p_gen, u4_noun_4)));
  }
  else if ( u4_b_pq(gen, u4_atom_pock, &p_gen, &q_gen) ) {
    return _open_mast(p, q_gen);
  }
  else if ( u4_b_p(gen, u4_atom_teck, &p_gen) ) {
    return p_gen;
  }
  else if ( u4_b_pq(gen, u4_atom_velt, &p_gen, &q_gen) ) {
    u4_tool ryx = u4_kc(lan, u4_atom_frag, u4_noun_4);

    return u4_kt
      (lan,
       u4_atom_gant,
       u4_kt(lan, u4_atom_wost, u4_atom_mave, q_gen),
       u4_kc
        (lan,
         u4_atom_lome,
         u4_kt
          (lan, 
           u4_atom_flac,
            u4_kt
              (lan,
               u4_atom_mack,
               u4_blip,
               u4_kl
                (lan,
                 u4_kc
                  (lan, 
                   ryx,
                   u4_kq
                    (lan, u4_atom_mong, _open_mast(p, q_gen), ryx, u4_nul)))),
           _open_mast_fix(p, p_gen, u4_noun_4))));
  }
  else {
    u4_gene bog = _crow_open(p, gen);

    if ( !u4_n_eq(gen, bog) ) {
      return _open_mast(p, bog);
    }
    else {
      return u4_kt
        (lan,
         u4_atom_gant,
         u4_kt(lan, u4_atom_wost, u4_atom_mave, gen),
         u4_kc(lan, u4_atom_lome, _open_mast_fix(p, gen, u4_noun_4)));
    }
  }
}

/* fist:open:crow
*/
  static u4_gene
  _open_fist(u4_crow, u4_gene);

  static u4_gene
  _open_fist_a(u4_crow p,
               u4_bank ban)
  {
    u4_lane lan = p->lan;

    if ( u4_n_zero(ban) ) {
      return u4_noun_0;
    }
    else {
      return u4_kc
        (lan, _open_fist(p, u4_ch(ban)), _open_fist_a(p, u4_ct(ban)));
    }
  }
static u4_gene
_open_fist(u4_crow p,
           u4_gene gen)
{
  u4_lane lan = p->lan;
  u4_noun p_gen, q_gen;

  if ( u4_b_p(gen, u4_atom_bean, &p_gen) ) {
    return gen;
  }
  else if ( u4_b_pq(gen, u4_atom_cast, &p_gen, &q_gen) ) {
    return u4_kt
      (lan, u4_atom_cast, p_gen, _open_fist(p, q_gen));
  }
  else if ( u4_b_pq(gen, u4_atom_twix, &p_gen, &q_gen) ) {
    return u4_kt
      (lan, u4_atom_twix, _open_fist(p, p_gen), _open_fist(p, q_gen));
  }
  else if ( u4_b_pq(gen, u4_atom_velt, &p_gen, &q_gen) ) {
    return u4_kt
      (lan, u4_atom_velt, _open_fist(p, p_gen), _open_fist(p, q_gen));
  }
  else if ( u4_b_p(gen, u4_atom_fist, &p_gen) ) {
    return _open_fist(p, p_gen);
  }
  else if ( u4_b_pq(gen, u4_atom_bran, &p_gen, &q_gen) ) {
    return u4_kt
      (lan, u4_atom_bran, p_gen, _open_fist(p, q_gen));
  }
  else if ( u4_b_p(gen, u4_atom_teck, &p_gen) ) {
    u4_noun pp_gen;

    if ( u4_b_p(p_gen, u4_atom_rond, &pp_gen) ) {
      return u4_kt(lan, u4_atom_teck, u4_atom_rond, _open_fist_a(p, pp_gen));
    }
    else {
      return u4_kc(lan, u4_atom_bean, u4_atom_blur);
    }
  }
  else if ( u4_b_pq(gen, u4_atom_pock, &p_gen, &q_gen) ) {
    return _open_fist(p, p_gen);
  }
  else if ( u4_b_p(gen, u4_atom_bone, &p_gen) ) {
    return gen;
  }
  else {
    u4_gene bog = _crow_open(p, gen);

    if ( !u4_n_eq(gen, bog) ) {
      return _open_fist(p, bog);
    }
    else {
      return u4_kc(lan, u4_atom_bean, u4_atom_blur);
    }
  }
}

_open_do_p(bean)
{
  u4_lane lan = p->lan;

  if ( u4_n_eq(u4_atom_atom, p_gen) ) {
    return u4_kt
      (lan, u4_atom_cast, 
            u4_kt(lan, u4_atom_vint, u4_atom_bone, u4_noun_0),
            u4_kc(lan, u4_atom_bone, u4_noun_0));
  }
  else if ( u4_n_eq(u4_atom_blur, p_gen) ) {
    u4_noun dud = u4_kc(lan, u4_atom_bone, u4_noun_0);

    return u4_kt
      (lan, u4_atom_cast, 
            u4_kt(lan, u4_atom_sail, dud, dud),
            dud);
  }
  else if ( u4_n_eq(u4_atom_cell, p_gen) ) {
    return u4_kt
      (lan, u4_atom_twix,
            u4_kc(lan, u4_atom_bean, u4_atom_blur),
            u4_kc(lan, u4_atom_bean, u4_atom_blur));
  }
  else if ( u4_n_eq(u4_atom_flag, p_gen) ) {
    return u4_kt
      (lan, u4_atom_cast,
            u4_kt(lan, u4_atom_dust, u4_atom_bone, u4_noun_0),
            u4_kc(lan, u4_atom_bone, u4_noun_0));
  }
  else if ( u4_n_eq(u4_atom_null, p_gen) ) {
    return u4_kc(lan, u4_atom_bone, u4_noun_0);
  }
  else return u4_trip;
}

_open_do_pq(lank)
{
  u4_lane lan = p->lan;
  u4_noun beg = u4_kc(lan, u4_atom_frag, u4_noun_4);

  if ( u4_n_zero(q_gen) ) {
    return _crow_fail(p, "lank");
  }
  else {
    u4_noun iq_gen = u4_ch(q_gen);
    u4_noun tq_gen = u4_ct(q_gen);

    if ( u4_n_zero(tq_gen) ) {
      return iq_gen;
    }
    else {
      return u4_kt
        (lan,
         u4_atom_gant,
         _open_in_lank(p, p_gen, tq_gen),
         u4_kt
          (lan,
           u4_atom_gant,
           u4_kt(lan, u4_atom_flac,
                      u4_kc(lan, u4_atom_frag, u4_noun_3),
                      iq_gen),
           u4_kt
            (lan, 
             u4_atom_gant,
             u4_kc(lan, u4_atom_frag, u4_noun_8), 
             u4_kc
              (lan,
               u4_atom_sunt,
               u4_kq
                (lan,
                 u4_atom_bong,
                 u4_kt(lan,
                       u4_atom_flac,
                       u4_kc(lan, u4_atom_frag, u4_cod_in(23)),
                       p_gen),
                 u4_kq
                  (lan,
                   u4_atom_mong,
                   u4_kc(lan, u4_atom_frag, u4_noun_10),
                   beg,
                   u4_nul),
                u4_kt
                  (lan,
                   u4_atom_mack,
                   u4_kc(lan, 
                         u4_kc(lan, u4_atom_frag, u4_cod_in(22)), 
                         u4_noun_0),
                   u4_kc
                    (lan,
                     u4_kc(lan, beg, beg),
                     u4_noun_0)))))));
    }
  }
}

_open_do_pqr(fron)
{
  u4_lane lan = p->lan;
  u4_noun beg = u4_kc(lan, u4_atom_frag, u4_noun_4);

  if ( u4_n_zero(q_gen) ) {
    return _crow_fail(p, "fron");
  }
  else {
    u4_noun ir_gen = u4_ch(r_gen);
    u4_noun tr_gen = u4_ct(r_gen);

    if ( u4_n_zero(tr_gen) ) {
      return u4_kt
        (lan,
         u4_atom_gant,
         ir_gen,
         u4_kt
          (lan,
           u4_atom_gant,
           u4_kc(lan, u4_atom_frag, u4_noun_8), 
           u4_kc
            (lan,
             u4_atom_sunt,
             u4_kt
              (lan,
               u4_atom_cast,
               u4_kq(lan,
                     u4_atom_mong,
                     u4_kt(lan, 
                           u4_atom_flac,
                           u4_kc(lan, u4_atom_frag, u4_cod_in(11)),
                           q_gen),
                     beg,
                     u4_nul),
               u4_kq
                (lan,
                 u4_atom_mong,
                 u4_kc(lan, u4_atom_frag, u4_noun_10),
                 beg,
                 u4_nul)))));
    }
    else {
      return u4_kt
        (lan,
         u4_atom_gant,
         _open_in_lank(p, p_gen, tr_gen),
         u4_kt
          (lan,
           u4_atom_gant,
           u4_kt(lan, u4_atom_flac,
                      u4_kc(lan, u4_atom_frag, u4_noun_3),
                      ir_gen),
           u4_kt
            (lan, 
             u4_atom_gant,
             u4_kc(lan, u4_atom_frag, u4_noun_8), 
             u4_kc
              (lan,
               u4_atom_sunt,
               u4_kt
                (lan,
                 u4_atom_cast,
                 u4_kq(lan,
                       u4_atom_mong,
                       u4_kt(lan, 
                             u4_atom_flac,
                             u4_kc(lan, u4_atom_frag, u4_cod_in(23)),
                             q_gen),
                       beg,
                       u4_nul),
                 u4_kq
                  (lan,
                   u4_atom_bong,
                   u4_kt(lan,
                         u4_atom_flac,
                         u4_kc(lan, u4_atom_frag, u4_cod_in(23)),
                         p_gen),
                   u4_kq
                    (lan,
                     u4_atom_mong,
                     u4_kc(lan, u4_atom_frag, u4_noun_10),
                     beg,
                     u4_nul),
                  u4_kt
                    (lan,
                     u4_atom_mack,
                     u4_kc(lan, 
                           u4_kc(lan, u4_atom_frag, u4_cod_in(22)), 
                           u4_noun_0),
                     u4_kc
                      (lan,
                       u4_kc(lan, beg, beg),
                       u4_noun_0))))))));
    }
  }
}

_open_do_p(prex)
{
  u4_lane lan = p->lan;

  if ( u4_n_zero(p_gen) ) {
    return u4_kc(lan, u4_atom_zike, u4_nul);
  }
  else {
    u4_noun ip_gen = u4_ch(p_gen);
    u4_noun tp_gen = u4_ct(p_gen);

    if ( u4_n_zero(tp_gen) ) {
      return ip_gen;
    } else {
      return u4_kt
        (lan, u4_atom_twix, ip_gen, _open_in_prex(p, tp_gen));
    }
  }
}

_open_do_p(mong)
{
  u4_lane lan = p->lan;
  u4_noun ip_gen = u4_ch(p_gen);
  u4_noun tp_gen = u4_ct(p_gen);

  if ( u4_n_zero(tp_gen) ) {
    return u4_kt
      (lan, u4_atom_flac, 
            ip_gen,
            u4_kc(lan, u4_atom_pane, u4_blip));
  } else {
    if ( u4_n_eq(tp_gen, u4_kc(lan, u4_atom_frag, u4_noun_4)) ) {
      return u4_trip;
    }
    return u4_kt
      (lan, u4_atom_gant,
            ip_gen,
            u4_kt
              (lan,
               u4_atom_mack,
               u4_kt(lan, 
                     u4_kc(lan, u4_atom_frag, u4_noun_2),
                     u4_kc(lan, u4_atom_pane, u4_noun_0),
                     u4_nul),
               u4_kl(lan,
                     u4_kc(lan,
                           u4_kc(lan, u4_atom_frag, u4_noun_4),
                           u4_kt(lan, u4_atom_flac, 
                                      u4_kc(lan, u4_atom_frag, u4_noun_3),
                                      u4_kc(lan, u4_atom_prex, tp_gen))))));
  }
}

_open_do_pq(velt)
{
  u4_lane lan = p->lan;

  return u4_kt
    (lan, u4_atom_gant,
          q_gen,
          u4_kt
            (lan, u4_atom_grel,
                  u4_kc(lan, u4_atom_frag, u4_noun_2),
                  u4_kl(lan,
                        u4_kc(lan,
                              u4_kt(lan, u4_atom_flac,
                                         u4_kc(lan, u4_atom_frag, u4_noun_3),
                                         q_gen),
                              u4_kc(lan, u4_atom_frag, u4_noun_2)))));
}

_open_do_p(mast)
{
  return _open_mast(p, p_gen);
}

_open_do_p(wost)
{
  return p_gen;
}

_open_do_p(zush)
{
  return p_gen;
}

_open_do_pq(marg)
{
  u4_lane lan = p->lan;

  return u4_kq
    (lan, u4_atom_trol,
          p_gen,
          u4_kc(lan, u4_atom_zike, u4_noun_0),
          q_gen);
}

_open_do_p(vern)
{
  u4_lane lan = p->lan;

  return u4_kq
    (lan, u4_atom_trol,
          p_gen,
          u4_kc(lan, u4_atom_bone, u4_noun_1),
          u4_kc(lan, u4_atom_bone, u4_noun_0));
}

_open_do_p(slax)
{
  u4_lane lan = p->lan;

  if ( u4_n_zero(p_gen) ) {
    return u4_kc(lan, u4_atom_bone, u4_noun_0);
  }
  else {
    u4_noun ip_gen = u4_ch(p_gen);
    u4_noun tp_gen = u4_ct(p_gen);

    return u4_kt(lan, u4_atom_twix, ip_gen, _open_in_slax(p, tp_gen));
  }
}

_open_do_p(frag)
{
  u4_lane lan = p->lan;

  return u4_kt
    (lan, u4_atom_mack, 
          u4_kc(lan, u4_kc(lan, u4_atom_frag, p_gen), u4_nul),
          u4_nul);
}

_open_do_p(fist)
{
  return _open_fist(p, p_gen);
}

_open_do_p(lome)
{
  u4_lane lan = p->lan;

  return u4_kc
    (lan, u4_atom_pank,
          u4_kl(lan, u4_kc(lan, u4_blip, p_gen)));
}

_open_do_pq(gnam)
{
  u4_lane lan = p->lan;

  return u4_kt
    (lan, u4_atom_mong, q_gen, u4_kc(lan, p_gen, u4_noun_0));
}

_open_do_pqr(bong)
{
  u4_lane lan = p->lan;

  return u4_kc
    (lan, u4_atom_mong, 
          u4_kq(lan, p_gen, q_gen, r_gen, u4_nul));
}

_open_do_pq(claf)
{
  u4_lane lan = p->lan;

  return u4_kt(lan, u4_atom_flac, q_gen, p_gen);
}

_open_do_pqr(lort)
{
  u4_lane lan = p->lan;

  return u4_kq(lan, u4_atom_trol, p_gen, r_gen, q_gen);
}

_open_do_p(vamp)
{
  u4_lane lan = p->lan;

  return u4_kt
    (lan, u4_atom_flac,
          u4_kc(lan, u4_atom_lome, p_gen),
          u4_kc(lan, u4_atom_pane, u4_blip));
}

_open_do_p(zole)
{
  u4_lane lan = p->lan;

  return u4_kc(lan, u4_atom_bone, p_gen);
}

_open_do_pq(moze)
{
  u4_lane lan = p->lan;

  if ( u4_n_zero(q_gen) ) {
    return u4_kc(lan, u4_atom_zike, u4_nul);
  }
  else {
    u4_noun iq_gen = u4_ch(q_gen);
    u4_noun tq_gen = u4_ct(q_gen);

#if 0
    if ( !u4_n_zero(p->bug) ) {
      u4_err(lan, "moze: iq_gen", iq_gen);
      u4_err(lan, "moze: fist", _open_fist(p, iq_gen));
      u4_err(lan, "moze: mast", _open_mast(p, iq_gen));
      printf("\n");
    }
#endif
    return u4_kq
      (lan,
       u4_atom_trol,
       u4_kt(lan, u4_atom_plin, _open_fist(p, iq_gen), p_gen),
       u4_kq(lan, u4_atom_mong, _open_mast(p, iq_gen), p_gen, u4_nul),
       _open_in_moze(p, p_gen, tq_gen));
  }
}

_open_do_p(rond)
{
  u4_lane lan = p->lan;

  if ( u4_n_zero(p_gen) ) {
    return u4_kc(lan, u4_atom_zike, u4_nul);
  }
  else {
    u4_noun ip_gen = u4_ch(p_gen);

    return u4_kt
      (lan,
       u4_atom_gant,
       u4_kc(lan, u4_atom_mave, ip_gen),
       u4_kc(lan, u4_atom_lome,
                  u4_kt(lan, u4_atom_moze, 
                             u4_kc(lan, u4_atom_frag, u4_noun_4),
                             p_gen)));
  }
}

_open_do_pq(frit)
{
  u4_lane lan = p->lan;

  return u4_kt
    (lan, u4_atom_gant,
          p_gen,
          u4_kt
            (lan,
             u4_atom_mack,
             u4_kl(lan, u4_kc(lan, u4_atom_frag, u4_noun_2)),
             u4_kl(lan,
                   u4_kc(lan,
                         u4_kc(lan, u4_atom_frag, u4_noun_4),
                         u4_kt(lan, u4_atom_flac, 
                                    u4_kc(lan, u4_atom_frag, u4_noun_3),
                                    q_gen)))));
}

_open_do_p(pane)
{
  u4_lane lan = p->lan;

  return u4_kt
    (lan, u4_atom_mack, 
          u4_kc(lan, u4_kc(lan, u4_atom_pane, p_gen), u4_nul),
          u4_nul);
}

_open_do_pq(tang)
{
  u4_lane lan = p->lan;

  return u4_kt
    (lan, u4_atom_gant, q_gen, p_gen);
}

_open_do_p(teck)
{
  u4_lane lan = p->lan;

  return u4_kc
    (lan, u4_atom_wost,
          u4_kt(lan, u4_atom_flac,
                     p_gen,
                     u4_kt(lan, u4_atom_mack, 
                                u4_kl(lan, u4_kc(lan, u4_atom_pane, u4_blip)),
                                u4_nul)));
}

_open_do_pq(gant)
{
  u4_lane lan = p->lan;

  return u4_kt
    (lan, u4_atom_flac,
          u4_kt(lan, u4_atom_twix, 
                     p_gen, 
                     u4_kc(lan, u4_atom_frag, u4_noun_1)),
          q_gen);
}

_open_do_pqrs(quax)
{
  u4_lane lan = p->lan;

  return u4_kt
    (lan, u4_atom_twix,
          p_gen,
          u4_kt
            (lan, u4_atom_twix,
                  q_gen,
                  u4_kt(lan, u4_atom_twix, r_gen, s_gen)));
}

_open_do_p(chan)
{
  u4_lane lan = p->lan;

  if ( u4_n_zero(p_gen) ) {
    return u4_kc(lan, u4_atom_bone, u4_noun_0);
  }
  else {
    u4_noun ip_gen = u4_ch(p_gen);
    u4_noun tp_gen = u4_ct(p_gen);

    return u4_kq
      (lan, u4_atom_trol,
            ip_gen,
            _open_in_chan(p, tp_gen),
            u4_kc(lan, u4_atom_bone, u4_noun_1));
  }
}

_open_do_pq(grel)
{
  u4_lane lan = p->lan;

  if ( u4_n_zero(q_gen) ) {
    return u4_kc(lan, u4_atom_zike, u4_nul);
  }
  else {
    u4_noun iq_gen = u4_ch(q_gen);
    u4_noun tq_gen = u4_ct(q_gen);
    u4_noun piq_gen = u4_ch(iq_gen);
    u4_noun qiq_gen = u4_ct(iq_gen);

    return u4_kq
      (lan, 
       u4_atom_trol,
       u4_kt(lan, u4_atom_plin, _open_fist(p, piq_gen), p_gen),
       u4_kt
        (lan, u4_atom_flac,
              u4_kt(lan,
                    u4_atom_stil,
                    piq_gen,
                    p_gen),
              qiq_gen),
       _open_in_grel(p, p_gen, tq_gen));
  }
}

_open_do_p(sunt)
{
  u4_lane lan = p->lan;

  return u4_kt
    (lan, u4_atom_tash, 
          u4_kc(lan, u4_blip, p_gen),
          u4_noun_0);
}

_open_do_pq(pock)
{
  u4_lane lan = p->lan;
  u4_noun rax = u4_kc(lan, u4_atom_frag, u4_noun_2);

  return u4_kt
    (lan,
     u4_atom_gant,
     q_gen, 
     u4_kt
      (lan,
       u4_atom_claf,
       rax,
       u4_kt(lan,
             u4_atom_stil,
             u4_kt(lan, 
                   u4_atom_flac, 
                   u4_kc(lan, u4_atom_frag, u4_noun_3), 
                   p_gen),
             rax)));
}

_open_do_p(dorn)
{
  u4_lane lan = p->lan;

  if ( u4_n_zero(p_gen) ) {
    return u4_kc(lan, u4_atom_bone, u4_noun_1);
  }
  else {
    u4_noun ip_gen = u4_ch(p_gen);
    u4_noun tp_gen = u4_ct(p_gen);

    return u4_kq
      (lan, u4_atom_trol,
            ip_gen,
            u4_kc(lan, u4_atom_bone, u4_noun_0),
            _open_in_dorn(p, tp_gen));
  }
}

_open_do_pq(zemp)
{
  return q_gen;
}

_open_do_pqr(feng)
{
  u4_lane lan = p->lan;

  return u4_kt
    (lan,
     u4_atom_grel,
     p_gen,
     u4_kt
      (lan,
       u4_kc(lan, u4_kc(lan, u4_atom_bone, u4_noun_0), q_gen),
       u4_kc(lan, u4_kc(lan, u4_atom_bean, u4_atom_cell), r_gen),
       u4_nul));
}

_open_do_pq(gram)
{
  u4_lane lan = p->lan;
  
  return u4_kq
    (lan, u4_atom_trol, p_gen, q_gen, u4_kc(lan, u4_atom_zike, u4_noun_0));
}

_open_do_pqr(trex)
{
  u4_lane lan = p->lan;

  return u4_kt
    (lan, u4_atom_twix,
          p_gen,
          u4_kt(lan, u4_atom_twix, q_gen, r_gen));
}

_open_do_pqrs(tong)
{
  u4_lane lan = p->lan;

  return u4_kq
    (lan, u4_atom_mong, 
          p_gen, 
          q_gen,
          u4_kt(lan, r_gen, s_gen, u4_nul));
}

_open_do_p(mave)
{
  u4_lane lan = p->lan;

  return u4_kt
    (lan, u4_atom_cast, 
          u4_kc(lan, u4_atom_bean, u4_atom_blur),
          p_gen);
}

_open_do_pq(yell)
{
  u4_lane lan = p->lan;

  return u4_kt(lan, u4_atom_mong, p_gen, q_gen);
}

/* open:crow
*/
  static u4_gene
  _crow_open_main(u4_crow p,
                  u4_gene gen)
  {
    u4_noun p_gen, q_gen, r_gen, s_gen;

    if ( u4_b_fork(gen, &p_gen, &q_gen) ) {
      u4_err(p->lan, "gen", gen);
      return _crow_fail(p, "bad code");
    }
    else {
      _open_p   (mast);
      _open_p   (wost);
      _open_p   (zush);
      _open_pq  (marg);
      _open_p   (vern);
      _open_p   (frag);
      _open_p   (fist);
      _open_p   (lome);
      _open_pq  (gnam);
      _open_pqr (bong);
      _open_pq  (claf);
      _open_pqr (lort);
      _open_p   (vamp);
      _open_p   (zole);
      _open_p   (pane);
      _open_pq  (tang);
      _open_p   (teck);
      _open_pq  (gant);
      _open_pqrs(quax);
      _open_p   (sunt);
      _open_pq  (zemp);
      _open_pq  (gram);
      _open_pqr (trex);
      _open_pqrs(tong);
      _open_p   (mave);

      _open_p   (bean);
      _open_pq  (lank);
      _open_pqr (fron);
      _open_p   (prex);
      _open_p   (mong);
      _open_pq  (velt);
      _open_p   (slax);
      _open_pq  (moze);
      _open_p   (rond);
      _open_pq  (frit);
      _open_p   (chan);
      _open_pq  (grel);
      _open_pq  (pock);
      _open_p   (dorn);
      _open_pqr (feng);
      _open_pq  (yell);

      return gen;
    }
  }
u4_gene
_crow_open(u4_crow p,
           u4_gene gen)
{
  u4_nopt zax = u4_tab_get(gen, p->pon);

  if ( u4_bull != zax ) {
    return zax;
  }
  else {
    zax = _crow_open_main(p, gen);

#if 0
    if ( !u4_n_zero(p->bug) && u4_b_p(gen, u4_atom_teck, 0) ) {
      u4_err(p->lan, "open: gen", gen);
      u4_err(p->lan, "open: zax", zax);
      printf("\n");
    }
#endif
    p->pon = u4_tab_add(p->lan, gen, zax, p->pon);
    return zax;
  }
}
