/* include/z/agent.h
**
** This file is in the public domain.
**
** Prefixes:
**
**   u3_zn  (zeno internal - zeno; the zeno interpreter)
**
** Description:
**
**   Agent structures for zeno.
**
**   zeno is a double-stack machine inside the loom.  It has one
**   register, (lab), which is a stack of agents to execute.
**
**   In general, a zeno agent pops itself off (cap), allocates its 
**   result on (hat), and pushes a pointer to it on (cap).
**
**   More precisely, the final effect of every agent, unless it errs
**   or terminates, is to:
**
**     - set (lab) to (poq) - the next agent
**     - set (cap) to (lid)
**     - push a result noun, [gus], on z->l.cap_ray
**
**   Some agents do this in one step; others apply a sequence.
**
**   An agent has two general forms: its forge form, as installed,
**   and its anvil form, followed by computed operands, as executed.
*/
  /** Macros.
  **/
    /* _zn_forge(): 
    **
    **   Reference a forge field.
    */
#     define _zn_forge(z, agent, kind, field) \
        u3_to(&z->l, agent, struct u3_zn_forge_##kind, field)

    /* _zn_anvil():
    **
    **   Reference an anvil field.
    */
#     define _zn_anvil(z, agent, type, field) \
        u3_at_ray(&z->l, \
                    ((agent) + \
                     ( ((c3_w *)&((struct u3_zn_anvil_##type *)0)->field) - \
                       ((c3_w *)0) ) \
                    ) \
                   )

    /* _zn_push_forge():
    **
    **   Push a forged agent on (cap).
    */
#     define _zn_push_forge(z, type) \
        ( (z->l.cap_ray += c3_wiseof(struct u3_zn_forge_##type)) - \
          c3_wiseof(struct u3_zn_forge_##type) )

    /* _zn_push_word()
    **
    **   Push a word on (cap).
    */
#     define _zn_push_word(z, word) \
        ( (*u3_at_ray(&z->l, z->l.cap_ray) = (word)), z->l.cap_ray++ )


  /** Data types.
  **/
    /** Agent parts.
    **/
      /* u3_zn_operator:
      **
      **  Operators.  Motes now, will be enums.
      */
        typedef u3_mote u3_zn_oper;

      /* u3_zn_control:
      **
      **  Core control logic.
      */
        struct u3_zn_control {
          /* ger: operation
          ** poq: next agent
          ** lid: cap at termination.
          */
          u3_zn_oper ger_op;
          u3_ray     poq_ray;
          u3_ray     lid_ray;
        };
      
      /* u3_zn_retreat:
      **
      **   Departure frame for subcomputation.  The lip is always
      **   the cap before retreating.
      */
        struct u3_zn_retreat {
          /* mat: saved mat.
          ** lip: base of buffer.
          */
          u3_ray mat_ray;
          u3_ray lip_ray;
        };

      /* u3_zn_mane:
      **
      **    Structures for mane memory management.
      */
        struct u3_zn_mane {
          /* Free lists per word count, 2^28 down to 2^4.
          */
          u3_ray lib_ray[25];
        };
        struct u3_zn_mane_bloc {
          /* Bit 0
          */
          c3_w wor_w;

          /* Next bloc in free list.
          */
          u3_ray nex_ray;
        };

    /** Forge and anvil structures, with opcodes:
    ***
    ***   bask
    ***   cons
    ***   cook
    ***   fine
    ***   drop
    ***   hint
    ***   goto
    ***   link
    ***   push
    ***   pick
    ***   root  [inc, tap, eq]
    ***   tail
    **/
      /* any:
      **
      **   General template for all agents.
      */
        struct u3_zn_forge_any {
          struct u3_zn_control c;
        };
        struct u3_zn_anvil_any {
          struct u3_zn_forge_any f;
        };

      /* bask:
      **
      **   Memory basket.  Capacity is between agent and cap,
      **   ie between forge and anvil, meaning anvil structure 
      **   cannot be used explicitly.
      */
        struct u3_zn_forge_bask {
          struct u3_zn_control c;
          struct {
            /* Number of words in basket, counting agent.
            */
            c3_w wor_w;

            /* Parent basket, or 0.
            */
            u3_ray par_ray;

            /* Manual memory allocator.
            */
            struct u3_zn_mane m;
          } s;
        };
        struct u3_zn_anvil_bask {
          struct u3_zn_forge_bask f;
          struct {
            u3_fox gus;
          } d;
        };

      /* cons:
      **
      **   Create a pair of two nouns.
      */
        struct u3_zn_forge_cons {
          struct u3_zn_control c;
        };
        struct u3_zn_anvil_cons {
          struct u3_zn_forge_cons f;
          struct {
            /* pux: head 
            ** nol: tail
            */
            u3_fox pux;
            u3_fox nol;
          } d;
        };

      /* cook: 
      ** 
      **   Compute a static formula on a static noun.
      */
        struct u3_zn_forge_cook {
          struct u3_zn_control c;
          struct {
            /* bus: subject.
            ** sef: formula.
            */
            u3_fox bus;
            u3_fox sef;
          } s;
        };
        struct u3_zn_anvil_cook {
          struct u3_zn_forge_cook f;
        };

      /* drop:
      **
      **   Shift a result down on the cap.
      */
        struct u3_zn_forge_drop {
          struct u3_zn_control c;
        };
        struct u3_zn_anvil_drop {
          struct u3_zn_forge_drop f;
          struct {
            /* gus: result.
            */
            u3_fox gus;
          } d;
        };

      /* fine: 
      **
      **   Terminate the computation and return successfully.
      */
        struct u3_zn_forge_fine {
          struct u3_zn_control c;
        };
        struct u3_zn_anvil_fine {
          struct u3_zn_forge_fine f;
          struct {
            /* gus: product.
            */
            u3_fox gus;
          } d;
        };

      /* jet: 
      **
      **   Use a jet accelerator to compute a static,
      **   well-known formula on a dynamic noun.
      */
        struct u3_zn_forge_jet {
          struct u3_zn_control c;
          struct u3_zn_retreat r;
          struct {
            /* sax: jet code.
            */
            c3_w sax_w;
          } s;
        };
        struct u3_zn_anvil_jet {
          struct u3_zn_forge_jet f;
          struct {
            /* gus: subject.
            */
            u3_fox gus;
          } d;
        };

      /* link:
      **
      **   Compute a static formula on a dynamic noun.
      */
        struct u3_zn_forge_link {
          struct u3_zn_control c;
          struct u3_zn_retreat r;
          struct {
            /* dep: static formula.
            */
            u3_fox dep;
          } s;
        };
        struct u3_zn_anvil_link {
          struct u3_zn_forge_link f;
          struct {
            /* gus: subject.
            */
            u3_fox gus;
          } d;
        };
      /* push:
      **
      **   Compute a static formula on a dynamic noun.
      */
        struct u3_zn_forge_push {
          struct u3_zn_control c;
          struct u3_zn_retreat r;
          struct {
            /* bus: original subject.
            ** dep: static formula.
            */
            u3_fox bus;
            u3_fox dep;
          } s;
        };
        struct u3_zn_anvil_push {
          struct u3_zn_forge_push f;
          struct {
            /* gus: subject.
            */
            u3_fox gus;
          } d;
        };
      /* hint:
      **
      **   Compute a static formula on a dynamic noun.
      */
        struct u3_zn_forge_hint {
          struct u3_zn_control c;
          struct u3_zn_retreat r;
          struct {
            /* bus: original subject.
            ** dep: static formula.
            */
            u3_fox bus;
            u3_fox dep;
          } s;
        };
        struct u3_zn_anvil_hint {
          struct u3_zn_forge_hint f;
          struct {
            /* gus: computed hint.
            */
            u3_fox gus;
          } d;
        };

      /* mate:
      **
      **   Test a jet-computed product.
      */
        struct u3_zn_forge_mate {
          struct u3_zn_control c;
          struct u3_zn_retreat r;
          struct {
            /* pod: jet-computed product.
            */
            u3_fox pod;
          } s;
        };
        struct u3_zn_anvil_mate {
          struct u3_zn_forge_mate f;
          struct {
            /* gus: soft-computed product.
            */
            u3_fox gus;
          } d;
        };

      /* pick: 
      **
      **   Branch.
      */
        struct u3_zn_forge_pick {
          struct u3_zn_control c;
          struct u3_zn_retreat r;
          struct {
            /* bus: subject.
            ** feg: then formula
            ** paf: else formula
            */
            u3_fox bus;
            u3_fox feg;
            u3_fox paf;
          } s;
        };
        struct u3_zn_anvil_pick {
          struct u3_zn_forge_pick f;
          struct {
            /* gus: condition value
            */
            u3_fox gus;
          } d;
        };

      /* root:
      **
      **   Root operation (eq, inc, tap).
      */
        struct u3_zn_forge_root {
          struct u3_zn_control c;
          struct u3_zn_retreat r;
        };
        struct u3_zn_anvil_root {
          struct u3_zn_forge_root f;
          struct {
            /* gus: operand
            */
            u3_fox gus;
          } d;
        };

      /* tail:
      **
      **  Complete a cons.
      */
        struct u3_zn_forge_tail {
          struct u3_zn_control c;
          struct u3_zn_retreat r;
          struct {
            /* bus: subject
            ** fel: formula
            */
            u3_fox bus;
            u3_fox fel;
          } s;
        };
        struct u3_zn_anvil_tail {
          struct u3_zn_forge_tail f;
          struct {
            /* gus: head of cons.
            */
            u3_fox gus;
          } d;
        };
