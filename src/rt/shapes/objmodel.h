/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        objmodel.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 26.07.2024
 * PURPOSE:     RayTracing's obj model header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __objmodel_h_
#define __objmodel_h_

#include "../rt_def.h"
#include "triangle.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  { 
    /* Triangle class */
    class objmodel : public shape
    {
    public:
      triangle **TrArray;   // array with pointers to triangles
      INT CountOfTriangles; // count of triangles

      /* Constructor of triangle by 3 points
       * ARGUMENTS:
       *   - points:
       *       const std::string &FileName;
       */
      objmodel( const std::string &FileName ) : 
        shape(vec3(0.1745, 0.01175, 0.01175), vec3(0.61424, 0.04136, 0.04136), vec3(0.727811, 0.626959, 0.626959), 76.8)
      {
        FILE *F = nullptr;
        vec3 *V;            // array with vertices

        try
        {
          INT nv = 0, nf = 0;
          static CHAR Buf[10000];
 
          if ((F = fopen(FileName.c_str(), "r")) == NULL)
            std::abort();

          /* Count vertices and indices */
          while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
            if (Buf[0] == 'v' && Buf[1] == ' ')
              nv++;
            else if (Buf[0] == 'f' && Buf[1] == ' ')
            {
              INT n = 0;
              CHAR *ptr = Buf + 2, old = ' ';
 
              while (*ptr != 0)
                n += *ptr != ' ' && old == ' ', old = *ptr++;
              nf += n - 2;
            }
 
          V = new vec3[nv];
          TrArray = new triangle *[nf];
          CountOfTriangles = nf;

          INT add_tr_count = 0;

          /* Read model data */
          rewind(F);
          nv = nf = 0;
          while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
            if (Buf[0] == 'v' && Buf[1] == ' ')
            {
              DBL x, y, z;
 
              sscanf(Buf + 2, "%lf %lf %lf", &x, &y, &z);
              V[nv++] = vec3(x, y, z);
            }
            else if (Buf[0] == 'f' && Buf[1] == ' ')
            {
              INT n = 0, c = 0, c0 = 0, c1 = 0, c2 = 0;
              CHAR *ptr = Buf + 2, old = ' ';
 
              while (*ptr != 0)
              {
                if (*ptr != ' ' && old == ' ')
                {
                  sscanf(ptr, "%d", &c);
                  if (c < 0)
                    c = nv + c;
                  else
                    c--;
 
                  if (n == 0)
                    c0 = c;
                  else if (n == 1)
                    c1 = c;
                  else
                  {
                    /* add new triangle */
                    TrArray[add_tr_count++] = new triangle(V[c0], V[c1], V[c]);
                    c1 = c;
                  }
                  n++;
                }
                old = *ptr++;
              }
            }
 
          fclose(F);
          delete[] V;
        }
        catch ( std::bad_alloc & )
        {
          if (F != nullptr)
            fclose(F);

          std::abort();
        }
      } /* End of 'box' function */

      /* Default destructor */
      ~objmodel( VOID ) override
      {
        for (INT i = 0; i < CountOfTriangles; ++i)
          delete[] TrArray[i];

        delete[] TrArray;
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
        intr best_intr;
        best_intr.T = -1;

        for (INT i = 0; i < CountOfTriangles; ++i)
        {
          intr current_intr;
          if (TrArray[i]->Intersect(R, &current_intr) && 
            (best_intr.T == -1 || current_intr.T < best_intr.T))
            best_intr = current_intr, best_intr.Shp = TrArray[i];
        }

        if (best_intr.T != -1)
        {
          *Intr = best_intr;
          Intr->M = 2;
          return TRUE;
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
      virtual INT AllIntersect( const ray &R, intr_list &Il )
      {
        INT count = 0;

        for (INT i = 0; i < CountOfTriangles; ++i)
        {
          intr current_intr;
          
          if (TrArray[i]->Intersect(R, &current_intr))
          {
            ++count;
            Il << current_intr;
          }
        }

        if (count)
          std::qsort(Il.data(), count, sizeof(intr), []( VOID const *A1, VOID const *A2 ) -> INT
            {
              intr const *E1 = (intr const *)A1;
              intr const *E2 = (intr const *)A2;

              return 
                (E1->T < E2->T) ? -1 :
                (E1->T > E2->T) ? 1 :
                0;
            });

        return count;
      } /* End of 'AllIntersect' function */

      /* Get information about insiding location point in shape function.
       * ARGUMENTS:
       *   - point:
       *       const vec3 &P;
       * RETURNS:
       *   (BOOL) true - if point inside, else false.
       */
      virtual BOOL IsInside( const vec3 &P )
      {
        ray R = ray(P, vec3(0, 1, 0));
        INT count = 0;

        for (INT i = 0; i < CountOfTriangles; ++i)
        {
          intr current_intr;
          
          if (TrArray[i]->Intersect(R, &current_intr))
            ++count;
        }

        return (count % 2) == 0 ? FALSE : TRUE;
      } /* End of 'IsInside' function */

      /* Get information about intersect ray of shape function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       * RETURNS:
       *   (BOOL) true - if ray intersect, else false.
       */
      virtual BOOL IsIntersect( const ray &R )
      {
        for (INT i = 0; i < CountOfTriangles; ++i)
        {
          intr current_intr;

          if (TrArray[i]->Intersect(R, &current_intr))
            return TRUE;
        }

        return FALSE;
      } /* End of 'IsIntersect' function */
    }; /* End of 'triangle' class */
  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__triangle_h_

/* END OF 'triangle.h' FILE */
