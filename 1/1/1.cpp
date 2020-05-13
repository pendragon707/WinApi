#include <windows.h>
#include <gdiplus.h>
#include <tchar.h>
#include <algorithm>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")
#pragma comment (lib, "winmm.lib")

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

//struct ind{
//	bool rl_show;
//	bool show;
//	ind(): show(0), rl_show(0) {};
//};

bool show = false;
bool rl_show = false;

static void OnDraw(const HDC hdc, const REAL width, const REAL height)
{
	if(show == 1)
	{
		Graphics graphics(hdc);
		const SolidBrush bluebrush(Color(0, 0, 139));
		const float dim = min(width * 0.6, height * 0.6);
		graphics.FillPie(&bluebrush, Rect((width - dim) / 2, (height - dim) / 2, dim, dim), -90, rl_show ? -180 : 180);
	}
}

int WINAPI _tWinMain(HINSTANCE This,		 // ���������� �������� ���������� 
HINSTANCE Prev, 	// � ����������� �������� ������ 0 
LPTSTR cmd, 		// ��������� ������ 
int mode) 		// ����� ����������� ����
{ 
	GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, 0);

	HWND hWnd;		// ���������� �������� ���� ��������� 
	MSG msg; 		// ��������� ��� �������� ��������� 
	WNDCLASS wc; 	// ����� ����
	// ����������� ������ ���� 
	wc.hInstance = This; 
	wc.lpszClassName = WinName; 				// ��� ������ ���� 
	wc.lpfnWndProc = WndProc; 					// ������� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// ����� ���� 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// ����������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// ����������� ������ 
	wc.lpszMenuName = NULL; 					// ��� ���� 
	wc.cbClsExtra = 0; 						// ��� �������������� ������ ������ 
	wc.cbWndExtra = 0; 						// ��� �������������� ������ ���� 
	wc.hbrBackground  = (HBRUSH) CreateSolidBrush(RGB(112, 128, 144));

	hWnd = CreateWindow(WinName,
	_T("������������ 1"), 		// ��������� ���� 
	WS_OVERLAPPEDWINDOW, 		// ����� ���� 
	CW_USEDEFAULT,				// x 
	CW_USEDEFAULT, 				// y	 ������� ���� 
	CW_USEDEFAULT, 				// width 
	CW_USEDEFAULT, 				// Height 
	HWND_DESKTOP, 				// ���������� ������������� ���� 
	NULL, 						// ��� ���� 
	This, 						// ���������� ���������� 
	NULL); 					// �������������� ���������� ��� 

	ShowWindow(hWnd, mode); 				// �������� ����

	// ���� ��������� ��������� 
	while(GetMessage(&msg, NULL, 0, 0)) 
	{ 
		TranslateMessage(&msg); 		// ������� ���������� ����� ������� ������� 
		DispatchMessage(&msg); 		// �������� ��������� ������� WndProc() 
	} 
	return 0;
}

// ������� ������� ���������� ������������ ��������
// � �������� ��������� �� ������� ��� ������� ����������

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{ 
	switch(message)		 
	{ 
		case WM_DESTROY : 
		{
			PostQuitMessage(0); 
			break; 				
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			const HDC hDC = BeginPaint(hWnd, &ps);

			RECT rect;
			GetClientRect(hWnd, &rect);

			OnDraw(hDC, rect.right, rect.bottom);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_LBUTTONDOWN:
		{
		  show = true; 
		  rl_show = true;
		  InvalidateRect(hWnd, 0, TRUE);
		  break;
		}
		case WM_RBUTTONDOWN:
		{
		  show = true;
		  rl_show = false;
		  InvalidateRect(hWnd, 0, TRUE);		 
		  break;
		}
		default : 			
		    return DefWindowProc(hWnd, message, wParam, lParam); 
	} 
	return 0;
}
