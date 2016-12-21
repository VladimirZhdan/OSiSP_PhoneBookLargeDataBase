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
	delete(cBoxSearchCriterion);
	delete(editSearchString);
	delete(btnSearch);
}

void MainWindow::Show()
{
	Window::Show();
}

void MainWindow::Hide()
{
	Window::Hide();
}

void MainWindow::SaveEditedPhoneBookNode(PhoneBookNode *value)
{
	listViewPhonebook->SaveEditedPhoneBookNode(value);
	listViewPhonebook->Refresh();
	SendMessage(hWnd, WM_SIZE, NULL, NULL);
}

void MainWindow::Init()
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
 	listViewPhonebook = new PhonebookListView(0, 50, clientRect.right, clientRect.bottom - 50, hWnd, ID_LISTVIEW_PHONEBOOK, WindowManager::GetHInstance(), clientRect);

	btnRefresh = new Button(clientRect.right - 100, clientRect.top + 10, 100, 30, hWnd, ID_BTN_REFRESH, WindowManager::GetHInstance(), _T("Обновить"));
	btnRefresh->SetEnabled(true);

	cBoxSearchCriterion = new ComboBox(clientRect.left + 10, clientRect.top + 10, 100, 30, hWnd, ID_COMBOBOX_SEARCH, WindowManager::GetHInstance(), 3);
	cBoxSearchCriterion->AddString(_T("Фамилия"));
	cBoxSearchCriterion->AddString(_T("Телефон"));
	cBoxSearchCriterion->AddString(_T("Улица"));

	editSearchString = new Edit(clientRect.left + 150, clientRect.top + 10, 100, 30, hWnd, ID_EDIT_SEARCH, WindowManager::GetHInstance());

	btnSearch = new Button(clientRect.left + 350, clientRect.top + 10, 100, 30, hWnd, ID_BTN_SEARCH, WindowManager::GetHInstance(), _T("Найти"));
	btnSearch->SetEnabled(false);
}

void MainWindow::RefrechListView()
{			
	listViewPhonebook->Refresh();
}

void MainWindow::UdpateWindow()
{
	tstring emptyStr(_T(""));
	bool btnSearchEnabled = false;
	if ((cBoxSearchCriterion->GetSelectedItem() != emptyStr) && (editSearchString->GetText().length() != 0))
	{
		btnSearchEnabled = true;
	}
	btnSearch->SetEnabled(btnSearchEnabled);
}

void MainWindow::SearchPhoneBookList()
{
	tstring searchType = cBoxSearchCriterion->GetSelectedItem();
	tstring searchKey = editSearchString->GetText();
	if (searchType == tstring(_T("Фамилия")))
	{
		listViewPhonebook->SearchAndRefresh(SEARCH_TYPE::SURNAME, (LPTSTR)searchKey.c_str());
	}
	if (searchType == tstring(_T("Телефон")))
	{
		listViewPhonebook->SearchAndRefresh(SEARCH_TYPE::TELEPHONE, (LPTSTR)searchKey.c_str());
	}
	if (searchType == tstring(_T("Улица")))
	{
		listViewPhonebook->SearchAndRefresh(SEARCH_TYPE::STREET, (LPTSTR)searchKey.c_str());
	}
}

void MainWindow::OpenEditingWindow()
{
	PhoneBookNode *selectedItem = listViewPhonebook->GetSelectedItem();
	if (selectedItem != nullptr)
	{
		WindowManager *windowManager = WindowManager::GetInstance();
		windowManager->SetEditingPhoneBookNode(selectedItem);
		windowManager->ShowWindow(WINDOW_TYPE::EDITING);
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
		case ID_EDIT_SEARCH:
		{
			if (wmEvent == EN_UPDATE)
			{
				mainWindow->UdpateWindow();
			}				
		}			
		break;
		case ID_COMBOBOX_SEARCH:
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
		switch (((LPNMHDR)lParam)->code)
		{
		case NM_DBLCLK:
		{		
			mainWindow->OpenEditingWindow();			
		}
		break;		
		break;		
		default:
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}