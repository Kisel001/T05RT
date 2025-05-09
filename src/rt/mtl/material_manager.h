/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        material_manager.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 05.09.2024
 * PURPOSE:     RayTracing's material manager header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __material_manager_h_
#define __material_manager_h_

#include "../rt_def.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    /* Material manager class */
    class mtl_manager
    {
    public:
      INT MtlCount;                 // Total count of all surfaces, needing for set unique number for every surfaces.
      std::map<INT, surface> Stock; // Surface stock

      /* Default constructor */
      mtl_manager() : MtlCount(0)
      {
        for (auto &i : SurfaceLib)
          AddMaterial({i.SurfaceData.Ka, i.SurfaceData.Kd, i.SurfaceData.Ks, i.SurfaceData.Ph});
      } /* End of 'mtl_manager' function */

      /* Add surface function.
       * ARGUMENTS:
       *   - reference to source surface struct:
       *       const surface &Surf;
       * RETURNS:
       *   (surface *) pointer to surface.
       */
      surface * AddMaterial( const surface &Surf )
      {
        return &(Stock[MtlCount++] = Surf);
      } /* End of 'AddMaterial' function */

      /* Add surface function.
       * ARGUMENTS:
       *   - reference to source surface struct:
       *       const surface &Surf;
       * RETURNS:
       *   (INT) number of material in stock.
       */
      INT AddMaterialNo( const surface &Surf )
      {
        Stock[MtlCount] = Surf;
        return MtlCount++;
      } /* End of 'AddMaterial' function */

      /* Get surface by number in stock function.
       * ARGUMENTS:
       *   - number of surface:
       *       INT No;
       * RETURNS:
       *   (surface *) pointer to surface, if number valid, or nullptr, if no valid.
       */
      surface * GetSurfByNo( INT No )
      {
        auto find = Stock.find(No);

        if (find != Stock.end())
          return &Stock[No];
        return nullptr;
      } /* End of 'GetSurfByNo' function */

      /* Clear surface stock function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID Clear( VOID )
      {
        Stock.clear();
        MtlCount = 0;
      } /* End of 'Clear' function */

    }; /* End of 'mtl_manager' class */

    /* Global variable with material manager */
    inline mtl_manager MtlManager {};

  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__material_manager_h_

/* END OF 'material_manager.h' FILE */
