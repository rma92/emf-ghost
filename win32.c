#include <windows.h>
#include "res.h"

HENHMETAFILE hemf;
HWND g_hwnd;
int dx = 20;
int dy = 5;
int width = 320;
int height = 240;
int max_x = 1000;
int max_y = 600;
int min_x = 40;
int min_y = 40;
//for sound
DWORD WINAPI MyThreadFunction( LPVOID lpParam )
{

  SetTimer( g_hwnd, IDT_TIMER1, TIMER_INTERVAL, (TIMERPROC) NULL );
  PlaySound( MAKEINTRESOURCE( IDW_WAV1 ),
    GetModuleHandle( NULL ),
    SND_RESOURCE);
  while(1)
  {
  PlaySound( MAKEINTRESOURCE( IDW_WAV2 ),
    GetModuleHandle( NULL ),
    SND_RESOURCE);
  }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  HDC hdc;
  HANDLE hres;
  PAINTSTRUCT ps;
  RECT rct;
  DWORD dw;
  HRSRC hrsrc;
  switch(message)
  {
    case WM_CREATE:
    { 
      g_hwnd = hWnd;
      hrsrc = FindResource( GetModuleHandle( NULL ),MAKEINTRESOURCE(ID_EMF1), "ENHANCEDMETAFILE"); 
      hres = LoadResource( GetModuleHandle( NULL ), hrsrc);
      dw = SizeofResource( GetModuleHandle( NULL ), hrsrc);
      hemf = SetEnhMetaFileBits( dw , hres );
      EnableMenuItem( GetSystemMenu(hWnd, 0), SC_CLOSE, MF_BYCOMMAND | MF_GRAYED); 
      
      CreateThread( NULL, 0, MyThreadFunction, 0, 0, 0 );
    }
    break;
    case WM_PAINT:
      hdc = BeginPaint( hWnd, &ps );
      GetClientRect( hWnd, &rct );
      PlayEnhMetaFile( hdc, hemf, &rct );
      EndPaint( hWnd, &ps );
    break;
    case WM_TIMER:
    switch( wParam )
    {
      case IDT_TIMER1:
      {
        RECT r;
        GetWindowRect( hWnd, &r );
        if( r.left > max_x )
        {
          dx = abs( dx ) * -1;
        }
        if( r.left < min_x )
        {
          dx = abs( dx );
        }
        if( r.bottom > max_y )
        {
          dy = abs( dy ) * -1;
        }
        if( r.top < min_y )
        {
          dy = abs( dy );
        }
        SetWindowPos( hWnd, 0, r.left+dx, r.top+dy, width, height, 0 );
      }
      return 0;
    }
    break;
    case WM_DESTROY:
      PostQuitMessage(0);
    break;
    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
  }
  return 0;
}
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
  MSG msg1;
  WNDCLASS wc1;
  HWND hWnd1;
  ZeroMemory(&wc1, sizeof wc1);
  wc1.hInstance = hInst;
  wc1.lpszClassName = AppName;
  wc1.lpfnWndProc = (WNDPROC)WndProc;
  wc1.style = CS_DBLCLKS | CS_VREDRAW | CS_HREDRAW;
  wc1.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
  wc1.hIcon = LoadIcon(NULL, IDI_INFORMATION);
  wc1.hCursor = LoadCursor(NULL, IDC_ARROW);
  if(RegisterClass(&wc1) == FALSE) return 0;
  hWnd1 = CreateWindow(AppName, AppName, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 10, 10, 360, 240, 0, 0, hInst, 0);
  if(hWnd1 == NULL) return 0;
  while(GetMessage(&msg1,NULL,0,0) > 0){
    TranslateMessage(&msg1);
    DispatchMessage(&msg1);
  }
  return msg1.wParam;
}

