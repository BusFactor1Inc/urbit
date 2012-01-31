/* f/coal.c
**
** This file is in the public domain.
*/
#include "all.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#include "../gen222/pit.h"

  /**  Jet dependencies.  Minimize these.
  **/
#   define Pt5Y   k_222__a__b__c__d__e

  /**  Jet dependencies.  Minimize these.
  **/
#   define Pt3Y   k_222__a__b__c
#   define Pt4Y   k_222__a__b__c__d
#   define Pt5Y   k_222__a__b__c__d__e

    u2_noun j2_mbc(Pt3Y, gor)(u2_wire, u2_noun a, u2_noun b);
    u2_noun j2_mcc(Pt4Y, by, get)(u2_wire, u2_noun a, u2_noun b);
    u2_noun j2_mcc(Pt4Y, by, put)(u2_wire, u2_noun a, u2_noun b, u2_noun c);
    u2_noun j2_mby(Pt5Y, jam)(u2_wire, u2_noun a);

#   define _coal_jam  j2_mby(Pt5Y, jam)

#   define _coal_gor  j2_mbc(Pt3Y, gor)
#   define _coal_get  j2_mcc(Pt4Y, by, get)
#   define _coal_put  j2_mcc(Pt4Y, by, put)




/* u2_cf_path(): assemble local path with noun thap and ext.
*/
  /* _cf_path_1: write at/inpath.
  */
  static c3_w
  _cf_path_1(c3_c*   buf_c,
             c3_w    pos_w,
             u2_noun hut)                                         //  retain
  {
    if ( u2_no == u2_cr_du(hut) ) {
      c3_w met_w = u2_cr_met(3, hut);

      if ( buf_c ) u2_cr_bytes(0, met_w, (c3_y*)(buf_c + pos_w), hut);
      return (pos_w + met_w);
    } 
    else {
      c3_w met_w = u2_cr_met(3, u2h(hut));
      c3_w end_w = _cf_path_1(buf_c, pos_w, u2t(hut));

      if ( buf_c ) buf_c[end_w] = '/';
      end_w++;

      if ( buf_c ) u2_cr_bytes(0, met_w, (c3_y*)(buf_c + end_w), u2h(hut));
      end_w += met_w;

      return end_w;
    }
  }

u2_noun
u2_cf_path(c3_c* top_c, 
           c3_c* ext_c, 
           u2_noun tah)
{
  c3_w    top_w = strlen(top_c);
  c3_w    len_w = _cf_path_1(0, (top_w + 1), tah);
  c3_c*   buf_c = malloc(len_w + 1 + strlen(ext_c) + 1);
  c3_w    pos_w;
  u2_noun pas;

  strcpy(buf_c, top_c);
  pos_w = top_w;
  buf_c[pos_w++] = '/';

  pos_w = _cf_path_1(buf_c, pos_w, tah);
  buf_c[pos_w++] = '.'; 
  strcpy(buf_c + pos_w, ext_c);

  pas = u2_ci_string(buf_c);
  free(buf_c);

  u2_cz(tah);
  return pas;
}
  
/* u2_cf_flat_date(): date for `pas`.  Unix time * 10^6, or 0.
*/
c3_d
u2_cf_flat_date(u2_noun pas)
{
  c3_c*       pas_c = u2_cr_string(pas);
  struct stat pas_s;

  u2_cz(pas);
  if ( stat(pas_c, &pas_s) < 0 ) {
    free(pas_c);

    return 0;
  } else {
    free(pas_c);

    return ( ((c3_d)pas_s.st_mtimespec.tv_sec) +
             ((c3_d)(pas_s.st_mtimespec.tv_nsec / 1000)) );
  }
}

/* u2_cf_flat_load(): load `mod` at `pas`.  Bail on error.
*/
u2_weak
u2_cf_flat_load(u2_noun mod,
                u2_noun pas)
{
  c3_assert(c3__atom == mod);
  {
    c3_c*       pas_c = u2_cr_string(pas);
    c3_i        fid_i;
    struct stat sat_s;
    c3_w        fln_w;
    c3_c*       fil_c;
    u2_atom     fil;

    fid_i = open(pas_c, O_RDONLY, 0644);
    free(pas_c);
    u2_cz(pas);

    if ( (fid_i < 0) || (fstat(fid_i, &sat_s) < 0) ) {
      perror(pas_c);
      return u2_none;
    }

    fln_w = sat_s.st_size;
    fil_c = malloc(sat_s.st_size);

    if ( fln_w != read(fid_i, fil_c, fln_w) ) {
      return u2_none;
    }
    close(fid_i);

    fil = u2_ci_bytes(fln_w, (c3_y *)fil_c); 
    free(fil_c);

    return fil;
  }
}

/* u2_cf_flat_save(): save `som` as `mod` at `pas`. 
*/
u2_flag
u2_cf_flat_save(u2_noun mod, 
                u2_noun pas,
                u2_noun som)
{
  c3_assert(c3__atom == mod);
  {
    c3_c*       pas_c = u2_cr_string(pas);
    c3_i    fid_i;
    c3_w    fln_w;
    c3_y*   fil_y;

    fid_i = open(pas_c, O_WRONLY | O_CREAT, 0666);
    free(pas_c);
    u2_cz(pas);

    if ( fid_i < 0 ) {
      perror(pas_c);
      u2_cz(som);
      return u2_no;
    }

    fln_w = u2_met(3, som);
    fil_y = malloc(fln_w);
    u2_cr_bytes(0, fln_w, fil_y, som);
    u2_cz(som);
 
    if ( fln_w != write(fid_i, fil_y, fln_w) ) {
      return u2_no;
    }
    close(fid_i);

    return u2_yes;
  }
}

/* u2_cn_mong():
**
**   Call `(function sample)`.
*/
u2_noun
u2_cn_mong(u2_noun fun,
           u2_noun sam)
{
  u2_noun pro = u2_bn_mong(u2_Wire, fun, sam);

  u2_cz(fun);
  return pro;
}

/* u2_ci_string():
**
**   u2_ci_bytes(strlen(a_c), (c3_y *)a_c);
*/
u2_atom
u2_ci_string(const c3_c* a_c)
{
  return u2_bn_string(u2_Wire, a_c);
}
 
/* u2_cr_string(): `a` as malloced C string.
*/
c3_c* 
u2_cr_string(u2_atom a)
{
  c3_w  met_w = u2_cr_met(3, a);
  c3_c* str_c = malloc(met_w + 1);

  u2_cr_bytes(0, met_w, (c3_y*)str_c, a);
  str_c[met_w] = 0;
  return str_c;
}

/* u2_ci_bytes():
**
**   Construct `a` bytes from `b`, LSB first, as an atom.
*/
u2_atom
u2_ci_bytes(c3_w        a_w,
            const c3_y* b_y)
{
  return u2_bn_bytes(u2_Wire, a_w, b_y);
}

/* u2_cm_trip(): descend into a memory region.
**
**   Memory allocated in the heap above is senior & frozen.
*/
void
u2_cm_trip()
{
#if 0
  if ( u2_no == u2_rl_leap(u2_Wire, c3__rock) ) {
    u2_cm_bail(c3__fail);
  }
#endif
}

/* u2_cm_chin(): ascend out of a memory region.
**
**   Memory allocated in the heap below is junior & volatile.
*/
void
u2_cm_chin()
{
#if 0
  u2_rl_fall(u2_Wire);
#endif
}

/* u2_cm_bury(): store fresh or volatile noun `som` to freezer.
*/
u2_weak
u2_cm_bury(u2_weak som)
{
  if ( u2_none == som ) {
    return u2_none;
  } else {
    u2_noun pro = u2_rl_take(u2_wire_bas_r(u2_Wire), som);

    u2_cz(som);
    return pro;
  }
}

/* u2_cm_wind(): enter new opaque bail context, returning old (or 0).
**
**   usage:  
**        c3_w qop_w = u2_cm_wind();
**  
**        if ( 0 != u2_cm_trap() ) {
**          u2_cm_done(qop_w);
**          [... exception ...]
**        }
**        else {
**          [... code as normal ...]
**          u2_cm_done(qop_w);
**        }
*/
c3_w
u2_cm_wind()
{
  return u2_bl_open(u2_Wire);
}

/* u2_cm_done(): terminate and restore old opaque bail context.
*/
void
u2_cm_done(c3_w qop_w)
{
  u2_bl_done(u2_Wire, qop_w);
}

/* u2_cm_poll(): poll for interrupts, etc.
*/
void
u2_cm_poll()
{
  if ( LoomStop ) {
    LoomStop = 0;
    if ( LoomIntr ) {
      LoomIntr = 0;

      fprintf(stderr, "{poll: interrupt}\n");
      u2_cm_bail(c3__intr);
    } else {
      fprintf(stderr, "{poll: stack overflow}\n");
      u2_cm_bail(c3__wild);
    }
  }
}
 
/* u2_cm_sweep(): return bytes leaked; match bytes saved.
*/
c3_w
u2_cm_sweep(c3_w sav_w)
{
  return u2_rl_gc_sweep(u2_Wire, sav_w);
}

/* u2_cm_purge(): purge memo cache.
*/
void
u2_cm_purge()
{
  u2_rl_drain(u2_Wire);
}

/* u2_cm_mark_noun(): mark individual noun.
*/
c3_w
u2_cm_mark_noun(u2_noun som)
{
  return u2_rl_gc_mark_noun(u2_Wire, som);
}

/* u2_cm_mark_ray(): mark a root for gc (do not use again before gc)
*/
c3_w
u2_cm_mark_ray(u2_ray ray_r)
{
  return u2_rl_gc_mark_ptr(u2_Wire, ray_r);
}

/* u2_cm_mark_internal(): mark all coal internals
*/
c3_w
u2_cm_mark_internal()
{
  return u2_wr_mark(u2_Wire);
}
 
/* u2_cm_trac(): extract and clear stack trace.
*/
u2_noun
u2_cm_trac()
{
  u2_noun tax = u2_wire_tax(u2_Wire);

  u2_wire_tax(u2_Wire) = u2_nul;
  return tax;
}

/* u2_cm_push(): push `mon` on trace stack.
*/
void
u2_cm_push(u2_noun mon)
{
  u2_wire_tax(u2_Wire) = u2nc(mon, u2_wire_tax(u2_Wire));
}

/* u2_cm_bean(): push `[%bean roc]` on trace stack.
*/
void
u2_cm_bean(u2_noun roc)
{
  u2_cm_push(u2nc(c3__bean, roc));
}

/* u2_cm_drop(): drop from meaning stack.
*/
void
u2_cm_drop()
{
  u2_noun tax = u2_wire_tax(u2_Wire);

  c3_assert(u2_nul != tax);
  u2_wire_tax(u2_Wire) = u2_ct(u2t(tax));
  u2_cz(tax);
}

/* u2_cm_bail(): bail out to the local trap.  Does not return.
*/
extern u2_noun u2_Flag_Abort;
u2_noun
u2_cm_bail(c3_l    how_l)
{
  u2_ray kit_r = u2_wire_kit_r(u2_Wire);

  if ( u2_yes == u2_Flag_Abort ) {
    if ( c3__fail == how_l ) {
      c3_assert(0);
    }
  }
  u2_tx_sys_bit(u2_Wire, u2_yes);
  _longjmp((void *)u2_at_cord(u2_kite_buf_r(kit_r), c3_wiseof(jmp_buf)), how_l);
  return u2_none;
}

/* u2_cm_foul():
*/
u2_noun
u2_cm_foul(const c3_c* err_c)
{
  u2_cm_bean(u2_ci_string(err_c));
  fprintf(stderr, "foul: %s\n", err_c);

  return u2_bl_error(u2_Wire, err_c); 
}

/* u2_cn_cell(): produce the cell `[a b]`.
*/
u2_noun
u2_cn_cell(u2_noun a,
           u2_noun b)
{
  return u2_bn_cell(u2_Wire, a, b);
}

/* u2_cn_trel(): produce the cell `[a b c]`.
*/
u2_noun
u2_cn_trel(u2_noun a,
           u2_noun b,
           u2_noun c)
{
  return u2_bn_trel(u2_Wire, a, b, c);
}

/* u2_cn_qual(): produce the cell `[a b c d]`.
*/
u2_noun
u2_cn_qual(u2_noun a,
           u2_noun b,
           u2_noun c,
           u2_noun d)
{
  return u2_bn_qual(u2_Wire, a, b, c, d);
}

/* u2_ckb_flop(): reverse list `a`.
*/
u2_noun
u2_ckb_flop(u2_noun a)
{
  u2_noun b = j2_mbc(Pt2, flop)(u2_Wire, a);

  u2_cz(a);
  return b;
}

/* u2_ckd_by_get(): map get for key `b` in map `a` with u2_none.
*/
u2_weak
u2_ckd_by_get(u2_noun a, u2_noun b)
{
  u2_noun c = _coal_get(u2_Wire, a, b);

  u2_cz(a); u2_cz(b);
  if ( u2_no == u2_cr_du(c) ) {
    u2_cz(c); 
    return u2_none;
  } else {
    u2_noun pro = u2_ct(u2t(c));

    u2_cz(c);
    return pro;
  }
}

/* u2_ckd_by_got(): map get for key `b` in map `a` with fail.
*/
u2_noun
u2_ckd_by_got(u2_noun a, u2_noun b)
{
  u2_weak c = u2_ckd_by_get(a, b);

  if ( u2_none == c ) {
    return u2_cm_bail(c3__exit);
  } 
  else return c;
}

/* u2_ckd_by_put(): map put for key `b`, value `c` in map `a`.
*/
u2_weak
u2_ckd_by_put(u2_noun a, u2_noun b, u2_noun c)
{
  // Bizarre asymmetry in old jets.
  //
  u2_noun pro = _coal_put(u2_Wire, a, b, c);

  u2_cz(a); u2_cz(b); u2_cz(c);
  return pro;
}

/* u2_cke_cue(): expand saved pill.
*/
  static u2_noun                                                  //  produce
  _cue_in(u2_wire wir_r,
          u2_atom a,                                              //  retain
          u2_atom b,                                              //  retain
          u2_ray  t_r)                                            //  retain
  {
    u2_noun p, q;

    if ( _0 == j2_mbc(Pt3, cut)(wir_r, 0, b, 1, a) ) {
      u2_noun x = j2_mbc(Pt1, inc)(wir_r, b);
      u2_noun c = j2_mby(Pt5, rub)(wir_r, x, a);

      p = j2_mbc(Pt1, inc)(wir_r, u2_h(c));
      q = u2_rx(wir_r, u2_t(c));
      q = u2_cs_save(wir_r, t_r, 0, b, q);

      u2_rz(wir_r, c);
      u2_rz(wir_r, x);
    }
    else {
      u2_noun c = j2_mbc(Pt1, add)(wir_r, _2, b);
      u2_noun l = j2_mbc(Pt1, inc)(wir_r, b);

      if ( _0 == j2_mbc(Pt3, cut)(wir_r, 0, l, 1, a) ) {
        u2_noun u, v, w;
        u2_noun x, y;

        u = _cue_in(wir_r, a, c, t_r);
        x = j2_mbc(Pt1, add)(wir_r, u2_h(u), c);
        v = _cue_in(wir_r, a, x, t_r);

        w = u2_bc(wir_r, u2_rx(wir_r, u2_t(u)),
                         u2_rx(wir_r, u2_t(v)));

        y = j2_mbc(Pt1, add)(wir_r, u2_h(u), u2_h(v));

        p = j2_mbc(Pt1, add)(wir_r, _2, y);
        q = u2_cs_save(wir_r, t_r, 0, b, w);

        u2_rz(wir_r, u); u2_rz(wir_r, v); u2_rz(wir_r, x); u2_rz(wir_r, y);
      }
      else {
        u2_noun d = j2_mby(Pt5, rub)(wir_r, c, a);
        u2_weak x = u2_cs_find(wir_r, t_r, 0, u2_t(d));

        p = j2_mbc(Pt1, add)(wir_r, _2, u2_h(d));

        if ( u2_none == x ) {
          return u2_bl_bail(wir_r, c3__fail);
        }
        q = u2_rx(wir_r, x);

        u2_rz(wir_r, d);
      }
      u2_rz(wir_r, l);
      u2_rz(wir_r, c);
    }
    return u2_bc(wir_r, p, q);
  }

  u2_noun                                                         //  transfer
  _cue_internal(u2_wire wir_r, 
                u2_atom a)                                        //  retain
  {
    u2_ray  t_r = u2_cs_make(wir_r);
    u2_noun x   = _cue_in(wir_r, a, _0, t_r);
    u2_noun y   = u2_rx(wir_r, u2_t(x));

    u2_rz(wir_r, x);
    u2_cs_free(wir_r, t_r);

    return y;
  }

u2_noun
u2_cke_cue(u2_atom a)
{
  u2_noun b = _cue_internal(u2_Wire, a);

  u2_cz(a);
  return b;
}

/* u2_cke_jam(): pack noun as atom.
*/
u2_atom
u2_cke_jam(u2_noun a)
{
  u2_atom b = _coal_jam(u2_Wire, a);

  u2_cz(a);
  return b;
}
