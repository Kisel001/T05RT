/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        rt_win.cpp
 * PROGRAMMER:  IP5
 * LAST UPDATE: 09.09.2024
 * PURPOSE:     RayTracing's window addons functions file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "pirt.h"

/* Base project namespace */
namespace pirt
{
  /* Ray tracing namespace */
  namespace rt
  {
    /* Default constructor
     * ARGUMENTS:
     *   - instance:
     *       HINSTANCE hInstance;
     */
    rt_win::rt_win( HINSTANCE hInstance ) : win(hInstance), Scene(), Camera()
    {
      Camera.SetLocAtUp(vec3(3), vec3(0, 0, 0));

      srand(time(nullptr));

      // for (int i = 0; i < 500; ++i)
      // {
      //   vec3 S1 = vec3(rand() % 30 - 15, rand() % 30 - 15, rand() % 30 - 15);
      // 
      //   Scene << new box(S1, vec3(S1.X + 0.5, S1.Y + 0.5, S1.Z + 0.5), SurfaceLib[rand() % SurfaceLibSize].SurfaceName);
      // }

      // Scene << new csg::subtrack(new sphere(vec3(0, 0, 0), 5, "Emerald"),
      //                            new sphere(vec3(4, 0, 0), 5, "Emerald"));

#if 0
      shape *S1 = 
        new csg::intersection(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new box(vec3(-1), vec3(1), "Pearl"),
        new sphere(vec3(0, 0, 1), 0.20, "Black Rubber")),
        new sphere(vec3(1, -0.5, -0.5), 0.20, "Black Rubber")),
        new sphere(vec3(1, 0, 0), 0.20, "Black Rubber")),
        new sphere(vec3(1, 0.5, 0.5), 0.20, "Black Rubber")),
        new sphere(vec3(0.5, 1, 0.5), 0.20, "Black Rubber")),
        new sphere(vec3(-0.5, 1, -0.5), 0.20, "Black Rubber")),
        new sphere(vec3(0, 0, 1), 0.20, "Black Rubber")),
        new sphere(vec3(0), sqrt(3.0) - 0.30, "Pearl"));
      
      S1->SetMatr(matr::RotateY(25));
      
      shape *S2 =
        new csg::intersection(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new box(vec3(-1), vec3(1), "Pearl"),
        new sphere(vec3(0, 0, 1), 0.20, "Black Rubber")),
        new sphere(vec3(1, -0.5, -0.5), 0.20, "Black Rubber")),
        new sphere(vec3(1, 0, 0), 0.20, "Black Rubber")),
        new sphere(vec3(1, 0.5, 0.5), 0.20, "Black Rubber")),
        new sphere(vec3(0.5, 1, 0.5), 0.20, "Black Rubber")),
        new sphere(vec3(-0.5, 1, -0.5), 0.20, "Black Rubber")),
        new sphere(vec3(0, 0, 1), 0.20, "Black Rubber")),
        new sphere(vec3(0), sqrt(3.0) - 0.30, "Pearl"));

      shape *S3 =
        new csg::intersection(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new csg::subtrack(
        new box(vec3(-1), vec3(1), "Pearl"),
        new sphere(vec3(0, 0, 1), 0.20, "Black Rubber")),
        new sphere(vec3(1, -0.5, -0.5), 0.20, "Black Rubber")),
        new sphere(vec3(1, 0, 0), 0.20, "Black Rubber")),
        new sphere(vec3(1, 0.5, 0.5), 0.20, "Black Rubber")),
        new sphere(vec3(0.5, 1, 0.5), 0.20, "Black Rubber")),
        new sphere(vec3(-0.5, 1, -0.5), 0.20, "Black Rubber")),
        new sphere(vec3(0, 0, 1), 0.20, "Black Rubber")),
        new sphere(vec3(0), sqrt(3.0) - 0.30, "Pearl"));
      
      S2->SetMatr(matr::Translate(vec3(0, 0, 3)));
      S3->SetMatr(matr::Translate(vec3(0, 0, -3)));

      Scene << S1 << S2 << S3;
#endif
      //shape *SSS = new box(vec3(-1, -1, -1), vec3(1, 1, 1), "Gold");
      //SSS->SetMatr(matr::Rotate(60, vec3(1, 4, 6)));
      //Scene << SSS;

      // Scene << new tor(vec3(0, 5, 0), 2.0, 1.0);

      // shape *S1 = new box(vec3(-1, -1, -1), vec3(1, 1, 1), "Emerald");
      // shape *S2 = new box(vec3(-1, -1, -1), vec3(1, 1, 1), "Emerald");
      //
      // S1->SetMatr(matr::RotateY(15) *
      //             matr::Translate(vec3(5, 0, 0)));
      //
      // Scene << S1;
      // Scene << S2;

      shape *S = new plane(vec3(0, 1, 0), vec3(0, -1, 0));
      S->SetUsingModeFlag(true);
      Scene << S;
      
      // Scene << new plane(vec3(0, 1, 0), vec3(0, -1, 0), "bin/images/CGSG.g24");
      // Scene << new csg::bound(new objmodel("cow.obj"), new box(vec3(14, 14, 4), vec3(-9, -1, -4), "Gold"));
         
      shape *S1 = new g3dm("x6.g3dm");
      //S1->Surf = surface("Gold");
      S1->SetMatr(matr::RotateX(-90));
      Scene << S1;

      S1 = new box(vec3(-1, 0, 0), vec3(-2, 1, 1), "Gold");
      Scene << S1;

      // Scene << new box(vec3(0), vec3(1), "Emerald");
      // Scene << new csg::subtrack(new box(vec3(-1), vec3(1), "Gold"), new box(vec3(0), vec3(2), "Emerald"));
      // Scene << new tor(vec3(0, 5, 0), 2, 1);
      // Scene << new sphere(vec3(1.25, 0, 1.25), vec3(0.8, 0.47, 0.3), 1);
      // Scene << new sphere(vec3(-1.25, 0, -1.25), vec3(0.8, 0.47, 0.3), 0.47);
      // Scene << new sphere(vec3(10, 5, 10), 6, "Emerald");
      // Scene << new plane(vec3(0, 1, 0), vec3(0, 0.5, 0));
      // Scene << new box(vec3(0, 0, -5), vec3(1, 1, -4));
      // Scene << new box(vec3(3, 0, -5), vec3(4, 1, -4));
      // Scene << new triangle(vec3(-5, 5, -5), vec3(-4, 4, -4), vec3(-6, 2, -3));
      // Scene << new objmodel("cow.obj");
      Scene << new lights::point_light(0.7, 0.1, 0.1, vec3(1, 1, 1), vec3(3.5, 5, 5));
      // Scene << new lights::point_light(0.3, 0, 0, vec3(1, 1, 1), vec3(10, 10, 20));
      // Scene << new lights::point_light(1, 0, 0, vec3(1, 1, 1), vec3(0, 10, -20));

      // Scene << new triangle(vec3(3, 1, 0), vec3(0, -3, 0), vec3(2, -2, 2));
      // Scene << new plane((vec3(0.30, 0.47, 0.8)).Normalizing(), vec3(0, 0, 0));
      // Scene << new 
      // csg::bound(new objmodel("cow.obj"),
      // new box(vec3(-5, -5, -5), vec3(10, 10, 10)));
    } /* End of 'rt_win::rt_win' function */

    /* Default destructor */
    rt_win::~rt_win()
    {
      Scene.ClearScene();
      //delete[] Scene.Shapes;
      //Scene.Shapes.~vector;
    } /* End of 'rt_win::~rt_win' function */

    /* Resize window.
     * ARGUMENTS:
     *   - new size:
     *       INT NewW, INT NewH;
     * RETURNS: None.
     */
    VOID rt_win::Resize( INT NewW, INT NewH )
    {
      Frame.Resize(NewW, NewH);
      Camera.Resize(NewW, NewH);
    } /* End of 'rt_win::Resize' function */

    /* Ray tracing animation render.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID rt_win::Render( VOID )
    {
      //static BOOL IsRender = FALSE;
      Frame.Fill(0xFF000000);

#if 0
      for (INT ys = 0; ys < Frame.H; ys++)
        for (INT xs = 0; xs < Frame.W; xs++)
        {
          //ray R = Camera.FrameRay(xs + 0.5, ys - 0.5);
          Frame.PutPixel(xs, ys, frame::ToRGB(1 - DBL(ys) / Frame.H, DBL(ys) / Frame.H, DBL(xs) / Frame.W));
        }
#endif

      Scene.Render(Camera, Frame);
    } /* End of 'rt_win::Render' function */

    /* WM_SIZE window message handle function.
      * ARGUMENTS:
      *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
      *       UINT State;
      *   - new width and height of client area:
      *       INT W, H;
      * RETURNS: None.
      */
    VOID rt_win::OnSize( UINT State, INT W, INT H )
    {
      Resize(W, H);
    } /* End of 'OnSize' function */

    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */    
    VOID rt_win::OnTimer( INT Id )
    {
      //Render();
      InvalidateRect(hWnd, nullptr, false);
    } /* End of 'rt_win::OnTimer' function */

    /* WM_PAINT window message handle function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     *   - paint message structure pointer:
     *       PAINTSTRUCT *PS;
     * RETURNS: None.
     */
    VOID rt_win::OnPaint( HDC hDC, PAINTSTRUCT *Ps )
    {
      Frame.Draw(hDC, 0, 0, Frame.W, Frame.H);
    } /* End of 'OnPaint' function */

    /* WM_KEYDOWN window message handle function.
     * ARGUMENTS:
     *   - pressed key:
     *       WPARAM Key;
     *   - coordinates:
     *       LPARAM Coordinates;
     * RETURNS: None.
     */
    VOID rt_win::OnKeydown( WPARAM Key, LPARAM Coordinates )
    {
      switch (Key)
      {
      case VK_ESCAPE:
        if (MessageBox(hWnd, "Do you want to leave from program?", "CGSG", MB_YESNO | MB_ICONQUESTION) == IDYES)
          SendMessage(hWnd, WM_CLOSE, 0, 0);
      }
    } /* End of 'OnKeydown' function */
  } /* end of 'rt' namespace */
} /* end of 'pirt' namespace */

/* END OF 'rt_win.h' FILE */
