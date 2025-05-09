/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        mth_camera.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 21.07.2024
 * PURPOSE:     Base math camera header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __mth_camera_h_
#define __mth_camera_h_

#include "mth_def.h"

/* Math library namespace */
namespace mth
{
  /* Space camera handle class */
  template<typename Type>
    class camera
    {
    public:
      vec3<Type>
        Loc,            // camera location
        Dir, Up, Right, // basis camera directions
        At;             // camera pivot point    ...
      Type
        ProjDist,       // near project plane distance
        FarClip,        // far project plane distance
        Size,           // inner project plane rectangle size
        Wp, Hp;         // project plane size
      INT
        FrameW, FrameH; // Camera frame size in pixels
#if 0 // not used
      matr<Type>
        View,           // view matrix
        Proj,           // projection matrix
        VP;             // View and Proj matrix production
#endif

      /* Get frame ray function.
       * ARGUMENTS:
       *   - source coordinates:
       *       Type Xs, Ys;
       * RETURNS:
       *   ray<Type> new ray.
       */
      ray<Type> FrameRay( Type Xs, Type Ys ) const
      {
        vec3<Type> Q =
          Dir * ProjDist +
          Right * ((Xs - FrameW / 2) * Wp / FrameW) +
          Up * ((FrameH / 2 - Ys) * Hp / FrameH);

        return ray<Type>(Loc + Q, Q);
      } /* End of 'FrameRay' function */

      /* Default constructor */
      camera( VOID ) :
        Loc(0, 0, 5), Dir(0, 0, -1), Up(0, 1, 0), Right(1, 0, 0), At(0, 0, 0),
        ProjDist(0.1), FarClip(500), Size(0.1), FrameW(30), FrameH(30)
      {
        UpdateProj();
      } /* End of 'camera' function*/

      /* Set projection function.
       * ARGUMENTS:
       *   - new size:
       *       Type NewSize;
       *   - new proj dist:
       *       Type NewProjDist;
       *   - new far clip:
       *       Type NewFarClip;
       * RETURNS:
       *   (camera &) camera with new parameters.
       */
      camera & SetProj( Type NewSize, Type NewProjDist, Type NewFarClip )
      {
        ProjDist = NewProjDist;
        Size = NewSize;
        FarClip = NewFarClip;

        UpdateProj();
        return *this;
      } /* End of 'SetProj' function */

      /* Resize camera function.
       * ARGUMENTS:
       *   - New frame size:
       *       INT NewFrameW, NewFrameH;
       * RETURNS:
       *   (camera &) camera with new parameters.
       */
      camera & Resize( INT NewFrameW, INT NewFrameH )
      {
        FrameW = NewFrameW;
        FrameH = NewFrameH;

        UpdateProj();
        return *this;
      } /* End of 'Resize' function */

      /* Set location and at-position function.
       * ARGUMENTS:
       *   - location vector:
       *       const vec3<Type> &L;
       *   - at vector:
       *       const vec3<Type> &A;
       *   - up vector:
       *       const vec3<Type> &U;
       * RETURNS:
       *   (camera &) camera with new parameters.
       */
      camera & SetLocAtUp( const vec3<Type> &L, const vec3<Type> &A, const vec3<Type> &U = vec3<Type>(0, 1, 0) )
      {
        Loc = L;
        At = A;
        Up = U;

        Dir = (At - Loc).Normalizing();
        Right = (Dir % Up).Normalizing();
        Up = Right % Dir;

        UpdateProj();
        return *this;
      } /* End of 'SetLocAtUp' function */

    private:
      /* Update projection function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID UpdateProj( VOID )
      {
        Type rx = Size / 2, ry = Size / 2;

        if (FrameW > FrameH)
          rx *= (Type)FrameW / FrameH;
        else
          ry *= (Type)FrameH / FrameW;
        Wp = rx * 2;
        Hp = ry * 2;
        // Proj = matr<Type>::Frustum(-rx, rx, -ry, ry, ProjDist, FarClip);
      } /* End of 'UpdateProj' function */
    }; /* End of 'camera' class */

} /* end of 'mth' namespace */

#endif // !__mth_camera_h_

/* END OF 'mth_camera.h' FILE */
