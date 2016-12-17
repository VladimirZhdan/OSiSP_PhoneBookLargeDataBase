#pragma once

#include "Window.h"
#include "resource.h"
#include "WindowManager.h"
#include "DialogManager.h"
#include "PhonebookListView.h"

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
	//friends procs
	
	static LRESULT CALLBACK MainWndProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);
	
	//fields	
	
	bool needRefresh;
};

