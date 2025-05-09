/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        csg_clip.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 25.07.2024
 * PURPOSE:     RayTracing's csg intersection header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __csg_clip_h_
#define __csg_clip_h_

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
      /* Clip class */
      class clip : public shape
      {
      public:
        shape *ShpA, *ShpB; // shapes

        /* Constructor of intersection by 2 shapes.
         * ARGUMENTS:
         *   - pointers to shapes:
         *       shape *A, *B;
         */
        clip( shape *A, shape *B ) : ShpA(A), ShpB(B)
        {
        } /* End of 'intersection' function */

        /* Default destructor */
        ~clip( VOID ) override
        {
          delete ShpA;
          delete ShpB;
        } /* End of '~intersection' function' */

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
          intr_list il1;

          if (ShpA->AllIntersect(R, il1))
          {
            intr best_in(0, nullptr);
            for (auto &i : il1)
            {
              i.P = R(i.T);
              if (!ShpB->IsInside(i.P))
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
      }; /* End of 'clip' class */
    } /* end of 'csg' namespace */
  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__csg_clip_h_

/* END OF 'csg_clip.h' FILE */
