/* include/all.h
**
** This file is in the public domain.
*/

  /** Internal includes.
  **/
    /** u3_c: the C layer.
    **/
#     include "c/portable.h"
#     include "c/types.h"
#     include "c/defs.h"
#     include "c/motes.h"

#       define u3_assert(x) u3_c_assert(x)
#       define u3_wiseof(x) u3_c_wiseof(x)
#       define u3_stub      u3_c_stub

    /** u3_l: the clam layer.
    **/
#     include "l.h"

#       define u3_h(l, a) u3_lr_h(l, a)
#       define u3_t(l, a) u3_lr_t(l, a)

#       define u3_hh(l, a)  u3_h(l, u3_h(l, a))
#       define u3_ht(l, a)  u3_t(l, u3_h(l, a))
#       define u3_th(l, a)  u3_h(l, u3_t(l, a))
#       define u3_tt(l, a)  u3_t(l, u3_t(l, a))

#       define u3_hhh(l, a)  u3_h(l, u3_h(l, u3_h(l, a)))
#       define u3_hht(l, a)  u3_t(l, u3_h(l, u3_h(l, a)))
#       define u3_hth(l, a)  u3_h(l, u3_t(l, u3_h(l, a)))
#       define u3_htt(l, a)  u3_t(l, u3_t(l, u3_h(l, a)))
#       define u3_thh(l, a)  u3_h(l, u3_h(l, u3_t(l, a)))
#       define u3_tht(l, a)  u3_t(l, u3_h(l, u3_t(l, a)))
#       define u3_tth(l, a)  u3_h(l, u3_t(l, u3_t(l, a)))
#       define u3_ttt(l, a)  u3_t(l, u3_t(l, u3_t(l, a)))


    /** u3_b: boot assistance, from u4.  To be deleted.
    **/
#     include "b.h"

    /** u3_z: zeno, the interpreter.
    **/
#     include "z/machine.h"
#     include "z/agent.h"
#     include "z/jato.h"

#     define _zj_dry(nam, mug) 
#     define _zj_wet(nam, mug) \
        u3_fox u3_zx_##nam(u3_z, u3_fox);
#     include "z/jets.h"
#     undef _zj_dry
#     undef _zj_wet

    /** u3_x: xeno, the interpreter.
    **/
#     include "x/machine.h"
#     include "x/agent.h"
#     include "x/jato.h"

#     define _xj_dry(nam, mug) 
#     define _xj_wet(nam, mug) \
        u3_fox u3_xx_##nam(u3_x, u3_fox);
#     include "x/jets.h"
#     undef _xj_dry
#     undef _xj_wet

    /** u2: the new interpreter.
    **/
#     include "f/loom.h"
#     include "f/rail.h"
#     include "f/chad.h"
#     include "f/bask.h"
#     include "f/plow.h"
#     include "f/shed.h"
#     include "f/host.h"
#     include "f/bail.h"
#     include "f/benx.h"
#     include "f/wire.h"
#     include "f/funj.h"
