// win32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "wmain.h"
#include <ogui/ogui.h>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

HBITMAP bitmap=0;
unsigned* bitmap_pixels=0;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
void        ExitInstance(HINSTANCE);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
  ExitInstance(hInstance);
	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   //HDC dc = GetDC(hWnd);
   BITMAPINFO bmi;
   ZeroMemory(&bmi, sizeof(BITMAPINFO));
   bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   bmi.bmiHeader.biWidth = 640;
   bmi.bmiHeader.biHeight = -480;
   bmi.bmiHeader.biPlanes = 1;
   bmi.bmiHeader.biBitCount = 32;
   bmi.bmiHeader.biCompression = BI_RGB;
   bitmap = CreateDIBSection(0, &bmi, DIB_RGB_COLORS, (void**)&bitmap_pixels, 0, 0);
   for (int i = 0; i < (640 * 480); ++i)
     bitmap_pixels[i] = 0xFFFFFFFF;
   //ReleaseDC(hWnd, dc);
   RECT rect;
   rect.left = rect.top = 0;
   rect.right = 640;
   rect.bottom = 480;
   InvalidateRect(hWnd, &rect, TRUE);
   OGUI::OGUIManager::instance()->initialize_desktop(640, 480);

   void load_demo_layout();
   load_demo_layout();

   SetTimer(hWnd, 555, 50, 0);
   return TRUE;
}

void ExitInstance(HINSTANCE hInstnace)
{
  DeleteObject(bitmap);
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc,bmp_dc;
  HGDIOBJ oldbmp;
  OGUI::Image target(640, 480, (unsigned char*)bitmap_pixels);
  RECT rect;
  int x, y;

  rect.left = rect.top = 0;
  rect.right = 640;
  rect.bottom = 480;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
  case WM_TIMER:
    if (OGUI::OGUIManager::instance()->get_desktop()->draw(target, OGUI::Rect(0, 0, 640, 480)))
      InvalidateRect(hWnd, &rect, FALSE);
    break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
    bmp_dc = CreateCompatibleDC(hdc);
    oldbmp=SelectObject(bmp_dc, bitmap);
    BitBlt(hdc, 0, 0, 640, 480, bmp_dc, 0, 0, SRCCOPY);
    SelectObject(bmp_dc, oldbmp);
    DeleteDC(bmp_dc);
		EndPaint(hWnd, &ps);
		break;
  case WM_LBUTTONDOWN:
    x = GET_X_LPARAM(lParam);
    y = GET_Y_LPARAM(lParam);
    OGUI::OGUIManager::instance()->mouse_down(0, x, y);
    break;
  case WM_LBUTTONUP:
    x = GET_X_LPARAM(lParam);
    y = GET_Y_LPARAM(lParam);
    OGUI::OGUIManager::instance()->mouse_up(0, x, y);
    break;
  case WM_MOUSEMOVE:
    x = GET_X_LPARAM(lParam);
    y = GET_Y_LPARAM(lParam);
    OGUI::OGUIManager::instance()->mouse_move(x, y);
    break;
  case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
