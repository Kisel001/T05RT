/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        rt_win.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 23.07.2024
 * PURPOSE:     RayTracing's window addons functions header file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __rt_win_h_
#define __rt_win_h_

#include <iostream>

#include "win/win.h"
#include "frame.h"
#include "rt_scene.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    /* RayTracing window class */
    class rt_win : public win
    {
    public:
      frame Frame;
      camera Camera;
      scene Scene;

      /* Default constructor
       * ARGUMENTS:
       *   - instance:
       *       HINSTANCE hInstance;
       */
      rt_win( HINSTANCE hInstance );

      /* Default destructor */
      ~rt_win() override;

      /* Resize window.
       * ARGUMENTS:
       *   - new size:
       *       INT NewW, INT NewH;
       * RETURNS: None.
       */
      VOID Resize( INT NewW, INT NewH );

      /* Ray tracing animation render.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      VOID Render( VOID );

      /* WM_TIMER window message handle function.
       * ARGUMENTS:
       *   - specified the timer identifier.
       *       INT Id;
       * RETURNS: None.
       */    
      VOID OnTimer( INT Id ) override;

      /* WM_SIZE window message handle function.
       * ARGUMENTS:
       *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
       *       UINT State;
       *   - new width and height of client area:
       *       INT W, H;
       * RETURNS: None.
       */
      VOID OnSize( UINT State, INT W, INT H ) override;

      /* WM_PAINT window message handle function.
       * ARGUMENTS:
       *   - window device context:
       *       HDC hDC;
       *   - paint message structure pointer:
       *       PAINTSTRUCT *PS;
       * RETURNS: None.
       */
      VOID OnPaint( HDC hDC, PAINTSTRUCT *Ps ) override;

      /* WM_KEYDOWN window message handle function.
       * ARGUMENTS:
       *   - pressed key:
       *       WPARAM Key;
       *   - coordinates:
       *       LPARAM Coordinates;
       * RETURNS: None.
       */
      VOID OnKeydown( WPARAM Key, LPARAM Coordinates ) override;


      /* Other message function.
       * ARGUMENTS:
       *   - msg id:
       *       UINT Msg;
       *   - word param:
       *       WPARAM wParam;
       *   - long param:
       *       LPARAM lParam;
       * RETURNS:
       *   (LRESULT) result of working with message.
       */
      LRESULT OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam ) override
      {
        static BOOL DEBUG_MODE_PARAM = false;

        switch (Msg)
        {
        case WM_KEYDOWN:
          if (wParam == 'R' || wParam == 'D')
          {
            if (!Scene.IsRenderActive)
            {
              if (wParam == 'D')
                DEBUG_MODE_PARAM = TRUE;
              else
                DEBUG_MODE_PARAM = FALSE;

              Scene.IsRenderActive = TRUE;
              Scene.IsToBeStop = FALSE;
              Scene.IsReadyToFinish = FALSE;
              std::cout << std::endl << "Start render scene" << std::endl << ((wParam == 'D') ? "Debug Mode" : "Release mode") << std::endl;
              std::thread Th;
              Th = std::thread(
                [&]( VOID )
                {
                  LONG tt = clock();
                  Scene.Render(Camera, Frame, DEBUG_MODE_PARAM);
                  tt = clock() - tt;
                  INT Seconds = (INT)((DBL)tt / CLOCKS_PER_SEC);

                  std::cout <<
                    std::fixed << (DBL)tt / CLOCKS_PER_SEC <<
                    " :: " << std::setfill('0') << std::setw(2) <<
                                                   Seconds / 60 / 60 <<
                    ":" << std::setfill('0') << std::setw(2) <<
                                                   Seconds / 60 % 60 <<
                    ":" << std::setfill('0') << std::setw(2) <<
                                                   Seconds % 60 << "\r";
                  
                  if (wParam != 'D')
                    Frame.AutoSaveTGA("CGSG forever!!!",
                      {Seconds / 60 / 60, Seconds / 60 % 60, Seconds % 60});
                  InvalidateRect(hWnd, NULL, FALSE);
                  UpdateWindow(hWnd);
                  Scene.IsRenderActive = FALSE;
                  Scene.IsToBeStop = FALSE;
                  Scene.IsReadyToFinish = TRUE;
                });
              Th.detach();
            }
          }
          else if (wParam == VK_ESCAPE)
          {
            if (!Scene.IsRenderActive)
              DestroyWindow(hWnd);
            else
              Scene.IsToBeStop = TRUE;
          }
          return 0;
        }
      return DefWindowProc(hWnd, Msg, wParam, lParam);
      }
    }; /* End of 'rt_win' class */
  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

#endif // !__rt_win_h_

/* END OF 'rt_win.h' FILE */
