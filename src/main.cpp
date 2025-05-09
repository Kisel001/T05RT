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


extern "C" size_t StringLen( const CHAR *Str );

/* Window function prototype */
LRESULT CALLBACK WindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

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
  pirt::rt::rt_win::CreateClass(WND_CLASS_NAME, hInstance);
  pirt::rt::rt_win myw(hInstance);
  myw.WindowCreate("CGSG");

  pirt::stock<INT> S;

  pirt::matr _m = pirt::matr::Translate(pirt::vec3(1, 0, 0));
  
  pirt::matr _m1 = _m.Inverse();

  //HeapAlloc(GetProcessHeap(), 0, 10);

  S << 5;

//#ifdef _DEBUG
  // Enable debug console for VS DEBUG mode.

  AllocConsole();
  SetConsoleTitle("CGSG IP5 :: Ray Tracing :: Debug console");
  HWND hCnsWnd = GetConsoleWindow();
  RECT rc;
  GetWindowRect(hCnsWnd, &rc);
  MoveWindow(hCnsWnd, 102, 0, 500, 300, TRUE);
  std::freopen("CONOUT$", "w", stdout);
  std::system("@chcp 1251 > nul");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);

#if 0
  for (int i = 32; i <= 255; ++i)
  {
    if (i % 16 == 0)
      std::cout << std::endl;
    std::cout << (char)i << ' ';
  }

  std::cout << std::endl;
//#endif // _DEBUG
#endif

#if 0
  std::cout << StringLen("CGSG forever");

  mth::matr<DBL> m = mth::matr<DBL>::Identity();
  mth::matr<DBL> m1 = mth::matr<DBL>::Identity();
  mth::matr<DBL> m2;

  mth::matr<DBL>::matrmulmatr(&m2, &m, &m1);


  std::cout << m2;
#endif

#if 0
  mth::matr<FLT> m3 = mth::matr<FLT>::Identity();
  mth::matr<FLT> m4 = mth::matr<FLT>::Identity();
  mth::matr<FLT> m5;

  clock_t t = clock();

  for (int i = 0 ; i < 100000; i++)
    m2 = m * m1;

  t = clock() - t;

  std::cout << t / 1000.0 << std::endl;

  t = clock();

  for (int i = 0 ; i < 100000; i++)
    m5 = m3 * m4;

  t = clock() - t;
  
  std::cout << t / 1000.0 << std::endl;
#endif


//  mth::matr<DBL>::matrmulmatr(&m2, &m, &m1);

  //std::cout << m2;

  myw.Run();

  return 0;
} /* End of 'WinMain' function */

/* END OF 'main.cpp' FILE */
