/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        sphere.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 24.07.2024
 * PURPOSE:     RayTracing's sphere header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __sphere_h_
#define __sphere_h_

#include "../rt_def.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    class sphere : public shape
    {
    public:
      vec3
        Center; // Center of sphere
      DBL
        R2;     // radius^2 of sphere

      /* Sphere constructor.
       * ARGUMENTS:
       *   - center:
       *       vec3 Cen;
       *   - material name:
       *       const CHAR *MtlName;
       *   - radius:
       *       DBL Radius;
       */
      sphere( vec3 Cen, DBL Radius, const CHAR *MtlName = "Gold" ) : Center(Cen), R2(Radius * Radius), shape(surface(MtlName))
      {
        this->material = 2;
      } /* End of 'sphere' function */

      /* Default destructor */
      ~sphere( VOID ) override
      {
      } /* End of '~sphere' function' */

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
        vec3 a = Center - R.Org;
        DBL 
          oc2 = a.Len2(),
          ok = a & R.Dir,
          ok2 = ok * ok,
          h2 = R2 - (oc2 - ok2);

        // Ray start inter sphere
        if (oc2 < R2)
        {
          Intr->T = ok + std::sqrt(h2);
          Intr->N = (a - R.Dir * Intr->T).Normalizing();
          Intr->Shp = this;
          return TRUE;
        }
        if (ok < Treashold)
          return FALSE;
        if (h2 < Treashold)
          return FALSE;
        Intr->T = ok - sqrt(h2);
        Intr->N = (a - R.Dir * Intr->T).Normalizing();
        Intr->Shp = this;
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
        Intr->N = (Center - Intr->P).Normalizing();
        //Intr->N = (a - Intr->P).Normalizing();
      } /* End of 'GetNormal' function */

      /* Get all intersects function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       *   - list with intersections:
       *       intr_list &Il;
       * RETURNS:
       *   (INT) count of intersections.
       */
      INT AllIntersect( const ray &R, intr_list &Il ) override
      {
        vec3 a = Center - R.Org;
        DBL 
          oc2 = a.Len2(),
          ok = a & R.Dir,
          ok2 = ok * ok,
          h2 = R2 - (oc2 - ok2);
        INT count = 0;

        DBL tmp = ok + std::sqrt(h2);

        if (tmp > Treashold)
        {
          intr tmp1;

          tmp1.T = tmp;
          tmp1.N = (a - R.Dir * tmp1.T).Normalizing();
          tmp1.Shp = this;
          Il << tmp1;
          ++count;
        }

        tmp = ok - std::sqrt(h2);

        if (tmp > Treashold)
        {
          intr tmp1;

          tmp1.T = tmp;
          tmp1.N = (a - R.Dir * tmp1.T).Normalizing();
          tmp1.Shp = this;
          Il << tmp1;
          ++count;
        }

        return count;


#if 0
        if (oc2 < R2)
        {
          intr tmp1;

          tmp1.T = ok + std::sqrt(h2);
          tmp1.N = (a - R.Dir * tmp1.T).Normalizing();
          tmp1.Shp = this;
          Il << tmp1;
          return 1;
        }
        if (ok < Treashold)
          return 0;
        if (h2 < Treashold)
          return 0;
        
        intr tmp1, tmp2;

        tmp1.T = ok - std::sqrt(h2);
        tmp1.N = (a - R.Dir * tmp1.T).Normalizing();
        tmp1.Shp = this;
        tmp2.T = ok + std::sqrt(h2);
        tmp2.N = (a - R.Dir * tmp2.T).Normalizing();
        tmp2.Shp = this;
        Il << tmp1;
        Il << tmp2;

        return 2;
#endif
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
        DBL 
          x = P.X - Center.X,
          y = P.Y - Center.Y,
          z = P.Z - Center.Z;

        return (x * x + y * y + z * z < R2) ? TRUE : FALSE;
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
        vec3 a = Center - R.Org;
        DBL 
          oc2 = a.Len2(),
          ok = a & R.Dir,
          ok2 = ok * ok,
          h2 = R2 - (oc2 - ok2);

        if (oc2 < R2)
          return TRUE;
        if (ok < Treashold)
          return FALSE;
        if (h2 < Treashold)
          return FALSE;
        return TRUE;
      } /* End of 'IsIntersect' function */
    }; /* End of 'sphere' class */
  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__sphere_h_

/* END OF 'sphere.h' FILE */
