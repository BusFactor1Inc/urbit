/* j/6/cull.c
**
** This file is in the public domain.
*/
#include "all.h"
#include "../pit.h"

/* logic
*/
  u2_noun
  j2_mcx(Pit, ut, cull)(u2_wire, u2_noun, u2_noun, u2_atom, u2_noun);

  u2_noun                                                         //  transfer
  j2_mcx(Pit, ut, cull)(u2_wire wir_r, 
                        u2_noun van,                              //  retain
                        u2_noun sut,                              //  retain
                        u2_atom axe,
                        u2_noun ref)                              //  retain
  {
    u2_noun ret, p_sut, q_sut;

    if ( _1 == axe ) {
      return j2_mcy(Pit, ut, fuse)(wir_r, van, sut, ref);
    } else {
      u2_atom now = j2_mbc(Pit, cap)(wir_r, axe);
      u2_atom lat = j2_mbc(Pit, mas)(wir_r, axe);

      if ( u2_no == u2_dust(sut) ) switch ( sut ) {
        default: return u2_bl_bail(wir_r);

        case c3__atom: {
          ret = c3__void; 
          break;
        }
        case c3__noun: {
          u2_noun por = j2_mcy(Pit, ut, repo)(wir_r, sut);
          u2_noun yot = j2_mcx(Pit, ut, cull)(wir_r, van, rep, axe, ref);
          
          if ( u2_yes == u2_sing(por, yot) ) {
            ret = u2_rx(wir_r, sut); 
          } else {
            ret = u2_rx(wir_r, yot);
          }
          u2_rl_lose(wir_r, por);
          u2_rl_lose(wir_r, yot);
          break;
        }
        case c3__void: {
          ret = c3__void;
        }
      }
      else switch ( u2_h(sut) ) {
        default: return u2_bl_bail(wir_r);

        case c3__cell: u2_bi_cell(wir_r, u2_t(sut), &p_sut, &q_sut);
        {
          u2_noun hub;

          if ( _2 == now ) {
            hub = j2_mcx(Pit, ut, cull)(wir_r, van, p_sut, lat, ref);
            ret = j2_mby(Pit, cell)(wir_r, hub, q_sut);
          } else {
            hub = j2_mcx(Pit, ut, cull)(wir_r, van, q_sut, lat, ref);
            ret = j2_mby(Pit, cell)(wir_r, p_sut, hub);
          }
          u2_rl_lose(wir_r, hub);
          break;
        }
        case c3__core: u2_bi_cell(wir_r, u2_t(sut), &p_sut, &q_sut);
        {
          if ( _2 != now ) {
            ret = u2_rx(wir_r, sut);
          } else {
            u2_noun hub = j2_mcx(Pit, ut, cull)(wir_r, van, p_sut, lat, ref);

            ret = j2_mby(Pit, core)(wir_r, hub, p_sut, q_sut);

            u2_rl_lose(wir_r, hub);
          }
          break;
        }
        case c3__cube: p_sut = u2_t(sut);
        {
          if ( u2_no == u2_dust(p_sut) ) {
            ret = c3__void;
          } else {
            u2_noun por = j2_mcy(Pit, ut, repo)(wir_r, sut);
            u2_noun yot = j2_mcx(Pit, ut, cull)(wir_r, van, rep, axe, ref);
            
            if ( u2_yes == u2_sing(por, yot) ) {
              ret = u2_rx(wir_r, sut); 
            } else {
              ret = u2_rx(wir_r, yot);
            }
            u2_rl_lose(wir_r, por);
            u2_rl_lose(wir_r, yot);
          }
          break;
        }
        case c3__face: u2_bi_cell(wir_r, u2_t(sut), &p_sut, &q_sut);
        {
          u2_noun por = j2_mcy(Pit, ut, repo)(wir_r, sut);
          u2_noun hic = j2_mcx(Pit, ut, cull)(wir_r, van, rep, axe, ref);
          u2_noun yot = j2_mby(Pit, face)(wir_r, p_sut, hic);

          if ( u2_yes == u2_sing(por, yot) ) {
            ret = u2_rx(wir_r, sut); 
          } else {
            ret = u2_rx(wir_r, yot);
          }
          u2_rl_lose(wir_r, por);
          u2_rl_lose(wir_r, yot);
          break;
        }
        case c3__fork: u2_bi_cell(wir_r, u2_t(sut), &p_sut, &q_sut);
        {
          u2_noun sin = j2_mcx(Pit, ut, cull)(wir_r, van, p_sut, axe, ref);
          u2_noun dex = j2_mcx(Pit, ut, cull)(wir_r, van, q_sut, axe, ref);

          ret = j2_mby(Pit, fork)(wir_r, sin, dex);
          u2_rl_lose(wir_r, sin);
          u2_rl_lose(wir_r, dex);

          return ret;
        }
        case c3__hold: u2_bi_cell(wir_r, u2_t(sut), &p_sut, &q_sut);
        {
          u2_noun por = j2_mcy(Pit, ut, repo)(wir_r, sut);
          u2_noun yot = j2_mcx(Pit, ut, cull)(wir_r, van, rep, axe, ref);

          if ( u2_yes == u2_sing(por, yot) ) {
            ret = u2_rx(wir_r, sut); 
          } else {
            ret = u2_rx(wir_r, yot);
          }
          u2_rl_lose(wir_r, por);
          u2_rl_lose(wir_r, yot);
          break;
        }
      }
      u2_rl_lose(wir_r, lat);
      return ret;
    }
  }
 
/* boilerplate
*/
  u2_ho_jet 
  j2_mcj(Pit, ut, cull)[];

  u2_noun                                                         //  transfer
  j2_mc(Pit, ut, cull)(u2_wire wir_r, 
                       u2_noun cor)                               //  retain
  {
    u2_noun sut, ref, van;

    if ( (u2_no == u2_mean(cor, u2_cv_sam_2, &axe, 
                                u2_cv_sam_3, &ref,
                                u2_cv_con, &van, 0)) ||
         (u2_no == u2_stud(axe)) ||
         (u2_none == (sut = u2_frag(u2_cv_sam, van))) )
    {
      return u2_bl_bail(wir_r);
    } else {
      return j2_mcx(Pit, ut, cull)(wir_r, van, sut, axe, ref);
    }
  }

  u2_weak                                                         //  transfer
  j2_mci(Pit, ut, cull)(u2_wire wir_r,
                        u2_noun van,                              //  retain
                        u2_noun sut,                              //  retain 
                        u2_atom axe,                              //  retain
                        u2_noun ref)                              //  retain
  {
    u2_weak hoc = u2_sh_look(wir_r, van, "cull");

    if ( u2_none == hoc ) {
      c3_assert(!"register cull");
      return u2_none;
    } else {
      u2_weak von = u2_rl_molt(wir_r, van, u2_cv_sam, u2_rx(wir_r, sut), 0);
      u2_weak gat = u2_nk_soft(wir_r, von, hoc);
      u2_weak cor = u2_rl_molt(wir_r, gat, 
                                      u2_cv_sam_2, u2_rx(wir_r, axe), 
                                      u2_cv_sam_3, u2_rx(wir_r, ref), 
                                      0);

      if ( (u2_none == j2_mcj(Pit, ut, cull)[0].xip) ) {
        u2_noun xip = u2_sh_find(wir_r, cor);
     
        c3_assert(u2_none != xip);
        j2_mcj(Pit, ut, cull)[0].xip = xip;
      }
      u2_rl_lose(wir_r, gat);
      return cor;
    }
  }

  u2_noun                                                         //  transfer
  j2_mcy(Pit, ut, cull)(u2_wire wir_r,
                        u2_noun van,                              //  retain
                        u2_noun sut,                              //  retain
                        u2_atom axe,                              //  retain
                        u2_noun ref)                              //  retain
  {
    u2_ho_jet *jet_j = &j2_mcj(Pit, ut, cull)[0];

    switch ( jet_j->sat_s ) {
      default: c3_assert(0); return u2_bl_bail(wir_r);

      case u2_jet_live: {
        return j2_mcx(Pit, ut, cull)(wir_r, van, sut, axe, ref);
      }
      case u2_jet_dead: {
        u2_noun cor, sof;

        cor = j2_mci(Pit, ut, cull)(wir_r, van, sut, axe, ref);
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
              had = j2_mcx(Pit, ut, cull)(wir_r, van, sut, axe, ref);
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
            cor = j2_mci(Pit, ut, cull)(wir_r, van, sut, ref);
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
  j2_mcj(Pit, ut, cull)[] = {
    { ".3", c3__hevy, j2_mc(Pit, ut, cull), SafeTier6, u2_none, u2_none },
    { }
  };
