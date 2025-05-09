/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        texture.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 05.09.2024
 * PURPOSE:     RayTracing's texture and texture manager header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __texture_h_
#define __texture_h_

#include "../rt_def.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    /* Texture class */
    class texture
    {
    private:
      DWORD *Buf; // Buffer of texture
      INT
        W, H;     // Size of image

    public:
      INT Num;    // Texture number in stock

      /* Default constructor */
      texture() : W(0), H(0), Buf(nullptr), Num(-1)
      {
      } /* End of 'texture' function */

      /* Constructor function.
       * ARGUMENTS:
       *   - other texture:
       *       texture &&Other;
       */
      texture( texture &&Other ) : W(Other.W), H(Other.H), Num(Other.Num)
      {
        std::swap(Other.Buf, Buf);
        Other.Buf = nullptr;
      } /* End of 'texture' function */

      /* Constructor function.
       * ARGUMENTS:
       *   - other texture:
       *       const texture &Other;
       */
      texture( const texture &Other ) : W(Other.W), H(Other.H), Num(Other.Num)
      {
        Buf = new DWORD[W * H];
        memcpy(Buf, Other.Buf, W * H * 4);
      } /* End of 'texture' function */

      /* Constructor by base parameters
       * ARGUMENTS:
       *   - size:
       *       INT NewW, INT NewH;
       *   - count of bytes to one pixel:
       *       INT C;
       *   - buffer with pixels:
       *       VOID *Buf;
       *   - number:
       *       INT TNum;
       */
      texture( INT NewW, INT NewH, INT C, const VOID *NewBuf, INT TNum ) : W(NewW), H(NewH), Buf(new DWORD[NewW * NewH]), Num(TNum)
      {
        DWORD *ptr = Buf;
        const BYTE *src = reinterpret_cast<const BYTE *>(NewBuf);

        switch (C)
        {
        // One byte texture: monochrome texture
        case 1:
          for (INT i = 0; i < NewW * NewH; ++i)
          {
            BYTE C = *src++;
            *ptr++ = COM_MAKELONG0123(C, C, C, 0);
          }
          break;

        // Three bytes texture: texture without alpha
        case 3:
          for (INT i = 0; i < NewW * NewH; ++i)
          {
            BYTE B = *src++;
            BYTE G = *src++;
            BYTE R = *src++;

            *ptr++ = COM_MAKELONG0123(B, G, R, 0);
          }
          break;

        // Four bytes texture: texture with alpha
        case 4:
          std::memcpy(Buf, NewBuf, (UINT_PTR)NewW * NewH * 4);
          break;

        // Invalide count of bytes for texture
        default:
          assert(0 && "Invalide texture!");
          break;
        }
      } /* End of 'texture' function */

      /* Delete texture function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID Free()
      {
        if (Buf != nullptr)
        {
          delete[] Buf;
          Buf = nullptr;
        }
      } /* End of '~texture' function */

      /* Texture destructor function */
      ~texture()
      {
        Free();
      } /* End of '~texture' function */

      /* Get color from texture function.
       * ARGUMENTS:
       *   - texture coordinates:
       *       vec2 TC (X, Y in [0, 1]);
       * RETURNS:
       *   (vec3) color.
       */
      vec3 GetColor( vec2 TC ) const
      {
        //std::swap(TC.X, TC.Y);
        TC.Y = 1 - TC.Y;

        static auto F = []( DBL X ) -> DBL
        {
          return X < 0 ? 0 : X > 1 ? 1 : X;
        };

#ifdef _DEBUG
        if (TC.X > 1 || TC.X < 0 || TC.Y > 1 || TC.Y < 0)
          return vec3(0);
#endif // _DEBUG

        DWORD color = Buf[(INT)round(F(TC.Y) * (H - 1)) * W + (INT)round(F(TC.X) * (W - 1))];
        DWORD b = color & 0xFF;
        DWORD g = (color & 0xFF00) >> 8;
        DWORD r = (color & 0xFF0000) >> 16;

        return vec3(r / 255., g / 255., b / 255.);
      } /* End of 'GetColor' function */
    }; /* End of 'texture' class */

    /* Texture manager class */
    class texture_manager
    {
    public:
      INT TexCount;                 // Total count of all textures, needing for set unique number for every textures.
      std::map<INT, texture> Stock; // Texture stock

      /* Default constructor */
      texture_manager() : TexCount(0)
      {
      } /* End of 'texture_manager' function */

      /* Add texture function.
       * ARGUMENTS:
       *   - size:
       *       INT W, INT H;
       *   - count of bytes to one pixel:
       *       INT C;
       *   - buffer with pixels:
       *       const VOID *Buf;
       * RETURNS:
       *   (texture *) new texture.
       */
      texture * AddTexture( INT W, INT H, INT C, const VOID *Buf )
      {
        texture tex{W, H, C, Buf, TexCount};
        return &(Stock.insert({TexCount++, tex}).first->second);
      } /* End of 'AddTexture' function */

      /* Add texture function.
       * ARGUMENTS:
       *   - size:
       *       INT W, INT H;
       *   - count of bytes to one pixel:
       *       INT C;
       *   - buffer with pixels:
       *       const VOID *Buf;
       * RETURNS:
       *   (INT) number of new texture.
       */
      INT AddTextureNo( INT W, INT H, INT C, const VOID *Buf )
      {
        texture tex {W, H, C, Buf, TexCount};
        Stock.insert({TexCount, tex});

        return TexCount++;
      } /* End of 'AddTextureNo' function */

      /* Get texture by number in stock function.
       * ARGUMENTS:
       *   - number of texture:
       *       INT No;
       * RETURNS:
       *   (texture *) pointer to texture, if number valid, or nullptr, if no valid.
       */
      texture * GetTexByNo( INT No )
      {
        auto find = Stock.find(No);

        if (find != Stock.end())
          return &find->second;
        return nullptr;
      } /* End of 'GetTexByNo' function */

      /* Delete texture function
       * ARGUMENTS:
       *   - pointer to texture:
       *       texture *Tex;
       * RETURNS: None.
       */
      VOID DeleteTexture( texture *Tex )
      {
        Tex->Free();

        if (auto find_entry = Stock.find(Tex->Num); 
            find_entry != Stock.end())
          Stock.erase(find_entry);
      } /* End of 'DeleteTexture' function */

      /* Clear texture stock function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID Clear( VOID )
      {
        Stock.clear();
        TexCount = 0;
      } /* End of 'Clear' function */

    }; /* End of 'texture_manager' class */

    /* Global variable with texture manager */
    inline texture_manager TexManager {};
  } /* End of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__texture_h_

/* END OF 'texture.h' FILE */
