#pragma once

#include "ListView.h"
#include "PhoneDataBase.h"
#include <vector>

class PhonebookListView
{
public:
	PhonebookListView(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst, RECT windowRect);
	void ChangeSize(int newWidth, int newHeight);
	void Refresh();
	~PhonebookListView();

private:	
	//methods

	void InitListLiew(bool isRefresh = false);	

	//fields

	ListView *listViewPhonebook;
	double ratioX;
	double ratioY;
	double ratioNWidth;
	double ratioNHeight;
	PhoneDataBase *phoneDataBase;
	std::vector<PhoneBookNode*>* phoneBookList;

};

