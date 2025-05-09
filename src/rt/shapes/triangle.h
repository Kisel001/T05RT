/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        triangle.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 26.07.2024
 * PURPOSE:     RayTracing's triangle header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __triangle_h_
#define __triangle_h_

#include "../rt_def.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  { 
    /* Triangle class */
    class triangle : public shape
    {
    public:
      vec3
        P1, P2, P3, // points of triangle;
        N,          // normal of triangle
        U1, V1;     // vectors for search u & v
      DBL
        u0, v0;     // coef for search u & v

      /* Constructor of triangle by 3 points
       * ARGUMENTS:
       *   - points:
       *       const vec3 &P1, &P2, &P3;
       */
      triangle( const vec3 &p1, const vec3 &p2, const vec3 &p3 ) :
        P1(p1), P2(p2), P3(p3), 
        shape(vec3(0.1745, 0.01175, 0.01175), vec3(0.61424, 0.04136, 0.04136), vec3(0.727811, 0.626959, 0.626959), 76.8)
      {
        N = ((p2 - p1) % (p3 - p1)).Normalizing();
        vec3 s1 = p2 - p1;
        vec3 s2 = p3 - p1;
        
        U1 = (s1 * s2.Len2() - s2 * (s1 & s2)) / (s1.Len2() * s2.Len2() - (s1 & s2) * (s1 & s2));
        u0 = P1 & U1;

        V1 = (s2 * s1.Len2() - s1 * (s1 & s2)) / (s1.Len2() * s2.Len2() - (s1 & s2) * (s1 & s2));
        v0 = P1 & V1;
      } /* End of 'triangle' function */

      /* Default destructor */
      ~triangle( VOID ) override
      {
      } /* End of '~triangle' function' */

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
        DBL T = (N & (P1 - R.Org)) / (N & R.Dir);

        if (T < Treashold)
          return FALSE;

        Intr->P = R.Org + R.Dir * T;

        DBL u = (Intr->P & U1) - u0;

        if (u < Treashold)
          return FALSE;

        DBL v = (Intr->P & V1) - v0;

        if (v < Treashold)
          return FALSE;

        if (u + v - 1 > Treashold)
          return FALSE;

        Intr->N = N;
        Intr->T = T;

        return TRUE;
      } /* End of 'Intersect' function */

      /* Get normal function.
       *   ARGUMENTS:
       *     - intersection:
       *         intr *Intr;
       * RETURNS: None.
       */
      VOID GetNormal( intr *Intr ) override
      {
        Intr->N = N;
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
        intr tmp_intr;

        if (Intersect(R, &tmp_intr))
        {
          Il << tmp_intr;
          return 1;
        }

        return FALSE;
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
        intr tmp_intr;

        return Intersect(R, &tmp_intr);
      } /* End of 'IsIntersect' function */

    }; /* End of 'triangle' class */
  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__triangle_h_

/* END OF 'triangle.h' FILE */
