/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        win.cpp
 * PROGRAMMER:  IP5
 * LAST UPDATE: 23.07.2024
 * PURPOSE:     Window's addons functions file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "pirt.h"

/* Base project namespace */
namespace pirt
{
  /* Window constructor.
   * ARGUMENTS:
   *   - instance:
   *       HINSTANCE hInst
   */
  win::win( HINSTANCE hInst ) : hInstance(hInst), IsFullScreen(false), MouseWheel(0), IsActive(false)
  {
  } /* End of 'win::win' function */

  /* Create window function.
   * ARGUMENTS:
   *   - title name:
   *       CHAR *Name;
   *   - parent class (nullptr if doesn't parent class):
   *       HWND hPrnWnd;
   * RETURNS: None.
   */
  VOID win::WindowCreate( const CHAR *Name, HWND hPrnWnd )
  {
    hWnd = 
      CreateWindow(WND_CLASS_NAME,
        Name,
        WS_OVERLAPPEDWINDOW,
        0, 0,
        1000, 500,
        hPrnWnd, NULL, 
        hInstance, reinterpret_cast<VOID *>(this));

    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);
  } /* End of 'win::WindowCreate' function */
    
  /* Create class function.
   * ARGUMENTS:
   *   - class name:
   *       CHAR *Name;
   *   - application descriptor:
   *       HINSTANCE hInstance;
   * RETURNS: None.
   */
  VOID win::CreateClass( const CHAR *Name, HINSTANCE hInstance )
  {
    WNDCLASS wc {};

    wc.style = CS_VREDRAW | CS_HREDRAW;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);
    wc.lpszMenuName = NULL;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = NULL;
    wc.lpszClassName = WND_CLASS_NAME;
    wc.lpfnWndProc = WinFunc;
    wc.cbWndExtra = sizeof(win *);

    if (!RegisterClass(&wc))
      MessageBox(NULL, "Don't create window's class", "ERROR", MB_OK);
  } /* End of 'win::CreateClass' function */

  /* Window function.
   * ARGUMENTS:
   *   - window handle:
   *       HWND hWnd;
   *   - message:
   *       UINT Msg;
   *   - word parameter:
   *       WPARAM wParam;
   *   - long param:
   *       LPARAM lParam;
   * RETURNS:
   *   (LRESULT) result of message proc.
   */
  LRESULT CALLBACK win::WinFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
  {
    win *Win;
    HDC hDC;
    PAINTSTRUCT ps;

    switch (Msg)
    {
    case WM_GETMINMAXINFO:
      ((MINMAXINFO *)lParam)->ptMinTrackSize.x = 50;
      ((MINMAXINFO *)lParam)->ptMinTrackSize.y = 20;
#if 0
      ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
        GetSystemMetrics(SM_CYMAXTRACK) +
        GetSystemMetrics(SM_CYCAPTION) +
        GetSystemMetrics(SM_CYMENU) +
        GetSystemMetrics(SM_CYBORDER) * 2;
      ((MINMAXINFO *)lParam)->ptMinTrackSize.y =
        GetSystemMetrics(SM_CYCAPTION) * 8 +
        GetSystemMetrics(SM_CYMENU) +
        GetSystemMetrics(SM_CYBORDER) * 2;
      ((MINMAXINFO *)lParam)->ptMinTrackSize.x += 300;
#endif
      return 0;
    case WM_CREATE:
      /* Attach 'this' pointer to window class to window */
      SetWindowLongPtr(hWnd, 0, (UINT_PTR)((CREATESTRUCT *)lParam)->lpCreateParams);
      [[fallthrough]];
    default:	
      Win = reinterpret_cast<win *>(GetWindowLongPtr(hWnd, 0));
      if (Win != nullptr)
        switch (Msg)
        {
        case WM_CREATE:
          Win->hWnd = hWnd;
          return Win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;
        case WM_SIZE:
          Win->W = (INT)(SHORT)LOWORD(lParam);
          Win->H = (INT)(SHORT)HIWORD(lParam);
          Win->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
          return 0;
        case WM_ACTIVATE:
          Win->IsActive = LOWORD(wParam) != WA_INACTIVE;
          Win->OnActivate((UINT)LOWORD(wParam),(HWND)(lParam),(BOOL)HIWORD(wParam));
          return 0;
        case WM_ERASEBKGND:
          return (LRESULT)Win->OnEraseBkgnd((HDC)wParam);
        case WM_PAINT:
          hDC = BeginPaint(hWnd, &ps);
          Win->OnPaint(hDC, &ps);
          EndPaint(hWnd, &ps);
          return 0;
        case WM_DRAWITEM:
          Win->OnDrawItem((INT)wParam, (DRAWITEMSTRUCT *)lParam);
          return 0;
        case WM_TIMER:
          Win->OnTimer((UINT)wParam);
          return 0;
        case WM_MOUSEWHEEL:
          Win->OnMouseWheel((INT)(SHORT)LOWORD(lParam),
                            (INT)(SHORT)HIWORD(lParam),
                            (INT)(SHORT)HIWORD(wParam),
                            (UINT)(SHORT)LOWORD(wParam));
          return 0;
        case WM_LBUTTONDBLCLK:
          Win->OnButtonDown(TRUE, (INT)(SHORT)LOWORD(lParam),
                            (INT)(SHORT)HIWORD(lParam),(UINT)(SHORT)LOWORD(wParam));
          return 0;
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
          Win->OnButtonDown(FALSE, (INT)(SHORT)LOWORD(lParam),
                           (INT)(SHORT)HIWORD(lParam), (UINT)(SHORT)LOWORD(wParam));
          return 0;
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
          Win->OnButtonUp((INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam), 
                           (UINT)(SHORT)LOWORD(wParam));
          return 0;
#if 0
        case WM_KEYDOWN:
          Win->OnKeydown(wParam, lParam);
          return 0;
#endif
        case WM_DROPFILES:
          Win->OnDropFiles((HDROP)wParam);
          return 0;
        case WM_NOTIFY:
          return Win->OnNotify((INT)wParam, (NMHDR *)lParam);
        case WM_COMMAND:
          Win->OnCommand((INT)LOWORD(wParam), (HWND)lParam, (UINT)HIWORD(wParam));
          return 0;
        case WM_MENUSELECT:
          Win->OnMenuSelect((HMENU)lParam,
            (HIWORD(wParam) & MF_POPUP) ? 0L : (INT)LOWORD(wParam),
            (HIWORD(wParam) & MF_POPUP) ?
              GetSubMenu((HMENU)lParam, LOWORD(wParam)) : 0L,
            (UINT)(((SHORT)HIWORD(wParam) == -1) ? 0xFFFFFFFF : HIWORD(wParam)));
          return 0;
        case WM_INITMENUPOPUP:
          Win->OnInitMenuPopup((HMENU)wParam, (UINT)LOWORD(lParam),
            (BOOL)HIWORD(lParam));
          return 0;
        case WM_HSCROLL:
          Win->OnHScroll((HWND)lParam, LOWORD(wParam), HIWORD(wParam));
          return 0;
        case WM_VSCROLL:
          Win->OnVScroll((HWND)lParam, LOWORD(wParam), HIWORD(wParam));
          return 0;
        case WM_ENTERSIZEMOVE:
          Win->OnEnterSizeMove();
          return 0;
        case WM_EXITSIZEMOVE:
          Win->OnExitSizeMove();
          return 0;
        case WM_DESTROY:
          Win->OnDestroy();
          PostQuitMessage(30);
          return 0;
        default:
          return Win->OnMessage(Msg, wParam, lParam);
        }
    }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
  } /* End of 'win::WinFunc' function */

  /* Window run function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID win::Run( VOID )
  {
    MSG msg;

    while (TRUE)
    {
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
        if (msg.message == WM_QUIT)
          break;
        DispatchMessage(&msg);
      }
      else
        SendMessage(hWnd, WM_TIMER, 47, 0);
    }
  } /* End of 'win::Run' function */

  /* Window destructor */
  win::~win()
  {
  } /* End of 'win::~win' function */

} /* end of 'pirt' namespace */

/* END OF 'win.cpp' FILE */
