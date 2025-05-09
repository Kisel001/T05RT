/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        mth_vec4.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 22.07.2024
 * PURPOSE:     Base math vector 4D header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __mth_vec4_h_
#define __mth_vec4_h_

#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* 4D vector type */
  template<typename Type> 
    class vec4
    {
    public:
      Type 
        X, Y, Z, W; // Vector components

      /* Default constructor */
      vec4() : X(0), Y(0), Z(0), W(0)
      {
      } /* End of 'vec4' function */

      /* Constructor by one component.
       * ARGUMENTS:
       *   - component:
       *       const Type N;
       */
      explicit vec4( const Type N ) : X(N), Y(N), Z(N), W(N)
      {
      } /* End of 'vec4' function */

      /* Constructor by 4 components.
       * ARGUMENTS:
       *   - components:
       *       const Type A, B, C, D;
       */
      vec4( const Type A, const Type B, const Type C, const Type D ) : X(A), Y(B), Z(C), W(D)
      {
      } /* End of 'vec4' function */

      /* Random (components 0 - 1) vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) vector random.
       */
      static vec4 Rnd0()
      {
        return vec4(Type(rand()) / RAND_MAX,
                    Type(rand()) / RAND_MAX,
                    Type(rand()) / RAND_MAX,
                    Type(rand()) / RAND_MAX);
      } /* End of 'Rnd0' function */

      /* Random (components -1 - 1) vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) vector random.
       */
      static vec4 Rnd1()
      {
        return vec4(2 * Type(rand()) / RAND_MAX - 1,
                    2 * Type(rand()) / RAND_MAX - 1,
                    2 * Type(rand()) / RAND_MAX - 1,
                    2 * Type(rand()) / RAND_MAX - 1);
      } /* End of 'Rnd0' function */

      /* Vec add vec function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) new vector.
       */
      vec4 operator+( const vec4 &V ) const
      {
        return vec4(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
      } /* End of 'operator+' function */

      /* Vec sub vec function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) new vector.
       */
      vec4 operator-( const vec4 &V ) const
      {
        return vec4(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
      } /* End of 'operator-' function */

      /* Vec mul num function.
       * ARGUMENTS:
       *   - number:
       *       const Type N;
       * RETURNS:
       *   (vec4) new vector.
       */
      vec4 operator*( const Type N ) const
      {
        return vec4(X * N, Y * N, Z * N, W * N);
      } /* End of 'operator+' function */

      /* Vec div num function.
       * ARGUMENTS:
       *   - number:
       *       const Type N;
       * RETURNS:
       *   (vec4) new vector.
       */
      vec4 operator/( const Type N ) const
      {
        return vec4(X / N, Y / N, Z / N, W / N);
      } /* End of 'operator/' function */

      /* Vec length^2 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) length^2.
       */
      Type Len2() const
      {
        return X * X + Y * Y + Z * Z + W * W;
      } /* End of 'Len2' function */

      /* Vec length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) length.
       */
      Type operator!() const
      {
        return std::sqrt(X * X + Y * Y + Z * Z + W * W);
      } /* End of 'operator!' function */

      /* Vec dot vec function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec4 &V;
       * RETURNS:
       *   (Type) vec dot vec.
       */
      Type operator&( const vec4 &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z + W * V.W;
      } /* End of 'operator&' function */

      /* Vec mul num function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4) new vector.
       */
      vec4 operator*( const vec4 &V ) const
      {
        return vec4(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
      } /* End of 'operator*' function */

      /* +V function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) vector.
       */
      vec4 operator+() const
      {
        return *this;
      } /* End of 'operator+' function */

      /* -V function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) -vector.
       */
      vec4 operator-() const
      {
        return vec4(-X, -Y, -Z, -W);
      } /* End of 'operator-' function */

      /* Vec add vec eq function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) this vector.
       */
      vec4 & operator+=( const vec4 &V )
      {
        X += V.X;
        Y += V.Y;
        Z += V.Z;
        W += V.W;

        return *this;
      } /* End of 'operator+=' function */

      /* Vec sub vec eq function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) this vector.
       */
      vec4 & operator-=( const vec4 &V )
      {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;
        W -= V.W;

        return *this;
      } /* End of 'operator-=' function */

      /* Vec mul vec eq function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec4 &V;
       * RETURNS:
       *   (vec4 &) this vector.
       */
      vec4 & operator*=( const vec4 &V )
      {
        X *= V.X;
        Y *= V.Y;
        Z *= V.Z;
        W *= V.W;

        return *this;
      } /* End of 'operator*=' function */


      /* Vec mul num eq function.
       * ARGUMENTS:
       *   - number:
       *       const Type N;
       * RETURNS:
       *   (vec4 &) this vector.
       */
      vec4 & operator*=( const Type N )
      {
        X *= N;
        Y *= N;
        Z *= N;
        W *= N;

        return *this;
      } /* End of 'operator*=' function */

      /* Vec div num eq function.
       * ARGUMENTS:
       *   - number:
       *       const Type N;
       * RETURNS:
       *   (vec4 &) this vector.
       */
      vec4 & operator/=( const Type N )
      {
        X /= N;
        Y /= N;
        Z /= N;
        W /= N;

        return *this;
      } /* End of 'operator/=' function */

      /* Normalize vector.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4 &) this vector.
       */
      vec4 & Normalize()
      {
        Type len2 = this->Len2();

#ifdef _DEBUG
        if (len2 == 0 || len2 == 1)
          return *this;
#endif // _DEBUG

        return *this /= std::sqrt(len2);
      } /* End of 'Normalize' function */

      /* Get normalize vector.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec4) new normalize vector.
       */
      vec4 Normalizing() const
      {
        Type len2 = this->Len2();

#ifdef _DEBUG
        if (len2 == 0 || len2 == 1)
          return *this;
#endif // _DEBUG

        return *this / std::sqrt(len2);
      } /* End of 'Normalize' function */

      /* Get Type-pointer to vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type *) pointer to first element
       */
      operator Type *()
      {
        return &this->X;
      } /* End of 'operator Type *' function*/

      /* Get component function.
       * AGRUMENTS:
       *   - component number:
       *       INT i;
       * RETURNS:
       *   (Type &) V[i] component.
       */
      Type & operator[]( INT i )
      {
        switch (i)
        {
        case 0:
          return X;
        case 1:
          return Y;
        case 2:
          return Z;
        case 3:
          return W;
        default:
          assert(0 && "Incorrect access to field");
          return W;
        }
      } /* End of 'operator[]' function */

      /* Get const component function.
       * AGRUMENTS:
       *   - component number:
       *       INT i;
       * RETURNS:
       *   (Type) V[i] component.
       */
      Type operator[]( INT i ) const
      {
        switch (i)
        {
        case 0:
          return X;
        case 1:
          return Y;
        case 2:
          return Z;
        case 3:
          return W;
        default:
          assert(0 && "Incorrect access to field");
          return Type();
        }
      } /* End of 'operator[]' function */

    }; /* End of 'vec4' class */
} /* end of 'mth' namespace */

/* Print to stdout vector data function.
 * ARGUMENTS:
 *   - out object:
 *       std::ostream & coutvar;
 *   - vector:
 *       const mth::vec4<Type> &V;
 * RETURNS:
 *   (std::ostream &) out object.
 */
template<typename Type>
  inline std::ostream & operator<<( std::ostream & coutvar, const mth::vec4<Type> &V )
  {
    coutvar << '(' << V.X << ',' << V.Y << ',' << V.Z << ',' << V.W << ')';
    return coutvar;
  } /* End of 'operator<<' function */


#endif // !__mth_vec4_h_

/* END OF 'mth_vec4.h' FILE */
