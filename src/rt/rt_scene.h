/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        rt_scene.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 05.09.2024
 * PURPOSE:     RayTracing's scene header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __rt_scene_h_
#define __rt_scene_h_

#include "rt_def.h"
/* Lights headers */
#include "lights/point.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    /* Scene class */
    class scene
    {
    public:
      //-----------------------------
      // Sync flags:
      //-----------------------------
      std::atomic_bool IsRenderActive = FALSE;  // Is render active flag
      std::atomic_bool IsToBeStop = FALSE;      // Is to be stop flag
      std::atomic_bool IsReadyToFinish = TRUE;  // Is ready to finish flag
      // Store rendering line
      std::atomic_int StartRow = 0;             // Store rendering line counting

      //-----------------------------
      // Scene shapes storage:
      //-----------------------------
      
      // Stock with shapes
      stock<shape *> Shapes;                    // Stock for storage shapes of scene

      /* Add shape to scene function.
       * ARGUMENTS:
       *   - pointer to shape:
       *       shape *Shp;
       * RETURNS:
       *   (scene &) this scene.
       */
      scene & operator<<( shape *Shp )
      {
        Shapes << Shp;
        return *this;
      } /* End of 'operator<<' function */

      //-----------------------------
      // Scene lightning parameters:
      //-----------------------------
      vec3 
        AmbientColor = vec3(0.0, 0.0, 0.0),     // Ambient color of scene
        BackgroundColor = vec3(0.3, 0.47, 0.8), // Background color of scene
        FogColor;                               // Fog color of scene
      DBL 
        FogStart,                               // Fog start coefficient
        FogEnd;                                 // Fog end coefficient
      stock<light *> 
        Lights;                                 // Stock for storage light of scene

      /* Add light to scene function.
       * ARGUMENTS:
       *   - pointer to light source:
       *       light *Lgh;
       * RETURNS:
       *   (scene &) this scene.
       */
      scene & operator<<( light *Lgh )
      {
        Lights << Lgh;
        return *this;
      } /* End of 'operator<<' function */

      /* Shading store info type */
      struct shade_info
      {
      public:
        vec3 P;                                 // Point of shading evaluation
        vec3 N;                                 // Point normal
        shape *Shp;                             // Shape pointer
        surface Surf;                           // Surface material
        envi Media;                             // Object media environment
        vec3 Du, Dv;                            // Tangent vectors
        intr *In;                               // Intersection
      }; /* End of 'shade_info' class */

      //-----------------------------
      // Recursion parameters:
      //-----------------------------
      INT
        //RecLevel = 0,                         // Current recurse level, not used
        MaxRecLevel = 5;                        // Maximal avaliable recurse level
      envi Air;                                 // Air enviroment data

      //-----------------------------
      // Scene render methods:
      //-----------------------------

      /* Render scene function.
       * ARGUMENTS:
       *   - camera:
       *       const camera &Cam;
       *   - frame:
       *       frame &Frm;
       *   - is debug mode flag:
       *       BOOL IsDebug = FALSE;
       * RETURNS: None.
       */
      VOID Render( const camera &Cam, frame &Frm, BOOL IsDebug = FALSE )
      {
        INT n = std::thread::hardware_concurrency();
        if (IsDebug) // For debug mode, render with one thread (for render checking)
          n = 1;

        std::vector<std::thread> Ths;
        Ths.resize(n);

        StartRow = 0;
        for (INT i = 0; i < n; i++)
        {
          Ths[i] = std::thread(
            [&]( VOID )
            {
              INT y = 0;
              while (y < Frm.H)
              {
                y = StartRow++;
                for (INT x = 0; x < Frm.W; x++)
                {
                  //ray r = Cam.FrameRay(x + 0.5, y + 0.5);
                  //vec3 c = Trace(r, Air, 0.1);
                  const INT l = 2;
                  const DBL s = 1.0 / l;

                  //if (y < Frm.H / 2)// || x < Frm.W / 2)
                  //  continue;
                  //if (y == Frm.H / 2 && x == Frm.W / 2)
                  //  __debugbreak();

                  vec3 c;
                  
                  for (INT i = 0; i < l; ++i)
                    for (INT j = 0; j < l; ++j)
                    {
                      ray r = Cam.FrameRay(x + j * s, y + i * s);
                      c += Trace(r, Air, 0.1);
                    }
                  
                  c /= l * l;
                  
                  Frm.PutPixel(x, y, frame::ToRGB(c.X, c.Y, c.Z));
                }
              }
            });
        }
        for (INT i = 0; i < n; i++)
          Ths[i].join();

        // Old render, without multithread
#if 0 
        for (INT y = 0; y < Frm.H; ++y)
          for (INT x = 0; x < Frm.W; ++x)
          {
            ray R = Cam.FrameRay(x, y);
            vec3 color = Trace(R);
            Frm.PutPixel(x, y, frame::ToRGB(color));
          }
#endif // 0
      } /* End of 'Render' function */

      /* Trace function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       *   - enviroment:
       *       const envi &Media;
       *   - weight:
       *       DBL Weight;
       *   - recurse level:
       *       INT RecLevel;
       * RETURNS:
       *   (vec3) color.
       */
      vec3 Trace( const ray &R, const envi &Media, DBL Weight, INT RecLevel = 0 )
      {
        intr in;

        if (IsToBeStop)
          return vec3(0);

        vec3 color = BackgroundColor;
#if 1
        if (RecLevel < MaxRecLevel)
        {
          ++RecLevel;
          if (Intersect(R, &in))
          {
            const matr &InvMatr = in.Shp->GetInvMatr();
            const matr &Matr = in.Shp->GetMatr();
            ray R1 {R.Org, R.Dir}; // InvMatr.TransformPoint(R.Org), InvMatr.TransformVector(R.Dir)

            in.P = R1(in.T);
            //in.Shp->GetNormal(&in);
            in.N.Normalize();

            color = Shade(R1.Dir, Media, &in, Weight, RecLevel);
            //color = Shade(in.P, Media, &in, Weight);
            color *= exp(-in.T * Media.Decay);
          }
          --RecLevel;
        }
        return color;
#else  // 0
//        vec3 color;

        if (Intersect(R, &in))
        {
          in.P = R(in.T);
          in.Shp->GetNormal(&in);
          color = Shade(in.P, Media, &in, Weight);
        }
        else
          color = vec3(0.3, 0.47, 0.8);////vec3(0.3, 0.47, 0.8);//vec3(0, 0, 0);//BackgroundColor;
        return color;
#endif // 0
      } /* End of 'Trace' function */

      /* Shade function.
       * ARGUMENTS:
       *   - point:
       *       const vec3 &V;
       *   - enviroment:
       *       const envi &Media;
       *   - intersection:
       *       intr *In;
       *   - weight:
       *       DBL Weight;
       *   - recurse level:
       *       INT RecLevel;
       * RETURNS:
       *   (vec3) color.
       */
      vec3 Shade( const vec3 &V, const envi &Media, intr *In, DBL Weight, INT RecLevel )
      {
        shade_info si {In->P, In->N, In->Shp, In->Shp->Surf, Media, {1, 0, 0}, {0, 1, 0}, In};
          /// modifiers (later)
          // face forward (si.N):
        // Faceforward normal
        DBL vn = V & si.N;

        if (vn > 0)
        {
          si.N = -si.N;
          vn = -vn;
          //DBL vn = V & si.N;
          BOOL IsEnter = TRUE;
          IsEnter = FALSE;
        }

#if 0
        vec3 N = In->N;
        vec3 L = -((In->P - vec3(20, 10, 30))).Normalizing();

        vec3 surface_color;

        // Material #1 - segmented field
        if (In->M == 1)
        {
          DBL X = In->P.X;
          DBL Z = In->P.Z;
          BOOL flag = true;

          if (X < 0)
            flag = 1 - flag, X = -X;
          if (Z < 0)
            flag = 1 - flag, Z = -Z;

          INT c1 = fmod(X, 5.0) < 2.5 ? 1 : 0; 
          INT c2 = fmod(Z, 5.0) < 2.5 ? 1 : 0;

          if (flag)
          {
            if ((c1 + c2) % 2 == 0)
              surface_color = vec3(0.5, 0.25, 0.5);
            else
              surface_color = vec3(0.25, 0, 0.25);
          }
          else
          {
            if ((c1 + c2) % 2 != 0)
              surface_color = vec3(0.5, 0.25, 0.5);
            else
              surface_color = vec3(0.25, 0, 0.25);
          }
        }
        else
          surface_color = vec3(1, 1, 0);

        intr in1;

        if (this->Intersect(ray(In->P, L), &in1, In->Shp))
          surface_color /= 5;

        //vec3 surface_color = vec3(1, 0, 0);
        vec3 diffuse = surface_color * max(0.18, (L & N));
        //surface_color *= (L & N);
        //vec3 r = P.Reflect(N);
        //diffuse += vec3(pow(max((r & L), 0.0), 5)) * vec3(0.7);

        return diffuse;
#endif
        // Ambient
        vec3 color = si.Surf.Ka * AmbientColor;
        vec3 R = (V - si.N * (2 * (V & si.N))).Normalizing();

        for (auto Lgh : Lights)
        {
          light_info li;
          DBL sh = Lgh->Shadow(si.P, &li);
          intr il;
          li.L.Normalize();
          if (Intersect(ray(si.P + li.L * Threshold, li.L), &il) > 0 &&
              il.T < li.Dist)
            continue; // point in shadow
          DBL nl = si.N & li.L;

          // diffuse
          if (nl > Threshold)
          {
            if (si.Shp->IsUsingMod)
              color += si.Shp->Mode(si.P, si.N, si.In) * li.Color * nl;
            else
              color += si.Surf.Kd * li.Color * nl; // ??? * sh

            // specular
            if (DBL rl = R & li.L; rl > Threshold)
              color += si.Surf.Ks * li.Color * pow(rl, si.Surf.Ph); // ??? * sh
          }
        }

        // Reflection other scene shapes
        if (DBL w = si.Surf.Kr.MaxComponent() * Weight; w > ColorThresold)
          // OR si.Surf.Kr.IsUsage && coef(si.Surf.Kr.K * Weight).IsUsage
          color += si.Surf.Kr.K * Trace(ray(si.P + R * Threshold, R), Media, w, RecLevel);

        return color;
      } /* End of 'Shade function' */

      /* Intersection function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       *   - intersection:
       *       intr *In;
       *   - current shape for shade (nullptr if no):
       *       shape *cur
       * RETURNS:
       *   (BOOL) status of intersection.
       */
      BOOL Intersect( const ray &R, intr *In, shape *cur = nullptr )
      {
        intr best_intr;
        best_intr.T = -1;

        for (auto *shp : Shapes)
        {
          const matr &m1 = shp->GetMatr();
          const matr &m1inv = shp->GetInvMatr();

          ray R1 {m1inv.TransformPoint(R.Org), m1inv.TransformVector(R.Dir)};

          if (shp == cur)
            continue;

          intr current_intr;

          if (shp->Intersect(R1, &current_intr))
          {
            current_intr.P = m1.TransformPoint(current_intr.P);
            current_intr.N = m1.TransformVector(current_intr.N);

            if (best_intr.T == -1 || current_intr.T < best_intr.T)
              best_intr = current_intr, best_intr.M = shp->material;
          }
        }
        if (best_intr.T == -1)
          return FALSE;
        *In = best_intr;
        return TRUE;
      } /* End of 'Intersect' function */

      /* Scene elements clear function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID ClearScene( VOID )
      {
        for (auto &i : this->Shapes)
          delete i;

        for (auto &i : this->Lights)
          delete i;
      } /* End of 'ClearScene' function */

    }; /* End of 'scene' class */
  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__rt_scene_h_

/* END OF 'rt_scene.h' FILE */
