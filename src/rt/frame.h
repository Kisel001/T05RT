/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : frame.h
 * PURPOSE     : Raytracing project.
 *               Frame buffer class declaration module.
 * PROGRAMMER  : IP5.
 * LAST UPDATE : 24.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __frame_h_
#define __frame_h_

#include <mutex>
#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>

#include "mem/memtools.h"
#include "rt_def.h"

#pragma pack(push, 1)
#include <tgahead.h>
#pragma pack(pop)

/* Project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    /* Frame buffer handle class */
    class frame
    {
    private:
      DWORD *Pixels = nullptr; // Frame buffer pixels

      // Frame access mutex
      std::recursive_mutex frame_mutex;

    public:
      // Frame size
      INT W = 0, H = 0;

      /* Resize frame buffer function.
       * ARGUMENTS:
       *   - new frame size:
       *       INT NewW, NewH;
       * RETURNS: None.
       */
      VOID Resize( INT NewW, INT NewH )
      {
        // Lock access
        const std::lock_guard<std::recursive_mutex> lock(frame_mutex);

        if (Pixels != nullptr)
          delete[] Pixels;
        Pixels = nullptr;
        W = H = 0;
        if (NewW != 0 && NewH != 0)
        {
          Pixels = new DWORD[NewW * NewH];
          FillZero(Pixels, (UINT_PTR)NewW * NewH);
          //ZeroMemory(Pixels, NewW * NewH * 4);
          W = NewW;
          H = NewH;
        }
      } /* End of Resize' function */

      /* Put pixel with specified color function.
       * ARGUMENTS:
       *   - pixel coordinates:
       *       INT X, Y;
       *   - pixel color:
       *       DWORD Color;
       * RETURNS: None.
       */
      VOID PutPixel( INT X, INT Y, DWORD Color )
      {
        // Lock access
        const std::lock_guard<std::recursive_mutex> lock(frame_mutex);

        // Clipping
        if (X < 0 || Y < 0 || X >= W || Y >= H)
          return;

        // Set pixel color
        Pixels[Y * W + X] = Color;
      } /* End of 'PutPixel' function */

      /* Get pixel color function.
       * ARGUMENTS:
       *   - pixel coordinates:
       *       INT X, Y;
       * RETURNS:
       *   (DWORD) pixel color.
       */
      DWORD GetPixel( INT X, INT Y )
      {
        // Lock access
        const std::lock_guard<std::recursive_mutex> lock(frame_mutex);

        // Clipping
        if (X < 0 || Y < 0 || X >= W || Y >= H)
          return 0;

        // Set pixel color
        return Pixels[Y * W + X];
      } /* End of 'PutPixel' function */

      /* Fill frame with specified color function.
       * ARGUMENTS:
       *   - pixels color:
       *       DWORD Color;
       * RETURNS: None.
       */
      VOID Fill( DWORD Color )
      {
        // Lock access
        const std::lock_guard<std::recursive_mutex> lock(frame_mutex);

        // Set pixel color
        DMemset(Pixels, Color, (UINT_PTR)W * H);
  #if 0
        // Set pixel color
        INT n = W * H;
        DWORD *ptr = Pixels;
        while (n-- > 0)
          *ptr++ = Color;
  #endif
      } /* End of 'Fill' function */

      /* Blit frame to device context function.
       * ARGUMENTS:
       *   - device context:
       *       HDC hDC;
       *   - window coordinates:
       *       INT X, Y;
       *   - window rectangle size:
       *       INT DrawW, DrawH;
       *   - image draw offset:
       *       INT OffX, OffY;
       * RETURNS: None.
       */
      VOID Draw( HDC hDC, INT X, INT Y, INT DrawW, INT DrawH,
                 INT OffX = 0, INT OffY = 0 )
      {
        // Lock access
        const std::lock_guard<std::recursive_mutex> lock(frame_mutex);

        // Draw buffer through DIB
        BITMAPINFOHEADER bih {};
        bih.biSize = sizeof(BITMAPINFOHEADER);
        bih.biBitCount = 32;
        bih.biPlanes = 1;
        bih.biWidth = W;
        bih.biHeight = -H;
        bih.biSizeImage = W * H * 4;
        bih.biCompression = BI_RGB;
        bih.biClrUsed = 0;
        bih.biClrImportant = 0;
        bih.biXPelsPerMeter = 30;
        bih.biYPelsPerMeter = 30;
        SetStretchBltMode(hDC, COLORONCOLOR);
        StretchDIBits(hDC, X, Y, DrawW, DrawH, OffX, OffY, W, H, Pixels,
          (BITMAPINFO *)&bih, DIB_RGB_COLORS, SRCCOPY);
      } /* End of 'Draw' function */

      /* Convert float point 0..1 range color to DWORD function.
       * ARGUMENTS:
       *   - color RGB values:
       *       DBL R, G, B;
       * RETURNS:
       *   (DWORD) result packed color.
       */
      static DWORD ToRGB( DBL R, DBL G, DBL B )
      {
        auto clamp =
          []( FLT Value ) -> BYTE
          {
            if (Value < 0)
              return 0;
            if (Value > 1)
              return 255;
            return Value * 255;
          };
        return (clamp(R) << 16) | (clamp(G) << 8) | clamp(B);
      } /* End of 'ToRGB' function */

      /* Convert float point 0..1 range color to DWORD function.
       * ARGUMENTS:
       *   - color RGB values:
       *       const vec3 &V;
       * RETURNS:
       *   (DWORD) result packed color.
       */
      static DWORD ToRGB( const vec3 &V )
      {
        auto clamp =
          []( FLT Value ) -> BYTE
          {
            if (Value < 0)
              return 0;
            if (Value > 1)
              return 255;
            return Value * 255;
          };
        return (clamp(V.X) << 16) | (clamp(V.Y) << 8) | clamp(V.Z);
      } /* End of 'ToRGB' function */

      /* Class destructor */
      ~frame( VOID )
      {
        std::cout << "\nFrame destroyed\n";
        Resize(0, 0);
      } /* End of '~frame' function */

      /* Store frame buffer image to TGA file function.
       * ARGUMENTS:
       *   - file name:
       *       const std::string &FileName;
       *   - addition comments:
       *       const std::string &Comments;
       *   - render/job time (hours, minutes, seconds):
       *       const std::tuple<INT, INT, INT> &JobTime;
       * RETURNS:
       *   (BOOL) TRUE if success, FALSE otherwise.
       */
      BOOL SaveTGA( const std::string &FileName,
                    const std::string &Comments = "",
                    const std::tuple<INT, INT, INT> &JobTime = {0, 0, 0} )
      {
        // Lock access
        const std::lock_guard<std::recursive_mutex> lock(frame_mutex);

        std::fstream f(FileName, std::fstream::out | std::fstream::binary);
        if (!f.is_open())
          return FALSE;

        // Fill file header
        tgaFILEHEADER head {};
        INT len = (INT)Comments.length();

        if (len > 254)
          len = 255;
        else
          if (len != 0)
            len++;
        head.IDLength = len;
        head.ColorMapType = 0;
        head.ImageType = 2;
        head.BitsPerPixel = 32;
        head.Width = W;
        head.Height = H;
        head.ImageDescr = 1 << 5; // image start - left-top corner

        // Store header and comments
        f.write((CHAR *)&head, sizeof(head));
        if (len != 0)
          f.write(Comments.c_str(), (INT_PTR)len - 1), f.put(0);

        // Store image
        f.write((CHAR *)Pixels, (INT_PTR)W * H * 4);

        tgaEXTHEADER ext = {0};
        strcpy(ext.AuthorName, "IP5");
        strcpy(ext.SoftwareID, "CGSG RayTracing'2024-summer");
        strcpy(ext.AuthorComment, "CGSG forever!!!");
        ext.VersionNumber = 100;
        ext.GammaDenominator = 1;
        ext.GammaNumerator = 1;
        ext.PixelDenominator = 1;
        ext.PixelNumerator = 1;
        strcpy(ext.JobName, "CGSG Raytracing");

        ext.JobHour = std::get<0>(JobTime);
        ext.JobMinute = std::get<1>(JobTime);
        ext.JobSecond = std::get<2>(JobTime);
        f.write((CHAR *)&ext, sizeof(ext));

        tgaFILEFOOTER foot = {0};
        foot.ExtensionOffset = sizeof(head) + head.IDLength + (INT_PTR)4 * W * H;
        strncpy(foot.Signature, TGA_EXT_SIGNATURE, 18);
        f.write((CHAR *)&foot, sizeof(foot));

        f.close();
        return TRUE;
      } /* End of 'SaveTGA' function */

      /* Auto naming store frame buffer image to TGA file function.
       * ARGUMENTS:
       *   - addition comments:
       *       const std::string &Comments;
       *   - render/job time (hours, minutes, seconds):
       *       const std::tuple<INT, INT, INT> &JobTime;
       * RETURNS:
       *   (BOOL) TRUE if success, FALSE otherwise.
       */
      BOOL AutoSaveTGA( const std::string &Comments = "",
                        const std::tuple<INT, INT, INT> &JobTime = {0, 0, 0} )
      {
        SYSTEMTIME st;

        GetLocalTime(&st);
        CHAR Buf[300];

        std::string path("bin/images/AutoSave");
        std::filesystem:: create_directories(path);  // <filesystem>

        wsprintf(Buf, "%04d%02d%02d_%02d%02d%02d_%03d_%02d",
          st.wYear, st.wMonth, st.wDay, st.wHour,
          st.wMinute, st.wSecond, st.wMilliseconds,
          rand() % 90);
        return SaveTGA(path + "/" + Buf + ".tga", Comments, JobTime);
      } /* End of 'AutoSaveTGA' function */
    }; /* End of 'frame' class */
  } /* end of 'rt' namespace */
} /* end of 'virt' namespace */

#endif /* __frame_h_ */

/* END OF 'frame.h' FILE */
