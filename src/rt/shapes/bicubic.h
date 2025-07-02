/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        bicubic.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 09.09.2024
 * PURPOSE:     RayTracing's bicubic header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __bicubic_h_
#define __bicubic_h_

#include "../rt_def.h"
#include "triangle.h"
#include "g3dm.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    /* Grid class */
    class grid
    {
    private:
      //std::vector<triangle *> Triangles; // Triangles
      prim* Prim; // primitive

    public:
      /* Grid constructor.
       * ARGUMENTS:
       *   - points array:
       *       std::vector<vec3> &P;
       * RETURNS: None.
       */
      grid( std::vector<vec3> &P )
      {
        std::vector<INT> I;
        INT
          N2 = INT(P.size()),
          N = sqrt(N2);
        std::vector<vertex> V;
        for (auto &i : P)
          V.push_back({fvec3(i.X, i.Y, i.Z), {}, {}, {}});

        for (INT i = 0; i < N - 1; ++i)
          for (INT j = 0; j < N - 1; ++j)
          {
            I.push_back(i * N + j);
            I.push_back(i * N + j + 1);
            I.push_back((i + 1) * N + j);
            I.push_back((i + 1) * N + j);
            I.push_back((i + 1) * N + j + 1);
            I.push_back(i * N + j + 1);
            //Tr.push_back(new triangle(P[i * N + j], P[i * N + j + 1], P[(i + 1) * N + j]));
            //Tr.push_back(new triangle(P[(i + 1) * N + j], P[(i + 1) * N + j + 1], P[i  * N + j + 1]));
          }

        Prim = new prim(V, I);
      } /* End of 'grid' function */

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
        if (prim_storage::BBIsIntersected(R, Prim->MinBB, Prim->MaxBB))
          return Prim->Intersect(R, Intr);
        return FALSE;
      } /* End of 'Intersect' functions */

      /* Get all intersects function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       *   - list with intersections:
       *       intr_list &Il;
       * RETURNS:
       *   (INT) Count of intersections.
       */
      INT AllIntersect( const ray &R, intr_list &Il )
      {
        if (prim_storage::BBIsIntersected(R, Prim->MinBB, Prim->MaxBB))
          return Prim->AllIntersect(R, Il);
        return 0;
      } /* End of 'AllIntersect' function */
    }; /* End of 'grid' class */

    /* Bicubic class */
    class bicubic : public shape
    {
    private:
      std::vector<grid *> Planes; // Bicubic planes

      /* Get position function.
       * ARGUMENTS:
       *   - coordinates:
       *       vec2 T;
       *   - array with postions:
       *       std::vector<vec3> &P;
       * RETURNS:
       *   (vec3) interpolatet vector position.
       */
      vec3 Get( vec2 T, std::vector<vec3> &P )
      {
        INT C[] = {1, 3, 3, 1};
        DBL
          v = T.Y,
          vs[] = {1, v, v * v, v * v * v},
          vs1[] = {1, 1 - v, (1 - v) * (1 - v), (1 - v) * (1 - v) * (1 - v)};
        vec3 p;
        DBL
          u = T.X,
          us[] = {1, u, u * u, u * u * u},
          us1[] = {1, 1 - u, (1 - u) * (1 - u), (1 - u) * (1 - u) * (1 - u)};

        p = vec3(0);
        for (int ii = 0; ii < 4; ii++)
          for (int jj = 0; jj < 4; jj++)
            p += P[ii * 4 + jj] * C[ii] * C[jj] * us1[jj] * us[3 - jj] * vs1[ii] * vs[3 - ii];

        return p;
      } /* End of 'Get' function */


    public:
      const INT TessLvl = 10; // Bicubic tesselation level.

      /* Bicubic constructor.
       * ARGUMENTS:
       *   - filename:
       *       std::string Filename;
       */
      bicubic( std::string Filename )
      {
        FILE *F = fopen(Filename.c_str(), "r");
        INT CountOfPlanes;

        if (F == nullptr)
          return;

        fscanf(F, "%i", &CountOfPlanes);
        Planes.resize(CountOfPlanes);

        std::vector<vec3> P;
        std::vector<vec3> ReleaseP;
        //P.resize(16);

        for (INT i = 0; i < CountOfPlanes; ++i)
        {
          for (INT j = 0; j < 16; ++j)
          {
            DBL x, y, z;
            fscanf(F, "%lf%lf%lf", &x, &y, &z);
            P.push_back(vec3(x, y, z));
          }
          for (INT j = 0; j <= TessLvl; ++j)
          {
            for (INT k = 0; k <= TessLvl; ++k)
            {
              //for (INT m = 0; m <= TessLvl; ++m)
              //{
              vec2 T = vec2(DBL(j) / TessLvl, DBL(k) / TessLvl);
              vec3 P1 = Get(T, P);
              ReleaseP.push_back(P1);
              //}
            }
          }

          Planes[i] = new grid(ReleaseP);
          P.clear();
          ReleaseP.clear();
        }

      } /* End of 'bicubic' function */

      /* Default destructor */
      ~bicubic() override
      {
      } /* End of '~bicubic' function */

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
        intr tmp;
        DBL BT = -1;
        BOOL flag = FALSE;

        for (auto &i : Planes)
          if (i->Intersect(R, &tmp) && (tmp.T < BT || flag == FALSE))
            *Intr = tmp, BT = tmp.T, flag = TRUE;

        return flag;
      } /* End of 'Intersect' function */

      /* Get normal function.
       *   ARGUMENTS:
       *     - intersection:
       *         intr *Intr;
       * RETURNS: None.
       */
      VOID GetNormal( intr *Intr )
      {
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
      INT AllIntersect( const ray &R, intr_list &Il )
      {
        INT count = 0;

        for (auto &i : Planes)
          count += i->AllIntersect(R, Il);
 
        return count;
      } /* End of 'AllIntersect' function */

    }; /* End of 'bicubic' class */

  } /* end of 'rt' class */
} /* end of 'pirt' class */

#endif // !__bicubic_h_
