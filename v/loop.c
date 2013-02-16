/* v/loop.c
**
** This file is in the public domain.
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <setjmp.h>
#include <gmp.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ev.h>
#include <errno.h>
#include <curses.h>
#include <termios.h>
#include <term.h>

#include <libtecla.h>

#include "all.h"
#include "v/vere.h"

/* _lo_init(): initialize I/O across the process.
*/
static void
_lo_init(u2_reck* rec_u)
{
  u2_term_io_init(rec_u);
  u2_http_io_init(rec_u);
}

/* _lo_exit(): terminate I/O across the process.
*/
static void
_lo_exit(u2_reck* rec_u)
{
  u2_term_io_exit(rec_u);
  u2_http_io_exit(rec_u);
}

/* _lo_stop(): stop event I/O across the process.
*/
static void
_lo_stop(u2_reck*        rec_u,
         struct ev_loop* lup_u)
{
  u2_http_io_stop(rec_u, lup_u);
  u2_term_io_stop(rec_u, lup_u);
}

/* _lo_poll(): reset event flags across the process.
*/
static void
_lo_poll(u2_reck*        rec_u,
         struct ev_loop* lup_u)
{
  u2_http_io_poll(rec_u, lup_u);
  u2_term_io_poll(rec_u, lup_u);
}

/* _lo_spin(): restart event I/O across the process.
*/
static void
_lo_spin(u2_reck*        rec_u,
         struct ev_loop* lup_u)
{
  u2_http_io_spin(rec_u, lup_u);
  u2_term_io_spin(rec_u, lup_u);
}

/* _lo_how(): print how.
*/
static const c3_c* 
_lo_how(u2_noun how)
{
  switch ( how ) {
    default: c3_assert(0); break;

    case c3__term: return "cons";
    case c3__htcn: return "http-conn";
    case c3__htls: return "http-lisn";
  }
}

/* _lo_suck(): process input on a socket.
*/
static void
_lo_suck(u2_reck*      rec_u,
         struct ev_io* wax_u,
         u2_noun       how)
{
  switch ( how ) {
    default: c3_assert(0); break;

    case c3__term: u2_term_io_suck(rec_u, wax_u); break;
    case c3__htcn: u2_http_io_suck_conn(rec_u, wax_u); break;
    case c3__htls: u2_http_io_suck_lisn(rec_u, wax_u); break;
  }
}

/* _lo_fuck(): process output on a socket.
*/
static void
_lo_fuck(u2_reck*      rec_u,
         struct ev_io* wax_u,
         u2_noun       how)
{
  switch ( how ) {
    default: c3_assert(0); break;

    case c3__term: u2_term_io_fuck(rec_u, wax_u); break;
    case c3__htcn: u2_http_io_fuck_conn(rec_u, wax_u); break;
    case c3__htls: c3_assert(0); break;
  }
}

/* u2_lo_bail(): clean up all event state.
*/
void
u2_lo_bail(u2_reck* rec_u)
{
  fflush(stdout);
  _lo_exit(rec_u);

  exit(1);
}

/* _lo_tape(): dump a tape, old style.  Don't do this.
*/
static void
_lo_tape(u2_reck* rec_u, FILE* fil_u, u2_noun tep)
{
  u2_noun tap = tep;

  while ( u2_nul != tap ) {
    c3_c car_c;

    if ( u2h(tap) >= 127 ) {
      car_c = '?';
    } else car_c = u2h(tap);

    putc(car_c, fil_u);
    tap = u2t(tap);
  }
  u2z(tep);
}

/* _lo_wall(): dump a wall, old style.  Don't do this.
*/
static void
_lo_wall(u2_reck* rec_u, u2_noun wol)
{
  FILE* fil_u = u2_term_io_hija();
  u2_noun wal = wol;

  while ( u2_nul != wal ) {
    _lo_tape(rec_u, fil_u, u2k(u2h(wal)));

    putc(13, fil_u);
    putc(10, fil_u);

    wal = u2t(wal);
  }
  u2_term_io_loja(0);
  u2z(wol);
}

/* _lo_punt(): dump tank list.  A last resort, hopefully soon abolished.
*/
static void
_lo_punt(u2_reck* rec_u, c3_l tab_l, u2_noun tac)
{
  c3_l    col_l = u2_ve_dump_columns();
  u2_noun cat   = tac;

  //  We are calling nock here, but hopefully need no protection.
  //
  while ( u2_yes == u2_cr_du(cat) ) {
    u2_noun wol = u2_cn_mung(u2k(rec_u->toy.wash), 
                             u2nc(u2nc(tab_l, col_l), u2k(u2h(cat))));
    _lo_wall(rec_u, wol);
    cat = u2t(cat);
  }
  u2z(tac);
}

/* _lo_soft(): standard soft wrapper.  
**
**  Produces [%% result] or [%error (list tank)].
*/
static u2_noun
_lo_soft(u2_reck* rec_u, u2_funk fun_f, u2_noun arg)
{
  u2_noun hoe, pro, rop;

  // u2_cm_trip();
  if ( 0 != (hoe = u2_cm_trap()) ) {
    u2_noun mok;

    u2_cm_purge();
    u2_ve_grab(hoe, arg, 0);

    mok = u2_cn_mung(u2k(rec_u->toy.mook), u2nc(2, u2_ckb_flop(u2k(u2t(hoe)))));
    rop = u2nc(u2k(u2h(hoe)), u2k(u2t(mok)));

    u2z(hoe);
    u2z(mok);
  } 
  else {
    u2_noun pro = fun_f(rec_u, arg);
    u2_cm_done();
  
    u2_cm_purge();
    rop = u2nc(u2_blip, pro);
  }
  pro = rop;
  // u2_cm_chin();
  // pro = u2_cm_keep(rop);
  // u2_cm_pack();

  return pro;
}

/* _lo_hard(): standard hard wrapper.  Produces result and/or asserts.
*/
static u2_noun
_lo_hard(u2_reck* rec_u, u2_funk fun_f, u2_noun arg)
{
  u2_noun pro = _lo_soft(rec_u, fun_f, arg);

  if ( u2_blip == u2h(pro) ) {
    u2_noun poo = u2k(u2t(pro));

    u2z(pro); return poo;
  } 
  else {
    _lo_punt(rec_u, 2, u2k(u2t(pro)));
    u2z(pro);
    c3_assert(0);
  }
}

/* _lo_mung(): formula wrapper with gate and sample.
*/
  static u2_noun
  _lo_mung_in(u2_reck* rec_u, u2_noun gam)
  {
    u2_noun pro = u2_cn_mung(u2k(u2h(gam)), u2k(u2t(gam)));

    u2z(gam); return pro;
  }
static u2_noun
_lo_mung(u2_reck* rec_u, u2_noun gat, u2_noun sam)
{
  u2_noun gam = u2nc(gat, sam);

  return _lo_hard(rec_u, _lo_mung_in, gam);
}

/* _lo_save(): log an ovum at the present time.  sync; sync; sync.
*/
static void
_lo_save(u2_reck* rec_u, u2_noun ovo)
{
}

/* _lo_sing(): replay ovum from the past, time already set.
*/
static void
_lo_sing(u2_reck* rec_u, u2_noun ovo)
{
  u2_noun gon = _lo_soft(rec_u, u2_reck_poke, u2k(ovo));

  if ( u2_blip != u2h(gon) ) {
    uL(fprintf(uH, "sing: ovum failed!\n"));
    _lo_punt(rec_u, 2, u2k(u2t(gon)));
    c3_assert(0);
  }
  else {
    //  Discard effects and continue result.
    //
    u2_noun gax = u2t(gon);
  
    u2z(rec_u->roc);
    rec_u->roc = u2k(u2t(gax));
  }
  u2z(gon);
}

/* _lo_punk(): insert and apply an input ovum (unprotected).
*/
static void
_lo_punk(u2_reck* rec_u, u2_noun ovo)
{
  u2_noun gon = _lo_soft(rec_u, u2_reck_poke, u2k(ovo));

  if ( u2_blip != u2h(gon) ) {
    u2_noun bov = u2nc(u2k(u2h(ovo)), u2nc(c3__crud, u2k(u2t(gon))));

    u2z(ovo); ovo = bov;
    u2z(gon); gon = _lo_soft(rec_u, u2_reck_poke, u2k(ovo));

    if ( u2_blip != u2h(gon) ) {
      u2_noun bov = u2nc(u2k(u2h(ovo)), 
                         u2nc(c3__warn, u2_ci_tape("crude crash!")));

      u2z(ovo); ovo = bov;
      u2z(gon); gon = _lo_soft(rec_u, u2_reck_poke, u2k(ovo));

      if ( u2_blip != u2h(gon) ) {
        uL(fprintf(uH, "crude: all efforts failed!\n"));

        u2z(gon); u2z(ovo);
        return;
      }
    }
  }

  //  Whatever worked, apply the effects and then save it.
  {
    u2_noun gax = u2t(gon);
  
    u2z(rec_u->roc);
    rec_u->roc = u2k(u2t(gax));

    {
      u2_noun hux = u2h(gax);

      while ( u2_nul != hux ) {
        u2_reck_kick(rec_u, u2k(u2h(hux)));
        hux = u2t(hux);
      }
    }

    _lo_save(rec_u, u2k(ovo));
  }
  u2z(ovo);
  u2z(gon);
}

/* _lo_work(): work in rec_u.
*/
static void
_lo_work(u2_reck* rec_u)
{
  while ( rec_u->ova.egg_u ) {
    u2_cart* egg_u = rec_u->ova.egg_u;
    u2_noun  egg = egg_u->egg;

    rec_u->ova.egg_u = egg_u->nex_u;
    if ( 0 == rec_u->ova.egg_u ) {
      c3_assert(egg_u == rec_u->ova.geg_u);
      rec_u->ova.geg_u = 0;
    }
    free(egg_u);

    _lo_punk(rec_u, egg);
  }
}

/* u2_lo_call(): central callback.
*/
void
u2_lo_call(u2_reck*        rec_u,
           struct ev_loop* lup_u,
           struct ev_io*   wax_u,
           u2_noun         how,
           c3_i            revents)
{
  u2_bean inn = (revents & EV_READ) ? u2_yes : u2_no;
  u2_bean out = (revents & EV_WRITE) ? u2_yes : u2_no;

  _lo_stop(rec_u, lup_u);

#if 0
  {
    uL(fprintf(uH, "call %s inn %s out %s\n", 
                      _lo_how(how), 
                      (inn == u2_yes) ? "yes" : "no", 
                      (out == u2_yes) ? "yes" : "no"));
  }
#endif

  {
    //  update time
    //
    u2_reck_time(rec_u);

    //  process input on this socket
    //
    if ( u2_yes == inn ){
      _lo_suck(rec_u, wax_u, how);
    }

    //  process output on this socket
    //
    if ( u2_yes == out ) {
      _lo_fuck(rec_u, wax_u, how);
    }

    //  process actions
    //
    _lo_work(rec_u);
  }
  _lo_poll(rec_u, lup_u);
  _lo_spin(rec_u, lup_u);
}

/* _lo_make(): post initial ova.  XX, add command-line arguments.
*/
static void
_lo_make(u2_reck* rec_u)
{
  u2_noun pax = u2nc(c3__gold, u2nq(c3__term, u2k(rec_u->sen), '1', u2_nul));

  u2_reck_plan
    (rec_u, pax, 
            u2nt(c3__boot, 
                 u2nq(c3__make, c3__zuse, 256, 0),
                 u2nq(u2nc(c3__blew, u2_term_ef_blew(rec_u, 1)), 
                      u2nc(c3__hail, u2_nul),
                      u2nc(c3__helo, u2_nul),
                      u2_nul)));
}

/* _lo_boot(): configure after install.
*/
static void
_lo_boot(u2_reck* rec_u)
{
  u2_noun pax = u2nq(c3__gold, c3__http, u2k(rec_u->sen), u2_nul);

  c3_assert(u2_nul != rec_u->own);

  u2_reck_plan
    (rec_u, pax, u2nt(c3__bind, u2k(u2h(rec_u->own)), u2nc(u2_yes, u2_nul)));

  u2_reck_sync(rec_u);
}

/* u2_lo_loop(): enter main event loop.
*/
void
u2_lo_loop(u2_reck* rec_u)
{
  _lo_init(rec_u);

  // uL(fprintf(uH, "loop: about to make\n"));
  _lo_make(rec_u);

  // uL(fprintf(uH, "loop: about to work\n"));
  _lo_work(rec_u);

  // uL(fprintf(uH, "loop: about to boot\n"));
  _lo_boot(rec_u);

  {
    struct ev_loop *lup_u = ev_default_loop(0);

    _lo_poll(rec_u, lup_u);
    _lo_spin(rec_u, lup_u);

    ev_loop(lup_u, 0);

    _lo_exit(rec_u);
  }
}
