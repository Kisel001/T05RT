/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        mth_ray.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 21.07.2024
 * PURPOSE:     Base math ray header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __mth_ray_h_
#define __mth_ray_h_

#include "mth_def.h"

/* Mathematic namespace */
namespace mth
{
  /* Ray Type */
  template<typename Type>
    class ray
    {
    public:
      vec3<Type> 
        Org, Dir; // Position and direction types
  
      /* Base constructor */
      ray( VOID )
      {
      } /* End of 'ray' function */

      /* Constructor by position and direction.
       * ARGUMENTS:
       *   - origin:
       *       const vec3<Type> &O;
       *   - direction:
       *       const vec3<Type> &D;
       */
      ray( const vec3<Type> &O, const vec3<Type> &D ) : Org(O), Dir(D.Normalizing())
      {
      } /* End of 'ray' function */
      
      /* Function of ray.
       * ARGUMENTS:
       *   - parameter (> 0):
       *       Type T;
       * RETURNS:
       *   (vec3<Type>) f(T).
       */
      vec3<Type> operator()( Type T ) const
      {
        return Org + Dir * T;
      } /* End of 'operator()' function */
    }; /* End of 'ray' class */
} /* end of 'mth' namespace */

#endif // !__mth_ray_h_

/* END OF 'mth_ray.h' FILE */
