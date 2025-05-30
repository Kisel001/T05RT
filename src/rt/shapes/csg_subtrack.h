/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        csg_subtrack.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 25.07.2024
 * PURPOSE:     RayTracing's csg subtrack header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __csg_subtrack_h_
#define __csg_subtrack_h_

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
      /* Subtrack class */
      class subtrack : public shape
      {
      public:
        shape *ShpA, *ShpB; // shapes

        /* Constructor of box by 2 points
         * ARGUMENTS:
         *   - shapes:
         *       
         */
        subtrack( shape *A, shape *B ) : ShpA(A), ShpB(B)
        {
        } /* End of 'subtrack' function */

        /* Default destructor */
        ~subtrack( VOID ) override
        {
          delete ShpA;
          delete ShpB;
        } /* End of '~subtrack' function' */

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
          intr_list il1, il2;

          if (ShpA->AllIntersect(R, il1) > 0)
          {
            intr best_in(0, nullptr);
            ShpB->AllIntersect(R, il2);

            for (auto &i : il1)
            {
              i.P = R(i.T);
              if (!ShpB->IsInside(i.P))
                if (best_in.Shp == nullptr || best_in.T > i.T)
                  best_in = i;
            }
            for (auto &i : il2)
            {
              i.P = R(i.T);
              if (ShpA->IsInside(i.P))
                if (best_in.Shp == nullptr || best_in.T > i.T)
                  best_in = i;
            }
            *Intr = best_in;

            return best_in.Shp != nullptr;
          }

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
          intr_list il1, il2;

          if (ShpA->AllIntersect(R, il1) > 0)
          {
            INT count = 0;
            ShpB->AllIntersect(R, il2);

            for (auto &i : il1)
            {
              i.P = R(i.T);
              if (!ShpB->IsInside(i.P))
                Il << i, ++count;
            }
            for (auto &i : il2)
            {
              i.P = R(i.T);
              if (ShpA->IsInside(i.P))
                Il << i, ++count;
            }

            return count;
          }

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
          return ShpA->IsInside(P) && !ShpB->IsInside(P);
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
          intr tmp_intr;

          return Intersect(R, &tmp_intr);
        } /* End of 'IsIntersect' function */
      }; /* End of 'subtrack' class */
    } /* end of 'csg' namespace */
  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__csg_subtrack_h_

/* END OF 'csg_subtrack.h' FILE */
