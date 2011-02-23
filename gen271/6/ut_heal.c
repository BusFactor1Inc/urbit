/* j/6/heal.c
**
** This file is in the public domain.
*/
#include "all.h"
#include "../pit.h"


/* internals
*/
  static u2_noun
  _heal_as(u2_wire, u2_noun, u2_noun, u2_noun, u2_atom, u2_noun);

  static u2_noun
  _heal_by(u2_wire wir_r,
           u2_noun van,
           u2_noun sut,
           u2_noun ref)
  {
    u2_noun p_sut, q_sut;

    if ( u2_no == u2_dust(sut) ) {
      goto repo;
    }
    else switch ( u2_h(sut) ) {
      default: goto repo;

      case c3__core:
      {
        return u2_rx(wir_r, ref);
      }
      case c3__face: u2_bi_cell(wir_r, u2_t(sut), &p_sut, &q_sut);
      {
        return j2_mby(Pit, face)(wir_r, p_sut, ref);
      }
      case c3__fork: u2_bi_cell(wir_r, u2_t(sut), &p_sut, &q_sut);
      {
        u2_noun dis = _heal_by(wir_r, van, p_sut, ref);
        u2_noun dat = _heal_by(wir_r, van, q_sut, ref);
        u2_noun ret = j2_mby(Pit, fork)(wir_r, dis, dat);

        u2_rl_lose(wir_r, dis);
        u2_rl_lose(wir_r, dat);
        return ret;
      }
    }

    repo: {
      u2_noun rep = j2_mcy(Pit, ut, repo)(wir_r, van, sut);
      u2_noun ret = _heal_by(wir_r, van, rep, ref);

      u2_rz(wir_r, rep);
      return ret;
    }
  }

  static u2_noun
  _heal_to(u2_wire wir_r,
           u2_noun van,
           u2_noun sut,
           u2_noun qog,
           u2_noun ref,
           u2_atom now,
           u2_atom lat)
  {
    u2_noun p_sut, q_sut;

    if ( u2_no == u2_dust(sut) ) {
      if ( c3__atom == sut ) {
        return c3__void;
      } else {
        goto repo;
      }
    }
    else switch ( u2_h(sut) ) {
      default: goto repo;

      case c3__cell: u2_bi_cell(wir_r, u2_t(sut), &p_sut, &q_sut);
      {
        u2_noun ter, ret;

        if ( _2 == now ) {
          ter = _heal_as(wir_r, van, p_sut, qog, lat, ref);
          ret = j2_mby(Pit, cell)(wir_r, ter, q_sut);
        } else {
          ter = _heal_as(wir_r, van, q_sut, qog, lat, ref);
          ret = j2_mby(Pit, cell)(wir_r, p_sut, ter);
        }
        u2_rz(wir_r, ter);
        return ret;
      }

      case c3__core: u2_bi_cell(wir_r, u2_t(sut), &p_sut, &q_sut);
      {
        if ( _2 != now ) {
          return u2_bl_bail(wir_r);
        } else {
          u2_noun ter = _heal_as(wir_r, van, p_sut, qog, lat, ref);
          u2_noun ret = j2_mby(Pit, core)(wir_r, ter, q_sut);

          u2_rz(wir_r, ter);
          return ret;
        }
      }

      case c3__fork: u2_bi_cell(wir_r, u2_t(sut), &p_sut, &q_sut);
      {
        u2_noun dis = _heal_to(wir_r, van, p_sut, qog, ref, now, lat);
        u2_noun dat = _heal_to(wir_r, van, q_sut, qog, ref, now, lat);
        u2_noun ret = j2_mby(Pit, fork)(wir_r, dis, dat);

        u2_rl_lose(wir_r, dis);
        u2_rl_lose(wir_r, dat);
        return ret;
      }
    }

    repo: {
      u2_noun rep = j2_mcy(Pit, ut, repo)(wir_r, van, sut);
      u2_noun ret = _heal_to(wir_r, van, rep, qog, ref, now, lat);

      u2_rz(wir_r, rep);
      return ret;
    }
  }

  static u2_noun
  _heal_as(u2_wire wir_r,
           u2_noun van,
           u2_noun sut,
           u2_noun qog,
           u2_atom axe,
           u2_noun ref)
  {
    if ( _1 == axe ) {
      if ( u2_nul == qog ) {
        return u2_rx(wir_r, ref);
      } else return _heal_by(wir_r, van, sut, ref);
    }
    else {
      u2_atom now = j2_mbc(Pit, cap)(wir_r, axe);
      u2_atom lat = j2_mbc(Pit, mas)(wir_r, axe);
      u2_noun ret = _heal_to(wir_r, van, sut, qog, ref, now, lat);

      u2_rz(wir_r, lat);
      return ret;
    }
  }
  
/* functions
*/
  u2_noun                                                         //  transfer
  j2_mcx(Pit, ut, heal)(u2_wire wir_r, 
                        u2_noun van,                              //  retain
                        u2_noun sut,                              //  retain
                        u2_noun qog,                              //  retain
                        u2_noun axe,                              //  retain
                        u2_noun ref)                              //  retain
  {
    return _heal_as(wir_r, van, sut, qog, axe, ref);
  }

/* boilerplate
*/
  u2_ho_jet 
  j2_mcj(Pit, ut, heal)[];

  u2_noun                                                         //  transfer
  j2_mc(Pit, ut, heal)(u2_wire wir_r, 
                       u2_noun cor)                               //  retain
  {
    u2_noun van, sut, qog, axe, ref;

    if ( (u2_no == u2_mean(cor, u2_cv_sam_2, &qog, 
                                u2_cv_sam_6, &axe,
                                u2_cv_sam_7, &ref,
                                u2_cv_con, &van, 
                                0)) ||
         (u2_no == u2_stud(axe)) ||
         (u2_none == (sut = u2_frag(u2_cv_sam, van))) )
    {
      return u2_bl_bail(wir_r);
    } else {
      return j2_mcx(Pit, ut, heal)(wir_r, van, sut, qog, axe, ref);
    }
  }

  u2_weak                                                         //  transfer
  j2_mci(Pit, ut, heal)(u2_wire wir_r,
                        u2_noun van,                              //  retain
                        u2_noun sut,                              //  retain
                        u2_noun qog,                              //  retain
                        u2_noun axe,                              //  retain
                        u2_noun ref)                              //  retain
  {
    u2_weak hoc = u2_sh_look(wir_r, van, "heal");

    if ( u2_none == hoc ) {
      c3_assert(!"register heal");
      return u2_none;
    } else {
      u2_weak von = u2_rl_molt(wir_r, van, u2_cv_sam, u2_rx(wir_r, sut), 0);
      u2_weak gat = u2_nk_soft(wir_r, von, hoc);
      u2_weak cor = u2_rl_molt(wir_r, gat, u2_cv_sam_2, u2_rx(wir_r, qog), 
                                           u2_cv_sam_6, u2_rx(wir_r, axe),
                                           u2_cv_sam_7, u2_rx(wir_r, ref),
                                           0);

      if ( (u2_none == j2_mcj(Pit, ut, heal)[0].xip) ) {
        u2_noun xip = u2_sh_find(wir_r, cor);
     
        c3_assert(u2_none != xip);
        j2_mcj(Pit, ut, heal)[0].xip = xip;
      }
      u2_rl_lose(wir_r, gat);
      return cor;
    }
  }

  u2_noun                                                         //  transfer
  j2_mcy(Pit, ut, heal)(u2_wire wir_r,
                        u2_noun van,                              //  retain
                        u2_noun sut,                              //  retain
                        u2_noun qog,                              //  retain
                        u2_noun axe,                              //  retain
                        u2_noun ref)                              //  retain
  {
    u2_ho_jet *jet_j = &j2_mcj(Pit, ut, heal)[0];

    switch ( jet_j->sat_s ) {
      default: c3_assert(0); return u2_none;

      case u2_jet_live: {
        return j2_mcx(Pit, ut, heal)(wir_r, van, sut, qog, axe, ref);
      }
      case u2_jet_dead: {
        u2_noun cor, sof;

        cor = j2_mci(Pit, ut, heal)(wir_r, van, sut, qog, axe, ref);
        sof = u2_nk_soft(wir_r, cor, u2_frag(u2_cv_noc, cor));

        return u2_bl_good(wir_r, sof);
      }
      case u2_jet_limp: {
        u2_weak had, cor, sof;

        /* Compute `had`, the C version.  Jet is full-on recursive.
        ** Catch bails.
        */
        {
          jet_j->sat_s = u2_jet_live;
          {
            u2_ray jub_r = u2_bl_open(wir_r);

            if ( u2_bl_set(wir_r) ) {
              u2_bl_done(wir_r, jub_r);
              had = u2_none;
            } 
            else {
              had = j2_mcx(Pit, ut, heal)(wir_r, van, sut, qog, axe, ref);
              u2_bl_done(wir_r, jub_r);
            }
          }
          jet_j->sat_s = u2_jet_limp;
        }

        /* Compute `sof`, the Nock version.  Jet is full-off recursively.
        */
        {
          jet_j->sat_s = u2_jet_dead;
          {
            cor = j2_mci(Pit, ut, heal)(wir_r, van, sut, qog, axe, ref);
            sof = u2_nk_soft(wir_r, u2_rx(wir_r, cor), 
                                    u2_frag(u2_cv_noc, cor));
          }
          jet_j->sat_s = u2_jet_limp;
        }
        u2_ho_test(jet_j, cor, sof, had);
        u2_rl_lose(wir_r, cor);

        if ( u2_none == sof ) {
          return had;
        } else {
          u2_rl_lose(wir_r, had);
          return sof;
        }
      }
    }
  }

/* structures
*/
  u2_ho_jet 
  j2_mcj(Pit, ut, heal)[] = {
    { ".3", c3__hevy, j2_mc(Pit, ut, heal), SafeTier6, u2_none, u2_none },
    { }
  };
