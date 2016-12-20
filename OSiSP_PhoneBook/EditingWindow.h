#pragma once

#include "CommonTTypes.h"
#include "Window.h"
#include "WindowManager.h"
#include "PhoneBookNode.h"
#include "Edit.h"
#include "Label.h"
#include "Button.h"

#define ID_BTN_SAVE 2017	
#define ID_BTN_CANCEL 2018

class EditingWindow : public Window
{
public:
	EditingWindow(PhoneBookNode *phoneBookNode);
	void CloseWindow();
	~EditingWindow();
private:
	//controls
	Edit *editPhoneNumber;
	Edit *editSurname;
	Edit *editName;
	Edit *editPatronymic;
	Edit *editStreet;
	Edit *editHouse;
	Edit *editBuilding;
	Edit *editApartment;

	Label *labelPhoneNumber;
	Label *labelSurname;
	Label *labelName;
	Label *labelPatronymic;
	Label *labelStreet;
	Label *labelHouse;
	Label *labelBuilding;
	Label *labelApartment;

	Button *btnSave;
	Button *btnCancel;

	//methods
	void Init();
	void SaveChanges();
	void CheckAndFillEmptyString(tstring &str);

	static LRESULT CALLBACK EditingWndProc(
		HWND,
		UINT,
		WPARAM,
		LPARAM
	);

	//fields

	PhoneBookNode *editingPhoneBookNode;

	

	
};

