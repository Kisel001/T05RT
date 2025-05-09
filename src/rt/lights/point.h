/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        point.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 25.07.2024
 * PURPOSE:     RayTracing's point light header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __point_h_
#define __point_h_

#include "../rt_def.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    /* Lights namespace */
    namespace lights
    {
      /* Point light class */
      class point_light : public light
      {
      public:
        vec3 Coord; // coordinates of light

        /* Constructor by all parameters.
         * ARGUMENTS:
         *   - attenuation coefficients:
         *       DBL cc, cl, cq;
         *   - color:
         *       vec3 color;
         *   - coordinates:
         *       vec3 coord;
         */
        point_light( DBL cc, DBL cl, DBL cq, vec3 color, vec3 coord ) : light(cc, cl, cq, color), Coord(coord)
        {
        } /* End of 'point_light' function */

        /* Light shadow evaluvating function.
         * ARGUMENTS:
         *   - point:
         *       const vec3 &P;
         *   - light_info:
         *       light_info *L;
         * RETURNS:
         *   (DBL) information about shadow.
         */
        DBL Shadow( const vec3 &P, light_info *L ) override
        {
          L->Color = Color;
          L->Dist = (P - Coord).Len2();
          L->L = -(P - Coord).Normalizing();

          return 1.0;
        } /* End of 'Shadow' function */
      }; /* End of 'point_light' class */
    } /* end of 'lights' namespace */
  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__point_h_

/* END OF 'point.h' FILE */
