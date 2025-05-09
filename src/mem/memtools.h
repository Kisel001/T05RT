/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        memtools.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 23.07.2024
 * PURPOSE:     Work with memory routines header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __memtools_h_
#define __memtools_h_

#include "def.h"

/* Base project namespace */
namespace pirt
{
#ifdef _WIN64
  /* Fill memory by dword value routine.
   * ARGUMENTS:
   *   - destination:
   *       VOID *dest;
   *   - value:
   *       DWORD value;
   *   - count:
   *       UINT_PTR count;
   * RETURNS: 
   *   (VOID *) destination.
   */
  extern "C" VOID * DMemset( VOID *dest, DWORD value, UINT_PTR count );

  /* Fill memory by zero value routine.
   * ARGUMENTS:
   *   - destination:
   *       VOID *dest;
   *   - count (in dwords):
   *       UINT_PTR count;
   * RETURNS: 
   *   (VOID *) destination.
   */
  extern "C" VOID * FillZero( VOID *dest, UINT_PTR count );

  /* Fill memory by word value routine.
   * ARGUMENTS:
   *   - destination:
   *       VOID *dest;
   *   - value:
   *       WORD value;
   *   - count:
   *       UINT_PTR count;
   * RETURNS: 
   *   (VOID *) destination.
   */
  extern "C" VOID * WMemset( VOID *dest, WORD value, UINT_PTR count );

  /* Fill memory by qword value routine.
   * ARGUMENTS:
   *   - destination:
   *       VOID *dest;
   *   - value:
   *       UINT64 value;
   *   - count:
   *       UINT_PTR count;
   * RETURNS: 
   *   (VOID *) destination.
   */
  extern "C" VOID * QMemset( VOID *dest, UINT64 value, UINT_PTR count );

#else  // _WIN64

  /* Fill memory by dword value routine.
   * ARGUMENTS:
   *   - destination:
   *       VOID *dest;
   *   - value:
   *       DWORD value;
   *   - count:
   *       UINT_PTR count;
   * RETURNS: 
   *   (VOID *) destination.
   */
  inline VOID * DMemset( VOID *dest, UINT64 value, UINT_PTR count )
  {
    DWORD *ptr = reinterpret_cast<DWORD *>(dest);

    while (count--)
      *ptr++ = value;

    return dest;
  } /* End of 'DMemset' function */

  /* Fill memory by zero value routine.
   * ARGUMENTS:
   *   - destination:
   *       VOID *dest;
   *   - count (in dwords):
   *       UINT_PTR count;
   * RETURNS: 
   *   (VOID *) destination.
   */
  inline VOID * FillZero( VOID *dest, UINT_PTR count )
  {
    return DMemset(dest, 0, count);
  } /* End of 'FillZero' function */

  /* Fill memory by word value routine.
   * ARGUMENTS:
   *   - destination:
   *       VOID *dest;
   *   - value:
   *       WORD value;
   *   - count:
   *       UINT_PTR count;
   * RETURNS: 
   *   (VOID *) destination.
   */
  inline VOID * WMemset( VOID *dest, WORD value, UINT_PTR count )
  {
    WORD *ptr = reinterpret_cast<WORD *>(dest);

    while (count--)
      *ptr++ = value;

    return dest;
  } /* End of 'WMemset' function */

  /* Fill memory by qword value routine.
   * ARGUMENTS:
   *   - destination:
   *       VOID *dest;
   *   - value:
   *       UINT64 value;
   *   - count:
   *       UINT_PTR count;
   * RETURNS: 
   *   (VOID *) destination.
   */
  inline VOID * QMemset( VOID *dest, UINT64 value, UINT_PTR count )
  {
    QWORD *ptr = reinterpret_cast<QWORD *>(dest);

    while (count--)
      *ptr++ = value;

    return dest;
  } /* End of 'QMemset' function */

#endif // _WIN64
} /* end of 'pirt' namespace */

#endif // !__memtools_h_

/* END OF 'memtools.h' FILE */
