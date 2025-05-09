/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        tor.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 01.09.2024
 * PURPOSE:     RayTracing's tor header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __tor_h_
#define __tor_h_

#include "../rt_def.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    using cmpl = std::complex<FLT>;

    /* Triangle class */
    class tor : public shape
    {
    protected:
      /* Get sqr function.
       * ARGUMENTS:
       *   - number:
       *       Type X;
       * RETURNS:
       *   (Type) X * X;
       */
      template<typename Type>
        Type FastSqr( Type X )
        {
          return X * X;
        } /* End of 'FastSqr' function */

      /* Get cube function.
       * ARGUMENTS:
       *   - number:
       *       Type X;
       * RETURNS:
       *   (Type) X * X * X;
       */
      template<typename Type>
        Type FastCube( Type X )
        {
          return X * X * X;
        } /* End of 'FastCube' function */

      /* Decide equation with power 2.
       * ARGUMENTS:
       *   - coefficients:
       *       DBL L, B, C;
       *   - list with roots:
       *       std::vector<DBL> &Roots;
       * RETURNS: None.
       */
      VOID Equat2Pow( DBL L, DBL B, DBL C, std::vector<DBL> &Roots )
      {
        DBL
          d = B * B - 4 * L * C;

        if (d < 0)
          return;
        if (d == 0)
          Roots.push_back(-B / (2 * L));
        else
        {
          DBL ds = sqrt(d);
          Roots.push_back((-B - ds) / (2 * L));
          Roots.push_back((-B + ds) / (2 * L));
        }
      } /* End of 'Equat2Pow' function */

      /* Fixed power function.
       * ARGUMENTS:
       *   - number:
       *       DBL Num;
       *   - power:
       *       DBL Power;
       * RETURNS:
       *   (DBL) result of power function.
       */
      DBL FixedPow( DBL Num, DBL Pow )
      {
        if (Num == 0)
          return 0;
        if (Num < 0)
          return -std::pow(-Num, Pow);
        return std::pow(Num, Pow);
      } /* End of 'FixedPow' function */

    public:
      DBL
        R2, r2;     // Radiuses of tor (in power 2).
      vec3 pos;     // Coordinates of center of tor
      //DBL
      //  x0, y0, z0; // Coordinates of center of tor.

      /* Constructor by base parameters.
       * ARGUMENTS:
       *   - position:
       *       vec3 Pos;
       *   - big radius:
       *       DBL BigR;
       *   - small radius:
       *       DBL LitR;
       */
      tor( vec3 Pos, DBL BigR, DBL LitR ) : R2(BigR * BigR), r2(LitR * LitR), pos(Pos), shape(surface("Gold"))//x0(Pos.X), y0(Pos.Y), z0(Pos.Z)
      {
      } /* End of 'tor' function */

      /* Default destructor */
      ~tor( VOID ) override
      {
      } /* End of '~tor' function' */

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
        DBL po = 1.0;
        vec3 L = R.Org - pos;
        DBL 
          m = L & L,
          n = L & R.Dir,
          k = (m + R2 - r2) / 2.0,
          k3 = n,
          k2 = n * n - R2 * (vec2(R.Dir.X, R.Dir.Y) & vec2(R.Dir.X, R.Dir.Y)) + k,
          k1 = n * k - R2 * (vec2(R.Dir.X, R.Dir.Y) & vec2(L.X, L.Y)),
          k0 = k * k - R2 * (vec2(L.X, L.Y) & vec2(L.X, L.Y));
      
        if (abs(k3 * (k3 * k3 - k2) + k1) < Treashold)
        {
          po = -1.0;
          std::swap(k1, k3);
          k0 = 1.0 / k0;
          k1 = k1 * k0;
          k2 = k2 * k0;
          k3 = k3 * k0;
        }
      
        DBL 
          c2 = k2 * 2.0 - 3.0 * k3 * k3,
          c1 = k3 * (k3 * k3 - k2) + k1,
          c0 = k3 * (k3 * (c2 + 2.0 * k2) - 8.0 * k1) + 4.0 * k0;
        c2 /= 3.0;
        c1 *= 2.0;
        c0 /= 3.0;
        DBL 
          Q = c2 * c2 + c0,
          Rk = c2 * c2 * c2 - 3.0 * c2 * c0 + c1 * c1,
          h = Rk * Rk - Q * Q * Q;
      
        if (h >= 0.0)
        {
          h = sqrt(h);
          DBL 
            v = COM_SIGN(Rk + h) * pow(abs(Rk + h), 1.0 / 3.0),
            u = COM_SIGN(Rk - h) * pow(abs(Rk - h), 1.0 / 3.0); 
          vec2 s {(v + u) + 4.0 * c2, (v - u) * sqrt(3.0)};
          DBL 
            y = sqrt(0.5 * ((!s) + s.X)),
            x = 0.5 * s.Y / y,
            r = 2.0 * c1 / (x * x + y * y),
            t1 =  x - r - k3; 
          t1 = (po < 0.0) ? 2.0 / t1 : t1;
          DBL t2 = -x - r - k3; 
          t2 = (po < 0.0) ? 2.0 / t2 : t2;
          DBL t = 1e20;
          
          BOOL flag = FALSE;

          if (t1 > 0.0) 
            t = t1, flag = TRUE;
          if (t2 > 0.0) 
            t = min(t, t2), flag = TRUE;

          if (!flag)
            return FALSE;

          vec3 npos = L + R.Dir * t;
          Intr->N = (npos * (npos & npos) - npos * (r2) - npos * vec3(1.0, 1.0, -1.0) * R2).Normalize();
          Intr->T = t;
          Intr->Shp = this;
          return TRUE;
        }
      
        DBL 
          sQ = sqrt(Q),
          w = sQ * cos(acos(-Rk/(sQ * Q)) / 3.0),
          d2 = -(w + c2); 
        
        if (d2 < 0.0)
          return FALSE;
        
        DBL 
          d1 = sqrt(d2),
          h1 = sqrt(w - 2.0 * c2 + c1 / d1),
          h2 = sqrt(w - 2.0 * c2 - c1 / d1),
          t1 = -d1 - h1 - k3; 
        t1 = (po < 0.0) ? 2.0 / t1 : t1;
        DBL t2 = -d1 + h1 - k3; 
        t2 = (po < 0.0) ? 2.0 / t2 : t2;
        DBL t3 =  d1 - h2 - k3; 
        t3 = (po < 0.0) ? 2.0 / t3 : t3;
        DBL t4 =  d1 + h2 - k3; 
        t4 = (po < 0.0) ? 2.0 / t4 : t4;
        
        BOOL flag = FALSE;
        DBL t = 1e20;
        if (t1 > 0.0) 
          t = t1, flag = TRUE;
        if (t2 > 0.0) 
          t = min(t, t2), flag = TRUE;
        if (t3 > 0.0)
          t = min(t, t3), flag = TRUE;
        if (t4 > 0.0) 
          t = min(t, t4), flag = TRUE;

        if (!flag)
          return FALSE;

        vec3 npos = L + R.Dir * t;
        Intr->N = (npos * (npos & npos) - npos * r2 - npos * vec3(1.0, 1.0, -1.0) * R2).Normalize();
        Intr->T = t;
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
        //Intr->N = vec3(0, 0, 1);
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
        return 0;
      } /* End of 'AllIntersect' fuction */

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

    }; /* End of 'tor' class */
  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__tor_h_

/* END OF 'tor.h' FILE */
