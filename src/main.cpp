/***************************************************************
 * Copyright (C) 1992-2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 ***************************************************************/

/* FILE:        main.cpp
 * PROGRAMMER:  IP5
 * LAST UPDATE: 22.07.2024
 * PURPOSE:     Main project file.
 * NOTE:        None.
 * 
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum.
 */

#include "pirt.h"

/* Windows desktop application main function.
 * ARGUMENTS:
 *   - current instance:
 *       HINSTANCE hInstance;
 *   - prev instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show cmd parameter:
 *       INT ShowCmd;
 * RETURNS:
 *   (INT) application exit code.
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  pirt::rt::rt_win myw(hInstance);
  myw.WindowCreate("T05RT");

#if 0
  // Enable debug console
  AllocConsole();
  SetConsoleTitle("CGSG IP5 :: Ray Tracing :: Debug console");
  HWND hCnsWnd = GetConsoleWindow();
  RECT rc;
  GetWindowRect(hCnsWnd, &rc);
  MoveWindow(hCnsWnd, 102, 0, 500, 300, TRUE);
  std::freopen("CONOUT$", "w", stdout);
  std::system("@chcp 1251 > nul");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);
#endif

  myw.Run();

  return 0;
} /* End of 'WinMain' function */

/* END OF 'main.cpp' FILE */
