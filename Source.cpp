#include <windows.h>
#include<tchar.h>
#include <math.h>
#include "FactoryVRML.h"
#include <fstream>


#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <vector>

struct Leaks {
	~Leaks()
	{
		_CrtDumpMemoryLeaks();
	}
} _l;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
int APIENTRY WinMain(HINSTANCE This, HINSTANCE Prev, LPSTR cmd, int
	mode)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wc;
	wc.hInstance = This;
	wc.lpszClassName = WinName;
	wc.lpfnWndProc = WndProc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	if (!RegisterClass(&wc)) return 0;
	hWnd = CreateWindow(WinName, _T("Каркас Windows-приложения"),
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, HWND_DESKTOP, NULL, This,
		NULL);
	ShowWindow(hWnd, mode);
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}



FactoryVRML* factory = new FactoryVRML();
GroupField* scene = factory->decrypt("test.txt");
char* c = new char('c');

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	static int x0, y0, sx = 0, sy = 0;
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_SIZE:
		sx = LOWORD(lParam);
		sy = HIWORD(lParam);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(hWnd, &ps);

		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, 1, 1, NULL);
		SetViewportExtEx(hdc, sx, sy, NULL);
		SetViewportOrgEx(hdc, 0, 0, NULL);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_MOUSEWHEEL:
		InvalidateRect(hWnd, 0, 1);
		break;
	case WM_DESTROY:
		delete factory;
		delete scene;
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}