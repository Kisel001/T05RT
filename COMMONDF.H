/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum.
 *    All rights reserved.
 ***************************************************************/

/* FILE NAME   : COMMONDF.H
 * PURPOSE     : Temporary OS depended implementation.
 * PROGRAMMER  : Vitaly Galinsky (VG4),
 *               Ivan Pashkov (IP5).
 * LAST UPDATE : 04.04.2024 (from 22.02.2000)
 * NOTE        : None (partial module prefix 'COM')
 *
 * Supported compiles:
 *
 * Old compillers:
 *   Turbo C/C++, Borland C++ - memory model Large.
 *   Watcom C/C++ - memory model Flat (32-bit protected mode
 *       with DOS4GW DOS extender), v.9-50 and later.
 *   and OpenGL
 * New compillers:
 *   Microsoft Visual C/C++ and compilers for Win32.
 * 
 * Old compilers supported for compatibility with old code
 *
 * [!]
 * For use old version of <commondf.h> without FLT, DBL, INT64, UINT64 types,
 * use macros COMDF_OLD.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 *
 * [PUBLIC]
 */

#ifndef _WWWCOMMONDF_H_
#define _WWWCOMMONDF_H_

#define COMMONDF_VERSION 202402L

#if (defined _MSC_VER) || (defined _WIN32)
#  ifdef _MSC_VER
#    pragma warning(disable : 4200 4244 4013 4018 4115 4761 4127 4305)
#    pragma warning(error : 4016 4027 4701)
#  endif /* _MSC_VER */
#  include <wcomdf.h>
#  include <windows.h>
#else /* _MSC_VER || _WIN32 */
   /* Inclide file for old compilers */
#  include <commondf\commondf.h>
#endif /* _MSC_VER || _WIN32 */

#endif /* _WWWCOMMONDF_H_ */

/* END OF 'COMMONDF.H' FILE */
