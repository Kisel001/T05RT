/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        win_msg.cpp
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
  /* WM_CREATE window message handle function.
   * ARGUMENTS:
   *   - structure with creation data:
   *       CREATESTRUCT *CS;
   * RETURNS:
   *   (BOOL) TRUE to continue creation window, FALSE to terminate.
   */
  BOOL win::OnCreate( CREATESTRUCT *CS )
  {
    return TRUE;
  } /* End of 'win::OnCreate' function */

  /* WM_DESTROY window message handle function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID win::OnDestroy( VOID )
  {
  } /* End of 'win::OnDestroy' function */

  /* WM_SIZE window message handle function.
   * ARGUMENTS:
   *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
   *       UINT State;
   *   - new width and height of client area:
   *       INT W, H;
   * RETURNS: None.
   */
  VOID win::OnSize( UINT State, INT W, INT H )
  {
  } /* End of 'win::OnSize' function */

  /* WM_ERASEBKGND window message handle function.
   * ARGUMENTS:
   *   - device context of client area:
   *       HDC hDC;
   * RETURNS:
   *   (BOOL) TRUE if background is erased, FALSE otherwise.
   */
  BOOL win::OnEraseBkgnd( HDC hDC )
  {
    return TRUE;
  } /* End of 'win::OnEraseBkgnd' function */

  /* WM_PAINT window message handle function.
   * ARGUMENTS:
   *   - window device context:
   *       HDC hDC;
   *   - paint message structure pointer:
   *       PAINTSTRUCT *PS;
   * RETURNS: None.
   */
  VOID win::OnPaint( HDC hDC, PAINTSTRUCT *PS )
  {
  } /* End of 'win::OnPaint' function */ 

  /* WM_ACTIVATE window message handle function.
   * ARGUMENTS:
   *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
   *       UINT Reason;
   *   - handle of active window:
   *       HWND hWndActDeact;
   *   - minimized flag:
   *       BOOL IsMinimized;
   * RETURNS: None.
   */
  VOID win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
  {
    // IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;
  } /* End of 'win::OnActivate' function */

  /* WM_TIMER window message handle function.
   * ARGUMENTS:
   *   - specified the timer identifier.
   *       INT Id;
   * RETURNS: None.
   */
  VOID win::OnTimer( INT Id ) 
  {
  } /* End of 'win::OnTimer' function */

  /* WM_MOUSEWHEEL window message handle function.
   * ARGUMENTS:
   *   - mouse window position:
   *       INT X, Y;
   *   - mouse wheel relative delta value:
   *       INT Z;
   *   - mouse keys bits (see MK_*** bits constants):
   *       UINT Keys;
   * RETURNS: None.
   */
  VOID win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
  {
    MouseWheel += Z;
  } /* End of 'win::OnMouseWheel' function */

  /* WM_DROPFILES window message handle function.
   * ARGUMENTS:
   *   - handle to an internal structure describing the dropped files:
   *       HDROP hDrop;
   * RETURNS: None.
   */
  VOID win::OnDropFiles( HDROP hDrop )
  {
    static CHAR Buf[_MAX_PATH];

    INT n = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
    if (n > 0)
    {
      POINT pt;
      DragQueryPoint(hDrop, &pt);
      ClientToScreen(hWnd, &pt);
      HWND hWndItem = WindowFromPoint(pt);
#if 0 // not used
      if (hWndItem == /* Check window */ )
      {
        /* for single file: DragQueryFile(hDrop, 0, Buf, sizeof(Buf)); */
        // Handle every file
        for (INT i = 0; i < n; i++)
        {
          DragQueryFile(hDrop, i, Buf, sizeof(Buf));
          /// Handle filename from 'Buf'
          // Can split:
          static CHAR
            Drive[_MAX_DRIVE], Dir[_MAX_DIR],
            FileName[_MAX_FNAME], FileExt[_MAX_EXT];
          _splitpath(Buf, Drive, Dir, FileName, FileExt);
          // . . .
        }
      }
#endif // 0
    }
  } /* End of 'win::OnDropFiles' function */

  /* WM_NOTIFY window message handle function.
   * ARGUMENTS:
   *   - control identifier:
   *       INT Id;
   *   - notification header depended to control type:
   *       NMHDR *NoteHead;
   * RETURNS:
   *   (LRESULT) return value depended to notification.
   */
  LRESULT win::OnNotify( INT Id, NMHDR *NoteHead )
  {
    return 0;
  } /* End of 'win::OnNotify' function */

  /* WM_COMMAND window message handle function.
   * ARGUMENTS:
   *   - item (menu or accelerator) or control window identifier:
   *       INT Id;
   *   - control window handle:
   *       HWND hWndCtl;
   *   - notification: 0 - menu, 1 - accelerator, otherwise -
   *     depended to control (like BM_CLICKED):
   *       UINT CodeNotify;
   * RETURNS: None.
   */
  VOID win::OnCommand( INT Id, HWND hWndCtl, UINT CodeNotify )
  {
  } /* End of 'win::OnCommand' function */

  /* WM_DRAWITEM window message handle function.
   * ARGUMENTS:
   *   - control identifier (for menu - 0):
   *       INT Id;
   *   - draw item information structure pointer:
   *       DRAWITEMSTRUCT *DrawItem;
   * RETURNS: None.
   *   (LRESULT) return value depended to notification.
   */
  VOID win::OnDrawItem( INT Id, DRAWITEMSTRUCT *DrawItem )
  {
#if 0 // not used
    if (DrawItem->CtlID == 0) // sample for check bax draw as button
    {
      UINT Flags = DFCS_BUTTONPUSH;

      if (DrawItem->itemState & ODS_DISABLED)
        Flags |= DFCS_INACTIVE;
      if (DrawItem->itemState & ODS_SELECTED)
        Flags |= DFCS_PUSHED;

      DrawFrameControl(DrawItem->hDC, &DrawItem->rcItem, DFC_BUTTON, Flags);
      InflateRect(&DrawItem->rcItem, -2, -2);
      Flags &= ~DFCS_PUSHED;
      Flags &= ~DFCS_BUTTONPUSH;
      Flags |= DFCS_BUTTONCHECK | DFCS_FLAT;
      if (DrawItem->CtlID == 0)
        Flags |= DFCS_CHECKED;
      DrawFrameControl(DrawItem->hDC, &DrawItem->rcItem, DFC_BUTTON, Flags);
    }
#endif // 0
  } /* End of 'win::OnDrawItem' function */

  /* WM_HSCROLL message handle function.
   * ARGUMENTS:
   *   - handle of scroll window or nullptr for window scroll bars:
   *       HWND hWndCtl;
   *   - scrool bar request code (see SB_***):
   *       UINT Code;
   *   - schroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
   *       INT Pos;
   * RETURNS: None.
   */
  VOID win::OnHScroll( HWND hWndCtl, UINT Code, INT Pos )
  {
  } /* End of 'win::OnHScroll' function */

  /* WM_VSCROLL message handle function.
   * ARGUMENTS:
   *   - handle of scroll window or nullptr for window scroll bars:
   *       HWND hWndCtl;
   *   - scrool bar request code (see SB_***):
   *       UINT Code;
   *   - schroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
   *       INT Pos;
   * RETURNS: None.
   */
  VOID win::OnVScroll( HWND hWndCtl, UINT Code, INT Pos )
  {
  } /* End of 'win::OnVScroll' function */

  /* WM_MENUSELECT window message handle function.
   * ARGUMENTS:
   *   - handle of menu:
   *       HMENU hMenu;
   *   - submenu item ID or submenu index
   *       INT Item;
   *   - handle of popup menu if selected popup submenu:
   *       HMENU hMenuPopup;
   *   - menu item flags (see MF_***):
   *       UINT Flags;
   * RETURNS: None.
   */
  VOID win::OnMenuSelect( HMENU hMenu, INT Item, HMENU hMenuPopup, UINT Flags )
  {
  } /* End of 'win::OnMenuSelect' function */

  /* WM_INITMENUPOPUP window message handle function.
   * ARGUMENTS:
   *   - handle of popup menu:
   *       HMENU hMenu;
   *   - submenu item position:
   *       UINT Item;
   *   - window system menu flag:
   *       BOOL IsSystemMenu;
   * RETURNS: None.
   */
  VOID win::OnInitMenuPopup( HMENU hMenu, UINT Item, BOOL IsSystemMenu )
  {
  } /* End of 'win::OnInitMenuPopup' function */

  /* WM_EXITSIZEMOVE window message handle function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID win::OnExitSizeMove( VOID )
  {
  } /* End of 'win::OnExitSizeMove' function */

  /* WM_ENTERSIZEMOVE window message handle function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
  VOID win::OnEnterSizeMove( VOID )
  {
  } /* End of 'win::OnEnterSizeMove' function */

  /* Window message universal handle function.
   * Should be returned 'DefWindowProc' call result.
   * ARGUMENTS:
   *   - message type (see WM_***):
   *      UINT Msg;
   *   - message 'word' parameter:
   *      WPARAM wParam;
   *   - message 'long' parameter:
   *      LPARAM lParam;
   * RETURNS:
   *   (LRESULT) message depende return value.
   */
  LRESULT win::OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam )
  {
    return DefWindowProc(hWnd, Msg, wParam, lParam);
  } /* End of 'win::OnMessage' function */

  /* Windows button down message.
   * ARGUMENTS:
   *   - is double click flag:
   *       BOOL IsDoubleClick;
   *   - coordinates:
   *       INT X, Y;
   *   - keys:
   *       UINT Keys;
   * RETURNS: None.
   */
  VOID win::OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys )
  {
  } /* End of 'win::onButtonDown' function */

  /* Windows button up message.
   * ARGUMENTS:
   *   - coordinates:
   *       INT X, Y;
   *   - keys:
   *       UINT Keys;
   * RETURNS: None.
   */
  VOID win::OnButtonUp( INT X, INT Y, UINT Keys )
  {
    //fopen_s(&F, )
  } /* End of 'win::onButtonUp' function */

  /* Windows mouse move message.
   * ARGUMENTS:
   *   - coordinates:
   *       INT X, Y;
   *   - keys:
   *       UINT Keys;
   * RETURNS: None.
   */
  VOID win::OnMouseMove( INT X, INT Y, UINT Keys )
  {
  } /* End of 'win::onMouseMove' function */

  /* WM_KEYDOWN window message handle function.
   * ARGUMENTS:
   *   - pressed key:
   *       WPARAM Key;
   *   - coordinates:
   *       LPARAM Coordinates;
   * RETURNS: None.
   */
  VOID win::OnKeydown( WPARAM Key, LPARAM Coordinates )
  {
  } /* End of 'win::OnKeydown' function */

} /* end of 'pirt' namespace */

/* END OF 'win_msg.cpp' FILE */
