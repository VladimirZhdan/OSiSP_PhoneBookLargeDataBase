#pragma once

#include <CommCtrl.h>
#include "CommonTTypes.h"

class Edit
{
public:
	Edit(int X, int Y, int nWidth, int nHeight, HWND hWndParent, int editIdentifier, HINSTANCE hInst);
	void SetText(tstring value);
	tstring GetText();
	~Edit();
private:
	HWND hEdit;
};

