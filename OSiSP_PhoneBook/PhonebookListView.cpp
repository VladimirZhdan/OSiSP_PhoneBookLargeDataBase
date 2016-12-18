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
	phoneDataBase = new PhoneDataBase(listViewPhonebook->GetHWND());
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

void PhonebookListView::Refresh()
{
	delete phoneBookList;
	listViewPhonebook->Clear();
	InitListLiew(false);
	InvalidateRect(listViewPhonebook->GetHWND(), NULL, TRUE);
}

void PhonebookListView::InitListLiew(bool isRefresh)
{
	phoneBookList = phoneDataBase->LoadPhoneBookList(_T("DataBase.txt"));

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

	for (int i = 0; i < phoneBookList->size(); ++i)
	{
		int currentRow;
		listViewPhonebook->InsertNewRowWithFirstColumn((TCHAR*)(*phoneBookList)[i]->GetPhoneNumber(), currentRow);

		listViewPhonebook->SetItem(currentRow, 1, (TCHAR*)(*phoneBookList)[i]->GetSurname());		
		listViewPhonebook->SetItem(currentRow, 2, (TCHAR*)(*phoneBookList)[i]->GetName());
		listViewPhonebook->SetItem(currentRow, 3, (TCHAR*)(*phoneBookList)[i]->GetPatronymic());
		listViewPhonebook->SetItem(currentRow, 4, (TCHAR*)(*phoneBookList)[i]->GetStreet());
		listViewPhonebook->SetItem(currentRow, 5, (TCHAR*)(*phoneBookList)[i]->GetHouse());
		listViewPhonebook->SetItem(currentRow, 6, (TCHAR*)(*phoneBookList)[i]->GetBuilding());
		listViewPhonebook->SetItem(currentRow, 7, (TCHAR*)(*phoneBookList)[i]->GetApartment());
	}
}

PhonebookListView::~PhonebookListView()
{
	delete listViewPhonebook;
	delete phoneDataBase;
	delete phoneBookList;
}


