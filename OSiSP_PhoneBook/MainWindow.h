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
	ComboBox *cBoxSearchCriterion;
	Edit *editSearchString;
};

