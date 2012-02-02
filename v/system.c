/* v/system.c
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

#include "all.h"
#include "v/vere.h"

/* u2_ve_tag: simple string from stage number.
*/
u2_noun
u2_ve_tag(c3_w a_w)
{
  c3_c a_c[] = {0, 0, 0, 0};

  sprintf(a_c, "%d", a_w);
  return u2_ci_string(a_c);
}

/* u2_ve_bone(): direct execution from kernel, using ":!%".
*/
u2_noun
u2_ve_bone(c3_c *bon_c)
{
  c3_w    kno_w = u2_Host.kno_w;

  if ( 0 == u2_Host.ver_e[kno_w].ken ) {
    return u2_cm_foul("bone");
  } else {
    u2_noun ken = u2_ct(u2_Host.ver_e[kno_w].ken);
    u2_noun src, fol, cor;

    //  Obviously heavily syntax dependent.
    //  May vary in future by kernel number.
    {
      c3_c *src_c = alloca(strlen(bon_c) + 4);

      strcpy(src_c, bon_c);
      strcat(src_c, ":!%");

      src = u2_ci_string(src_c);
    }
    fol = u2_cn_nock(src, ken);
    cor = u2_cn_nock(0, fol);

    return cor;
  }
}

/* u2_ve_seed(): return kernel seed.
*/
u2_noun
u2_ve_seed()
{
  c3_assert(0 != u2_ve_at()->toy.seed);

  return u2_ct(u2_ve_at()->toy.seed);
}

/* u2_ve_slap(): use slap gate. 
*/
u2_noun
u2_ve_slap(u2_noun vax, u2_noun gen)
{
  c3_assert(0 != u2_ve_at()->toy.slap);

  return u2_cn_mong(u2_ct(u2_ve_at()->toy.slap), u2nc(vax, gen));
}

/* u2_ve_slam(): use slam gate. 
*/
u2_noun
u2_ve_slam(u2_noun gat, u2_noun sam)
{
  c3_assert(0 != u2_ve_at()->toy.slam);

  return u2_cn_mong(u2_ct(u2_ve_at()->toy.slam), u2nc(gat, sam));
}

/* u2_ve_slop(): use slop gate. 
*/
u2_noun
u2_ve_slop(u2_noun hed, u2_noun tal)
{
  c3_assert(0 != u2_ve_at()->toy.slop);

  return u2_cn_mong(u2_ct(u2_ve_at()->toy.slop), u2nc(hed, tal));
}

/* u2_ve_sell(): use sell gate. 
*/
u2_noun
u2_ve_sell(u2_noun vax)
{
  c3_assert(0 != u2_ve_at()->toy.sell);

  return u2_cn_mong(u2_ct(u2_ve_at()->toy.sell), vax);
}

/* u2_ve_soul(): use soul gate. 
*/
u2_noun
u2_ve_soul(u2_noun typ)
{
  c3_assert(0 != u2_ve_at()->toy.soul);

  return u2_cn_mong(u2_ct(u2_ve_at()->toy.soul), typ);
}

/* u2_ve_ream(): use ream gate.
*/
u2_noun
u2_ve_ream(u2_noun txt)
{
  c3_assert(0 != u2_ve_at()->toy.ream);

  return u2_cn_mong(u2_ct(u2_ve_at()->toy.ream), txt);
}

/* u2_ve_slac(): slap with feature as C string.  highly convenient.
*/
u2_noun
u2_ve_slac(u2_noun vax, const c3_c* sam_c)
{
  return u2_ve_slap(vax, u2_ci_string(sam_c));
}

/* u2_ve_slan(): slap with gene as C string.
*/
u2_noun
u2_ve_slan(u2_noun vax, const c3_c* sam_c)
{
  return u2_ve_slap(vax, u2_ve_ream(u2_ci_string(sam_c)));
}

/* u2_ve_use(): use specified tool.
*/
u2_noun 
u2_ve_use(const c3_c* wit_c)
{
  u2_steg* ver_e = &u2_Host.ver_e[u2_Host.kno_w];
  u2_noun  wit   = u2_ci_string(wit_c);
  u2_weak  tul   = u2_ckd_by_get(u2_ct(ver_e->tul), wit);

  if ( u2_none == tul ) {
    u2_cm_bean(u2nc(u2_Host.kno_w, u2_ci_string(wit_c)));

    fprintf(stderr, "no %s, %d\n", wit_c, u2_Host.kno_w);
    return u2_cm_foul("vere-tool");
  }
  else return tul;
}

/* u2_ve_hard(): use standard tool gate without type check.
*/
u2_noun
u2_ve_hard(const c3_c* wit_c, c3_c* fun_c, u2_noun arg)
{           
  u2_noun tul = u2_ve_use(wit_c);
  u2_noun gat = u2_ve_slac(tul, fun_c);
  u2_noun cor = u2_ct(u2t(gat));
 
  u2z(gat);
  return u2_cn_mong(cor, arg);
}

/* u2_ve_soft(): use standard tool gate against vase.
*/
u2_noun
u2_ve_soft(const c3_c* wit_c, c3_c* fun_c, u2_noun vos)
{
  u2_noun tul = u2_ve_use(wit_c);
  u2_noun gat = u2_ve_slac(tul, fun_c);

  return u2_ve_slam(gat, vos);
}

/* u2_ve_meat(): return noun of vase.
*/
u2_noun 
u2_ve_meat(u2_noun vos)
{
  u2_noun myt = u2_ct(u2t(vos));

  u2_cz(vos);
  return myt;
}
