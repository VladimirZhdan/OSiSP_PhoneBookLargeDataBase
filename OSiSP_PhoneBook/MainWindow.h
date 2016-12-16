#pragma once

#include "Window.h"
#include "resource.h"
#include "WindowManager.h"

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
	//methods
	void Init();	
	//friends procs
	friend LRESULT CALLBACK MainWndProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);
	//fields	
	bool needRefresh;
};

