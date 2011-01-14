/* j/6/play.c
**
** This file is in the public domain.
*/
#include "all.h"
#include "../pit.h"

/* functions
*/
  u2_noun                                                         //  transfer
  j2_mcx(Pit, ut, play)(u2_wire wir_r, 
                          u2_noun van,                            //  retain
                          u2_noun sut,                            //  retain
                          u2_noun gen)                            //  retain
  {
    u2_noun vin = u2_bn_molt(wir_r, van, 87, u2_no, 0);
    u2_noun pox = j2_mcy(Pit, ut, mill)(wir_r, vin, sut, gen);
    u2_noun h_pox = u2_h(pox);

    u2_rl_gain(wir_r, h_pox);
    u2_rl_lose(wir_r, pox); 
    u2_rl_lose(wir_r, vin);

    return h_pox;
  }


/* boilerplate
*/
  u2_ho_jet 
  j2_mcj(Pit, ut, play)[];

  u2_noun                                                         //  transfer
  j2_mc(Pit, ut, play)(u2_wire wir_r, 
                         u2_noun cor)                             //  retain
  {
    u2_noun sut, gen, van;

    if ( (u2_no == u2_mean(cor, u2_cv_sam, &gen, u2_cv_con, &van, 0)) ||
         (u2_none == (sut = u2_frag(u2_cv_sam, van))) )
    {
      return u2_bl_bail(wir_r);
    } else {
      return j2_mcx(Pit, ut, play)(wir_r, van, sut, gen);
    }
  }

  u2_weak                                                         //  transfer
  j2_mci(Pit, ut, play)(u2_wire wir_r,
                          u2_noun van,                            //  retain
                          u2_noun sut,                            //  retain 
                          u2_noun gen)                            //  retain
  {
    u2_weak hoc = u2_sh_look(wir_r, van, "play");

    if ( u2_none == hoc ) {
      c3_assert(!"register play");
      return u2_none;
    } else {
      u2_weak von = u2_rl_molt(wir_r, van, u2_cv_sam, u2_rx(wir_r, sut), 0);
      u2_weak gat = u2_nk_soft(wir_r, von, hoc);
      u2_weak cor = u2_rl_molt(wir_r, gat, u2_cv_sam, u2_rx(wir_r, gen), 0);

      if ( (u2_none == j2_mcj(Pit, ut, play)[0].xip) ) {
        u2_noun xip = u2_sh_find(wir_r, cor);
     
        c3_assert(u2_none != xip);
        j2_mcj(Pit, ut, play)[0].xip = xip;
      }
      u2_rl_lose(wir_r, gat);
      return cor;
    }
  }

  u2_noun                                                         //  transfer
  j2_mcy(Pit, ut, play)(u2_wire wir_r,
                          u2_noun van,                            //  retain
                          u2_noun sut,                            //  retain
                          u2_noun gen)                            //  retain
  {
    u2_ho_jet *jet_j = &j2_mcj(Pit, ut, play)[0];

    switch ( jet_j->sat_s ) {
      default: c3_assert(0); return u2_bl_bail(wir_r);

      case u2_jet_live: {
        return j2_mcx(Pit, ut, play)(wir_r, van, sut, gen);
      }
      case u2_jet_dead: {
        u2_noun cor, sof;

        cor = j2_mci(Pit, ut, play)(wir_r, van, sut, gen);
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
              had = j2_mcx(Pit, ut, play)(wir_r, van, sut, gen);
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
            cor = j2_mci(Pit, ut, play)(wir_r, van, sut, gen);
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
  j2_mcj(Pit, ut, play)[] = {
    { ".3", c3__hevy, j2_mc(Pit, ut, play), SafeTier6, u2_none, u2_none },
    { }
  };
