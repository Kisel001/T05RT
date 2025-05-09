/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        csg_bound.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 28.07.2024
 * PURPOSE:     RayTracing's csg bound header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __csg_bound_h_
#define __csg_bound_h_

#include "../rt_def.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  { 
    /* CSG namespace */
    namespace csg
    {
      /* Bound class */
      class bound : public shape
      {
      public:
        shape 
          *Object, // shape
          *Bound;  // bound of shape

        /* Constructor of intersection by 2 shapes.
         * ARGUMENTS:
         *   - pointers to shapes:
         *       shape *Obj, *Bnd;
         */
        bound( shape *Obj, shape *Bnd ) : Object(Obj), Bound(Bnd)
        {
        } /* End of 'bound' function */

        /* Default destructor */
        ~bound( VOID ) override
        {
          delete Object;
          delete Bound;
        } /* End of '~bound' function' */

        /* Get intersection function.
         * ARGUMENTS:
         *   - ray:
         *       const ray &R;
         *   - intersection structure:
         *       intr *Intr;
         * RETURNS:
         *   (BOOL) status of success intersection.
         */
        BOOL Intersect( const ray &R, intr *Intr )
        {
          if (Bound->IsIntersect(R))
            return Object->Intersect(R, Intr);
          return FALSE;
        } /* End of 'Intersect' function */

        /* Get normal function.
         *   ARGUMENTS:
         *     - intersection:
         *         intr *Intr;
         * RETURNS: None.
         */
        VOID GetNormal( intr *Intr ) override
        {
          Intr->Shp->GetNormal(Intr);
        } /* End of 'GetNormal' function */

        /* Get all intersects function.
         * ARGUMENTS:
         *   - ray:
         *       const ray &R;
         *   - list with intersections:
         *       intr_list &Il;
         * RETURNS:
         *   (INT) Count of intersections.
         */
        INT AllIntersect( const ray &R, intr_list &Il ) override
        {
          if (Bound->IsIntersect(R))
            return Object->AllIntersect(R, Il);
          return 0;
        } /* End of 'AllIntersect' function */

        /* Get information about insiding location point in shape function.
         * ARGUMENTS:
         *   - point:
         *       const vec3 &P;
         * RETURNS:
         *   (BOOL) true - if point inside, else false.
         */
        BOOL IsInside( const vec3 &P ) override
        {
          if (Bound->IsInside(P))
            return Object->IsInside(P);
          return FALSE;
        } /* End of 'IsInside' function */

        /* Get information about intersect ray of shape function.
         * ARGUMENTS:
         *   - ray:
         *       const ray &R;
         * RETURNS:
         *   (BOOL) true - if ray intersect, else false.
         */
        BOOL IsIntersect( const ray &R ) override
        {
          if (Bound->IsIntersect(R))
            return Object->IsIntersect(R);
          return FALSE;
        } /* End of 'IsIntersect' function */

      }; /* End of 'bound' class */
    } /* end of 'csg' namespace */
  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__csg_clip_h_

/* END OF 'csg_bound.h' FILE */

