#pragma once

#include <tchar.h>
#include <windows.h>
#include "res.h"
#include "stations.h"

static const TCHAR generic_error_title[] = _T("Ошибка");
static const TCHAR wrong_date_msg[] = _T("Неверная дата");
static const TCHAR stations_same_msg[] = _T("Станция отправления и станция прибытия совпадают");
static const TCHAR failed_to_create_msg[] = _T("Не удалось создать файл");
static const TCHAR failed_to_read_msg[] = _T("Не удалось открыть файл");

struct Parameters
{
  SYSTEMTIME st_date;
  FILETIME date;
  const struct Station* from;
  const struct Station* to;
  BOOL twoway : 1;
  BOOL ordinary : 1;
  BOOL single : 1;
  BOOL reduced : 1;
};

static struct Parameters sanitize_and_read_parameters(HWND hwnd)
{
  struct Parameters p;
  p.from = stations + SendDlgItemMessage(hwnd, IDC_COMBOBOX_DEPARTURE, CB_GETCURSEL, 0, 0);
  p.to = stations + SendDlgItemMessage(hwnd, IDC_COMBOBOX_ARRIVAL, CB_GETCURSEL, 0, 0);
  p.twoway = (SendDlgItemMessage(hwnd, IDC_TWOWAY_YES, BM_GETCHECK, 0, 0) == BST_CHECKED);
  p.ordinary = (SendDlgItemMessage(hwnd, IDC_TRAIN_ORDINARY, BM_GETCHECK, 0, 0) == BST_CHECKED);
  //случай с экспрессом
  p.single = p.ordinary ?
    (SendDlgItemMessage(hwnd, IDC_TICKET_SINGLE, BM_GETCHECK, 0, 0) == BST_CHECKED) : TRUE;
  p.reduced = p.ordinary ?
    (SendDlgItemMessage(hwnd, IDC_REDUCED, BM_GETCHECK, 0, 0) == BST_CHECKED) : FALSE;

  EnableWindow(GetDlgItem(hwnd, IDC_TICKET_KIND), p.ordinary);
  EnableWindow(GetDlgItem(hwnd, IDC_TICKET_SINGLE), p.ordinary);
  EnableWindow(GetDlgItem(hwnd, IDC_TICKET_SUBSCRIPTION), p.ordinary);
  EnableWindow(GetDlgItem(hwnd, IDC_REDUCED), p.ordinary);

  SendDlgItemMessage(hwnd, IDC_DATE_SELECTOR, DTM_GETSYSTEMTIME, 0, (LPARAM)&p.st_date);
  p.st_date.wHour = 0;
  p.st_date.wMinute = 0;
  p.st_date.wSecond = 0;
  p.st_date.wMilliseconds = 0;
  SystemTimeToFileTime(&p.st_date, &p.date);

  return p;
}

static int calc_price(const Parameters* const p)
{
  int price = (abs(p->to->zone - p->from->zone) + 1) * 23;
  if (p->twoway) price *= 2;
  if (!p->ordinary) price = (int)((double)price * 1.3);
  if (!p->single) price *= 30;
  if (p->reduced) price /= 2;
  return price;
}

static void buy(HWND hwnd)
{
  const struct Parameters p = sanitize_and_read_parameters(hwnd);

    SYSTEMTIME st_now;
    GetLocalTime(&st_now);
    st_now.wHour = 0;
    st_now.wMinute = 0;
    st_now.wSecond = 0;
    st_now.wMilliseconds = 0;

    FILETIME now;
    SystemTimeToFileTime(&st_now, &now);
    if (CompareFileTime(&p.date, &now) == -1)
    {
      MessageBox(hwnd, wrong_date_msg, generic_error_title, 0);
      return;
    }
 
  if (p.from == p.to)
  {
	  MessageBox(hwnd, stations_same_msg, generic_error_title, 0);
      return;
  }

  FILE* f = _tfopen(_T("ticket.txt"), _T("wb"));
  if (!f)
  {
    MessageBox(hwnd, failed_to_create_msg, generic_error_title, 0);
    return;
  }

  _ftprintf(f, _T("%ls%ls%ls\r\n"),
    p.single ? _T("РАЗОВЫЙ") : _T("АБОНЕМЕНТ"),
    p.ordinary ? _T(" ОБЫЧНЫЙ") : _T(" ЭКСПРЕСС"),
    p.reduced ? _T(" ЛЬГОТНЫЙ") : _T(""));
  _ftprintf(f, _T("%ls%ls%ls\r\n"),
    p.from->name, p.twoway ? _T("<=>") : _T("=>"), p.to->name);
  _ftprintf(f, _T("Полн. цена: %d\r\n"),
    calc_price(&p));
  _ftprintf(f, _T("%02d-%02d-%02d\r\n"),
    p.st_date.wDay, p.st_date.wMonth, p.st_date.wYear % 100),
  _ftprintf(f, _T("Подопригорова Н ИУ5-44б"));
//  _ftprintf(f, TEXT("%llu\r\n"), params_to_int(&p));
  fclose(f);
}

static void put_price(HWND hwnd)
{
  const struct Parameters p = sanitize_and_read_parameters(hwnd);

  std::wostringstream str;
  str << calc_price(&p);
  SendDlgItemMessage(hwnd, IDC_PRICE, WM_SETTEXT, 0, (LPARAM)str.str().c_str());
}