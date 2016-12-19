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
 	listViewPhonebook = new PhonebookListView(0, 50, clientRect.right, clientRect.bottom - 50, hWnd, WindowManager::GetHInstance(), clientRect);

	btnRefresh = new Button(clientRect.right - 100, clientRect.top + 10, 100, 30, hWnd, ID_BTN_REFRESH, WindowManager::GetHInstance(), _T("Обновить"));
	btnRefresh->SetEnabled(true);

	cBoxSearchCriterion = new ComboBox(clientRect.left + 10, clientRect.top + 10, 100, 30, hWnd, WindowManager::GetHInstance(), 3);
	cBoxSearchCriterion->AddString(_T("Фамилия"));
	cBoxSearchCriterion->AddString(_T("Телефон"));
	cBoxSearchCriterion->AddString(_T("Улица"));
}

void MainWindow::RefrechListView()
{
	listViewPhonebook->Refresh();
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
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:
		if (wmEvent == BN_CLICKED)
		{
			switch (wmId)
			{
			case ID_BTN_REFRESH:
				{
					mainWindow->RefrechListView();
					SendMessage(hWnd, WM_SIZE, NULL, NULL);
				}
				break;
			}
		}

		switch (wmId)
		{
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
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}