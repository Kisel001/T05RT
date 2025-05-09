/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        box.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 09.05.2024
 * PURPOSE:     RayTracing's plane header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __box_h_
#define __box_h_

#include "../rt_def.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  { 
    /* Box class */
    class box : public shape
    {
    public:
      vec3
        P1, P2, P[8], N[6]; // point of cube
      DBL
        D[6]; // d coef of box planes

      /* Constructor of box by 2 points
       * ARGUMENTS:
       *   - points:
       *       const vec3 &P1, &P2;
       *   - name of material:
       *       const CHAR *MtlName;
       */
      box( const vec3 &p1, const vec3 &p2, const CHAR *MtlName ) : P1(p1), P2(p2), shape(MtlName)
      {
        P[0] = vec3(P1.X, P1.Y, P1.Z);
        P[1] = vec3(P1.X, P1.Y, P2.Z);
        P[2] = vec3(P2.X, P1.Y, P2.Z);
        P[3] = vec3(P2.X, P1.Y, P1.Z);
        P[4] = vec3(P1.X, P2.Y, P1.Z);
        P[5] = vec3(P1.X, P2.Y, P2.Z);
        P[6] = vec3(P2.X, P2.Y, P2.Z);
        P[7] = vec3(P2.X, P2.Y, P1.Z);

        // 0, 1, 2 - (0, -1, 0)
        // 0, 3, 4 - (0, 0, -1)
        // 3, 2, 6 - (1, 0, 0)
        // 0, 1, 5 - (-1, 0, 0)
        // 1, 2, 5 - (0, 0, 1)
        // 4, 5, 6 - (0, 1, 0)

        N[0] =  vec3(0, -1, 0);
        N[1] =  vec3(0, 0, -1);
        N[2] =  vec3(1, 0, 0);
        N[3] =  vec3(-1, 0, 0);
        N[4] =  vec3(0, 0, 1);
        N[5] =  vec3(0, 1, 0);

        D[0] = P1.Y;
        D[1] = P1.Z;
        D[2] = P2.X;
        D[3] = P1.X;
        D[4] = P2.Z;
        D[5] = P2.Y;
      } /* End of 'box' function */

      /* Default destructor */
      ~box( VOID ) override
      {
      } /* End of '~box' function' */

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
        DBL tnear = -1, tfar = 1000, t0, t1;
        //vec3 res;

#define SET_T(Axis) \
        if (R.Dir. ## Axis == 0)                                            \
          if (R.Org. ## Axis < P1. ## Axis && R.Org. ## Axis > P2. ## Axis) \
            return FALSE;                                                   \
                                                                            \
        t0 = (P1. ## Axis - R.Org. ## Axis) / R.Dir. ## Axis;               \
        t1 = (P2. ## Axis - R.Org. ## Axis) / R.Dir. ## Axis;               \
                                                                            \
        if (t0 > t1)                                                        \
          std::swap(t0, t1);                                                \
                                                                            \
        if (t0 > tnear)                                                     \
          tnear = t0;                                                       \
                                                                            \
        if (t1 < tfar)                                                      \
          tfar = t1;                                                        \
                                                                            \
        if (tnear > tfar)                                                   \
          return false;                                                     \
                                                                            \
        if (tfar < Treashold)                                               \
          return false;

        SET_T(X);
        SET_T(Y);
        SET_T(Z);

#undef SET_T

        Intr->T = tnear;
        Intr->P = R.Org + R.Dir * tnear;
        Intr->Shp = this;
        GetNormal(Intr);

        return true;
      } /* End of 'Intersect' function */

      /* Get normal function.
       *   ARGUMENTS:
       *     - intersection:
       *         intr *Intr;
       * RETURNS: None.
       */
      VOID GetNormal( intr *Intr ) override
      {
        if (fabs(Intr->P.X - P1.X) < Treashold)
        {
          Intr->N = vec3(-1, 0, 0);
          return;
        }
        if (fabs(Intr->P.Y - P1.Y) < Treashold)
        {
          Intr->N = vec3(0, -1, 0);
          return;
        }
        if (fabs(Intr->P.Z - P1.Z) < Treashold)
        {
          Intr->N = vec3(0, 0, -1);
          return;
        }
        if (fabs(Intr->P.X - P2.X) < Treashold)
        {
          Intr->N = vec3(1, 0, 0);
          return;
        }
        if (fabs(Intr->P.Y - P2.Y) < Treashold)
        {
          Intr->N = vec3(0, 1, 0);
          return;
        }
        if (fabs(Intr->P.Z - P2.Z) < Treashold)
        {
          Intr->N = vec3(0, 0, 1);
          return;
        }

        Intr->N = vec3(0, 1, 0);
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
        INT count = 0;
        static vec3 N[6] = 
        {
          vec3(-1, 0, 0), vec3(0, -1, 0), vec3(0, 0, -1),
          vec3(1, 0, 0),  vec3(0, 1, 0),  vec3(0, 0, 1)
        };
        vec3 P[6] = 
        {
          P1, P1, P1, P2, P2, P2
        };
        DBL topt = -1;

        for (INT i = 0; i < 6; ++i)
        {
          DBL T = (N[i] & (P[i] - R.Org)) / (N[i] & R.Dir);

          if (T < Treashold)
            continue;

          vec3 PPP = R(T);

          if (PPP.X - P1.X > Treashold && PPP.X - P2.X < Treashold &&
              PPP.Y - P1.Y > Treashold && PPP.Y - P2.Y < Treashold &&
              PPP.Z - P1.Z > Treashold && PPP.Z - P2.Z < Treashold)
          {
            intr tmp;
            tmp.T = T;
            tmp.P = PPP;
            tmp.Shp = this;
            tmp.N = N[i];

            Il << tmp;

            ++count;
          }
        }

        return count;
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
        if (P.X - P1.X >= 0 && P.X - P2.X <= 0 &&
            P.Y - P1.Y >= 0 && P.Y - P2.Y <= 0 &&
            P.Z - P1.Z >= 0 && P.Z - P2.Z <= 0)
          return TRUE;
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

    }; /* End of 'box' class */
  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__box_h_

/* END OF 'box.h' FILE */
