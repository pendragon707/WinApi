#include "res.h"
#include "stations.h"
#include "resour.cpp"

#pragma comment(lib, "comctl32.lib")

/*static uint64_t params_to_int(const struct Parameters* params)
{
  uint64_t ret = 0;
  uint8_t* ptr = (uint8_t*)&ret;

  ptr[0] |= (!!params->reduced);
  ptr[0] |= (!!params->single) << 1;
  ptr[0] |= (!!params->ordinary) << 2;
  ptr[0] |= (!!params->twoway) << 3;

  ptr[1] = (uint8_t)(params->to - stations);
  ptr[2] = (uint8_t)(params->from - stations);
  ptr[3] = (uint8_t)(((uint16_t)(params->st_date.wYear) & 0xFF00) >> 8);
  ptr[4] = (uint8_t)((uint16_t)(params->st_date.wYear) & 0x00FF);
  ptr[5] = (uint8_t)(params->st_date.wMonth);
  ptr[6] = (uint8_t)(params->st_date.wDay);
  return ret;
}

static struct Parameters int_to_params(const uint64_t i)
{
  struct Parameters params;
  const uint8_t* ptr = (uint8_t*)&i;

  params.reduced = !!(ptr[0] & 1);
  params.single = !!(ptr[0] & (1 << 1));
  params.ordinary = !!(ptr[0] & (1 << 2));
  params.twoway = !!(ptr[0] & (1 << 3));

  params.to = ptr[1] + stations;
  params.from = ptr[2] + stations;
  params.st_date.wYear = (((uint16_t)ptr[3]) << 8) | ((uint16_t)ptr[4]);
  params.st_date.wMonth = ptr[5];
  params.st_date.wDay = ptr[6];
  return params;
}*/

/*#ifndef UNICODE
  #define tifstream std::ifstream
  #define tstring std::string
  #define tstringstream std::stringstream
#else
  #define tifstream std::wifstream
  #define tstring std::wstring
  #define tstringstream std::wstringstream
#endif
  
 static void read_ticket(HWND hwnd)
{
  tifstream f(TEXT("ticket.txt"), std::ios::in | std::ios::binary);
  if (!f.is_open())
  {
    MessageBox(hwnd, failed_to_read_msg, generic_error_title, 0);
    return;
  }

  tstring s;
  for (size_t i = 0; i < 5; i++)
  {
    if (!std::getline(f, s))
    {
      MessageBox(hwnd, failed_to_read_msg, generic_error_title, 0);
      return;
    }
  }
  f.close();

  s.erase(std::remove(s.begin(), s.end(), 0), s.end());

  uint64_t iparams;
  tstringstream ss(s);
  ss >> iparams;

  struct Parameters params = int_to_params(iparams);
  SendDlgItemMessage(hwnd, IDC_REDUCED, BM_SETCHECK, params.reduced ? BST_CHECKED : BST_UNCHECKED, 0);

  SendDlgItemMessage(hwnd, IDC_TICKET_SINGLE, BM_SETCHECK, params.single ? BST_CHECKED : BST_UNCHECKED, 0);
  SendDlgItemMessage(hwnd, IDC_TRAIN_ORDINARY, BM_SETCHECK, params.ordinary ? BST_CHECKED : BST_UNCHECKED, 0);
  SendDlgItemMessage(hwnd, IDC_TWOWAY_YES, BM_SETCHECK, params.twoway ? BST_CHECKED : BST_UNCHECKED, 0);

  SendDlgItemMessage(hwnd, IDC_TICKET_SUBSCRIPTION, BM_SETCHECK, params.single ? BST_UNCHECKED : BST_CHECKED, 0);
  SendDlgItemMessage(hwnd, IDC_TRAIN_EXPRESS, BM_SETCHECK, params.ordinary ? BST_UNCHECKED : BST_CHECKED, 0);
  SendDlgItemMessage(hwnd, IDC_TWOWAY_NO, BM_SETCHECK, params.twoway ? BST_UNCHECKED : BST_CHECKED, 0);

  SendDlgItemMessage(hwnd, IDC_COMBOBOX_DEPARTURE, CB_SETCURSEL, params.from - stations, 0);
  SendDlgItemMessage(hwnd, IDC_COMBOBOX_ARRIVAL, CB_SETCURSEL, params.to - stations, 0);
  SendDlgItemMessage(hwnd, IDC_DATE_SELECTOR, DTM_SETSYSTEMTIME, 0, (LPARAM)&params.st_date);
  put_price(hwnd);
}*/

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd)
{
//  (void)hPrevInstance;
//  (void)lpCmdLine;
//  (void)nShowCmd;

/*WNDCLASSEX wc = { 0 };
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.lpfnWndProc = WndProc;
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(rand(), rand(), rand()));
  wc.lpszMenuName = 0;
  wc.lpszClassName = L"h ";
  wc.hIcon = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDC_PURCHASE), IMAGE_ICON, 16, 16, 0);
  wc.hIconSm = (HICON)LoadImage(hInst, MAKEINTRESOURCE(IDC_PURCHASE), IMAGE_ICON, 16, 16, 0);
  wc.hCursor = LoadCursor(0, IDC_ARROW);
  if (!RegisterClassEx(&wc))
  {
    DeleteObject(wc.hbrBackground);
    return 1;
  }

  const HWND hWnd = CreateWindowEx(0, L"h ", L"h ",
    WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 400, 0, 0, hInst, 0);
  if (!hWnd)
  {
    DeleteObject(wc.hbrBackground);
    UnregisterClass(L"h ", hInst);
    return 1;
  }
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  MSG msg;
  while (GetMessage(&msg, 0, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  DeleteObject(wc.hbrBackground);
  UnregisterClass(L"h ", hInst);
  return 0;*/
  
  INITCOMMONCONTROLSEX icc;
  icc.dwSize = sizeof(icc);
  icc.dwICC = ICC_USEREX_CLASSES | ICC_DATE_CLASSES | ICC_STANDARD_CLASSES;
  InitCommonControlsEx(&icc);

  HACCEL accels = LoadAccelerators(hInst, MAKEINTRESOURCE(ID_ACCEL));
  if (!accels) return 1;

  HWND hwnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_MAIN), 0, DlgProc);
  ShowWindow(hwnd, SW_SHOWNORMAL);
  UpdateWindow(hwnd);

  MSG msg;
  while (GetMessage(&msg, 0, 0, 0))
  {
    if (!TranslateAccelerator(hwnd, accels, &msg))
    {
      if (!IsDialogMessage(hwnd, &msg))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }
  }
    DestroyAcceleratorTable(accels);

  return 0;
}

static INT_PTR CALLBACK AboutDlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
//  (void)wParam;
//  (void)lParam;
  switch (message)
  {
    case WM_CLOSE:
      EndDialog(hwnd, 0);
      return TRUE;
  }
  return FALSE;
}

/*void funCreateMenu(HWND hWnd){
    HMENU menu          = CreateMenu();
    HMENU sub_menu      = CreateMenu();

	HBITMAP check   = (HBITMAP)LoadImage(0, MAKEINTRESOURCE(BMP_IMG), IMAGE_BITMAP, SM_CXMENUCHECK, SM_CYMENUCHECK, 0);

	MENUITEMINFO mii_menu = { 0 };
        mii_menu.cbSize         = sizeof(MENUITEMINFO);
        mii_menu.fMask          = MIIM_FTYPE | MIIM_STRING | MIIM_ID;
        mii_menu.fType          = MFT_STRING;
        mii_menu.dwTypeData     = L"File"; 
        mii_menu.cch            = sizeof(L"File");
        mii_menu.wID            = 1;
		mii_menu.hbmpItem = check;
		mii_menu.hbmpChecked = check;

    InsertMenuItem(menu,    0, FALSE, &mii_menu);

    SetMenu(hWnd, menu);
};*/

static INT_PTR CALLBACK DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch (message)
  {
    case WM_INITDIALOG:
    {
      for (size_t i = 0; i < sizeof(stations) / sizeof(stations[0]); i++)    //запоплняем комбобоксы со станциями 
      {
        SendDlgItemMessage(hwnd, IDC_COMBOBOX_DEPARTURE, CB_ADDSTRING, 0, (LPARAM)stations[i].name);
        SendDlgItemMessage(hwnd, IDC_COMBOBOX_ARRIVAL, CB_ADDSTRING, 0, (LPARAM)stations[i].name);
      }
      SendDlgItemMessage(hwnd, IDC_COMBOBOX_DEPARTURE, CB_SETCURSEL, 0, 0);   //значения по умолчанию
      SendDlgItemMessage(hwnd, IDC_COMBOBOX_ARRIVAL, CB_SETCURSEL, 1, 0);

      SendDlgItemMessage(hwnd, IDC_TWOWAY_NO, BM_SETCHECK, BST_CHECKED, 0);
      SendDlgItemMessage(hwnd, IDC_TRAIN_ORDINARY, BM_SETCHECK, BST_CHECKED, 0);
      SendDlgItemMessage(hwnd, IDC_TICKET_SINGLE, BM_SETCHECK, BST_CHECKED, 0);

      HICON icon_purchase = (HICON)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(ICN_PURCHASE), IMAGE_ICON, 16, 16, 0);

	  SendMessage(hwnd, WM_SETICON, IMAGE_ICON, (LPARAM)icon_purchase);
      DestroyIcon(icon_purchase);
//	  SendDlgItemMessage(, IDC_PURCHASE, BM_SETIMAGE, IMAGE_ICON, (LPARAM)icon_purchase);
//	  funCreateMenu(hwnd);

	    /*MENUITEMINFO mii;
		HMENU hmenuBar = GetMenu(hwnd);
		HBITMAP bmp_purchase = (HBITMAP)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(BMP_IMG), IMAGE_BITMAP, 16, 16, 0);

  
		GetMenuItemInfo(hmenuBar, 0, FALSE, &mii); 
		mii.hbmpItem = bmp_purchase;
		InsertMenuItem(hmenuBar, 0, FALSE, &mii);
		SetMenuItemInfo(hmenuBar, 0, FALSE, &mii);
		SetMenu(hwnd, hmenuBar);*/

	/*	HBITMAP bmp1 = (HBITMAP)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(BMP_IMG), IMAGE_BITMAP, 20, 20, 0);
		HBITMAP bmp2 = (HBITMAP)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(BMP_IMG), IMAGE_BITMAP, 25, 25, 0);
		HBITMAP bmp3 = (HBITMAP)LoadImage(GetModuleHandle(0), MAKEINTRESOURCE(BMP_IMG), IMAGE_BITMAP, 30, 30, 0);
		AppendMenu(GetMenu(hwnd), MF_BITMAP, BMP_IMG, (LPCWSTR) bmp1);
		AppendMenu(GetMenu(hwnd), MF_BITMAP, BMP_IMG, (LPCWSTR) bmp3);
		AppendMenu(GetMenu(hwnd), MF_BITMAP, BMP_IMG, (LPCWSTR) bmp2);
		AppendMenu(GetMenu(hwnd), MF_BITMAP, BMP_IMG, (LPCWSTR) bmp3);
		AppendMenu(GetMenu(hwnd), MF_BITMAP, BMP_IMG, (LPCWSTR) bmp1);
		AppendMenu(GetMenu(hwnd), MF_BITMAP, BMP_IMG, (LPCWSTR) bmp2);
		AppendMenu(GetMenu(hwnd), MF_BITMAP, BMP_IMG, (LPCWSTR) bmp1);*/
/*      HCURSOR hand = LoadCursor(0, IDC_HAND);
      SetClassLongPtr(GetDlgItem(hwnd, IDC_TWOWAY_YES), GCL_HCURSOR, (LONG_PTR)hand);
      SetClassLongPtr(GetDlgItem(hwnd, IDC_TWOWAY_NO), GCL_HCURSOR, (LONG_PTR)hand);
      SetClassLongPtr(GetDlgItem(hwnd, IDC_TRAIN_ORDINARY), GCL_HCURSOR, (LONG_PTR)hand);
      SetClassLongPtr(GetDlgItem(hwnd, IDC_TRAIN_EXPRESS), GCL_HCURSOR, (LONG_PTR)hand);
      SetClassLongPtr(GetDlgItem(hwnd, IDC_TICKET_SINGLE), GCL_HCURSOR, (LONG_PTR)hand);
      SetClassLongPtr(GetDlgItem(hwnd, IDC_TICKET_SUBSCRIPTION), GCL_HCURSOR, (LONG_PTR)hand);
      SetClassLongPtr(GetDlgItem(hwnd, IDC_REDUCED), GCL_HCURSOR, (LONG_PTR)hand);
      SetClassLongPtr(GetDlgItem(hwnd, IDC_PURCHASE), GCL_HCURSOR, (LONG_PTR)hand);
      DestroyCursor(hand);*/

      put_price(hwnd);
      return TRUE;
    }
    case WM_CLOSE:
      DestroyWindow(hwnd);
      return TRUE;
    case WM_DESTROY:
      PostQuitMessage(0);
      return TRUE;

    case WM_COMMAND:
	  if (LOWORD(wParam) == IDM_MENU_FILE_SAVE)
      {
        buy(hwnd);
        return TRUE;
      }
      else if (LOWORD(wParam) == IDM_MENU_FILE_QUIT)
      {
        PostQuitMessage(0);
        return TRUE;
      }
      else if (LOWORD(wParam) == IDM_ABOUT)
      {
        DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
        return TRUE;
      }

      else if (HIWORD(wParam) == BN_CLICKED)
      {
        switch (LOWORD(wParam))
        {
          case IDC_PURCHASE:
            buy(hwnd);
            return TRUE;
          case IDC_TWOWAY_YES:
          case IDC_TWOWAY_NO:
          case IDC_TRAIN_ORDINARY:
          case IDC_TRAIN_EXPRESS:
          case IDC_TICKET_SINGLE:
          case IDC_TICKET_SUBSCRIPTION:
          case IDC_REDUCED:
            put_price(hwnd);
            return TRUE;
          default:
            break;
        }
      }
      else if (HIWORD(wParam) == CBN_SELCHANGE)
      {
        switch (LOWORD(wParam))
        {
          case IDC_COMBOBOX_DEPARTURE:
          case IDC_COMBOBOX_ARRIVAL:
            put_price(hwnd);
            return TRUE;
          default:
            break;
        }
      }
      break;
  }
  return FALSE;
}

