/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        win.h
 * PROGRAMMER:  IP5
 * LAST UPDATE: 23.07.2024
 * PURPOSE:     Window's addons functions file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#ifndef __win_h_
#define __win_h_

#include "def.h"

/* Window class name macros */
#define WND_CLASS_NAME "CGSG IP5 :: APP"

/* Base project namespace */
namespace pirt
{
  class win
  {
  protected:
    HWND hWnd;           // window handle
    HINSTANCE hInstance; // application handle
  private:
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg,
                                     WPARAM wParam, LPARAM lParam );

    BOOL IsFullScreen;       // Is full screen flag
    RECT FullScreenSaveRect; // Full screen rect
    INT MouseWheel;          // Mouse wheel value
  public:
    BOOL IsActive;           // IsActive flag
    INT W, H;                // window size
    const CHAR 
      *WndClassName = "CGSG IP5 :: APP"; // Window class name

    /* Window constructor.
     * ARGUMENTS:
     *   - instance:
     *       HINSTANCE hInst
     */
    win( HINSTANCE hInst = GetModuleHandle(nullptr) );

    /* Create window function.
     * ARGUMENTS:
     *   - title name:
     *       CHAR *Name;
     *   - parent class (nullptr if doesn't parent class):
     *       HWND hPrnWnd;
     * RETURNS: None.
     */
    VOID WindowCreate( const CHAR *Name, HWND hPrnWnd = nullptr );

    /* Create class function.
     * ARGUMENTS:
     *   - class name:
     *       CHAR *Name;
     *   - application descriptor:
     *       HINSTANCE hInstance;
     * RETURNS: None.
     */
    static VOID CreateClass( const CHAR *Name, HINSTANCE hInstance );

    /* Window destructor */
    virtual ~win( VOID );

    /* Window run function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Run( VOID );

    /* Set full screen function. (not realized)
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FlipFullScreen( VOID );

  private:
    /* Message cracks */

    VOID OnGetMinMaxInfo( MINMAXINFO *MinMax ); // ???


    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    virtual BOOL OnCreate( CREATESTRUCT *CS );

    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID OnDestroy( VOID );

    /* WM_ERASEBKGND window message handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS:
     *   (BOOL) TRUE if background is erased, FALSE otherwise.
     */
    virtual BOOL OnEraseBkgnd( HDC hDC );

    /* WM_PAINT window message handle function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     *   - paint message structure pointer:
     *       PAINTSTRUCT *PS;
     * RETURNS: None.
     */
    virtual VOID OnPaint( HDC hDC, PAINTSTRUCT *Ps );

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
    virtual VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );

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
    virtual VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );
    
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
    virtual VOID OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys );
   
    /* Windows button up message.
     * ARGUMENTS:
     *   - coordinates:
     *       INT X, Y;
     *   - keys:
     *       UINT Keys;
     * RETURNS: None.
     */
    virtual VOID OnButtonUp( INT X, INT Y, UINT Keys );

    /* Windows mouse move message.
     * ARGUMENTS:
     *   - coordinates:
     *       INT X, Y;
     *   - keys:
     *       UINT Keys;
     * RETURNS: None.
     */
    virtual VOID OnMouseMove( INT X, INT Y, UINT Keys );
    
    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    virtual VOID OnSize( UINT State, INT W, INT H );
    
    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */    
    virtual VOID OnTimer( INT Id );
    
    /* WM_DROPFILES window message handle function.
     * ARGUMENTS:
     *   - handle to an internal structure describing the dropped files:
     *       HDROP hDrop;
     * RETURNS: None.
     */
    virtual VOID OnDropFiles( HDROP hDrop );
    
    /* WM_DRAWITEM window message handle function.
     * ARGUMENTS:
     *   - control identifier (for menu - 0):
     *       INT Id;
     *   - draw item information structure pointer:
     *       DRAWITEMSTRUCT *DrawItem;
     * RETURNS: None.
     *   (LRESULT) return value depended to notification.
     */
    virtual VOID OnDrawItem( INT Id, DRAWITEMSTRUCT *DrawItem );
    
    /* WM_NOTIFY window message handle function.
     * ARGUMENTS:
     *   - control identifier:
     *       INT Id;
     *   - notification header depended to control type:
     *       NMHDR *NoteHead;
     * RETURNS:
     *   (LRESULT) return value depended to notification.
     */
    virtual LRESULT OnNotify( INT Id, NMHDR *NoteHead );

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
    virtual VOID OnCommand( INT Id, HWND hWndCtl, UINT CodeNotify );

    /* Menu select message function.
     * ARGUMENTS:
     *   - menu handle:
     *       HMENU hMenu;
     *   - item:
     *       INT Item;
     *   - menu popup handle:
     *       HMENU hMenuPopup;
     *   - flags:
     *       UINT Flags;
     * RETURNS: None.
     */
    virtual VOID OnMenuSelect( HMENU hMenu, INT Item, HMENU hMenuPopup, UINT Flags);

    /* On menu poput message function.
     * ARGUMENTS:
     *   - menu handle:
     *       HMENU hMenu;
     *   - item:
     *       INT Item;
     *   - is system menu flag:
     *       BOOL IsSystemMenu;
     * RETURNS: None.
     */
    virtual VOID OnInitMenuPopup( HMENU hMenu, UINT Item, BOOL IsSystemMenu );
    
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
    virtual VOID OnHScroll( HWND hWndCtl, UINT Code, INT Pos );

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
    virtual VOID OnVScroll( HWND hWndCtl, UINT Code, INT Pos );

    /* WM_EXITSIZEMOVE window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID OnExitSizeMove( VOID );

    /* WM_ENTERSIZEMOVE window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID OnEnterSizeMove( VOID );
    
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
    virtual LRESULT OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam );

    /* WM_KEYDOWN window message handle function.
     * ARGUMENTS:
     *   - pressed key:
     *       WPARAM Key;
     *   - coordinates:
     *       LPARAM Coordinates;
     * RETURNS: None.
     */
    virtual VOID OnKeydown( WPARAM Key, LPARAM Coordinates );
  }; /* End of 'win' class */
}

#endif // !__win_h_

/* END OF 'win.h' FILE */
