#include "stdafx.h"
#include "PhonebookListView.h"


PhonebookListView::PhonebookListView(int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInst, RECT windowRect)
{
	int windowWidth = windowRect.right - windowRect.left;
	int windowHeight = windowRect.bottom - windowRect.top;
	if (windowWidth != 0)
	{
		this->ratioX = (double)X / windowWidth;
		this->ratioNWidth = (double)nWidth / windowWidth;
	}
	else
	{
		this->ratioX = 0;
		this->ratioNWidth = 0;
	}

	if (windowHeight != 0)
	{
		this->ratioY = (double)Y / windowHeight;
		this->ratioNHeight = (double)nHeight / windowHeight;
	}
	else
	{
		this->ratioY = 0;
		this->ratioNHeight = 0;
	}
	listViewPhonebook = new ListView(X, Y, nWidth, nHeight, hWndParent, hInst);
	InitListLiew();
}

void PhonebookListView::ChangeSize(int newWidth, int newHeight)
{
	int x = (int)(newWidth * ratioX);
	int y = (int)(newHeight * ratioY);
	int nWidht = (int)(newWidth * ratioNWidth);
	int nHeight = (int)(newHeight * ratioNHeight);
	listViewPhonebook->ChangeSize(x, y, nWidht, nHeight);
}

void PhonebookListView::InitListLiew(bool isRefresh)
{
	if (!isRefresh)
	{
		//Inserting Columns	
		listViewPhonebook->AddColumn(_T("Телефон"), 0.13);
		listViewPhonebook->AddColumn(_T("Фамилия"), 0.17);
		listViewPhonebook->AddColumn(_T("Имя"), 0.17);
		listViewPhonebook->AddColumn(_T("Отчество"), 0.17);
		listViewPhonebook->AddColumn(_T("Улица"), 0.15);
		listViewPhonebook->AddColumn(_T("Дом"), 0.05);
		listViewPhonebook->AddColumn(_T("Корпус"), 0.08);
		listViewPhonebook->AddColumn(_T("Квартира"), 0.08);
	}

	/*for (int i = 0; i < programs.size(); ++i)
	{
		int currentRow;
		listViewPrograms->InsertNewRowWithFirstColumn((TCHAR*)programs[i]->GetDisplayName().c_str(), programImageIndex[i], currentRow);

		listViewPrograms->SetItem(currentRow, 1, (TCHAR*)programs[i]->GetSize().c_str());
		listViewPrograms->SetItem(currentRow, 2, (TCHAR*)programs[i]->GetVersion().c_str());
		listViewPrograms->SetItem(currentRow, 3, (TCHAR*)programs[i]->GetInstallDate().c_str());
		listViewPrograms->SetItem(currentRow, 4, (TCHAR*)programs[i]->GetCompany().c_str());
	}*/
}

PhonebookListView::~PhonebookListView()
{
	delete listViewPhonebook;
}


