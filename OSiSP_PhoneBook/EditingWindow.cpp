#include "stdafx.h"
#include "EditingWindow.h"

EditingWindow::EditingWindow(PhoneBookNode * phoneBookNode) : Window(EditingWndProc, _T("EDITINGWINDOW"), _T("Изменение записи"), WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX, 400, 450, WindowManager::GetInstance()->GetWindow(WINDOW_TYPE::MAIN)->GetHwnd())
{
	this->editingPhoneBookNode = phoneBookNode;
	Init();
}

void EditingWindow::CloseWindow()
{
	WindowManager *windowManager = WindowManager::GetInstance();
	windowManager->ShowWindow(WINDOW_TYPE::MAIN, true);
}

EditingWindow::~EditingWindow()
{
}

void EditingWindow::Init()
{
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);

	editPhoneNumber = new Edit(clientRect.right - 200, clientRect.top + 10, 150, 30, hWnd, 0, WindowManager::GetHInstance());
	editPhoneNumber->SetText(editingPhoneBookNode->GetPhoneNumber());
	editSurname = new Edit(clientRect.right - 200, clientRect.top + 50, 150, 30, hWnd, 0, WindowManager::GetHInstance());
	editSurname->SetText(editingPhoneBookNode->GetSurname());
	editName = new Edit(clientRect.right - 200, clientRect.top + 90, 150, 30, hWnd, 0, WindowManager::GetHInstance());
	editName->SetText(editingPhoneBookNode->GetName());
	editPatronymic = new Edit(clientRect.right - 200, clientRect.top + 130, 150, 30, hWnd, 0, WindowManager::GetHInstance());
	editPatronymic->SetText(editingPhoneBookNode->GetPatronymic());
	editStreet = new Edit(clientRect.right - 200, clientRect.top + 170, 150, 30, hWnd, 0, WindowManager::GetHInstance());
	editStreet->SetText(editingPhoneBookNode->GetStreet());
	editHouse = new Edit(clientRect.right - 200, clientRect.top + 210, 150, 30, hWnd, 0, WindowManager::GetHInstance());
	editHouse->SetText(editingPhoneBookNode->GetHouse());
	editBuilding = new Edit(clientRect.right - 200, clientRect.top + 250, 150, 30, hWnd, 0, WindowManager::GetHInstance());
	editBuilding->SetText(editingPhoneBookNode->GetBuilding());
	editApartment = new Edit(clientRect.right - 200, clientRect.top + 290, 150, 30, hWnd, 0, WindowManager::GetHInstance());
	editApartment->SetText(editingPhoneBookNode->GetApartment());

	labelPhoneNumber = new Label(clientRect.left + 50, clientRect.top + 10, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Телефон"));
	labelSurname = new Label(clientRect.left + 50, clientRect.top + 50, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Фамилия"));
	labelName = new Label(clientRect.left + 50, clientRect.top + 90, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Имя"));
	labelPatronymic = new Label(clientRect.left + 50, clientRect.top + 130, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Отчество"));
	labelStreet = new Label(clientRect.left + 50, clientRect.top + 170, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Улица"));
	labelHouse = new Label(clientRect.left + 50, clientRect.top + 210, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Дом"));
	labelBuilding = new Label(clientRect.left + 50, clientRect.top + 250, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Корпус"));
	labelApartment = new Label(clientRect.left + 50, clientRect.top + 290, 100, 30, hWnd, 0, WindowManager::GetHInstance(), _T("Квартира"));

	btnSave = new Button(clientRect.left + 50, clientRect.top + 350, 100, 30, hWnd, ID_BTN_SAVE, WindowManager::GetHInstance(), _T("Сохранить"));
	btnSave->SetEnabled(true);

	btnCancel = new Button(clientRect.right - 150, clientRect.top + 350, 100, 30, hWnd, ID_BTN_SAVE, WindowManager::GetHInstance(), _T("Отмена"));
	btnCancel->SetEnabled(true);
}

void EditingWindow::SaveChanges()
{
	tstring *phoneNumber = new tstring(editPhoneNumber->GetText());
	CheckAndFillEmptyString(*phoneNumber);
	tstring surname = editSurname->GetText();
	CheckAndFillEmptyString(surname);
	tstring name = editName->GetText();
	CheckAndFillEmptyString(name);
	tstring patronymic = editPatronymic->GetText();
	CheckAndFillEmptyString(patronymic);
	tstring street = editStreet->GetText();
	CheckAndFillEmptyString(street);
	tstring house = editHouse->GetText();
	CheckAndFillEmptyString(house);
	tstring building = editBuilding->GetText();
	CheckAndFillEmptyString(building);
	tstring apartment = editApartment->GetText();
	CheckAndFillEmptyString(apartment);
	PhoneBookNode *editedPhoneBookNode = new PhoneBookNode((LPTSTR)(*phoneNumber).c_str(), (LPTSTR)surname.c_str(), (LPTSTR)name.c_str(), 
		(LPTSTR)patronymic.c_str(), (LPTSTR)street.c_str(), (LPTSTR)house.c_str(), (LPTSTR)building.c_str(), (LPTSTR)apartment.c_str());
	editedPhoneBookNode->number = editingPhoneBookNode->number;
	
	WindowManager *windowManager = WindowManager::GetInstance();
	windowManager->SaveEditedPhoneBookNode(editedPhoneBookNode);
}

void EditingWindow::CheckAndFillEmptyString(tstring &str)
{
	if (str.length() == 0)
	{
		str = _T("-");
	}
}

LRESULT CALLBACK EditingWindow::EditingWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_GETMINMAXINFO:
	{
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 400;
		lpMMI->ptMinTrackSize.y = 450;
		lpMMI->ptMaxTrackSize.x = 400;
		lpMMI->ptMaxTrackSize.y = 450;
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);
		// Разобрать выбор в меню:		
		switch (wmId)
		{		
		case ID_BTN_SAVE:
		{
			if (wmEvent == BN_CLICKED)
			{
				EditingWindow *editingWindow = (EditingWindow*)((WindowManager::GetInstance())->GetWindow(WINDOW_TYPE::EDITING));
				editingWindow->SaveChanges();
				SendMessage(hWnd, WM_DESTROY, NULL, NULL);
			}
		}
		case ID_BTN_CANCEL:
		{
			if (wmEvent == BN_CLICKED)
			{
				SendMessage(hWnd, WM_DESTROY, NULL, NULL);
			}
		}
		break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_SIZE:
	{
		
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
		{
			EditingWindow *editingWindow = (EditingWindow*)((WindowManager::GetInstance())->GetWindow(WINDOW_TYPE::EDITING));
			editingWindow->CloseWindow();
		}		
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


