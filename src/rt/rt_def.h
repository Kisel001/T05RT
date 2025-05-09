/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        rt_def.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 05.09.2024
 * PURPOSE:     RayTracing's basic defines header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __rt_def_h_
#define __rt_def_h_

#include "materials.h"

/* Basic project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    /* Shape class prototype */
    class shape;

    /* Enviroment of defraction data type */
    class envi
    {
    public:
      DBL
        RefractionCoef, // Refraction coefficient
        Decay;          // Environment media decay coefficient
    }; /* End of 'envi' class */

    /* Information about source (for return) data type */
    class light_info
    {
    public:
      vec3 L;           // Light source direction
      vec3 Color;       // Light source color
      DBL Dist;         // Distance to light source
    }; /* End of 'light_info' class */


    /* Light source data type */
    class light
    {
    public:
      DBL Cc, Cl, Cq;   // Attenuation coefficients
      vec3 Color;       // Light source color

      /* Constructor by all parameters.
       * ARGUMENTS:
       *   - attenuation coefficients:
       *       DBL cc, cl, cq;
       *   - color:
       *       vec3 color;
       */
      light( DBL cc, DBL cl, DBL cq, vec3 color ) : Cc(cc), Cl(cl), Cq(cq), Color(color)
      {
      } /* End of 'light' function */

      /* Light shadow evaluvating function.
       * ARGUMENTS:
       *   - point:
       *       const vec3 &P;
       *   - light_info:
       *       light_info *L;
       * RETURNS:
       *   (DBL) information about shadow.
       */
      virtual DBL Shadow( const vec3 &P, light_info *L )
      {
        return 0.0;
      } /* End of 'Shadow' function */

    }; /* End of 'light' class */

    /* Intersection class */
    class intr
    {
    public:
      DBL   T;          // Intersection ray distance
      shape *Shp;       // Intersected shape

      //----------------------------------
      // Intersection point data fields:
      //----------------------------------
      vec3  P;          // Intersection point
      BOOL  IsP;        // Exis point flag
      
      //----------------------------------
      // Intersection normal data fields:
      //----------------------------------
      vec3  N;          // Normal at intersection point
      BOOL  IsN;        // Exis normal flag

      INT   M;          // Material of intersection element. (outdated)

      /* Ray object entering flag */
      enum ENTER_TYPE
      {
        ENTER, // Ray goes inside object
        STAY,  // Ray stay in object
        LEAVE  // Ray goes outside object
      } EnterFlag;      // Intersection entering flag

      //----------------------------------
      // Cache addon:
      //----------------------------------
      INT    I[2];         // Integer data array addon.
      DBL    D[2];         // Double float data array addon.
      vec3   V[2];         // 3D vector (double) data array addon.
      const VOID *Ptr[2]; // Pointers data array addon.
      
      // In future, may be more array-addons...

    }; /* End of 'intersection' class */

    /* Intersection list type */
    typedef stock<intr> intr_list;

    /* Base shape class */
    class shape
    {
    private:
      matr 
        ComM = matr::Identity(), InvM = matr::Identity(); // Matrix
    public:
      INT material = 0;   // Material of shape
      surface Surf;       // Enviroment shape param
      BOOL IsUsingMod = false; // Is using mode parameter.

      /* Default constructor */
      shape() : 
        Surf({0.24725,0.1995,0.0745}, {0.75164,0.60648,0.22648}, {0.628281,0.555802,0.366065}, 51.2) // gold material
      {
      } /* End of 'shape' function */

      /* Constructor by material parameters.
       * ARGUMENTS:
       *   - ka, kd, ks:
       *       vec3 ka, kd, ks;
       *   - ph:
       *       DBL ph;
       */
      shape( vec3 ka, vec3 kd, vec3 ks, DBL ph ) :
        Surf(ka, kd, ks, ph) // any material
      {
      } /* End of 'shape' function */

      /* Constructor by material.
       * ARGUMENTS:
       *   - material:
       *       surface Mtl;
       */
      shape( surface Mtl ) : Surf(Mtl)
      {
      } /* End of 'shape' function */

      /* Set using mode function
       * ARGUMENTS:
       *   - new flag of using mode:
       *       BOOL Flag;
       * RETURNS: None.
       */
      VOID SetUsingModeFlag( BOOL Flag )
      {
        IsUsingMod = Flag;
      } /* End of 'SetUsingModeFlag' function */

      /* Default destructor */
      virtual ~shape( VOID )
      {
      } /* End of '~shape' function */

      /* Get reference to matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (const matr &) reference to matrix.  
       */
      const matr & GetMatr( VOID ) const
      {
        return ComM;
      } /* End of 'GetMatr' function */

      /* Get reference to inverse matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (const matr &) reference to inverse matrix.
       */
      const matr & GetInvMatr( VOID ) const
      {
        return InvM;
      } /* End of 'GetInvMatr' function */

      /* Get reference to inverse matrix function.
       * ARGUMENTS:
       *   - matrix:
       *       const matr &M;
       * RETURNS: None.
       */
      VOID SetMatr( const matr &M )
      {
        ComM = M;
        InvM = M.Inverse();// .Transpose();
      } /* End of 'SetMatr' function */

      /* Get intersection function.
       * ARGUMENTS:
       *   - ray:
       *       const ray &R;
       *   - intersection structure:
       *       intr *Intr;
       * RETURNS:
       *   (BOOL) status of success intersection.
       */
      virtual BOOL Intersect( const ray &R, intr *Intr )
      {
        return FALSE;
      } /* End of 'Intersect' function */

      /* Get normal function.
       *   ARGUMENTS:
       *     - intersection:
       *         intr *Intr;
       * RETURNS: None.
       */
      virtual VOID GetNormal( intr *Intr )
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
      virtual INT AllIntersect( const ray &R, intr_list &Il )
      {
        return 0;
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
        return FALSE;
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
        return FALSE;
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
      virtual vec3 Mode( const vec3 &Pos, const vec3 &N, intr *In )
      {
        return vec3(0);
      } /* End of 'Mode' function */

    }; /* End of 'shape' class */
  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // __rt_def_h_

/* END OF 'rt_def.h' FILE */
