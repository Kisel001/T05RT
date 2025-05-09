/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        transformed.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 02.09.2024
 * PURPOSE:     RayTracing's transformed header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __transformed_h_
#define __transformed_h_

#include "../rt_def.h"

#if 0 // not used
/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    /* Transform class  */
    class transform : public shape
    {
    private:
      matr ComM;  // Transform matrix 
      matr InvM;  // Inverse of transform matrix
      shape *Shp; // Transformed shape

    public:
      /* Constructor of transformed shape.
       * ARGUMENTS:
       *   - pointer to transformed shape:
       *       shape *Shape;
       *   - reference to matrix:
       *       const matr &M;
       */
      transform( shape *Shape, const matr &M ) : ComM(M), InvM(M.Inverse()), Shp(Shape)
      {
      } /* End of 'transform' function */

      /* Default destructor */
      ~transform( VOID ) override
      {
      } /* End of '~transform' function' */

      /* Get intersection function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       *   - intersection structure:
       *       intr *Intr;
       * RETURNS:
       *   (BOOL) status of success intersection.
       */
      BOOL Intersect( const ray &R, intr *Intr ) override
      {
        ray R1 {InvM.TransformPoint(R.Org), InvM.TransformVector(R.Dir)};

        return Intersect(R1, Intr);
      } /* End of 'Intersect' function */

      /* Get normal function.
       *   ARGUMENTS:
       *     - intersection:
       *         intr *Intr;
       * RETURNS: None.
       */
      VOID GetNormal( intr *Intr ) override
      {
        Shp->GetNormal(Intr);
        Intr->N = ComM.TransformVector(Intr->N);
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
        ray R1 {InvM.TransformPoint(R.Org), InvM.TransformVector(R.Dir)};

        INT intersections = Shp->AllIntersect(R1, Il);

        for (INT i = 0; i < intersections; ++i)
        {
          Il[i] = 
        }
      } /* End of 'AllIntersect' function */
    }; /* End of 'transform' class */

  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */
#endif

#endif // !__transformed_h_

/* END OF 'transformed.h' FILE */
