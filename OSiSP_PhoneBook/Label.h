#pragma once

#include <CommCtrl.h>
#include "CommonTTypes.h"

class Label
{
public:
	Label(int X, int Y, int nWidth, int nHeight, HWND hWndParent, int editIdentifier, HINSTANCE hInst, tstring caption);
	void SetCaption(tstring value);
	tstring GetCaption();
	~Label();
private:
	HWND hLabel;
};

