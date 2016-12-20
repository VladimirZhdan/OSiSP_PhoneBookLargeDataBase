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
#define ID_EDIT_SEARCH 1021
#define ID_COMBOBOX_SEARCH 1007
#define ID_LISTVIEW_PHONEBOOK 1010

class MainWindow : public Window
{
public:
	MainWindow();
	~MainWindow();
	void Show();
	void Hide();	
	void SaveEditedPhoneBookNode(PhoneBookNode *value);
protected:
	//controls	
	
	HMENU hMenu;
	PhonebookListView *listViewPhonebook;
	Button *btnRefresh;
	Button *btnSearch;
	ComboBox *cBoxSearchCriterion;
	Edit *editSearchString;

	//methods
	
	void Init();	
	void RefrechListView();
	void UdpateWindow();
	void SearchPhoneBookList();
	void OpenEditingWindow();

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

