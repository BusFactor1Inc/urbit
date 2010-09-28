/* f/host.c: driver system.
**
** This file is in the public domain.
*/
#include "all.h"
 
  /** Types.
  **/
    /* u2_ho_jet: a C function, per formula.
    */
      typedef struct {
        /* Control string - formula from battery.
        **
        **    "%@" | "hook"
        */
        const c3_c* cos_c;

        /* disc: battery identifier.
        */
        u2_disc dac;

        /* Tool: Nock formula.
        */
        u2_tool fol;
 
        /* Stable iff true; test iff false.
        */
        c3_t ace_t;

        /* C function, on core `[[sam con] bat]`.
        */
        u2_weak (*fun_f)(u2_ray wir_r, u2_noun cor);
      } u2_ho_jet;

    /* u2_ho_driver: battery driver.
    */
      typedef struct {
        /* Control string - matches disc from C:
        **
        **    cos: kid | kid__cos
        **    kid: pro ver
        **    pro: asc | asc_asc
        **    ver: @ | @_@ | @_@_@
        */
        const c3_c* cos_c;
      
        /* disc: battery identifier, from shed.
        */
        u2_disc dac;

        /* Mug: short hash of battery, or 0.  Must match if set.
        */
        c3_w mug_w;

        /* Function/formula jets.  Null `cos` terminates.
        */
        u2_ho_jet fan_j[1];
      } u2_ho_driver;

    /* u2_ho_pear: mug-to-pointer binding.
    */
      typedef struct {
        u2_noun tag;
        void*   ptr_v;
      } u2_ho_pear;

    /* u2_ho_cash: mug-to-pointer cache.  Semantics match sham.
    */
      typedef struct {
        u2_ho_pear dol_p[16];
      } u2_ho_cash;

    /* u2_ho_hangar: driver system.
    */
      typedef struct {
        /* Cache from formula to jet.
        */
        u2_ho_cash jac_s;

        /* Cache from disc to driver.
        */
        u2_ho_cash bad_s;
      } u2_ho_hangar;


  /** Global structures.
  **/
    /* Static hangar.
    */
      static u2_ho_hangar JetHangar;

    /* Built-in battery drivers.   Null `cos` terminates. 
    */
      static u2_ho_driver JetBase[] = {
        { 0 }
      };


/* _ho_cash_free(): free a cache, freeing.
*/
static void
_ho_cash_free(u2_ho_cash *cas_s)
{
  c3_w i_w;

  for ( i_w = 0; i_w < 16; i_w++ ) {
    if ( u2_none == cas_s->dol_p[i_w].tag ) {
      if ( 0 == cas_s->dol_p[i_w].ptr_v ) {
        _ho_cash_free(cas_s->dol_p[i_w].ptr_v);
        free(cas_s->dol_p[i_w].ptr_v);
      }
    }
  }
}

/* _ho_cash_init(): initialize an empty cache.
*/
static void
_ho_cash_init(u2_ho_cash *cas_s)
{
  c3_w i_w;

  for ( i_w = 0; i_w < 16; i_w++ ) {
    cas_s->dol_p[i_w].tag = u2_none;
    cas_s->dol_p[i_w].ptr_v = 0;
  }
}

/* jx_cash_find(): find a noun in a cache, or return 0.
*/
static void*
_ho_cash_find(u2_ho_cash *cas_s,
              u2_noun    som)
{
#if 1
  return 0;
#else
#endif
}

/* _ho_cash_save(): save a noun in a cache.
*/
static void
_ho_cash_save(u2_ho_cash *cas_s,
              u2_noun    som,
              void*      ptr_v)
{
#if 1
#else
#endif
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

      u2_mp(num_mp, num);
      len_w = mpz_sizeinbase(num_mp, 10);

      if ( buf_c ) {
        gmp_sprintf(buf_c, "%Z", num_mp);
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

/* _ho_mop_mint(): measure/print mint.
*/
static c3_w
_ho_mop_mint(c3_c *buf_c, u2_noun min)
{
  if ( u2_no == u2_dust(min) ) {
    return _ho_mop_term(buf_c, min);
  }
  else {
    c3_w len_w = _ho_mop_term(buf_c, u2_h(min));

    if ( buf_c ) buf_c += len_w;
    len_w++;
    if ( buf_c ) *buf_c++ = '_';

    return (len_w + _ho_mop_term(buf_c, u2_t(min)));
  }
}

/* _ho_mop_version(): measure/print version.
*/
static c3_w
_ho_mop_version(c3_c *buf_c, u2_noun ver)
{
  if ( u2_no == u2_dust(ver) ) {
    return 0;
  }
  else {
    c3_w len_w = _ho_mop_decimal(buf_c, u2_h(ver));

    if ( buf_c ) buf_c += len_w;
    len_w++;
    if ( buf_c ) *buf_c++ = '_';

    return (len_w + _ho_mop_decimal(buf_c, u2_t(ver)));
  }
}

/* _ho_mop_release(): measure/print release definition.
*/
static c3_w
_ho_mop_release(c3_c *buf_c, u2_noun rel)
{
  if ( u2_no == u2_dust(rel) ) {
    return _ho_mop_decimal(buf_c, rel);
  }
  else {
    c3_w len_w = _ho_mop_version(buf_c, u2_h(rel));

    if ( buf_c ) buf_c += len_w;
    len_w++;
    if ( buf_c ) *buf_c++ = '_';

    return (len_w + _ho_mop_decimal(buf_c, u2_t(rel)));
  }
}

/* _ho_mop_mark(): measure/print objective mark.
*/
static c3_w
_ho_mop_mark(c3_c *buf_c, u2_noun mek)
{
  if ( u2_no == u2_dust(mek) ) {
    return 0;
  } else {
    c3_w len_w = _ho_mop_mint(buf_c, u2_h(mek));
  
    if ( buf_c ) buf_c += len_w;
    len_w++;
    if ( buf_c ) *buf_c++ = '_';

    return (len_w + _ho_mop_release(buf_c, u2_t(mek)));
  }
}

/* _ho_mop_cost(): measure/print control string, malloced, from disc.
*/
static c3_w
_ho_mop_cost(c3_c *buf_c, u2_noun dac)
{
  u2_noun nid = u2_h(dac);
  u2_noun pop = u2_h(nid);
  u2_noun mek = u2_t(nid);

  if ( u2_nul == pop ) {
    return _ho_mop_mark(buf_c, mek);
  }
  else {
    c3_w pal_w = _ho_mop_cost(buf_c, pop);

    if ( buf_c ) {
      buf_c += pal_w;
      *buf_c++ = '_';
      *buf_c++ = '_';
    }
    return (pal_w + 2 + _ho_mop_mark(buf_c, mek));
  }
}

/* u2_ho_boot(): 
**
**   Boot driver system.  Note that all discs and
**   tools are considered permanent between reboots.
*/
void
u2_ho_boot()
{
  _ho_cash_init(&JetHangar.jac_s);
  _ho_cash_init(&JetHangar.bad_s);

  {
    c3_w i_w, j_w;

    for ( i_w=0; JetBase[i_w].cos_c; i_w++ ) {
      JetBase[i_w].dac = u2_none;

      for ( j_w=0; JetBase[i_w].fan_j[j_w].cos_c; j_w++ ) {
        JetBase[i_w].fan_j[j_w].dac = u2_none;
        JetBase[i_w].fan_j[j_w].fol = u2_none;
      }
    }
  }
}

/* u2_ho_reset(): 
**
**   Reboot driver system.  Note that all discs and
**   tools are considered permanent between reboots.
*/
void
u2_ho_reset()
{
  _ho_cash_free(&JetHangar.jac_s);
  _ho_cash_free(&JetHangar.bad_s);

  _ho_cash_init(&JetHangar.jac_s);
  _ho_cash_init(&JetHangar.bad_s);
}

/* _ho_execute(): execute jet.
*/
static u2_weak
_ho_execute(u2_ray      wir_r,
            u2_ho_jet*  jet_j,
            u2_noun     cor)
{
  u2_ray cap_r = u2_rail_cap_r(wir_r);

  if ( 0 == jet_j->fun_f ) {
    return u2_none;
  }
  else if ( u2_no == u2_rl_leap(wir_r, c3__warm) ) {
    return u2_none;
  }
  else {
    u2_ray  jub_r = u2_wire_jub_r(wir_r);
    void*   env_j;
    u2_noun pro;
   
    u2_wire_jub_r(wir_r) = u2_rl_ralloc(wir_r, c3_wiseof(jmp_buf));
    env_j = u2_at_cord(u2_wire_jub_r(wir_r), c3_wiseof(jmp_buf));

    if ( 1 == setjmp(env_j) ) {
      u2_rl_fall(wir_r);
      u2_wire_jub_r(wir_r) = jub_r;

      u2_rail_cap_r(wir_r) = cap_r;
      return u2_none;
    } else {
      pro = jet_j->fun_f(wir_r, cor);

      u2_rl_fall(wir_r);
      u2_wire_jub_r(wir_r) = jub_r;

      pro = u2_rl_ice(wir_r, pro);
      u2_rail_cap_r(wir_r) = cap_r;
      return pro;
    }
  }
}

/* _ho_select(): find jet from driver, cor and fol, caching.
*/
static u2_ho_jet*
_ho_select(u2_ray        wir_r,
           u2_ho_driver* dry_d,
           u2_noun       fol,
           u2_noun       cor)
{
  u2_ho_jet*  jet_j;
  c3_w        i_w;

  for ( i_w = 0; dry_d->fan_j[i_w].cos_c; i_w++ ) {
    jet_j = &dry_d->fan_j[i_w];

    if ( u2_none == jet_j->dac ) {
      jet_j->dac = dry_d->dac;
    }
    if ( u2_none == jet_j->fol ) {
      c3_w    axe_w;
      u2_atom axe;

      if ( *jet_j->cos_c == '@' ) {
        sscanf(jet_j->cos_c+1, "%u", &axe_w);
        c3_assert(!(0x80000000 & axe_w));
      }
      else {
        c3_assert(0);   // hooks not yet supported
        // axe = u2_be_hook(dry_d->dac, jet_j->cos_c);
      }
      jet_j->fol = u2_frag(axe, cor);
      c3_assert(u2_none != jet_j->fol);
    }
    if ( u2_yes == u2_sing(fol, jet_j->fol) ) {
      printf("jet: found %s\n", jet_j->cos_c);

      _ho_cash_save(&JetHangar.jac_s, jet_j->fol, jet_j);
      return jet_j;
    }
  }
  printf("jet: not in driver\n");

  /* Jet not found.  Create a dummy, to avoid slow search.
  **
  ** XX: leaks on jet reboot.
  */
  {
    if ( !(jet_j = malloc(sizeof(u2_ho_jet))) ) {
      abort();
    }

    jet_j->dac = dry_d->dac;
    jet_j->fol = fol;
    jet_j->fun_f = 0;

    _ho_cash_save(&JetHangar.jac_s, fol, jet_j);
    return jet_j;
  }
}

/* _ho_explore(): find driver from disc, caching.
*/
static u2_ho_driver*
_ho_explore(u2_ray  wir_r,
            u2_noun dac)
{
  u2_ho_driver* dry_d;

  if ( 0 != (dry_d = _ho_cash_find(&JetHangar.bad_s, dac)) ) {
    return dry_d;
  } else {
    c3_c* cos_c; 
    c3_w  len_w;
    c3_w  i_w;

    len_w = _ho_mop_cost(0, dac);
    if ( !(cos_c = malloc(len_w + 1)) ) abort();
    _ho_mop_cost(cos_c, dac);
    cos_c[len_w] = 0;

    printf("explore: jet: control: %s\n", cos_c);

    for ( i_w=0; JetBase[i_w].cos_c; i_w++ ) {
      if ( (u2_none == JetBase[i_w].dac) &&
           !strcmp(cos_c, JetBase[i_w].cos_c) ) 
      {
        dry_d = &JetBase[i_w];

        dry_d->dac = dac;
        free(cos_c);

        _ho_cash_save(&JetHangar.bad_s, dac, dry_d);
        return dry_d;
      }
    }

    /* Driver not found.  Let's create a dummy, for speed.
    **
    ** XX: leaks on jet reboot.  
    */
    {
      if ( !(dry_d = malloc(sizeof(u2_ho_driver))) ) {
        abort();
      }

      dry_d->cos_c = cos_c;
      dry_d->dac = dac;
      dry_d->fan_j[0].cos_c = 0;

      _ho_cash_save(&JetHangar.bad_s, dac, dry_d);
      return dry_d;
    }
  }
}

/* _ho_discover(): find jet from dac and fol, caching.
*/
static u2_ho_jet*
_ho_discover(u2_ray  wir_r,
             u2_noun dac,
             u2_noun fol,
             u2_noun cor)
{
  u2_ho_jet*    jet_j;
  u2_ho_driver* dry_d;

  if ( (0 != (jet_j = _ho_cash_find(&JetHangar.jac_s, fol)) ) ) {
    return jet_j;
  }
  else {
    if ( 0 != (dry_d = _ho_explore(wir_r, dac)) ) {
      return _ho_select(wir_r, dry_d, fol, cor);
    }
    else return 0;
  }
}

/* u2_ho_fire(): 
**
**   Drive in disc to formula.  Core is valid.
**
**   If *ver_t is 1, caller must check result.
*/
u2_weak
u2_ho_fire(u2_ray  wir_r,
           u2_noun dac,
           u2_noun cor,
           u2_noun fol,
           c3_t*   ver_t)
{
  u2_ho_jet *jet_j;

  if ( 0 == (jet_j = _ho_discover(wir_r, dac, fol, cor)) ) {
    return u2_none;
  }
  else {
    *ver_t = !jet_j->ace_t;

    return _ho_execute(wir_r, jet_j, cor);
  }
}

/* u2_ho_dive():
**
**   Report compatibility failure in `dac`.  May not return.
*/
void
u2_ho_dive(u2_ray  wir_r,
           u2_noun dac)
{
  printf("ho: dive!\n");
  c3_assert(0);
}
