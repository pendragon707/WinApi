#include <windows.h>
#include <tchar.h>
#include <gdiplus.h>
#include <ctime>
#include <sstream>
using namespace Gdiplus;
#pragma comment(lib, "gdiplus.lib")

TCHAR ClassName[] = _T("������������ 2");
TCHAR mes[] = _T("��� ���������� ��� �������. ��������� ��� ���� ����?");
TCHAR varn[] = _T("��������������");

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

size_t last_instance_no = 0;
HWND second_window = 0;
HWND last_window = 0;
BOOL CALLBACK enum_window_proc(HWND hWnd, LPARAM lpParam)
{
	TCHAR sas[64];
	GetClassName(hWnd, sas, sizeof(sas) / sizeof(sas[0]));
	
	if (!_tcscmp(sas, ClassName))
	{
		size_t cur_instance_no = (size_t)SendMessage(hWnd, WM_USER, 0, 0);
		if (!second_window && cur_instance_no == 2)
			second_window = hWnd;
		if (last_instance_no < cur_instance_no) last_window = hWnd;
		last_instance_no = max(last_instance_no, cur_instance_no);
	}
	return TRUE;
}

SolidBrush* text_brush;
int WINAPI _tWinMain(HINSTANCE This, HINSTANCE Prev, LPTSTR cmd, int mode) 	
{
	SetProcessDPIAware(); 

	GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, 0);

	EnumWindows(enum_window_proc, 0);

	if(last_instance_no > 1 && MessageBox(0, mes, varn, MB_YESNO) == IDNO)
	{
		if (second_window)
		{
			SetForegroundWindow(second_window);
			ShowWindow(second_window, SW_SHOWNORMAL);
		}
		return 0;
	}

	srand((unsigned)time(0));

	HWND hWnd;		
	MSG msg; 		
	WNDCLASS wc; 		
	// ����������� ������ ���� 
	wc.hInstance = This; 
	wc.lpszClassName = ClassName; 				// ��� ������ ���� 
	wc.lpfnWndProc = WndProc; 					// ������� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// ����� ���� 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// ����������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// ����������� ������ 
	wc.lpszMenuName = NULL; 					// ��� ���� 
	wc.cbClsExtra = 0; 						// ��� �������������� ������ ������ 
	wc.cbWndExtra = 0; 						// ��� �������������� ������ ���� 
	const BYTE r = rand(), g = rand(), b = rand();
	wc.hbrBackground  = (HBRUSH) CreateSolidBrush(RGB(r, g, b)); 
	text_brush = new SolidBrush(Color::MakeARGB(255, ~r, ~g, ~b));

	if (!RegisterClass(&wc)) 
		{
			DeleteObject(wc.hbrBackground);
			delete text_brush;
			return 0; 	
		}

	hWnd = CreateWindowEx(0,			// ��� ������ ���� 
		ClassName,
		ClassName, 		// ��������� ���� 
	WS_OVERLAPPEDWINDOW, 		// ����� ���� 
	CW_USEDEFAULT,				// x 
	CW_USEDEFAULT, 				// y	 ������� ���� 
	400, 				// width 
	400, 				// Height 
	HWND_DESKTOP, 				// ���������� ������������� ���� 
	NULL, 						// ��� ���� 
	This, 						// ���������� ���������� 
	NULL); 					// �������������� ���������� ��� 

	ShowWindow(hWnd, mode); 				

	while(GetMessage(&msg, NULL, 0, 0)) 
	{ 
		TranslateMessage(&msg); 	
		DispatchMessage(&msg); 		
	} 

	DeleteObject(wc.hbrBackground);
	delete text_brush;
	return 0;
}

static void OnDraw(const HDC hdc, const REAL width, const REAL height)
{
	if (last_window)
	{
		Graphics graphics(hdc);
		graphics.SetSmoothingMode(SmoothingModeHighQuality);
		FontFamily ff(TEXT("Lucida Console"));
		Font f(&ff, 50, 0, UnitPixel);

		std::wostringstream wss;
		wss << std::hex << last_window;
	
		const size_t len = wss.str().length();
		const wchar_t* str = wss.str().c_str();

		const StringFormat sf = StringFormat::GenericDefault();

		RectF bounding_rect(0, 0, 0, 0);
		graphics.MeasureString(str, len, &f, PointF(0, 0), &sf, &bounding_rect);          
		graphics.DrawString(wss.str().c_str(), len, &f,
			PointF(width / 2 - bounding_rect.Width / 2, height / 2 - bounding_rect.Height / 2), 
			&sf, text_brush); 
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{ 
	switch(message)		 
	{ 
		case WM_DESTROY: 
		{
			PostQuitMessage(0); 
			break; 				
		}
		case WM_USER:
		{
			return last_instance_no + 1;
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
		default : 			
		    return DefWindowProc(hWnd, message, wParam, lParam); 
	}
	return 0;
}