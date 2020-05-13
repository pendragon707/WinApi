#pragma once

#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <algorithm>

static INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
static INT_PTR CALLBACK AboutDlgProc(HWND, UINT, WPARAM, LPARAM);

#define IDD_MAIN 100
#define IDC_STATIC -1
#define IDC_DATE_SELECTOR 101
#define IDC_COMBOBOX_DEPARTURE 102
#define IDC_COMBOBOX_ARRIVAL 103
#define IDC_TWOWAY_YES 104
#define IDC_TWOWAY_NO 105
#define IDC_TRAIN_ORDINARY 106
#define IDC_TRAIN_EXPRESS 107
#define IDC_TICKET_KIND 108
#define IDC_TICKET_SINGLE 109
#define IDC_TICKET_SUBSCRIPTION 110
#define IDC_PRICE 111
#define IDC_REDUCED 112
#define IDC_PURCHASE 113

#define ICN_PURCHASE 114
#define BMP_IMG 115

#define IDD_ABOUT 200

#define IDMB_MENUBAR 300
#define IDM_MENU_FILE_SAVE 302
#define IDM_MENU_FILE_QUIT 303
#define IDM_ABOUT 304
#define IDM_SAS 305

#define ID_ACCEL 400


