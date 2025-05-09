/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : materials.h
 * PURPOSE     : Raytracing project.
 *               Materials of shapes declaration module.
 * PROGRAMMER  : IP5.
 * LAST UPDATE : 28.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __materials_h_
#define __materials_h_

#include "def.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    /* Threshold coeficients */
    static const DBL Treashold     = 0.00001;
    static const DBL ColorThresold = 0.002;
    static const DBL Threshold     = 0.00001;

    /* Shading coefficient store class */
    class coef
    {
    public:
      vec3 K;           // Coefficient color value
      BOOL IsUsage;     // Coefficient usage flag

      /* Class constructor */
      coef( VOID ) : IsUsage(FALSE)
      {
      } /* End of 'coef' function */

      /* Class constructor.
       * AGUMENTS:
       *   - color all components value:
       *       DBL C;
       */
      coef( DBL C ) : K(C, C, C), IsUsage(C > Threshold)
      {
      } /* End of 'coef' function */

      /* Class constructor.
       * AGUMENTS:
       *   - color component values:
       *       DBL X, Y, Z;
       */
      coef( DBL X, DBL Y, DBL Z ) :
        K(X, Y, Z),
        IsUsage(X > Threshold ||
                Y > Threshold ||
                Z > Threshold)
      {
      } /* End of 'coef' function */

      /* Class constructor.
       * AGUMENTS:
       *   - color value:
       *       const vec3 &C;
       */
      coef( const vec3 &C ) :
        K(C),
        IsUsage(C.X > Threshold ||
                C.Y > Threshold ||
                C.Z > Threshold)
      {
      } /* End of 'coef' function */

      /* Coefficient set from vec3 function.
       * AGUMENTS:
       *   - color value:
       *       const vec3 &C;
       * RETURNS:
       *   (coef &) self reference.
       */
      coef & operator=( const vec3 &C )
      {
        K = C;
        IsUsage = C.X > Threshold ||
                  C.Y > Threshold ||
                  C.Z > Threshold;
        return *this;
      } /* End of 'operator=' constructor */

      /* Coefficient to vec3 color conversion function.
       * AGUMENTS: None.
       * RETURNS:
       *   (vec3) color value.
       */
      operator vec3( VOID ) const
      {
        return K;
      } /* End of 'operator vec3' function */

      /* Get max component function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (DBL) max component.
       */
      DBL MaxComponent( VOID ) const
      {
        return K.MaxComponent();
      } /* End of 'MaxComponent' function */
    }; /* End of 'coef' class */

    /* Array with base data for surface */
    static const struct MtlLibType
    {
      const CHAR *SurfaceName; /* Name of surface */
      const struct MtlLibDataType
      {
        const vec3 Ka, Kd, Ks; /* Material coefficients */
        const DBL Ph;          /* Phong coefficient */
      } SurfaceData;
    } SurfaceLib[] =
    {
      {"Black Plastic",   {{0.0, 0.0, 0.0},              {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},                 32}},
      {"Brass",           {{0.329412,0.223529,0.027451}, {0.780392,0.568627,0.113725}, {0.992157,0.941176,0.807843},    27.8974}},
      {"Bronze",          {{0.2125,0.1275,0.054},        {0.714,0.4284,0.18144},       {0.393548,0.271906,0.166721},    25.6}},
      {"Chrome",          {{0.25, 0.25, 0.25},           {0.4, 0.4, 0.4},              {0.774597, 0.774597, 0.774597},  76.8}},
      {"Copper",          {{0.19125,0.0735,0.0225},      {0.7038,0.27048,0.0828},      {0.256777,0.137622,0.086014},    12.8}},
      {"Gold",            {{0.24725,0.1995,0.0745},      {0.75164,0.60648,0.22648},    {0.628281,0.555802,0.366065},    51.2}},
      {"Peweter",         {{0.10588,0.058824,0.113725},  {0.427451,0.470588,0.541176}, {0.3333,0.3333,0.521569},        9.84615}},
      {"Silver",          {{0.19225,0.19225,0.19225},    {0.50754,0.50754,0.50754},    {0.508273,0.508273,0.508273},    51.2}},
      {"Polished Silver", {{0.23125,0.23125,0.23125},    {0.2775,0.2775,0.2775},       {0.773911,0.773911,0.773911},    89.6}},
      {"Turquoise",       {{0.1, 0.18725, 0.1745},       {0.396, 0.74151, 0.69102},    {0.297254, 0.30829, 0.306678},   12.8}},
      {"Ruby",            {{0.1745, 0.01175, 0.01175},   {0.61424, 0.04136, 0.04136},  {0.727811, 0.626959, 0.626959},  76.8}},
      {"Polished Gold",   {{0.24725, 0.2245, 0.0645},    {0.34615, 0.3143, 0.0903},    {0.797357, 0.723991, 0.208006},  83.2}},
      {"Polished Bronze", {{0.25, 0.148, 0.06475},       {0.4, 0.2368, 0.1036},        {0.774597, 0.458561, 0.200621},  76.8}},
      {"Polished Copper", {{0.2295, 0.08825, 0.0275},    {0.5508, 0.2118, 0.066},      {0.580594, 0.223257, 0.0695701}, 51.2}},
      {"Jade",            {{0.135, 0.2225, 0.1575},      {0.135, 0.2225, 0.1575},      {0.316228, 0.316228, 0.316228},  12.8}},
      {"Obsidian",        {{0.05375, 0.05, 0.06625},     {0.18275, 0.17, 0.22525},     {0.332741, 0.328634, 0.346435},  38.4}},
      {"Pearl",           {{0.25, 0.20725, 0.20725},     {1.0, 0.829, 0.829},          {0.296648, 0.296648, 0.296648},  11.264}},
      {"Emerald",         {{0.0215, 0.1745, 0.0215},     {0.07568, 0.61424, 0.07568},  {0.633, 0.727811, 0.633},        76.8}},
      {"Black Plastic",   {{0.0, 0.0, 0.0},              {0.01, 0.01, 0.01},           {0.5, 0.5, 0.5},                 32.0}},
      {"Black Rubber",    {{0.02, 0.02, 0.02},           {0.01, 0.01, 0.01},           {0.4, 0.4, 0.4},                 10.0}},
    };

    /* Size of surface lib */
    static const INT SurfaceLibSize = sizeof(SurfaceLib) / sizeof(SurfaceLib[0]);

    /* Surface class */
    class surface
    {
    public:

      /* Default constructor */
      surface() : Kr(0.1), Kt(0)
      {
      } /* End of 'surface' function */

      /* Constructor by parameters.
       * ARGUMENTS:
       *   - kads coef:
       *       vec3 ka, kd, ks;
       *   - phong coef:
       *       DBL ph;
       */
      surface( vec3 ka, vec3 kd, vec3 ks, DBL ph ) : Ka(ka), Kd(kd), Ks(ks), Ph(ph), Kr(0.5), Kt(0)
      {
        for (INT i = 0; i < 8; ++i)
          TexNum[i] = -1;
      } /* End of 'surface' function */

      /* Constructor by parameters.
       * ARGUMENTS:
       *   - surface name:
       *       const CHAR *SurfName;
       */
      surface( const CHAR *SurfName ) : Kr(0.1), Kt(0)
      {
        for (INT i = 0; i < SurfaceLibSize; ++i)
          if (std::strcmp(SurfName, SurfaceLib[i].SurfaceName) == 0)
          {
            Ka = SurfaceLib[i].SurfaceData.Ka;
            Kd = SurfaceLib[i].SurfaceData.Kd;
            Ks = SurfaceLib[i].SurfaceData.Ks;
            Ph = SurfaceLib[i].SurfaceData.Ph;
            memset(TexNum, 0, sizeof(INT[8]));

            return; // we finded true surface thats meen we may be leave.
          }

        // If no finded surface, then create default material
        surface({0.05375, 0.05, 0.06625}, {0.18275, 0.17, 0.22525}, {0.332741, 0.328634, 0.346435}, 38.4);
      } /* End of 'surface' function */

      vec3 Ka, Kd, Ks;  // ambient, diffuse, specular
      DBL Ph;           // Bui Tong Phong coefficient
      coef Kr {}, Kt {};      // reflected, transmitted

      INT TexNum[8];    // Number of textures
    }; /* End of 'surface' class */
  } /* end of 'rt' namespace */
} /* end of 'pitr' namespace */

#endif // !__materials_h_

/* END OF 'materials.h' FILE */


