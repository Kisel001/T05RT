/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        mth_matr.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 22.07.2024
 * PURPOSE:     Base math matrix header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __mth_matr_h_
#define __mth_matr_h_

#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* Matr mul matr for double routine.
   * ARGUMENTS:
   *   - dest:
   *       DBL *mdst;
   *   - src1:
   *       const DBL *msrc1;
   *   - src2:
   *       const DBL *msrc2;
   * RETURNS: None.
   */ 
  extern "C" VOID MatrMulMatr( DBL *mdst, const DBL *msrc1, const DBL *msrc2 );

  /* Matrix 4x4 type */
  template<typename Type> 
    class matr
    {
    public:
      Type M[4][4]; // Matr components
    private:
      mutable Type InvM[4][4];        // Inverse matr components.
      mutable BOOL IsInverse = FALSE; // Matr inverse status

      /* Default constructor */
      matr()
      {
      } /* End of 'matr' function */

      /* Constructor by 16 components.
       * ARGUMENTS:
       *   - 16 components:
       *       const Type A00-A33;
       */
      matr( const Type A00, const Type A01, const Type A02, const Type A03,
            const Type A10, const Type A11, const Type A12, const Type A13, 
            const Type A20, const Type A21, const Type A22, const Type A23, 
            const Type A30, const Type A31, const Type A32, const Type A33 )
      {
        M[0][0] = A00;
        M[0][1] = A01;
        M[0][2] = A02;
        M[0][3] = A03;
        M[1][0] = A10;
        M[1][1] = A11;
        M[1][2] = A12;
        M[1][3] = A13;
        M[2][0] = A20;
        M[2][1] = A21;
        M[2][2] = A22;
        M[2][3] = A23;
        M[3][0] = A30;
        M[3][1] = A31;
        M[3][2] = A32;
        M[3][3] = A33;
      } /* End of 'matr' function */

      /* Constructor by 4 vector 4D.
       * ARGUMENTS:
       *   - 4 vectors:
       *       const vec4<Type> &V(0-3);
       */
      matr( const vec4<Type> &V0, const vec4<Type> &V1, const vec4<Type> &V2, const vec4<Type> &V3 )
      {
        std::memcpy(M[0], V0, sizeof(vec4<Type>));
        std::memcpy(M[1], V1, sizeof(vec4<Type>));
        std::memcpy(M[2], V2, sizeof(vec4<Type>));
        std::memcpy(M[3], V3, sizeof(vec4<Type>));
      } /* End of 'matr' function */

      /* Constructor by Type array.
       * ARGUMENTS:
       *   - array:
       *       const Type A[4][4];
       */
      matr( const Type A[4][4] )
      {
        std::memcpy(M[0], A[0], sizeof(matr<Type>));
      } /* End of 'matr' function */

      /* Get identity matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) Identity matrix;
       */
      static matr Identity()
      {
        return matr(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
      } /* End of 'Identity' function */

      /* Get translated matrix function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &T;
       * RETURNS:
       *   (matr) new matrix.
       */
      static matr Translate( const vec3<Type> &T )
      {
        return matr(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    T.X, T.Y, T.Z, 1);
      } /* End of 'Translate' function */

      /* Get scaling matrix function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &S;
       * RETURNS:
       *   (matr) scale matr.
       */
      static matr Scale( const vec3<Type> &S )
      {
        return matr(S.X, 0, 0, 0,
                    0, S.Y, 0, 0,
                    0, 0, S.Z, 0,
                    0, 0, 0, 1);
      } /* End of 'Scale' function */

      /* Matrix of rotate around X to angle function.
       * ARGUMENTS:
       *   - angle in degree:
       *       const Type AngleInDegree;
       * RETURNS:
       *   (matr) new matrix.
       */
      static matr RotateX( const Type AngleInDegree )
      {
        Type
          an = D2R(AngleInDegree),
          c = cos(an),
          s = sin(an);

        return matr(1, 0, 0, 0,
                    0, c, s, 0,
                    0, -s, c, 0,
                    0, 0, 0, 1);
      } /* End of 'RotateX' function */

      /* Matrix of rotate around Y to angle function.
       * ARGUMENTS:
       *   - angle in degree:
       *       const Type AngleInDegree;
       * RETURNS:
       *   (matr) new matrix.
       */
      static matr RotateY( const Type AngleInDegree )
      {
        Type
          an = D2R(AngleInDegree),
          c = cos(an),
          s = sin(an);

        return matr(c, 0, -s, 0,
                    0, 1, 0, 0,
                    s, 0, c, 0,
                    0, 0, 0, 1);
      } /* End of 'RotateY' function */

      /* Matrix of rotate around Z to angle function.
       * ARGUMENTS:
       *   - angle in degree:
       *       const Type AngleInDegree;
       * RETURNS:
       *   (matr) new matrix.
       */
      static matr RotateZ( const Type AngleInDegree )
      {
        Type
          an = D2R(AngleInDegree),
          c = cos(an),
          s = sin(an);

        return matr(c, s, 0, 0,
                    -s, c, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
      } /* End of 'RotateZ' function */

      /* Matrix of Rotate around Vector to angle function.
       * ARGUMENTS:
       *   - angle in degree:
       *       const Type AngleInDegree;
       *   - vector of rotate:
       *       const vec3<Type> &R;
       * RETURNS:
       *   (matr) Rotated Matrix.
       */
      static matr Rotate( const Type AngleInDegree, const vec3<Type> &R )
      {
        FLT
          A = D2R(AngleInDegree),
          s = sin(A),
          c = cos(A);
        vec3<Type> V = R.Normalizing();
        
        return matr(c + V.X * V.X * (1 - c),
                    V.X * V.Y * (1 - c) + V.Z * s,
                    V.X * V.Z * (1 - c) - V.Y * s, 
                    0,
                    V.Y * V.X * (1 - c) - V.Z * s,
                    c + V.Y * V.Y * (1 - c),
                    V.Y * V.Z * (1 - c) + V.X * s, 
                    0,
                    V.Z * V.X * (1 - c) + V.Y * s,
                    V.Z * V.Y * (1 - c) - V.X * s, 
                    c + V.Z * V.Z * (1 - c), 0,
                    0, 
                    0, 
                    0, 
                    1);
      } /* End of 'Rotate' function */

      /* Multiplicate two matrixes function.
       * ARGUMENTS: 
       *   - second matrix:
       *       const matr &M;
       * RETURNS:
       *   (MATR) result matrix.
       */
      matr operator*( const matr &M ) const 
      {
        return
          matr(M[0][0] * M.M[0][0] + M[0][1] * M.M[1][0] + M[0][2] * M.M[2][0] + M[0][3] * M.M[3][0],
               M[0][0] * M.M[0][1] + M[0][1] * M.M[1][1] + M[0][2] * M.M[2][1] + M[0][3] * M.M[3][1],
               M[0][0] * M.M[0][2] + M[0][1] * M.M[1][2] + M[0][2] * M.M[2][2] + M[0][3] * M.M[3][2],
               M[0][0] * M.M[0][3] + M[0][1] * M.M[1][3] + M[0][2] * M.M[2][3] + M[0][3] * M.M[3][3],

               M[1][0] * M.M[0][0] + M[1][1] * M.M[1][0] + M[1][2] * M.M[2][0] + M[1][3] * M.M[3][0],
               M[1][0] * M.M[0][1] + M[1][1] * M.M[1][1] + M[1][2] * M.M[2][1] + M[1][3] * M.M[3][1],
               M[1][0] * M.M[0][2] + M[1][1] * M.M[1][2] + M[1][2] * M.M[2][2] + M[1][3] * M.M[3][2],
               M[1][0] * M.M[0][3] + M[1][1] * M.M[1][3] + M[1][2] * M.M[2][3] + M[1][3] * M.M[3][3],

               M[2][0] * M.M[0][0] + M[2][1] * M.M[1][0] + M[2][2] * M.M[2][0] + M[2][3] * M.M[3][0],
               M[2][0] * M.M[0][1] + M[2][1] * M.M[1][1] + M[2][2] * M.M[2][1] + M[2][3] * M.M[3][1],
               M[2][0] * M.M[0][2] + M[2][1] * M.M[1][2] + M[2][2] * M.M[2][2] + M[2][3] * M.M[3][2],
               M[2][0] * M.M[0][3] + M[2][1] * M.M[1][3] + M[2][2] * M.M[2][3] + M[2][3] * M.M[3][3],

               M[3][0] * M.M[0][0] + M[3][1] * M.M[1][0] + M[3][2] * M.M[2][0] + M[3][3] * M.M[3][0],
               M[3][0] * M.M[0][1] + M[3][1] * M.M[1][1] + M[3][2] * M.M[2][1] + M[3][3] * M.M[3][1],
               M[3][0] * M.M[0][2] + M[3][1] * M.M[1][2] + M[3][2] * M.M[2][2] + M[3][3] * M.M[3][2],
               M[3][0] * M.M[0][3] + M[3][1] * M.M[1][3] + M[3][2] * M.M[2][3] + M[3][3] * M.M[3][3]);
      } /* End of 'operator*' function */

      /* Matrix transponce function.
       * ARGUMENTS: None
       * RETURNS:
       *   (matr) Result matrix.
       */
      matr Transpose() const
      {
        return matr(M[0][0], M[1][0], M[2][0], M[3][0],
                    M[0][1], M[1][1], M[2][1], M[3][1],
                    M[0][2], M[1][2], M[2][2], M[3][2],
                    M[0][3], M[1][3], M[2][3], M[3][3]);
      } /* End of 'Transponce' function */

      /* Matrix 3*3 determination function.
       * ARGUMENTS:
       *   - arguments of matrix:
       *       FLT A11 - A33;
       * RETURNS:
       *   (FLT) result of determination matrix 3*3.
       */
      static Type Determ3x3( Type A11, Type A12, Type A13,
                             Type A21, Type A22, Type A23,
                             Type A31, Type A32, Type A33 )
      {
        return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
               A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
      } /* End of 'Determ3x3' function */

      /* Matrix 4*4 determination function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) result of determination matrix 4*4.
       */
      Type operator!() const
      {
        return
          +M[0][0] * Determ3x3(M[1][1], M[1][2], M[1][3],
                               M[2][1], M[2][2], M[2][3],
                               M[3][1], M[3][2], M[3][3]) +
          -M[0][1] * Determ3x3(M[1][0], M[1][2], M[1][3],
                               M[2][0], M[2][2], M[2][3],
                               M[3][0], M[3][2], M[3][3]) +
          +M[0][2] * Determ3x3(M[1][0], M[1][1], M[1][3],
                               M[2][0], M[2][1], M[2][3],
                               M[3][0], M[3][1], M[3][3]) +
          -M[0][3] * Determ3x3(M[1][0], M[1][1], M[1][2],
                               M[2][0], M[2][1], M[2][2],
                               M[3][0], M[3][1], M[3][2]);
      } /* End of 'operator!' function */

      /* Inverse of matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (MATR) Inverse Matrix.
       */
      matr Inverse() const
      {
        FLT det = !(*this);
        matr<Type> r;
        static const INT
          s[] = {1, -1},
          P[][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};
        INT
          i, j;

        if (det == 0)
          return Identity();

        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++)
            r.M[j][i] =
              s[(i + j) % 2] *
              Determ3x3(M[P[i][0]][P[j][0]], M[P[i][0]][P[j][1]], M[P[i][0]][P[j][2]],
                        M[P[i][1]][P[j][0]], M[P[i][1]][P[j][1]], M[P[i][1]][P[j][2]],
                        M[P[i][2]][P[j][0]], M[P[i][2]][P[j][1]], M[P[i][2]][P[j][2]]) / det;

        return r;
      } /* End of 'Inverse' function */

      /* Matrix look-at viewer setup function.
       * ARGUMENTS:
       *   - viewer position, look-at point, approximate up direction:
       *       const vec3<Type> & Loc, At, Up1;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr View( const vec3<Type> &Loc, const vec3<Type> &At, const vec3<Type> Up1 )
      {
        vec3<Type>
          Dir = (At % Loc).Normalize(),
          Right = (Dir % Up1).Normalize(),
          Up = (Right % Dir).Normalize();
        
        return
          matr(Right.X, Up.X, -Dir.X, 0, 
               Right.Y, Up.Y, -Dir.Y, 0,
               Right.Z, Up.Z, -Dir.Z, 0,
              -(Loc & Right), -(Loc & Up), -(Loc & Dir), 1);
      } /* End of 'View' function */

      /* Frustum projection matrix function.
       * ARGUMENTS:
       *   - parametrs of projection:
       *       const FLT L, R, B, T, N, F;
       * RETURNS:
       *   (matr) new matrix.
       */
      static matr Frustum( const FLT L, const FLT R, const FLT B, const FLT T, const FLT N, const FLT F )
      {
        return matr(2 * N / (R - L), 0, 0, 0,
                    0, 2 * N / (T - B), 0, 0,
                    (R + L) / (R - L), (T + B) / (T - B), -(F + N) / (F - N), -1,
                    0, 0, -2 * N * F / (F - N), 0);
      } /* End of 'Frustum' function */

      /* Ortho projection matrix function.
       * ARGUMENTS:
       *   - Parametrs of projection:
       *       FLT left (L), right (R), bottom (B), top (T), near (N), far (F);
       * RETURNS:
       *   (matr) New matrix.
       */
      static matr Ortho( FLT L, FLT R, FLT B, FLT T, FLT N, FLT F )
      {
        return matr(2 / (R - L), 0, 0, 0,
                    0, 2 / (T - B), 0, 0,
                    0, 0, -2 / (F - N), 0,
                   -(R + L) / (R - L), -(T + B) / (T - B), -(F + N) / (F - N), 1);
      } /* End of 'Ortho' function */

      /* Point radius-vector transformation by matrix function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) New vector.
       */
      vec3<Type> TransformPoint( const vec3<Type> &V ) const
      {
        return vec3<Type>((V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + M[3][0]),
                          (V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + M[3][1]),
                          (V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + M[3][2]));
      } /* End of 'TransformPoint' function */

      /* Transform vector by Matrix function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) New Vector.
       */
      vec3<Type> TransformVector( const vec3<Type> &V ) const
      {
        return vec3<Type>(V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0],
                          V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1],
                          V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2]);
      } /* End of 'TransformVector' function */

      /* Transform vector by Matrix 4 * 3 function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) New Vector.
       */
      vec3<Type> TransformNormal( const vec3<Type> &V ) const
      {
        matr m = this->Transpose().Inverse();

        return vec3<Type>(V.X * m.M[0][0] + V.Y * m.M[1][0] + V.Z * m.M[2][0],
                          V.X * m.M[0][1] + V.Y * m.M[1][1] + V.Z * m.M[2][1],
                          V.X * m.M[0][2] + V.Y * m.M[1][2] + V.Z * m.M[2][2]);
      } /* End of 'TransformVector' function */

      /* Transform 4x4 vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &V;
       * RETURNS: New Vector.
       */
      vec3<Type> Transform4x4( const vec3<Type> &V ) const
      {
        FLT w = V.X * M[0][3] + V.Y * M[1][3] + V.Z * M[2][3] + M[3][3];

        return vec3<Type>((V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + M[3][0]) / w,
                          (V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + M[3][1]) / w,
                          (V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + M[3][2]) / w);
      } /* End of 'Transform4x4' function */

      /* Transform 4x4 vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<Type> &V;
       * RETURNS: New Vector.
       */
      vec4<Type> Transform4x4( const vec4<Type> &V ) const
      {
        return vec4<Type>((V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + V.W * M[3][0]),
                          (V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + V.W * M[3][1]),
                          (V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + V.W * M[3][2]),
                          (V.X * M[0][3] + V.Y * M[1][3] + V.Z * M[2][3] + V.W * M[3][3]));
      } /* End of 'Transform4x4' function */

      /* Get Type-pointer to matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type *) pointer to first element
       */
      operator Type *()
      {
        return &this->M[0][0];
      } /* End of 'operator Type *' function*/

      /* Get matrix line function.
       * ARGUMENTS:
       *   - number of line:
       *       const INT Num;
       * RETURNS:
       *   (Type *) pointer to line.
       */
      Type * operator[]( const INT Num )
      {
        assert(Num >= 0 && Num <= 3);

        return M[Num];
      } /* End of 'operator[]' function */

      /* Get const matrix line function.
       * ARGUMENTS:
       *   - number of line:
       *       const INT Num;
       * RETURNS:
       *   (Type *) pointer to line.
       */
      const Type * operator[]( const INT Num ) const
      {
        assert(Num >= 0 && Num <= 3);

        return M[Num];
      } /* End of 'operator[]' function */

    }; /* End of 'matr' class */

  /* Matrix 4x4 type */
  template<> 
    class matr<DBL>
    {
    public:
      DBL M[4][4]; // Matr components
    private:
#if 0
      mutable DBL InvM[4][4];         // Inverse matr components.
      mutable BOOL IsInverse = FALSE; // Matr inverse status
#endif
    public:

      /* Default constructor */
      matr()
      {
      } /* End of 'matr' function */

      /* Constructor by 16 components.
       * ARGUMENTS:
       *   - 16 components:
       *       const DBL A00-A33;
       */
      matr( const DBL A00, const DBL A01, const DBL A02, const DBL A03,
            const DBL A10, const DBL A11, const DBL A12, const DBL A13, 
            const DBL A20, const DBL A21, const DBL A22, const DBL A23, 
            const DBL A30, const DBL A31, const DBL A32, const DBL A33 )
      {
        M[0][0] = A00;
        M[0][1] = A01;
        M[0][2] = A02;
        M[0][3] = A03;
        M[1][0] = A10;
        M[1][1] = A11;
        M[1][2] = A12;
        M[1][3] = A13;
        M[2][0] = A20;
        M[2][1] = A21;
        M[2][2] = A22;
        M[2][3] = A23;
        M[3][0] = A30;
        M[3][1] = A31;
        M[3][2] = A32;
        M[3][3] = A33;
      } /* End of 'matr' function */

      /* Constructor by 4 vector 4D.
       * ARGUMENTS:
       *   - 4 vectors:
       *       const vec4<DBL> &V(0-3);
       */
      matr( const vec4<DBL> &V0, const vec4<DBL> &V1, const vec4<DBL> &V2, const vec4<DBL> &V3 )
      {
        std::memcpy(M[0], &V0, sizeof(vec4<DBL>));
        std::memcpy(M[1], &V1, sizeof(vec4<DBL>));
        std::memcpy(M[2], &V2, sizeof(vec4<DBL>));
        std::memcpy(M[3], &V3, sizeof(vec4<DBL>));
      } /* End of 'matr' function */

      /* Constructor by DBL array.
       * ARGUMENTS:
       *   - array:
       *       const DBL A[4][4];
       */
      matr( const DBL A[4][4] )
      {
        std::memcpy(M[0], A[0], sizeof(matr<DBL>));
      } /* End of 'matr' function */

      /* Get identity matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) Identity matrix;
       */
      static matr Identity()
      {
        return matr(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
      } /* End of 'Identity' function */

      /* Get translated matrix function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<DBL> &T;
       * RETURNS:
       *   (matr) new matrix.
       */
      static matr Translate( const vec3<DBL> &T )
      {
        return matr(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    T.X, T.Y, T.Z, 1);
      } /* End of 'Translate' function */

      /* Get scaling matrix function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<DBL> &S;
       * RETURNS:
       *   (matr) scale matr.
       */
      static matr Scale( const vec3<DBL> &S )
      {
        return matr(S.X, 0, 0, 0,
                    0, S.Y, 0, 0,
                    0, 0, S.Z, 0,
                    0, 0, 0, 1);
      } /* End of 'Scale' function */

      /* Matrix of rotate around X to angle function.
       * ARGUMENTS:
       *   - angle in degree:
       *       const DBL AngleInDegree;
       * RETURNS:
       *   (matr) new matrix.
       */
      static matr RotateX( const DBL AngleInDegree )
      {
        DBL
          an = D2R(AngleInDegree),
          c = cos(an),
          s = sin(an);

        return matr(1, 0, 0, 0,
                    0, c, s, 0,
                    0, -s, c, 0,
                    0, 0, 0, 1);
      } /* End of 'RotateX' function */

      /* Matrix of rotate around Y to angle function.
       * ARGUMENTS:
       *   - angle in degree:
       *       const DBL AngleInDegree;
       * RETURNS:
       *   (matr) new matrix.
       */
      static matr RotateY( const DBL AngleInDegree )
      {
        DBL
          an = D2R(AngleInDegree),
          c = cos(an),
          s = sin(an);

        return matr(c, 0, -s, 0,
                    0, 1, 0, 0,
                    s, 0, c, 0,
                    0, 0, 0, 1);
      } /* End of 'RotateY' function */

      /* Matrix of rotate around Z to angle function.
       * ARGUMENTS:
       *   - angle in degree:
       *       const DBL AngleInDegree;
       * RETURNS:
       *   (matr) new matrix.
       */
      static matr RotateZ( const DBL AngleInDegree )
      {
        DBL
          an = D2R(AngleInDegree),
          c = cos(an),
          s = sin(an);

        return matr(c, s, 0, 0,
                    -s, c, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
      } /* End of 'RotateZ' function */

      /* Matrix of Rotate around Vector to angle function.
       * ARGUMENTS:
       *   - angle in degree:
       *       const DBL AngleInDegree;
       *   - vector of rotate:
       *       const vec3<DBL> &R;
       * RETURNS:
       *   (matr) Rotated Matrix.
       */
      static matr Rotate( const DBL AngleInDegree, const vec3<DBL> &R )
      {
        FLT
          A = D2R(AngleInDegree),
          s = sin(A),
          c = cos(A);
        vec3<DBL> V = R.Normalizing();
        
        return matr(c + V.X * V.X * (1 - c),
                    V.X * V.Y * (1 - c) + V.Z * s,
                    V.X * V.Z * (1 - c) - V.Y * s, 
                    0,
                    V.Y * V.X * (1 - c) - V.Z * s,
                    c + V.Y * V.Y * (1 - c),
                    V.Y * V.Z * (1 - c) + V.X * s, 
                    0,
                    V.Z * V.X * (1 - c) + V.Y * s,
                    V.Z * V.Y * (1 - c) - V.X * s, 
                    c + V.Z * V.Z * (1 - c), 0,
                    0, 
                    0, 
                    0, 
                    1);
      } /* End of 'Rotate' function */

      /* Multiplicate two matrixes function.
       * ARGUMENTS: 
       *   - second matrix:
       *       const matr &M1;
       * RETURNS:
       *   (MATR) result matrix.
       */
      matr operator*( const matr &M1 ) const 
      {
        matr C;

        __m256d row1 = _mm256_load_pd(&M1.M[0][0]);
        __m256d row2 = _mm256_load_pd(&M1.M[1][0]);
        __m256d row3 = _mm256_load_pd(&M1.M[2][0]);
        __m256d row4 = _mm256_load_pd(&M1.M[3][0]);

        for (INT i = 0; i < 4; ++i)
        {
          __m256d brod1 = _mm256_broadcast_sd(&M[i][0]);
          __m256d brod2 = _mm256_broadcast_sd(&M[i][1]);
          __m256d brod3 = _mm256_broadcast_sd(&M[i][2]);
          __m256d brod4 = _mm256_broadcast_sd(&M[i][3]);
          __m256d row = _mm256_add_pd(_mm256_add_pd(_mm256_mul_pd(brod1, row1),
                                                    _mm256_mul_pd(brod2, row2)),
                                      _mm256_add_pd(_mm256_mul_pd(brod3, row3),
                                                    _mm256_mul_pd(brod4, row4)));

          _mm256_store_pd(&C.M[i][0], row);
        }

        return C;
      } /* End of 'operator*' function */

      /* Multiplicate two matrixes function.
       * ARGUMENTS: 
       *   - second matrix:
       *       const matr &M1;
       * RETURNS:
       *   (MATR) result matrix.
       */
      __declspec(noinline) static VOID matrmulmatr( matr *MRes, matr *M1, matr *M2 )
      {
        __m256d row1 = _mm256_load_pd(&M2->M[0][0]);
        __m256d row2 = _mm256_load_pd(&M2->M[1][0]);
        __m256d row3 = _mm256_load_pd(&M2->M[2][0]);
        __m256d row4 = _mm256_load_pd(&M2->M[3][0]);

        for (INT i = 0; i < 4; ++i)
        {
          __m256d brod1 = _mm256_broadcast_sd(&M1->M[i][0]);
          __m256d brod2 = _mm256_broadcast_sd(&M1->M[i][1]);
          __m256d brod3 = _mm256_broadcast_sd(&M1->M[i][2]);
          __m256d brod4 = _mm256_broadcast_sd(&M1->M[i][3]);
          __m256d row   = _mm256_add_pd(_mm256_add_pd(_mm256_mul_pd(brod1, row1),
                                                      _mm256_mul_pd(brod2, row2)),
                                        _mm256_add_pd(_mm256_mul_pd(brod3, row3),
                                                      _mm256_mul_pd(brod4, row4)));

          _mm256_store_pd(&MRes->M[i][0], row);
        }
      } /* End of 'operator*' function */


      /* Matrix transponce function.
       * ARGUMENTS: None
       * RETURNS:
       *   (matr) Result matrix.
       */
      matr Transpose() const
      {
        return matr(M[0][0], M[1][0], M[2][0], M[3][0],
                    M[0][1], M[1][1], M[2][1], M[3][1],
                    M[0][2], M[1][2], M[2][2], M[3][2],
                    M[0][3], M[1][3], M[2][3], M[3][3]);
      } /* End of 'Transponce' function */

      /* Matrix 3*3 determination function.
       * ARGUMENTS:
       *   - arguments of matrix:
       *       FLT A11 - A33;
       * RETURNS:
       *   (FLT) result of determination matrix 3*3.
       */
      static DBL Determ3x3( DBL A11, DBL A12, DBL A13,
                             DBL A21, DBL A22, DBL A23,
                             DBL A31, DBL A32, DBL A33 )
      {
        return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 -
               A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
      } /* End of 'Determ3x3' function */

      /* Matrix 4*4 determination function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (DBL) result of determination matrix 4*4.
       */
      DBL operator!() const
      {
        return
          +M[0][0] * Determ3x3(M[1][1], M[1][2], M[1][3],
                               M[2][1], M[2][2], M[2][3],
                               M[3][1], M[3][2], M[3][3]) +
          -M[0][1] * Determ3x3(M[1][0], M[1][2], M[1][3],
                               M[2][0], M[2][2], M[2][3],
                               M[3][0], M[3][2], M[3][3]) +
          +M[0][2] * Determ3x3(M[1][0], M[1][1], M[1][3],
                               M[2][0], M[2][1], M[2][3],
                               M[3][0], M[3][1], M[3][3]) +
          -M[0][3] * Determ3x3(M[1][0], M[1][1], M[1][2],
                               M[2][0], M[2][1], M[2][2],
                               M[3][0], M[3][1], M[3][2]);
      } /* End of 'operator!' function */

      /* Inverse of matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (MATR) Inverse Matrix.
       */
      matr Inverse() const
      {
        FLT det = !(*this);
        matr<DBL> r;
        static const INT
          s[] = {1, -1},
          P[][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}};
        INT
          i, j;

        if (det == 0)
          return Identity();

        for (i = 0; i < 4; i++)
          for (j = 0; j < 4; j++)
            r.M[j][i] =
              s[(i + j) % 2] *
              Determ3x3(M[P[i][0]][P[j][0]], M[P[i][0]][P[j][1]], M[P[i][0]][P[j][2]],
                        M[P[i][1]][P[j][0]], M[P[i][1]][P[j][1]], M[P[i][1]][P[j][2]],
                        M[P[i][2]][P[j][0]], M[P[i][2]][P[j][1]], M[P[i][2]][P[j][2]]) / det;

        return r;
      } /* End of 'Inverse' function */

      /* Matrix look-at viewer setup function.
       * ARGUMENTS:
       *   - viewer position, look-at point, approximate up direction:
       *       const vec3<DBL> & Loc, At, Up1;
       * RETURNS:
       *   (matr) result matrix.
       */
      static matr View( const vec3<DBL> &Loc, const vec3<DBL> &At, const vec3<DBL> Up1 )
      {
        vec3<DBL>
          Dir = (At % Loc).Normalize(),
          Right = (Dir % Up1).Normalize(),
          Up = (Right % Dir).Normalize();
        
        return
          matr(Right.X, Up.X, -Dir.X, 0, 
               Right.Y, Up.Y, -Dir.Y, 0,
               Right.Z, Up.Z, -Dir.Z, 0,
              -(Loc & Right), -(Loc & Up), -(Loc & Dir), 1);
      } /* End of 'View' function */

      /* Frustum projection matrix function.
       * ARGUMENTS:
       *   - parametrs of projection:
       *       const FLT L, R, B, T, N, F;
       * RETURNS:
       *   (matr) new matrix.
       */
      static matr Frustum( const FLT L, const FLT R, const FLT B, const FLT T, const FLT N, const FLT F )
      {
        return matr(2 * N / (R - L), 0, 0, 0,
                    0, 2 * N / (T - B), 0, 0,
                    (R + L) / (R - L), (T + B) / (T - B), -(F + N) / (F - N), -1,
                    0, 0, -2 * N * F / (F - N), 0);
      } /* End of 'Frustum' function */

      /* Ortho projection matrix function.
       * ARGUMENTS:
       *   - Parametrs of projection:
       *       FLT left (L), right (R), bottom (B), top (T), near (N), far (F);
       * RETURNS:
       *   (matr) New matrix.
       */
      static matr Ortho( FLT L, FLT R, FLT B, FLT T, FLT N, FLT F )
      {
        return matr(2 / (R - L), 0, 0, 0,
                    0, 2 / (T - B), 0, 0,
                    0, 0, -2 / (F - N), 0,
                   -(R + L) / (R - L), -(T + B) / (T - B), -(F + N) / (F - N), 1);
      } /* End of 'Ortho' function */

      /* Point radius-vector transformation by matrix function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<DBL> &V;
       * RETURNS:
       *   (vec3<DBL>) New vector.
       */
      vec3<DBL> TransformPoint( const vec3<DBL> &V ) const
      {
        return vec3<DBL>((V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + M[3][0]),
                         (V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + M[3][1]),
                         (V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + M[3][2]));
      } /* End of 'TransformPoint' function */

      /* Transform vector by Matrix function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<DBL> &V;
       * RETURNS:
       *   (vec3<DBL>) New Vector.
       */
      vec3<DBL> TransformVector( const vec3<DBL> &V ) const
      {
        return vec3<DBL>(V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0],
                         V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1],
                         V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2]);
      } /* End of 'TransformVector' function */

      /* Transform vector by Matrix 4 * 3 function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<DBL> &V;
       * RETURNS:
       *   (vec3<DBL>) New Vector.
       */
      vec3<DBL> TransformNormal( const vec3<DBL> &V ) const
      {
        matr m = this->Transpose().Inverse();

        return vec3<DBL>(V.X * m.M[0][0] + V.Y * m.M[1][0] + V.Z * m.M[2][0],
                          V.X * m.M[0][1] + V.Y * m.M[1][1] + V.Z * m.M[2][1],
                          V.X * m.M[0][2] + V.Y * m.M[1][2] + V.Z * m.M[2][2]);
      } /* End of 'TransformVector' function */

      /* Transform 4x4 vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<DBL> &V;
       * RETURNS: New Vector.
       */
      vec3<DBL> Transform4x4( const vec3<DBL> &V ) const
      {
        FLT w = V.X * M[0][3] + V.Y * M[1][3] + V.Z * M[2][3] + M[3][3];

        return vec3<DBL>((V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + M[3][0]) / w,
                          (V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + M[3][1]) / w,
                          (V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + M[3][2]) / w);
      } /* End of 'Transform4x4' function */

      /* Transform 4x4 vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<DBL> &V;
       * RETURNS: New Vector.
       */
      vec4<DBL> Transform4x4( const vec4<DBL> &V ) const
      {
        return vec4<DBL>((V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + V.W * M[3][0]),
                          (V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + V.W * M[3][1]),
                          (V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + V.W * M[3][2]),
                          (V.X * M[0][3] + V.Y * M[1][3] + V.Z * M[2][3] + V.W * M[3][3]));
      } /* End of 'Transform4x4' function */

      /* Get DBL-pointer to matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (DBL *) pointer to first element
       */
      operator DBL *()
      {
        return &(this->M[0][0]);
      } /* End of 'operator DBL *' function*/

      /* Get matrix line function.
       * ARGUMENTS:
       *   - number of line:
       *       const INT Num;
       * RETURNS:
       *   (DBL *) pointer to line.
       */
      DBL * operator[]( const INT Num )
      {
        assert(Num >= 0 && Num <= 3);

        return M[Num];
      } /* End of 'operator[]' function */

      /* Get const matrix line function.
       * ARGUMENTS:
       *   - number of line:
       *       const INT Num;
       * RETURNS:
       *   (DBL *) pointer to line.
       */
      const DBL * operator[]( const INT Num ) const
      {
        assert(Num >= 0 && Num <= 3);

        return M[Num];
      } /* End of 'operator[]' function */

    }; /* End of 'matr<DBL>' class */

} /* end of 'mth' namespace */

/* Print to stdout vector data function.
 * ARGUMENTS:
 *   - out object:
 *       std::ostream & coutvar;
 *   - vector:
 *       mth::vec3<Type> &V;
 * RETURNS:
 *   (std::ostream &) out object.
 */
template<typename Type>
  inline std::ostream & operator<<( std::ostream & coutvar, mth::matr<Type> &M )
  {
    std::cout << '(';

    for (INT i = 0; i < 4; ++i)
    {
      for (INT j = 0; j < 4; ++j)
      {
        std::cout << M[i][j];
        if (i == 3 && j == 3)
          std::cout << ')';
        else
          std::cout << ',';
      }
      if (i != 3)
        std::cout << std::endl;
    }

    return coutvar;
  } /* End of 'operator<<' function */


#endif // !__mth_matr_h_

/* END OF 'mth_matr.h' FILE */
