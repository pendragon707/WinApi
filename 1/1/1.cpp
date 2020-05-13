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

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
HINSTANCE Prev, 	// В современных системах всегда 0 
LPTSTR cmd, 		// Командная строка 
int mode) 		// Режим отображения окна
{ 
	GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, 0);

	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This; 
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground  = (HBRUSH) CreateSolidBrush(RGB(112, 128, 144));

	hWnd = CreateWindow(WinName,
	_T("Лабораторная 1"), 		// Заголовок окна 
	WS_OVERLAPPEDWINDOW, 		// Стиль окна 
	CW_USEDEFAULT,				// x 
	CW_USEDEFAULT, 				// y	 Размеры окна 
	CW_USEDEFAULT, 				// width 
	CW_USEDEFAULT, 				// Height 
	HWND_DESKTOP, 				// Дескриптор родительского окна 
	NULL, 						// Нет меню 
	This, 						// Дескриптор приложения 
	NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

	// Цикл обработки сообщений 
	while(GetMessage(&msg, NULL, 0, 0)) 
	{ 
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	} 
	return 0;
}

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

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
