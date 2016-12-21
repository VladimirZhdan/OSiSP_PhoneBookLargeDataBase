#pragma once

#include "Window.h"
#include "resource.h"
#include "WindowManager.h"
#include "DialogManager.h"
#include "PhonebookListView.h"
#include "Button.h"
#include "ComboBox.h"
#include "Edit.h"
#include "Label.h"

#define ID_BTN_REFRESH 1000
#define ID_BTN_SEARCH 1001
#define ID_EDIT_PHONENUMBER 1021
#define ID_EDIT_SURNAME 1022
#define ID_EDIT_NAME 1023
#define ID_EDIT_PATRONYMIC 1024
#define ID_EDIT_STREET 1025
#define ID_EDIT_HOUSE 1026
#define ID_EDIT_BUILDING 1027
#define ID_EDIT_APARTMENT 1028
#define ID_LISTVIEW_PHONEBOOK 1010
#define ID_COMBOBOX_PAGING 1007
#define ID_BTN_PAGING 1003

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
	Button *btnRefresh;
	Button *btnSearch;
	Label *labelPhoneNumber;
	Label *labelSurname;
	Label *labelName;
	Label *labelPatronymic;
	Label *labelStreet;
	Label *labelHouse;
	Label *labelBuilding;
	Label *labelApartment;

	Edit *editPhoneNumberSearch;
	Edit *editSurnameSearch;
	Edit *editNameSearch;
	Edit *editPatronymicSearch;
	Edit *editStreetSearch;
	Edit *editHouseSearch;
	Edit *editBuildingSearch;
	Edit *editApartmentSearch;

	ComboBox *cBoxPaging;
	Button *btnPaging;
	//methods
	
	void Init();	
	void RefrechListView();
	void UdpateWindow();
	void SearchPhoneBookList();	
	void ChangeCurrentPage();

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

