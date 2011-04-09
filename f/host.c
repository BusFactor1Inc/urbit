/* f/host.c: driver system.
**
** This file is in the public domain.
*/
#include "all.h"

  /** Global structures.
  **/
    /* Suppress warnings.  Set after the first.
    */
      c3_t JetSuppress;

    /* Hangar stack; top hangar is active.
    */
      u2_ho_hangar *u2_HostHangar;

    /* External drivers.
    */
      extern u2_ho_driver j2_da(watt_268);
      extern u2_ho_driver j2_da(watt_269);
      extern u2_ho_driver j2_da(watt_270);

    /* Built-in battery drivers.   Null `cos` terminates. 
    */
      static u2_ho_driver *u2_HostDriverBase[] = {
        &j2_da(watt_268), 
        &j2_da(watt_269), 
        &j2_da(watt_270), 
        0
      };


  /** Forward declarations.
  **/
    /* _ho_explore(): find driver from chip, caching.
    */
    static u2_ho_driver*
    _ho_explore(u2_ray, u2_noun);

/* _cs_free(): free a cache, freeing.
*/
static void
_cs_free(u2_ho_cash *cas_s)
{
  c3_w i_w;

  for ( i_w = 0; i_w < 16; i_w++ ) {
    if ( u2_none == cas_s->dol_p[i_w].tag ) {
      if ( 0 == cas_s->dol_p[i_w].ptr_v ) {
        _cs_free(cas_s->dol_p[i_w].ptr_v);
        free(cas_s->dol_p[i_w].ptr_v);
      }
    }
  }
}

/* _cs_init(): initialize an empty cache.
*/
static void
_cs_init(u2_ho_cash *cas_s)
{
  c3_w i_w;

  for ( i_w = 0; i_w < 16; i_w++ ) {
    cas_s->dol_p[i_w].tag = u2_none;
    cas_s->dol_p[i_w].ptr_v = 0;
  }
}

/* _ho_cash_find(): find a pointer in a cache, or return 0.
*/
static void*
_ho_cash_find(u2_ho_cash *cas_s,
              u2_noun    som)
{
  c3_w mug_w = u2_mug(som);
  c3_w off_w = 0;

  while ( 1 ) {
    if ( off_w == 32 ) {
      c3_w i_w;

      for ( i_w = 0; i_w < 16; i_w++ ) {
        u2_ho_pear* per_p = &cas_s->dol_p[i_w];
        u2_noun     tag   = per_p->tag;

        if ( (u2_none != tag) && (u2_yes == u2_sing(som, tag)) ) {
          return per_p->ptr_v;
        }
      }
      return 0;
    }
    else {
      c3_w        fat_w = (mug_w >> off_w) & 15;
      u2_ho_pear* per_p = &cas_s->dol_p[fat_w];
      u2_noun     tag   = per_p->tag;

      if ( u2_none == tag ) {
        cas_s = per_p->ptr_v;

        if ( 0 == cas_s ) {
          return 0;
        } else {
          off_w += 4;
          continue;
        }
      }
      else if ( u2_yes == u2_sing(som, tag) ) {
        return per_p->ptr_v;
      }
      else return 0;
    }
  }
}

/* _cs_save(): as _ho_cash_save(), with mug and offset.
*/
static void
_cs_save(u2_ho_cash* cas_s,
         u2_noun     som,
         void*       ptr_v,
         c3_w        mug_w,
         c3_w        off_w)
{
  while ( 1 ) {
    if ( off_w == 32 ) {
      /* Linear search in a list of 16 total collisions.
      ** Overflow probability: (n/(2^31))^15 ~= 0.
      */
      c3_w i_w;

      for ( i_w = 0; i_w < 16; i_w++ ) {
        u2_ho_pear* per_p = &cas_s->dol_p[i_w];
        u2_noun     tag   = per_p->tag;

        if ( u2_none != tag ) {
          /* Duplicate entry - no need to save it.
          */
          return;
        }
        else {
          per_p->tag = som;
          per_p->ptr_v = ptr_v;
        }
      }
      return;
    }
    else {
      c3_w        fat_w = (mug_w >> off_w) & 15;
      u2_ho_pear* per_p = &cas_s->dol_p[fat_w];
      u2_noun     tag   = per_p->tag;

      if ( u2_none == tag ) {
        cas_s = per_p->ptr_v;

        if ( 0 == cas_s ) {
          per_p->tag = som;
          per_p->ptr_v = ptr_v;
          return;
        } 
        else {
          off_w += 4;
          continue;
        }
      }
      else {
        void*       qtr_v = per_p->ptr_v;
        u2_ho_cash* cax_s;

        if ( 0 == (cax_s = malloc(sizeof(*cax_s))) ) {
          return;
        }
        _cs_init(cax_s);

        _cs_save(cax_s, tag, qtr_v, u2_mug(tag), 4+off_w);
        _cs_save(cax_s, som, ptr_v, mug_w, 4+off_w);

        per_p->tag = u2_none;
        per_p->ptr_v = cax_s;

        return;
      }
    }
  }
}

/* _ho_cash_save(): save a noun in a cache.
*/
static void
_ho_cash_save(u2_ho_cash *cas_s,
              u2_noun    som,
              void*      ptr_v)
{
  _cs_save(cas_s, som, ptr_v, u2_mug(som), 0);
}

/* _ho_mop_decimal(): measure/print decimal number.
*/
static c3_w
_ho_mop_decimal(c3_c *buf_c, u2_noun num)
{
  if ( u2_no == u2_stud(num) ) {
    return 0;
  } else {
    if ( 0 == num ) {
      if ( buf_c ) *buf_c = '0';
      return 1;
    } else {
      mpz_t num_mp;
      c3_w  len_w;

      mpz_init(num_mp);
      u2_mp(num_mp, num);
      len_w = mpz_sizeinbase(num_mp, 10);

      if ( buf_c ) {
        gmp_sprintf(buf_c, "%Zu", num_mp);
      }
      mpz_clear(num_mp);
      return len_w;
    }
  }
}

/* _ho_mop_term(): measure/print term.
*/
static c3_w
_ho_mop_term(c3_c *buf_c, u2_noun tam)
{
  if ( u2_no == u2_stud(tam) ) {
    return 0;
  }
  else {
    c3_w len_w = u2_met(3, tam);

    if ( buf_c ) {
      u2_bytes(0, len_w, (c3_y *)buf_c, tam);
      {
        c3_w i_w;

        for ( i_w = 0; i_w < len_w; i_w++ ) {
          if ( !((buf_c[i_w] >= 'a') && (buf_c[i_w] <= 'z')) ) {
            buf_c[i_w] = '_';
          }
        }
      }
    }
    return len_w;
  }
}

/* _ho_mop_version(): measure/print version.
*/
static c3_w
_ho_mop_version(c3_c *buf_c, u2_noun ver)
{
  if ( u2_no == u2_dust(ver) ) {
    return _ho_mop_decimal(buf_c, ver);
  }
  else {
    c3_w len_w = _ho_mop_decimal(buf_c, u2_h(ver));

    if ( buf_c ) buf_c += len_w;
    len_w++;
    if ( buf_c ) *buf_c++ = 'x';

    return (len_w + _ho_mop_decimal(buf_c, u2_t(ver)));
  }
}

/* _ho_mop_seal(): measure/print identity declaration.
*/
static c3_w
_ho_mop_seal(c3_c *buf_c, u2_noun mek)
{
  u2_noun std, ven, pro, ver, kel;
  c3_w    len_w, lan_w, lon_w, lin_w;

  if ( u2_yes == u2_as_qual(mek, &ven, &pro, &ver, &kel) ) {
    len_w = _ho_mop_term(buf_c, ven);
    if ( buf_c ) buf_c += len_w;
    len_w++;
    if ( buf_c ) *buf_c++ = '_';

    lan_w = _ho_mop_term(buf_c, pro);
    if ( buf_c ) buf_c += lan_w;
    lan_w++;
    if ( buf_c ) *buf_c++ = '_';

    lon_w = _ho_mop_version(buf_c, ver);
    if ( buf_c ) buf_c += lon_w;
    lon_w++;
    if ( buf_c ) *buf_c++ = '_';

    lin_w = _ho_mop_decimal(buf_c, kel);
    if ( buf_c ) buf_c += lin_w;

    return (len_w + lan_w + lon_w + lin_w);
  }
  else if ( u2_yes == u2_as_trel(mek, &ven, &pro, &kel) ) {
    len_w = _ho_mop_term(buf_c, ven);
    if ( buf_c ) buf_c += len_w;
    len_w++;
    if ( buf_c ) *buf_c++ = '_';

    lan_w = _ho_mop_term(buf_c, pro);
    if ( buf_c ) buf_c += lan_w;
    lan_w++;
    if ( buf_c ) *buf_c++ = '_';

    lon_w = _ho_mop_decimal(buf_c, kel);
    if ( buf_c ) buf_c += lon_w;
    lon_w++;
    if ( buf_c ) *buf_c++ = '_';

    return (len_w + lan_w + lon_w);
  }
  else if ( u2_yes == u2_as_cell(mek, &std, &kel) ) {
    len_w = _ho_mop_term(buf_c, std);
    if ( buf_c ) buf_c += len_w;
    len_w++;
    if ( buf_c ) *buf_c++ = '_';

    lan_w = _ho_mop_decimal(buf_c, kel);
    if ( buf_c ) buf_c += lan_w;

    return (len_w + lan_w);
  }
  else {
    len_w = _ho_mop_term(buf_c, mek);
    
    return len_w;
  }
}

/* _ho_mop_chip(): measure/print control string, from chip.
*/
static c3_w
_ho_mop_chip(c3_c *buf_c, u2_noun xip)
{
  u2_disc dac = u2_h(xip);
  u2_noun pit = u2_t(u2_t(xip));

  if ( u2_nul == pit ) {
    return _ho_mop_seal(buf_c, u2_h(dac));
  }
  else {
    c3_w len_w = _ho_mop_chip(buf_c, u2_t(pit));

    if ( buf_c ) {
      buf_c += len_w;
      *buf_c++ = '_';
      *buf_c++ = '_';
    }
    return (len_w + 2 + _ho_mop_seal(buf_c, u2_h(dac)));
  }
}

/* u2_ho_cstring(): return malloced control string for `xip`.
*/
c3_c*                                                             //  produce
u2_ho_cstring(u2_noun xip)                                        //  retain
{
  c3_w len_w = _ho_mop_chip(0, xip);
  c3_c *cos_c;

  if ( !(cos_c = malloc(len_w + 1)) ) abort();

  _ho_mop_chip(cos_c, xip);
  cos_c[len_w] = 0;

  return cos_c;
}

/* u2_ho_boot(): 
**
**   Boot driver system.  Note that all chips and
**   tools are considered permanent between reboots.
*/
static void
_ho_boot(u2_ho_hangar *hag)
{
  _cs_init(&hag->bad_s);
}

/* _ho_down(): 
**
**   Release all resources in `hag`.
*/
static void
_ho_down(u2_ho_hangar *hag)
{
  _cs_free(&hag->bad_s);
}

/* u2_ho_push(): 
**
**   Push a driver hangar (corresponding to a jet shed).
*/
void
u2_ho_push(void)
{
  u2_ho_hangar *hag = malloc(sizeof(u2_ho_hangar));

  _ho_boot(hag);
  hag->nex_h = u2_HostHangar;
  u2_HostHangar = hag;
}

/* u2_ho_popp():
**
**  Pop a hangar.
*/
void
u2_ho_popp(void)
{
  u2_ho_hangar *hag = u2_HostHangar;
  u2_ho_hangar *nex_h = hag->nex_h;

  _ho_down(hag);
  free(hag);
  u2_HostHangar = nex_h;
}

/* u2_ho_klar():
**
**   Clear and release all hangars.
*/
void
u2_ho_klar(void)
{
  while ( u2_HostHangar ) {
    u2_ho_popp();
  }
}

/* u2_ho_warn(): report a warning, file and line.
*/
void
u2_ho_warn(const c3_c* fil_c,
           c3_w        lyn_w)
{
  if ( !JetSuppress ) {
    fprintf(stderr, "ho: warn: %s:%u\n", fil_c, lyn_w);
    JetSuppress = 1;
  }
}


/* _ho_abstract(): compute 31-bit jet axis in core battery.
*/
static c3_l
_ho_abstract(u2_noun xip,                                         //  retain 
             const c3_c *fcs_c)                                   //  retain
{
  if ( *fcs_c == '.' ) {
    c3_d axe_d = 0;
    c3_l axe_l = 0;

    sscanf(fcs_c+1, "%llu", &axe_d);
    if ( axe_d >> 32ULL || 
         ((1 << 31) & (axe_l = (c3_w)axe_d)) || 
         (axe_l < 3) )
    {
      u2_ho_warn_here();
      return 0;
    }
    // return u2_ax_mas(axe_l);
    return axe_l;
  }
  else {
    u2_noun nut = u2_t(u2_h(xip));

    while ( _0 != nut ) {
      u2_noun i_nut = u2_h(nut);

      if ( (u2_yes == u2_sing_c(fcs_c, u2_h(i_nut))) ) {
        u2_noun fal = u2_t(i_nut);

        /* `fal` must match `[9 x [0 1]]`
        */
        if ( (u2_yes == u2_dust(fal)) && (u2_nock_kick == u2_h(fal)) ) {
          u2_noun t_fal = u2_t(fal);

          if ( u2_yes == u2_dust(t_fal) ) {
            u2_noun ht_fal = u2_h(t_fal);
            u2_noun tt_fal = u2_t(t_fal);

            if ( (u2_yes == u2_stud(ht_fal)) &&
                 (u2_yes == u2_dust(tt_fal)) &&
                 (_0 == u2_h(tt_fal)) &&
                 (_1 == u2_t(tt_fal)) )
            {
              u2_atom axe = ht_fal;

              if ( !u2_fly_is_cat(axe) ) {
                u2_ho_warn_here();
              }
              // return u2_ax_mas(axe);
              return axe;
            }
          }
        }
        u2_ho_warn_here();
        return 0;
      }
      nut = u2_t(nut);
    }
    u2_ho_warn_here();
    return 0;
  }
}

/* _ho_attach(): process static driver for execution.
*/
static void
_ho_attach(u2_rail ral_r,
           u2_ho_driver* dry_d)                                   //  retain
{
  u2_ho_jet*    jet_j;
  c3_w          i_w;

  _cs_init(&dry_d->jax_s);

  if ( dry_d->fan_j ) {
    for ( i_w = 0; (jet_j = &dry_d->fan_j[i_w])->fcs_c; i_w++ ) {
      jet_j->xip = dry_d->xip;
      jet_j->axe_l = _ho_abstract(dry_d->xip, jet_j->fcs_c);

      _ho_cash_save(&dry_d->jax_s, jet_j->axe_l, jet_j);
    }
  }
}

/* _ho_explore_dummy(): produce dummy driver.
*/
static u2_ho_driver*                                              //  produce
_ho_explore_dummy(u2_rail     ral_r,
                  const c3_c* cos_c,                              //  submit
                  u2_noun     xip)                                //  senior
{
  u2_ho_driver *dry_d;

  if ( !(dry_d = malloc(sizeof(u2_ho_driver))) ) {
    abort();
  }
  dry_d->cos_c = cos_c;
  dry_d->xip = xip;
  if ( !(dry_d->fan_j = malloc(sizeof(u2_ho_jet))) ) {
    abort();
  }
  dry_d->fan_j->fcs_c = 0;

  return dry_d;
}

/* _ho_explore_static(): find driver from built-in list, or return 0.
*/
static u2_ho_driver*
_ho_explore_static(u2_rail ral_r,
                   u2_noun xip,
                   c3_c*   cos_c)
{
  c3_w  i_w;

  for ( i_w=0; u2_HostDriverBase[i_w]; i_w++ ) {
    u2_ho_driver *dry_d = u2_HostDriverBase[i_w];

    if ( (u2_none == dry_d->xip) && !strcmp(cos_c, dry_d->cos_c) ) {
      dry_d->xip = xip;
      free(cos_c);

      _ho_cash_save(&u2_HostHangar->bad_s, xip, dry_d);
      return dry_d;
    }
  }
  return 0;
}

/* _ho_explore_parent(): find driver from parent, or return 0.
*/
static u2_ho_driver*
_ho_explore_parent(u2_rail ral_r,
                   u2_noun xip,
                   c3_c*   cos_c)
{
  u2_noun pet = u2_t(u2_t(xip));

  if ( _0 == pet ) {
    return 0;
  } else {
    u2_ho_driver* par_d = _ho_explore(ral_r, u2_t(pet));
    c3_w          i_w;

    c3_assert(par_d);
    if ( par_d->sub_d ) {
      for ( i_w = 0; par_d->sub_d[i_w].cos_c; i_w++ ) {
        if ( (u2_none == par_d->sub_d[i_w].xip) &&
             !strcmp(cos_c, par_d->sub_d[i_w].cos_c) ) 
        {
          u2_ho_driver *dry_d = &par_d->sub_d[i_w];

          dry_d->xip = xip;
          free(cos_c);

          _ho_cash_save(&u2_HostHangar->bad_s, xip, dry_d);
          return dry_d;
        }
      }
    }
    return 0;
  }
}

/* _ho_explore(): find driver from chip, caching.
*/
static u2_ho_driver*                                              //  discover
_ho_explore(u2_rail ral_r,
            u2_noun xip)                                          //  senior
{
  u2_ho_driver* dry_d;

  if ( 0 != (dry_d = _ho_cash_find(&u2_HostHangar->bad_s, xip)) ) {
    return dry_d;
  } else {
    c3_c* cos_c = u2_ho_cstring(xip);

    if ( 0 != (dry_d = _ho_explore_parent(ral_r, xip, cos_c)) ) {
      // fprintf(stderr, "battery: child : %s\n", cos_c);
      _ho_attach(ral_r, dry_d);
      return dry_d;
    }
    else if ( 0 != (dry_d = _ho_explore_static(ral_r, xip, cos_c)) ) {
      // fprintf(stderr, "battery: static: %s\n", cos_c);
      _ho_attach(ral_r, dry_d);
      return dry_d;
    }
    else {
      // fprintf(stderr, "battery: dummy : %s\n", cos_c);
      dry_d = _ho_explore_dummy(ral_r, cos_c, xip);

      _ho_cash_save(&u2_HostHangar->bad_s, xip, dry_d);
      return dry_d;
    }
  }
}

/* u2_ho_prepare(): prepare jets in `xip`.
*/
void
u2_ho_prepare(u2_rail ral_r,
              u2_noun xip)                                        //  retain
{
  _ho_explore(ral_r, xip);
}

/* _ho_conquer(): find jet from xip and axe.
*/
static u2_ho_jet*
_ho_conquer(u2_rail ral_r,
            u2_noun xip,
            u2_atom axe)
{
  u2_ho_driver *dry_d;

  if ( 0 == (dry_d = _ho_explore(ral_r, xip)) ) {
    return 0;
  } else if ( 0 == dry_d->fan_j ) {
    return 0;
  } else {
    if ( 3 == axe ) {
      //  Linear search - slow, except in this common case.
      //
      u2_ho_jet *jet_j = dry_d->fan_j;

      while ( jet_j->fcs_c ) {
        if ( axe == jet_j->axe_l ) {
          return jet_j;
        }
        jet_j++;
      }
      return 0;
    } else {
      return _ho_cash_find(&dry_d->jax_s, axe);
    }
  }
}
 
/* u2_ho_test():
**
**   Report result of jet test.  `had` is native; `sof` is nock.
*/
void
u2_ho_test(u2_wire    wir_r, 
           u2_ho_jet* jet_j,
           u2_noun    cor,                                         //  retain
           u2_noun    sof,                                         //  retain
           u2_noun    had)                                         //  retain
{
  if ( (u2_none == cor) || 
       ((u2_none == had) && (u2_none == sof)) ||
       (u2_none == jet_j->xip) ) 
  {
    return;
  } else {
    c3_c*       cos_c = u2_ho_cstring(jet_j->xip);
    c3_w        mug_w = u2_mug(cor);
    const c3_c* msg_c;

    if ( u2_none == had ) {
      msg_c = "bail";
      printf("bail: cos_c: %s\n", cos_c);
    } else if ( u2_none == sof ) {
      msg_c = "funk";
      printf("funk: cos_c: %s\n", cos_c);
      c3_assert(0);

    } else if ( u2_no == u2_sing(had, sof) ) {
      msg_c = "fail";
      printf("fail: cos_c: %s\n", cos_c);

      //  For detailed debugging, activate/extend this junkheap as needed.
      //
#if 0
      {
        u2_noun sut, dab, van;

        if ( (u2_no == u2_mean(cor, u2_cv_sam, &dab, u2_cv_con, &van, 0)) ||
             (u2_none == (sut = u2_frag(u2_cv_sam, van))) )
        {
          c3_assert(0);
        } else {
          j2_mcy(watt_270, ut, dupt)(wir_r, van, "sut", sut);
        }
      }
      {
        u2_noun sut, gol, gen, van;

        if ( (u2_no == u2_mean(cor, u2_cv_sam_2, &gol, 
                                    u2_cv_sam_3, &gen,
                                    u2_cv_con, &van, 0)) ||
             (u2_none == (sut = u2_frag(u2_cv_sam, van))) )
        {
          c3_assert(0);
        } else {
          j2_mcy(watt_271, ut, dupt)(wir_r, van, "sut", sut);
          j2_mcy(watt_271, ut, dupt)(wir_r, van, "gol", gol);
          u2_err(wir_r, "gen", gen);
/*
          j2_mcy(watt_271, ut, dupt)(wir_r, van, "h_sof", u2_h(sof));
          j2_mcy(watt_271, ut, dupt)(wir_r, van, "h_had", u2_h(had));

          u2_err(wir_r, "t_sof", u2_t(sof));
          u2_err(wir_r, "t_had", u2_t(had));
*/
        }
      }
      {
        u2_noun sut, gen, van;

        if ( (u2_no == u2_mean(cor, u2_cv_sam, &gen,
                                    u2_cv_con, &van, 0)) ||
             (u2_none == (sut = u2_frag(u2_cv_sam, van))) )
        {
          c3_assert(0);
        } else {
          u2_err(wir_r, "sut", sut);
          // j2_mcy(watt_271, ut, dupt)(wir_r, van, "sut", sut);
          u2_err(wir_r, "gen", gen);
        }
      }
      {
        u2_err(wir_r, "wrong", had);
        u2_err(wir_r, "right", sof);
      }
      {
        u2_noun sut, ref, van;

        if ( (u2_no == u2_mean(cor, u2_cv_sam, &ref, u2_cv_con, &van, 0)) ||
             (u2_none == (sut = u2_frag(u2_cv_sam, van))) )
        {
          c3_assert(0);
        } else {
          j2_mcy(watt_271, ut, dupt)(wir_r, van, "sut", sut);
          j2_mcy(watt_271, ut, dupt)(wir_r, van, "ref", ref);

          j2_mcy(watt_271, ut, dupt)(wir_r, van, "sof", sof);
          j2_mcy(watt_271, ut, dupt)(wir_r, van, "had", had);
        }
      }
      {
        u2_noun sut, ref, van;

        if ( (u2_no == u2_mean(cor, u2_cv_sam, &ref, u2_cv_con, &van, 0)) ||
             (u2_none == (sut = u2_frag(u2_cv_sam, van))) )
        {
          c3_assert(0);
        } else {
          j2_mcy(watt_271, ut, dupt)(wir_r, van, "sut", sut);
          j2_mcy(watt_271, ut, dupt)(wir_r, van, "ref", ref);
        }
      }
      {
        u2_wire wir_r = 0;
        u2_noun sut, way, hep, van;

        if ( (u2_no == u2_mean(cor, u2_cv_sam_2, &way, 
                                    u2_cv_sam_3, &hep,
                                    u2_cv_con, &van, 0)) ||
             (u2_none == (sut = u2_frag(u2_cv_sam, van))) )
        {
          c3_assert(0);
        } else {
          j2_mcy(watt_271, ut, dupt)(wir_r, van, "sut", sut);
          u2_err(wir_r, "way", way);
          u2_err(wir_r, "hep", hep);

          u2_err(wir_r, "p_sof", u2_h(sof));
          u2_err(wir_r, "p_had", u2_h(had));

          j2_mcy(watt_271, ut, dupt)(wir_r, van, "r_sof", u2_t(u2_t(sof)));
          j2_mcy(watt_271, ut, dupt)(wir_r, van, "r_had", u2_t(u2_t(had)));
        }
      }
      {
        u2_noun sut, gol, gen, van;

        if ( (u2_no == u2_mean(cor, u2_cv_sam_2, &gol, 
                                    u2_cv_sam_3, &gen,
                                    u2_cv_con, &van, 0)) ||
             (u2_none == (sut = u2_frag(u2_cv_sam, van))) )
        {
          c3_assert(0);
        } else {
          j2_mcy(watt_271, ut, dupt)(wir_r, van, "sut", sut);
          j2_mcy(watt_271, ut, dupt)(wir_r, van, "gol", gol);
          u2_err(wir_r, "gen", gen);

          j2_mcy(watt_271, ut, dupt)(wir_r, van, "h_sof", u2_h(sof));
          j2_mcy(watt_271, ut, dupt)(wir_r, van, "h_had", u2_h(had));

          u2_err(wir_r, "t_sof", u2_t(sof));
          u2_err(wir_r, "t_had", u2_t(had));
        }
      }
#endif
      // LoomStop = 1;
      c3_assert(0);
    } else {
      msg_c = "nice";
    }

    if ( strcmp("nice", msg_c) ) {
      fprintf(stderr, "%s: %8x: %s\n", msg_c, mug_w, cos_c);
    }
    free(cos_c);
  }
}

/* _ho_run(): execute jet.
*/
static u2_weak                                                    //  produce
_ho_run(u2_ray      wir_r,
        u2_ho_jet*  jet_j,
        u2_noun     cor)                                          //  retain
{
  u2_noun ret;

  switch ( jet_j->vok_m ) {
    default: c3_assert(0); return u2_none;

    case c3__lite: {
      /* Lite jet: bail prohibited.  The lite jet must detect and control
      ** its own internal errors, freeing stray nouns and returning u2_none.
      ** u2_b functions may not be used.
      **
      ** Pro: lite jets minimize invocation latency. 
      **
      ** Con: manual programming of large functions in lite mode is difficult.
      ** Con: lite jets produce no crash report, requiring soft rerun.
      */
      {
        u2_ray  jub_r = u2_wire_jub_r(wir_r);
        u2_noun ret; 

        u2_wire_jub_r(wir_r) = 0;
        ret = jet_j->fun_f(wir_r, cor);
        u2_wire_jub_r(wir_r) = jub_r;

        return ret;
      }
    }
    case c3__fine: {
      /* Fine jet: bail context and crash tracking.
      **
      ** Pro: bail support and efficient crash reporting.
      **
      ** Con: invocation latency is higher than 'lite'.
      ** Con: programmer must accurately reproduce crash trace.
      ** Con: not yet supported - treated as hevy.
      */
    }
    case c3__hevy: {
      /* Hevy jet: maintains recursive bail context.  The hevy jet can
      ** bail out at any time.  The host framework should (but does not
      ** yet) free stray nouns.
      **
      ** Pro: hevy jets are the easiest to program.
      **
      ** Con: invocation latency is higher.
      ** Con: hevy jets produce no crash report, requiring soft rerun.
      */
      {
        u2_ray jub_r = u2_bl_open(wir_r);

        if ( u2_bl_set(wir_r) ) {
          u2_bl_done(wir_r, jub_r);
          ret = u2_none;
        } 
        else {
          ret = jet_j->fun_f(wir_r, cor);

          u2_bl_done(wir_r, jub_r);
        }
        return ret;
      }
    }
  }
}

    /* u2_ho_nice():
    **
    **   Verify quickly that a chip's jet supports this core.
    **
    **   Only the outer battery is assumed to match.
    */
      u2_flag
      u2_ho_nice(u2_ray     wir_r,
                 u2_ho_jet* jet_j,
                 u2_noun    cor);


/* u2_ho_use():
**
**   Run a jet.
*/
u2_weak                                                           //  produce
u2_ho_use(u2_ray     wir_r,
          u2_ho_jet* jet_j,
          u2_noun    cor,                                         //  retain
          u2_noun    fol)                                         //  retain
{
  u2_noun key=u2_none, pro;
  c3_m    fun_m = 0;

  if ( jet_j->sat_s & u2_jet_memo ) {
    if ( jet_j->key_f ) {
      if ( u2_none == (key = jet_j->key_f(wir_r, cor)) ) {
        return u2_none;
      }
      else {
        fun_m = (0x7fffffff & (c3_w)jet_j);

        if ( u2_none != (pro = u2_rl_find(wir_r, fun_m, key)) ) {
          u2_rz(wir_r, key);
          return pro;
        }
      }
    } else {
      if ( u2_none != (pro = u2_rl_find_cell(wir_r, 0, cor, fol)) ) {
        return u2_rx(wir_r, pro);
      }
    }
  }

  if ( !(jet_j->sat_s & u2_jet_live) ) {
    pro = u2_nk_soft(wir_r, u2_rx(wir_r, cor), fol);
  }
  else {
    if ( !(jet_j->sat_s & u2_jet_test) ) {
      pro = _ho_run(wir_r, jet_j, cor);

      if ( u2_none == pro ) {
        jet_j->sat_s &= ~u2_jet_live;
        {
          char *cos_c = u2_ho_cstring(jet_j->xip);

          fprintf(stderr, "<<lose: %s>>\n", cos_c);
          free(cos_c);
          pro = u2_nk_soft(wir_r, u2_rx(wir_r, cor), fol);
        }
        jet_j->sat_s |= u2_jet_live;

        u2_ho_test(wir_r, jet_j, cor, pro, u2_none);
      }
    }
    else { 
      u2_noun sof;

      jet_j->sat_s &= ~u2_jet_test;
      {
        pro = _ho_run(wir_r, jet_j, cor);
      }
      jet_j->sat_s |= u2_jet_test;

      jet_j->sat_s &= ~u2_jet_live;
      {
        sof = u2_nk_soft(wir_r, u2_rx(wir_r, cor), fol);
      }
      jet_j->sat_s |= u2_jet_live;

      u2_bx_used(wir_r);
      u2_ho_test(wir_r, jet_j, cor, sof, pro);
      u2_rz(wir_r, pro);

      pro = sof;
    }
  }

  if ( !(jet_j->sat_s & u2_jet_memo) ) {
    return pro;
  }
  else {
    if ( jet_j->key_f ) {
      pro = u2_rl_save(wir_r, fun_m, key, pro);
      u2_rz(wir_r, key);

      return pro;
    }
    else {
      return u2_rl_save_cell(wir_r, 0, cor, fol, pro);
    }
  }
}

/* u2_ho_kick():
**
**   Apply host nock driver on `xip`, `cor`, `fol`.
*/
u2_weak                                                           //  produce
u2_ho_kick(u2_ray   wir_r,
           u2_chip  xip,                                          //  retain
           u2_noun  cor,                                          //  retain
           u2_atom  axe)                                          //  retain
{
  u2_noun    fol; 
  u2_ho_jet* jet_j;

  if ( u2_none == (fol = u2_frag(axe, cor)) ) {
    return u2_none;
  }
  else if ( 0 == (jet_j = _ho_conquer(wir_r, xip, axe)) ) {
    return u2_nk_soft(wir_r, u2_rx(wir_r, cor), fol);
  }
  else {
    return u2_ho_use(wir_r, jet_j, cor, fol);
  }
}
