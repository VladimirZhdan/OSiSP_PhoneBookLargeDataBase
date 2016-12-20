#include "stdafx.h"
#include "WindowManager.h"

#include "Window.h"
#include "MainWindow.h"
#include "EditingWindow.h"

HINSTANCE WindowManager::hInstance;
int WindowManager::nCmdShow;

WindowManager::WindowManager()
{
	mainWindow = NULL;	
	activeWindow = NULL;
	activeWindowType = WINDOW_TYPE::NONE;	
}


WindowManager::~WindowManager()
{
	if (mainWindow != NULL)
	{
		delete(mainWindow);
	}
}

WindowManager * WindowManager::GetInstance()
{
	static WindowManager instance = WindowManager();
	return &instance;
}

Window * WindowManager::GetWindow(WINDOW_TYPE wndType)
{
	switch (wndType)
	{
	case WINDOW_TYPE::MAIN:
		if (mainWindow == NULL)
		{
			mainWindow = new MainWindow();
		}
		return mainWindow;	
	case WINDOW_TYPE::EDITING:
		if (editingWindow == NULL && (currentEditingPhoneBookNode != NULL))
		{
			editingWindow = new EditingWindow(currentEditingPhoneBookNode);
		}
		return editingWindow;
	default:
		return NULL;
	}
}

void WindowManager::ShowWindow(WINDOW_TYPE wndType, bool isCloseActive)
{
	Window* targetWindow = GetWindow(wndType);
	if (isCloseActive)
	{
		CloseActiveWindow();
	}
	targetWindow->Show();
	activeWindow = (Window*)targetWindow;
	activeWindowType = wndType;
}

void WindowManager::SetEditingPhoneBookNode(PhoneBookNode * editingPhoneBookNode)
{
	this->currentEditingPhoneBookNode = editingPhoneBookNode;	
}

void WindowManager::SaveEditedPhoneBookNode(PhoneBookNode * value)
{
	if (mainWindow != NULL)
	{
		mainWindow->SaveEditedPhoneBookNode(value);
	}
}

void WindowManager::CloseActiveWindow()
{
	if ((activeWindow != NULL) && (activeWindowType != WINDOW_TYPE::NONE))
	{
		activeWindow->Hide();
		activeWindow = NULL;
		switch (activeWindowType)
		{
		case WINDOW_TYPE::MAIN:
			delete(mainWindow);
			mainWindow = NULL;
			break;		
		case WINDOW_TYPE::EDITING:
			delete(editingWindow);
			editingWindow = NULL;
			break;
		default:
			break;
		}
		activeWindowType = WINDOW_TYPE::NONE;
	}
}
