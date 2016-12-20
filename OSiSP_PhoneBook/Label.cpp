#include "stdafx.h"
#include "Label.h"


Label::Label(int X, int Y, int nWidth, int nHeight, HWND hWndParent, int editIdentifier, HINSTANCE hInst, tstring caption)
{
	hLabel = CreateWindowEx(
		0,
		(LPCWSTR)WC_EDIT, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL | ES_READONLY,
		X,
		Y,
		nWidth,
		nHeight,
		hWndParent,
		(HMENU)editIdentifier,
		hInst,
		NULL
	);
	SendMessage(hLabel, EM_SETLIMITTEXT, 255, 0);
	SetCaption(caption);
}

void Label::SetCaption(tstring value)
{
	SendMessage(hLabel, WM_SETTEXT, NULL, (LPARAM)value.c_str());
}

tstring Label::GetCaption()
{
	TCHAR text[256];
	SendMessage(hLabel, WM_GETTEXT, 256, (LPARAM)text);
	return tstring(text);
}


Label::~Label()
{
}
