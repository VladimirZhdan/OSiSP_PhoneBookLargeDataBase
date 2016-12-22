#include "stdafx.h"
#include "MainWindow.h"


MainWindow::MainWindow() : Window(MainWndProc, _T("MAINWINDOW"), _T("Телефонный справочник"), WS_OVERLAPPEDWINDOW, 1024, 768, nullptr)
{
	hMenu = LoadMenu(WindowManager::GetHInstance(), MAKEINTRESOURCE(IDC_OSISP_PHONEBOOK));
	SetMenu(hWnd, hMenu);
	Init();
	needRefresh = false;
}


MainWindow::~MainWindow()
{
	delete(listViewPhonebook);
	delete(btnRefresh);		
	delete(btnSearch);

	delete(labelPhoneNumber);
	delete(labelSurname);
	delete(labelName);
	delete(labelPatronymic);
	delete(labelStreet);
	delete(labelHouse);
	delete(labelBuilding);
	delete(labelApartment);

	delete(editPhoneNumberSearch);
	delete(editSurnameSearch);
	delete(editNameSearch);
	delete(editPatronymicSearch);
	delete(editStreetSearch);
	delete(editHouseSearch);
	delete(editBuildingSearch);
	delete(editApartmentSearch);

	delete(cBoxPaging);
}

void MainWindow::Show()
{
	Window::Show();
}

void MainWindow::Hide()
{
	Window::Hide();
}

void MainWindow::Init()
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
 	listViewPhonebook = new PhonebookListView(0, 160, clientRect.right, clientRect.bottom - 200, hWnd, ID_LISTVIEW_PHONEBOOK, WindowManager::GetHInstance(), clientRect);

	btnRefresh = new Button(clientRect.right - 100, clientRect.top + 10, 100, 30, hWnd, ID_BTN_REFRESH, WindowManager::GetHInstance(), _T("Обновить"));
	btnRefresh->SetEnabled(true);

	labelPhoneNumber = new Label(clientRect.left + 10, clientRect.top + 10, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Телефон"));
	labelSurname = new Label(clientRect.left + 10, clientRect.top + 50, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Фамилия"));
	labelName = new Label(clientRect.left + 10, clientRect.top + 90, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Имя"));
	labelPatronymic = new Label(clientRect.left + 10, clientRect.top + 130, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Отчество"));
	labelStreet = new Label(clientRect.left + 300, clientRect.top + 10, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Улица"));
	labelHouse = new Label(clientRect.left + 300, clientRect.top + 50, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Дом"));
	labelBuilding = new Label(clientRect.left + 300, clientRect.top + 90, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Корпус"));
	labelApartment = new Label(clientRect.left + 300, clientRect.top + 130, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Квартира"));

	editPhoneNumberSearch = new Edit(clientRect.left + 120, clientRect.top + 10, 150, 30, hWnd, ID_EDIT_PHONENUMBER, WindowManager::GetHInstance());
	editSurnameSearch = new Edit(clientRect.left + 120, clientRect.top + 50, 150, 30, hWnd, ID_EDIT_SURNAME, WindowManager::GetHInstance());
	editNameSearch = new Edit(clientRect.left + 120, clientRect.top + 90, 150, 30, hWnd, ID_EDIT_NAME, WindowManager::GetHInstance());
	editPatronymicSearch = new Edit(clientRect.left + 120, clientRect.top + 130, 150, 30, hWnd, ID_EDIT_PATRONYMIC, WindowManager::GetHInstance());
	editStreetSearch = new Edit(clientRect.left + 410, clientRect.top + 10, 150, 30, hWnd, ID_EDIT_STREET, WindowManager::GetHInstance());
	editHouseSearch = new Edit(clientRect.left + 410, clientRect.top + 50, 150, 30, hWnd, ID_EDIT_HOUSE, WindowManager::GetHInstance());
	editBuildingSearch = new Edit(clientRect.left + 410, clientRect.top + 90, 150, 30, hWnd, ID_EDIT_BUILDING, WindowManager::GetHInstance());
	editApartmentSearch = new Edit(clientRect.left + 410, clientRect.top + 130, 150, 30, hWnd, ID_EDIT_APARTMENT, WindowManager::GetHInstance());

	btnSearch = new Button(clientRect.left + 650, clientRect.top + 10, 100, 30, hWnd, ID_BTN_SEARCH, WindowManager::GetHInstance(), _T("Найти"));
	btnSearch->SetEnabled(false);

	long countPages = listViewPhonebook->GetCountPages();
	cBoxPaging = new ComboBox(clientRect.left + 650, clientRect.top + 90, 100, 30, hWnd, ID_COMBOBOX_PAGING, WindowManager::GetHInstance(), countPages);
	for (long i = 1; i <= countPages; ++i)
	{
		cBoxPaging->AddString(to_tstring(i));
	}

	btnPaging = new Button(clientRect.left + 770, clientRect.top + 90, 100, 30, hWnd, ID_BTN_PAGING, WindowManager::GetHInstance(), _T("Перейти"));
	btnPaging->SetEnabled(false);
}

void MainWindow::RefrechListView()
{			
	listViewPhonebook->Refresh();
}

void MainWindow::UdpateWindow()
{
	tstring emptyStr(_T(""));
	bool btnSearchEnabled = false;
	if ((editPhoneNumberSearch->GetText().length() != 0))
	{
		btnSearchEnabled = true;
	}
	if ((editSurnameSearch->GetText().length() != 0))
	{
		btnSearchEnabled = true;
	}
	if ((editNameSearch->GetText().length() != 0))
	{
		btnSearchEnabled = true;
	}
	if ((editPatronymicSearch->GetText().length() != 0))
	{
		btnSearchEnabled = true;
	}
	if ((editStreetSearch->GetText().length() != 0))
	{
		btnSearchEnabled = true;
	}
	if ((editHouseSearch->GetText().length() != 0))
	{
		btnSearchEnabled = true;
	}
	if ((editBuildingSearch->GetText().length() != 0))
	{
		btnSearchEnabled = true;
	}
	if ((editApartmentSearch->GetText().length() != 0))
	{
		btnSearchEnabled = true;
	}
	btnSearch->SetEnabled(btnSearchEnabled);

	if (cBoxPaging->GetIndexSelectedItem() == -1)
	{
		btnPaging->SetEnabled(false);
	}
	else
	{
		btnPaging->SetEnabled(true);
	}
}

void MainWindow::SearchPhoneBookList()
{	
	tstring phoneNumber(editPhoneNumberSearch->GetText());
	tstring surname(editSurnameSearch->GetText());
	tstring name(editNameSearch->GetText());
	tstring patronymic(editPatronymicSearch->GetText());
	tstring street(editStreetSearch->GetText());
	tstring house(editHouseSearch->GetText());
	tstring building(editBuildingSearch->GetText());
	tstring apartment(editApartmentSearch->GetText());

	PhoneBookNode *searchedPhoneBookNode = new PhoneBookNode((LPTSTR)phoneNumber.c_str(), (LPTSTR)surname.c_str(), (LPTSTR)name.c_str(), (LPTSTR)patronymic.c_str(), 
		(LPTSTR)street.c_str(), (LPTSTR)house.c_str(), (LPTSTR)building.c_str(), (LPTSTR)apartment.c_str());
	
	listViewPhonebook->SearchAndRefresh(searchedPhoneBookNode);

	delete(searchedPhoneBookNode);
}

void MainWindow::ChangeCurrentPage()
{
	long indexSelectedPage = cBoxPaging->GetIndexSelectedItem();
	if (indexSelectedPage != -1)
	{
		listViewPhonebook->SetCurrentPageAndRefresh(indexSelectedPage + 1);
	}
}

static MainWindow *mainWindow = (MainWindow*)((WindowManager::GetInstance())->GetWindow(WINDOW_TYPE::MAIN));

LRESULT CALLBACK MainWindow::MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 1024;
		lpMMI->ptMinTrackSize.y = 768;
	}
	break;		
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:	

		if ((wmEvent == EN_UPDATE) && (mainWindow != NULL))
		{
			mainWindow->UdpateWindow();
		}

		switch (wmId)
		{
		case ID_LISTVIEW_PHONEBOOK:
		{
			if (wmEvent == LVN_ENDLABELEDIT)
			{
				int i = 0;
			}		
		}
		break;
		case ID_BTN_REFRESH:
		{
			if (wmEvent == BN_CLICKED)
			{
				mainWindow->RefrechListView();
				SendMessage(hWnd, WM_SIZE, NULL, NULL);
			}
		}
		break;
		case ID_BTN_SEARCH:
		{
			if (wmEvent == BN_CLICKED)
			{
				mainWindow->SearchPhoneBookList();
				SendMessage(hWnd, WM_SIZE, NULL, NULL);
			}
		}
		break;
		case ID_BTN_PAGING:
		{
			if (wmEvent == BN_CLICKED)
			{
				mainWindow->ChangeCurrentPage();
				SendMessage(hWnd, WM_SIZE, NULL, NULL);
			}
		}
		break;
		case ID_COMBOBOX_PAGING:
		{
			if (wmEvent == CBN_SELCHANGE)
			{
				mainWindow->UdpateWindow();
			}
		}
		break;
		case IDM_ABOUT:
			DialogManager::GetInstance()->ShowDialog(DIALOG_TYPE::ABOUT, hWnd);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_SIZE:
	{
		RECT clientRect;
		GetWindowRect(hWnd, &clientRect);
		if (mainWindow != nullptr)
		{
			mainWindow->listViewPhonebook->ChangeSize(clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_NOTIFY:		
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}