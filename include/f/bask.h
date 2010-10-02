/* include/bask.h
**
** This file is in the public domain.
*/
  /** Data types.
  **/
    /* u2_loom_bask: a memory basket, for caching nock results
    */
      typedef struct {
        u2_loom_rail o;

        /* par_r: parent basket: ray to u2_loom_bask
        */
        u2_ray par_r;

        /* h: chad: top-level hashtable
        */
        u2_loom_chad cad_c;
      } u2_loom_bask;

#       define u2_bask_par_r(bas_r)  *u2_at(bas_r, u2_loom_bask, par_r)
#       define u2_bask_cad_r(bas_r)  u2_aftr(bas_r, u2_loom_bask, cad_c)


  /** Functions.
  **/
    /* u2_ba_init(): 
    **
    **   Initialize basket from rail partition, with parent if any.
    */
      u2_ray
      u2_ba_init(u2_ray bas_r,
                 u2_ray par_r);
 
    /* u2_ba_find():
    **
    **   Basket search for `.*(bus fol)` in `bas`.
    */
      u2_weak
      u2_ba_find(u2_ray  bas_r,
                 u2_noun bus,
                 u2_noun fol);

    /* u2_ba_save():
    */
      void
      u2_ba_save(u2_ray  bas_r,
                 u2_noun bus,
                 u2_noun fol,
                 u2_noun pro);
