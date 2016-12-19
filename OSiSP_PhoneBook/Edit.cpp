#include "stdafx.h"
#include "Edit.h"


Edit::Edit(int X, int Y, int nWidth, int nHeight, HWND hWndParent, int editIdentifier, HINSTANCE hInst)
{
	hEdit = CreateWindowEx(
		0,
		(LPCWSTR)WC_EDIT, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		X,
		Y,
		nWidth,
		nHeight,
		hWndParent,
		(HMENU)editIdentifier,
		hInst,
		NULL
	);
	SendMessage(hEdit, EM_SETLIMITTEXT, 255, 0);
	SendMessage(hEdit, EM_SETCUEBANNER, FALSE, (LPARAM)_T("¬ведите..."));
}

void Edit::SetText(tstring value)
{
	SendMessage(hEdit, WM_SETTEXT, NULL, (LPARAM)value.c_str());
}

tstring Edit::GetText()
{
	TCHAR text[256];
	SendMessage(hEdit, WM_GETTEXT, 256, (LPARAM)text);
	return tstring(text);
}

Edit::~Edit()
{
}
