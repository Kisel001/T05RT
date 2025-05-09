/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        mth_vec3.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 22.07.2024
 * PURPOSE:     Base math vector 3D header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* 3D vector type */
  template<typename Type> 
    class vec3
    {
    public:
      Type 
        X, Y, Z; // Vector components

      /* Default constructor */
      vec3() : X(0), Y(0), Z(0)
      {
      } /* End of 'vec3' function */

      /* Constructor by one component.
       * ARGUMENTS:
       *   - component:
       *       const Type N;
       */
      explicit vec3( const Type N ) : X(N), Y(N), Z(N)
      {
      } /* End of 'vec3' function */

      /* Constructor by 3 components.
       * ARGUMENTS:
       *   - components:
       *       const Type A, B, C;
       */
      vec3( const Type A, const Type B, const Type C ) : X(A), Y(B), Z(C)
      {
      } /* End of 'vec3' function */

      /* Random (components 0 - 1) vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) vector random.
       */
      static vec3 Rnd0()
      {
        return vec3(Type(rand()) / RAND_MAX,
                    Type(rand()) / RAND_MAX,
                    Type(rand()) / RAND_MAX);
      } /* End of 'Rnd0' function */

      /* Random (components -1 - 1) vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) vector random.
       */
      static vec3 Rnd1()
      {
        return vec3(2 * Type(rand()) / RAND_MAX - 1,
                    2 * Type(rand()) / RAND_MAX - 1,
                    2 * Type(rand()) / RAND_MAX - 1);
      } /* End of 'Rnd0' function */

      /* Vec add vec function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator+( const vec3 &V ) const
      {
        return vec3(X + V.X, Y + V.Y, Z + V.Z);
      } /* End of 'operator+' function */

      /* Vec sub vec function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator-( const vec3 &V ) const
      {
        return vec3(X - V.X, Y - V.Y, Z - V.Z);
      } /* End of 'operator-' function */

      /* Vec mul num function.
       * ARGUMENTS:
       *   - number:
       *       const Type N;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator*( const Type N ) const
      {
        return vec3(X * N, Y * N, Z * N);
      } /* End of 'operator+' function */

      /* Vec div num function.
       * ARGUMENTS:
       *   - number:
       *       const Type N;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator/( const Type N ) const
      {
        return vec3(X / N, Y / N, Z / N);
      } /* End of 'operator/' function */

      /* Vec length^2 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) length^2.
       */
      Type Len2() const
      {
        return X * X + Y * Y + Z * Z;
      } /* End of 'Len2' function */

      /* Vec length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) length.
       */
      Type operator!() const
      {
        return std::sqrt(X * X + Y * Y + Z * Z);
      } /* End of 'operator!' function */

      /* Vec dot vec function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (Type) vec dot vec.
       */
      Type operator&( const vec3 &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z;
      } /* End of 'operator&' function */

      /* Vec cross vec function.
       * ARGUMENTS:
       *   - second vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator%( const vec3 &V ) const
      {
        return vec3(Y * V.Z - Z * V.Y,
                    Z * V.X - X * V.Z,
                    X * V.Y - Y * V.X);
      } /* End of 'operator%' function */

      /* Vec mul num function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator*( const vec3 &V ) const
      {
        return vec3(X * V.X, Y * V.Y, Z * V.Z);
      } /* End of 'operator*' function */

      /* +V function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) vector.
       */
      vec3 operator+() const
      {
        return *this;
      } /* End of 'operator+' function */

      /* -V function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) -vector.
       */
      vec3 operator-() const
      {
        return vec3(-X, -Y, -Z);
      } /* End of 'operator-' function */

      /* Vec add vec eq function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) this vector.
       */
      vec3 & operator+=( const vec3 &V )
      {
        X += V.X;
        Y += V.Y;
        Z += V.Z;

        return *this;
      } /* End of 'operator+=' function */

      /* Vec sub vec eq function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) this vector.
       */
      vec3 & operator-=( const vec3 &V )
      {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;

        return *this;
      } /* End of 'operator-=' function */

      /* Vec mul vec eq function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) this vector.
       */
      vec3 & operator*=( const vec3 &V )
      {
        X *= V.X;
        Y *= V.Y;
        Z *= V.Z;

        return *this;
      } /* End of 'operator*=' function */

      /* Vec mul num eq function.
       * ARGUMENTS:
       *   - number:
       *       const Type N;
       * RETURNS:
       *   (vec3 &) this vector.
       */
      vec3 & operator*=( const Type N )
      {
        X *= N;
        Y *= N;
        Z *= N;

        return *this;
      } /* End of 'operator*=' function */

      /* Vec div num eq function.
       * ARGUMENTS:
       *   - number:
       *       const Type N;
       * RETURNS:
       *   (vec3 &) this vector.
       */
      vec3 & operator/=( const Type N )
      {
        X /= N;
        Y /= N;
        Z /= N;

        return *this;
      } /* End of 'operator/=' function */

      /* Normalize vector.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3 &) this vector.
       */
      vec3 & Normalize()
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
       *   (vec3) new normalize vector.
       */
      vec3 Normalizing() const
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
        default:
          assert(0 && "Incorrect access to field");
          return Z;
        }
      } /* End of 'operator[]' function */

      /* Get component function.
       * AGRUMENTS:
       *   - component number:
       *       INT i;
       * RETURNS:
       *   (Type &) V[i] component.
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
        default:
          assert(0 && "Incorrect access to field");
          return Type();
        }
      } /* End of 'operator[]' function */
      
      /* Reflect function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 Reflect( const vec3 &n ) const
      {
        return *this - (n * (*this & n) * 2);
      } /* End of 'Reflect' function */

      /* Get max component function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) max component.
       */
      Type MaxComponent( VOID ) const
      {
        Type MaxC = X;
        if (MaxC < Y)
          MaxC = Y;
        if (MaxC < Z)
          MaxC = Z;

        return MaxC;
      } /* End of 'MaxComponent' function */
    }; /* End of 'vec3' class */

#if 0
  /* 3D vector type :: double specifiaction */
  template<> 
    class __declspec(align(32)) vec3<DBL>
    {
    public:
      DBL 
        X, Y, Z; // Vector components
    private:
      DBL align_reserved_w = 0.0; // reserved for align (32 bytes)
    public:

      /* Default constructor */
      vec3() : X(0), Y(0), Z(0)
      {
      } /* End of 'vec3' function */

      /* Constructor by one component.
       * ARGUMENTS:
       *   - component:
       *       const DBL N;
       */
      explicit vec3( const DBL N ) : X(N), Y(N), Z(N)
      {
      } /* End of 'vec3' function */

      /* Constructor by 3 components.
       * ARGUMENTS:
       *   - components:
       *       const DBL A, B, C;
       */
      vec3( const DBL A, const DBL B, const DBL C ) : X(A), Y(B), Z(C)
      {
      } /* End of 'vec3' function */

    private:
      /* Constructor by AVX register.
       * ARGUMENTS:
       *   - avx register:
       *       __m256d C256
       */
      vec3( __m256d C256 )
      {
        _mm256_store_pd(&this->X, C256);
      } /* End of 'vec3' function */

      /* Constructor by SSE registers.
       * ARGUMENTS:
       *   - sse registers:
       *       __m128d C1, C2;
       */
      vec3( __m128d C1, __m128d C2 )
      {
        _mm_store_pd(&this->X, C1);
        _mm_store_pd(&this->Z, C2);
      } /* End of 'vec3' function */


    public:
      /* Random (components 0 - 1) vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) vector random.
       */
      static vec3 Rnd0()
      {
        return vec3(DBL(rand()) / RAND_MAX,
                    DBL(rand()) / RAND_MAX,
                    DBL(rand()) / RAND_MAX);
      } /* End of 'Rnd0' function */

      /* Random (components -1 - 1) vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) vector random.
       */
      static vec3 Rnd1()
      {
        return vec3(2 * DBL(rand()) / RAND_MAX - 1,
                    2 * DBL(rand()) / RAND_MAX - 1,
                    2 * DBL(rand()) / RAND_MAX - 1);
      } /* End of 'Rnd0' function */

      /* Vec add vec function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator+( const vec3 &V ) const
      {
        return vec3(_mm256_add_pd(_mm256_load_pd(&this->X), _mm256_load_pd(&V.X)));
      } /* End of 'operator+' function */

      /* Vec sub vec function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator-( const vec3 &V ) const
      {
        return vec3(_mm256_sub_pd(_mm256_load_pd(&this->X), _mm256_load_pd(&V.X)));
      } /* End of 'operator-' function */

      /* Vec mul num function.
       * ARGUMENTS:
       *   - number:
       *       const DBL N;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator*( const DBL N ) const
      {
        __m256d N1 = _mm256_broadcast_sd(&N);
        return vec3(_mm256_div_pd(_mm256_load_pd(&this->X), N1));
      } /* End of 'operator+' function */

      /* Vec div num function.
       * ARGUMENTS:
       *   - number:
       *       const DBL N;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator/( const DBL N ) const
      {
        return vec3(V.X / N, V.Y / N, V.Z / N);
#if 0
        __m256d N1 = _mm256_broadcast_sd(&N);
        return vec3(_mm256_div_pd(_mm256_load_pd(&this->X), N1));//, _mm_div_pd(_mm_load_pd(&this->Z), N1));
#endif
      } /* End of 'operator/' function */

      /* Vec length^2 function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (DBL) length^2.
       */
      DBL Len2() const
      {
        return X * X + Y * Y + Z * Z;
#if 0
        __m256d C = _mm256_load_pd(&this->X);
        __m256d C1 = _mm256_mul_pd(C, C);
        C1 = _mm256_hadd_pd(C1, C1);
        C1 = _mm256_hadd_pd(C1, C1);
#endif

        //return _mm256_cvtsd_f64(C1);
      } /* End of 'Len2' function */

      /* Vec length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (DBL) length.
       */
      DBL operator!() const
      {
        __m256d C = _mm256_load_pd(&this->X);
        __m256d C1 = _mm256_mul_pd(C, C);
        C1 = _mm256_hadd_pd(C1, C1);
        C1 = _mm256_hadd_pd(C1, C1);
        C1 = _mm256_sqrt_pd(C1);

        return _mm256_cvtsd_f64(C1);
      } /* End of 'operator!' function */

      /* Vec dot vec function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (DBL) vec dot vec.
       */
      DBL operator&( const vec3 &V ) const
      {
        //__m256d C1 = _mm256_mul_pd(_mm256_load_pd(&this->X), _mm256_load_pd(&V.X));
        //C1 = _mm256_hadd_pd(C1, C1);
        //C1 = _mm256_hadd_pd(C1, C1);

        //return _mm256_cvtsd_f64(C1);
        return X * V.X + Y * V.Y + Z * V.Z;
      } /* End of 'operator&' function */

      /* Vec cross vec function.
       * ARGUMENTS:
       *   - second vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator%( const vec3 &V ) const
      {
        return vec3(Y * V.Z - Z * V.Y,
                    Z * V.X - X * V.Z,
                    X * V.Y - Y * V.X);
      } /* End of 'operator%' function */

      /* Vec mul num function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator*( const vec3 &V ) const
      {
        return vec3(_mm256_mul_pd(_mm256_load_pd(&this->X), _mm256_load_pd(&V.X)));
      } /* End of 'operator*' function */

      /* +V function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) vector.
       */
      vec3 operator+() const
      {
        return *this;
      } /* End of 'operator+' function */

      /* -V function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) -vector.
       */
      vec3 operator-() const
      {
        return vec3(-X, -Y, -Z);
      } /* End of 'operator-' function */

      /* Vec add vec eq function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) this vector.
       */
      vec3 & operator+=( const vec3 &V )
      {
        return *this = vec3(_mm256_add_pd(_mm256_load_pd(&this->X), _mm256_load_pd(&V.X)));
      } /* End of 'operator+=' function */

      /* Vec sub vec eq function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) this vector.
       */
      vec3 & operator-=( const vec3 &V )
      {
        return *this = vec3(_mm256_sub_pd(_mm256_load_pd(&this->X), _mm256_load_pd(&V.X)));;
      } /* End of 'operator-=' function */

      /* Vec mul vec eq function.
       * ARGUMENTS:
       *   - other vector:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3 &) this vector.
       */
      vec3 & operator*=( const vec3 &V )
      {
        return *this = vec3(_mm256_mul_pd(_mm256_load_pd(&this->X), _mm256_load_pd(&V.X)));
      } /* End of 'operator*=' function */

      /* Vec mul num eq function.
       * ARGUMENTS:
       *   - number:
       *       const DBL N;
       * RETURNS:
       *   (vec3 &) this vector.
       */
      vec3 & operator*=( const DBL N )
      {
        __m128d N1 = _mm_load_sd(&N);
        return *this = vec3(_mm_mul_pd(_mm_load_pd(&this->X), N1), _mm_mul_pd(_mm_load_pd(&this->Z), N1));
      } /* End of 'operator*=' function */

      /* Vec div num eq function.
       * ARGUMENTS:
       *   - number:
       *       const DBL N;
       * RETURNS:
       *   (vec3 &) this vector.
       */
      vec3 & operator/=( const DBL N )
      {
        __m128d N1 = _mm_load_sd(&N);
        return *this = vec3(_mm_mul_pd(_mm_load_pd(&this->X), N1), _mm_mul_pd(_mm_load_pd(&this->Z), N1));
      } /* End of 'operator/=' function */

      /* Normalize vector.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3 &) this vector.
       */
      vec3 & Normalize()
      {
        DBL len2 = this->Len2();

#ifdef _DEBUG
        if (len2 == 0 || len2 == 1)
          return *this;
#endif // _DEBUG

        return *this /= std::sqrt(len2);
      } /* End of 'Normalize' function */

      /* Get normalize vector.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) new normalize vector.
       */
      vec3 Normalizing() const
      {
        DBL len2 = this->Len2();

#ifdef _DEBUG
        if (len2 == 0 || len2 == 1)
          return *this;
#endif // _DEBUG

        return *this / std::sqrt(len2);
      } /* End of 'Normalize' function */

      /* Get DBL-pointer to vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (DBL *) pointer to first element
       */
      operator DBL *()
      {
        return &this->X;
      } /* End of 'operator DBL *' function*/

      /* Get component function.
       * AGRUMENTS:
       *   - component number:
       *       INT i;
       * RETURNS:
       *   (DBL &) V[i] component.
       */
      DBL & operator[]( INT i )
      {
        switch (i)
        {
        case 0:
          return X;
        case 1:
          return Y;
        case 2:
          return Z;
        default:
          assert(0 && "Incorrect access to field");
          return Z;
        }
      } /* End of 'operator[]' function */

      /* Get component function.
       * AGRUMENTS:
       *   - component number:
       *       INT i;
       * RETURNS:
       *   (DBL &) V[i] component.
       */
      DBL operator[]( INT i ) const
      {
        switch (i)
        {
        case 0:
          return X;
        case 1:
          return Y;
        case 2:
          return Z;
        default:
          assert(0 && "Incorrect access to field");
          return DBL();
        }
      } /* End of 'operator[]' function */

    }; /* End of 'vec3<DBL>' class */
#endif
    
} /* end of 'mth' namespace */

/* Print to stdout vector data function.
 * ARGUMENTS:
 *   - out object:
 *       std::ostream & coutvar;
 *   - vector:
 *       const mth::vec3<Type> &V;
 * RETURNS:
 *   (std::ostream &) out object.
 */
template<typename Type>
  inline std::ostream & operator<<( std::ostream & coutvar, const mth::vec3<Type> &V )
  {
    coutvar << '(' << V.X << ',' << V.Y << ',' << V.Z << ')';
    return coutvar;
  } /* End of 'operator<<' function */

#endif // !__mth_vec3_h_

/* END OF 'mth_vec3.h' FILE */
