#include "stdafx.h"
#include "PhonebookListView.h"

PhonebookListView::PhonebookListView(int X, int Y, int nWidth, int nHeight, HWND hWndParent, int listViewIdentifier, HINSTANCE hInst, RECT windowRect) : countNodesOnPage(15)
{	
	currentPage = 1;
	countPages = 1;
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
	listViewPhonebook = new ListView(X, Y, nWidth, nHeight, hWndParent, listViewIdentifier, hInst);
	phoneDataBase = new PhoneDataBase(listViewPhonebook->GetHWND(), _T("DataBase.txt"));
	InitPhoneBookList();
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

void PhonebookListView::Refresh(bool isSearchRefresh)
{
	if (!isSearchRefresh)
	{		
		InitPhoneBookList();
	}	
	listViewPhonebook->Clear();
	InitListLiew(false);
	InvalidateRect(listViewPhonebook->GetHWND(), NULL, TRUE);
}

void PhonebookListView::SearchAndRefresh(PhoneBookNode *searchedPhoneBookNode)
{	
	ClearPhoneBookList();
	phoneBookList = phoneDataBase->LoadSearchPhoneBookList(searchedPhoneBookNode);
	Refresh(true);
}

void PhonebookListView::SetCurrentPageAndRefresh(long value)
{
	currentPage = value;
	Refresh();
}

long PhonebookListView::GetCountPages()
{
	return countPages;
}

void PhonebookListView::EditSelectedRow()
{
	int selectedRow = listViewPhonebook->GetSelectedRow();
	if (selectedRow != -1)
	{
		listViewPhonebook->EditLabel(selectedRow);
	}
}

void PhonebookListView::EndEditSelectedRow()
{
	listViewPhonebook->CancelSelection();
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

	if (phoneBookList != nullptr)
	{
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
}

void PhonebookListView::InitPhoneBookList()
{
	ClearPhoneBookList();
	unsigned long countOfPhoneBookNode = phoneDataBase->LoadCountOfPhoneBookNode();
	if ((countOfPhoneBookNode % countNodesOnPage) != 0)
	{
		countPages = (countOfPhoneBookNode / countNodesOnPage) + 1;
	}
	else
	{
		countPages = (countOfPhoneBookNode / countNodesOnPage);
	}		
	phoneBookList = new std::vector<PhoneBookNode*>();
	unsigned long indexCurrentNode = ((countNodesOnPage * (currentPage - 1)) + 1);
	for (int i = 1; i <= countNodesOnPage; ++i)
	{
		PhoneBookNode *phoneBookNode = phoneDataBase->LoadPhoneBookNode(indexCurrentNode);
		if (phoneBookNode != nullptr)
		{
			phoneBookList->push_back(phoneBookNode);
		}
		++indexCurrentNode;		
	}	
}

void PhonebookListView::ClearPhoneBookList()
{
	if (phoneBookList != NULL)
	{
		for (int i = 0; i < phoneBookList->size(); ++i)
		{
			delete((*phoneBookList)[i]);
		}
		delete phoneBookList;
		phoneBookList = NULL;
	}
}

PhonebookListView::~PhonebookListView()
{
	delete listViewPhonebook;
	delete phoneDataBase;
	ClearPhoneBookList();
}


