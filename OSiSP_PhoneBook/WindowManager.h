#pragma once

#include "PhoneBookNode.h"

enum class WINDOW_TYPE { NONE, MAIN, EDITING };

class Window;
class MainWindow;
class EditingWindow;

class WindowManager
{
public:
	WindowManager();
	~WindowManager();
	static void SetAppParams(HINSTANCE hInstanceValue, int nCmdShowValue)
	{
		hInstance = hInstanceValue;
		nCmdShow = nCmdShowValue;
	}
	static HINSTANCE GetHInstance()
	{
		return hInstance;
	}
	static int GetNCmdShow()
	{
		return nCmdShow;
	}
	static WindowManager* GetInstance();
	Window* GetWindow(WINDOW_TYPE wndType);
	void ShowWindow(WINDOW_TYPE wndType, bool isCloseActive = false);	
	void SetEditingPhoneBookNode(PhoneBookNode *editingPhoneBookNode);
	void SaveEditedPhoneBookNode(PhoneBookNode *value);
private:
	//fields
	static HINSTANCE hInstance;
	static int nCmdShow;
	MainWindow *mainWindow;	
	EditingWindow *editingWindow;
	Window *activeWindow;
	WINDOW_TYPE activeWindowType;
	PhoneBookNode *currentEditingPhoneBookNode;

	//methods
	void CloseActiveWindow();
};

