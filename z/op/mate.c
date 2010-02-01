/* z/op/mate.c
**
** This file is in the public domain.
*/
#   define _zn_bip_mate(field) *_zn_anvil(z, ray_bip, mate, field)

    /* u3_cm_mate: mate to a static formula.
    */
      case u3_cm_mate: {
        _zn_retreat(z, _zn_bip_mate(f.r.ray_mat));
        {
          u3_ray ray_lid = _zn_bip_mate(f.c.ray_lid);
          u3_fox pod     = _zn_bip_mate(f.s.pod);
          u3_fox gus     = _zn_bip_mate(d.gus);

          if ( u3_yes == u3_lr_eq(z, pod, gus) ) {
            _zn_complete(z, ray_lid, pod);
          }
          else {
            printf("mate: jet mismatch\n");

            u3_b_print(&z->l, "hard", pod);
            u3_b_print(&z->l, "soft", gus);

            return u3_cm_fail;
          }
        }
        break;
      }
