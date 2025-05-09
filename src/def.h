/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        def.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 22.07.2024
 * PURPOSE:     Base defines header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __def_h_
#define __def_h_

/* Debug memory allocation support */
#ifdef _DEBUG
#  define _CRTDBG_MAP_ALLOC
#  include <crtdbg.h>
static struct __Dummy
{
  /* Structure constructor */
  __Dummy( void )
  {
    _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG));
  } /* End of '__Dummy' constructor */
} __oops;
#endif /* _DEBUG */

#ifdef _DEBUG
#  ifdef _CRTDBG_MAP_ALLOC
#    define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#  endif /* _CRTDBG_MAP_ALLOC */
#endif /* _DEBUG */

#ifdef _MSC_VER
  /* Disable warnings:
   *   - 6031:
   *       no using return values (useless);
   *   - 26451:
   *       arithmetic overflow (useless);
   *   - 26495:
   *       not inited element of class (useless);
   *   - 28251:
   *       WinMain (?) (useless);
   *   - 26819:
   *       No-annotated translated control in switch operator (useless);
   */
#  pragma warning(disable: 6031 26451 26495 28251 6385 6386 26451 26819)
#endif // _MSC_VER

#include "mth/mth.h"
#include <vector>
#include <complex>
#include <list>
#include <map>

/* Declare x64 integer data types */
typedef unsigned long long UINT64;
typedef long long INT64;
typedef unsigned long long QWORD;

/* Base project namespace */
namespace pirt
{
#define QSNR_STKSIZ (8 * sizeof(VOID *) - 2)

  /* Swap two elements function.
   * ARGUMENTS:
   *   - reference to elements:
   *       Type *A, *B;
   * RETURNS: None.
   */
  template<typename Type>
    VOID Swap( Type *A, Type *B )
    {
      Type tmp = *A;
      *A = *B;
      *B = tmp;
    } /* End of 'Swap' function */

   template<typename Type>
     VOID QuickSortStartup( Type *Arr, UINT_PTR Size )
     {
       if (Size >= 2)
         QuickSortNoRec(Arr, Size);
     }

#if 0
    /* Quick sorting (without recurse) function.
     * ARGUMENTS:
     *   - array:
     *       Type *Arr;
     *   - count of elements:
     *       UINT_PTR Size;
     * RETURNS: None.
     */
    template<typename Type>
      void QuickSortSuper( Type *const base, size_t const num, int (__cdecl* const comp)( void const *A, void const *B ) )
      {
        // A stack for saving the sub-arrays yet to be processed:
        Type *lostk[QSNR_STKSIZ];
        Type *histk[QSNR_STKSIZ];
        INT stkptr = 0;

        if (num < 2)
            return;

        Type *lo = base;
        Type *hi = base + (num - 1);

recurse:
        size_t const size = (hi - lo) / width + 1;

        CHAR *mid = lo + (size / 2) * width;

        if (comp(lo, mid) > 0)
          Swap(lo, mid);

        if (comp(lo, hi) > 0)
          Swap(lo, hi);

        if (comp(mid, hi) > 0)
          Swap(mid, hi);

        CHAR *loguy = lo;
        CHAR *higuy = hi;

        while (TRUE)
        {
          if (mid > loguy)
          {
            do
            {
              loguy += width;
            } while (loguy < mid && comp(loguy, mid) <= 0);
          }
          if (mid <= loguy)
          {
            do
            {
              loguy += width;
            } while (loguy <= hi && comp(loguy, mid) <= 0);
          }
          do
          {
            higuy -= width;
          } while (higuy > mid && comp(higuy, mid) > 0);

          if (higuy < loguy)
            break;

          swap(loguy, higuy, width);
          if (mid == higuy)
            mid = loguy;
        }
        higuy += width;
        if (mid < higuy)
        {
          do
          {
            higuy -= width;
          } while (higuy > mid && comp(higuy, mid) == 0);
        }
        if (mid >= higuy)
        {
          do
          {
            higuy -= width;
          } while (higuy > lo && comp(higuy, mid) == 0);
        }
        if (higuy - lo >= hi - loguy)
        {
          if (lo < higuy)
          {
            lostk[stkptr] = lo;
            histk[stkptr] = higuy;
            ++stkptr;
          }
          if (loguy < hi)
          {
            lo = loguy;
            goto recurse;
          }
        }
        else
        {
          if (loguy < hi)
          {
            lostk[stkptr] = loguy;
            histk[stkptr] = hi;
            ++stkptr;
          }
          if (lo < higuy)
          {
            hi = higuy;
            goto recurse;
          }
        }
        if (--stkptr >= 0)
        {
          lo = lostk[stkptr];
          hi = histk[stkptr];
          goto recurse;
        }
      } /* End of 'QuickSortSuper' function */
#endif

  /* Stock class */
  template<typename T>
    class stock : public std::vector<T>
    {
    public:

      /* Put to stock element function.
       * ARGUMENTS:
       *   - element:
       *       const T &X;
       * RETURNS:
       *   (stock &) this stock.
       */
      stock & operator<<( const T &X )
      {
        this->push_back(X);
        return *this;
      } /* End of 'operator<<' function */

      /* Walk throw stock.
       * ARGUMENTS:
       *   - structure with method for walk:
       *       WalkType Walk;
       * RETURNS: None.
       */
      template<class WalkType>
        void Walk( WalkType Walk )
        {
          for (auto &x : *this)
            Walk(x);
        } /* End of 'Walk' function */
    }; /* End of 'stock' class */

  /* Vec2 declare types */
  typedef mth::vec2<DBL>  vec2;
  typedef mth::vec2<FLT>  fvec2;
  typedef mth::vec2<INT>  ivec2;
  typedef mth::vec2<BOOL> bvec2;

  /* Vec3 declare types */
  typedef mth::vec3<DBL>  vec3;
  typedef mth::vec3<FLT>  fvec3;
  typedef mth::vec3<INT>  ivec3;
  typedef mth::vec3<BOOL> bvec3;

  /* Vec4 declare types */
  typedef mth::vec4<DBL>  vec4;
  typedef mth::vec4<FLT>  fvec4;
  typedef mth::vec4<INT>  ivec4;
  typedef mth::vec4<BOOL> bvec4;

  /* Matrix declare types */
  typedef mth::matr<DBL>  matr;
  typedef mth::matr<FLT>  fmatr;
  typedef mth::matr<INT>  imatr;
  typedef mth::matr<BOOL> bmatr;

  typedef mth::ray<DBL> ray;
  typedef mth::camera<DBL> camera;
} /* end of 'pirt' namespace */


#endif // !__def_h_

/* END OF 'def.h' FILE */
