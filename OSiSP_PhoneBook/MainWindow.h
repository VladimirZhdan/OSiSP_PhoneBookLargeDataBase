#pragma once

#include "Window.h"
#include "resource.h"
#include "WindowManager.h"
#include "DialogManager.h"
#include "PhonebookListView.h"
#include "Button.h"
#include "ComboBox.h"
#include "Edit.h"

#define ID_BTN_REFRESH 1000
#define ID_BTN_SEARCH 1001

class MainWindow : public Window
{
public:
	MainWindow();
	~MainWindow();
	void Show();
	void Hide();	
protected:
	//controls	
	
	HMENU hMenu;
	PhonebookListView *listViewPhonebook;

	//methods
	
	void Init();	
	void RefrechListView();
	void UdpateWindow();
	//friends procs
	
	static LRESULT CALLBACK MainWndProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);
	
	//fields	
	
	bool needRefresh;
	Button *btnRefresh;
	Button *btnSearch;
	ComboBox *cBoxSearchCriterion;
	Edit *editSearchString;
};

