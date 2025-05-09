/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        plane.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 05.09.2024
 * PURPOSE:     RayTracing's plane header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __plane_h_
#define __plane_h_

#include <conio.h>

#include "../rt_def.h"
#include "../tex/texture.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    /* Plane class */
    class plane : public shape
    {
    public:
      vec3
        N,                    // normal
        P;                    // point on plane
      INT UseTex = 0;         // use texture flag
      texture *Tex = nullptr; // texture

      /* Plane constructor.
       * ARGUMENTS:
       *   - normal:
       *       vec3 n;
       *   - pos:
       *       vec3 p;
       */
      plane( vec3 n, vec3 p ) : N(n), P(p)
      {
        this->material = 1; // material of plane
      } /* End of 'plane' function */

      /* Plane constructor with texture from file.
       * ARGUMENTS:
       *   - normal:
       *       vec3 n;
       *   - pos:
       *       vec3 p;
       *   - filename:
       *       std::string Filename
       */
      plane( vec3 n, vec3 p, std::string Filename ) : N(n), P(p)
      {
        FILE *F;

        if ((F = fopen(Filename.c_str(), "rb")) == nullptr)
          return;
        
        INT w = 0, h = 0;
        shape::IsUsingMod = 1;
        UseTex = 1;

        fread(&w, 2, 1, F);
        fread(&h, 2, 1, F);

        BYTE *Buf = new BYTE[w * h * 3];
        
        fread(Buf, 3, (UINT_PTR)w * h, F);

        Tex = TexManager.AddTexture(w, h, 3, Buf);

        delete[] Buf;
      } /* End of 'plane' function */

      /* Default destructor */
      ~plane( VOID ) override
      {
      } /* End of '~plane' function' */

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
        //DBL T = -(N.operator&(P) + 1.0) / (N & R.Dir);
        DBL T = (N & (P - R.Org)) / (N & R.Dir);

        if (T < Treashold)// || T > 1000)
          return FALSE;

        Intr->T = T;
        Intr->N = N;
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

      /* Modificate color of shape function.
       * ARGUMENTS:
       *   - position of drawing:
       *       const vec3 &Pos;
       *   - normal:
       *       const vec3 &N;
       *   - intersection:
       *       intr *In;
       * RETURNS:
       *   (vec3) color.
       */
      vec3 Mode( const vec3 &Pos, const vec3 &N, intr *In ) override
      {
        if (UseTex)
        {
          vec2 tc {Pos.X / 5 - INT(Pos.X / 5), Pos.Z / 5 - INT(Pos.Z / 5)};

          if (tc.X < 0)
            tc.X = 1 + tc.X;
          if (tc.Y < 0)
            tc.Y = 1 + tc.Y;

          return Tex->GetColor(tc);
        }
        else
        {
          INT x = INT(Pos.X);
          INT z = INT(Pos.Z);

          if (Pos.X < 0)
            x = -x + 1;
          if (Pos.Z < 0)
            z = -z + 1;

          if (((x % 2) + (z % 2)) % 2)
            return vec3(1, 0, 0);
          return vec3(1, 1, 1);
        }
      } /* End of 'Mode' function */

    }; /* End of 'plane' class */
  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__plane_h_

/* END OF 'plane.h' FILE */
