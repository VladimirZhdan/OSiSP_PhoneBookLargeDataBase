#include "stdafx.h"
#include "ListView.h"

ListView::ListView(int X, int Y, int nWidth, int nHeight, HWND hWndParent, int listViewIdentifier, HINSTANCE hInst)
{	
	//INITCOMMONCONTROLSEX icex;           // Structure for control initialization.
	//icex.dwICC = ICC_LISTVIEW_CLASSES;
	//InitCommonControlsEx(&icex);
	hListView = CreateWindowEx(
		0,
		(LPCWSTR)WC_LISTVIEWW, NULL, WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_SHOWSELALWAYS | LVS_REPORT | LVS_SINGLESEL,
		X,
		Y,
		nWidth,
		nHeight,
		hWndParent,
		(HMENU)listViewIdentifier,
		hInst,
		NULL
	);
	SendMessage(hListView, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT); // Set style		
	InitParamsWithStartValue();
}

void ListView::InitParamsWithStartValue()
{
	countCols = 0;
	countRows = 0;

	memset(&lvCol, 0, sizeof(lvCol));
	lvCol.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM | LVCF_FMT;
	lvCol.fmt = LVCFMT_CENTER;

	memset(&lvItem, 0, sizeof(lvItem));
	lvItem.cchTextMax = 256;
}

HWND ListView::GetHWND()
{
	return hListView;
}

void ListView::AddColumn(TCHAR *nameColumn, double columnRatio)
{
	columnRatioVector.push_back(columnRatio);
	lvCol.cx = 0x86;
	lvCol.pszText = nameColumn;
	SendMessage(hListView, LVM_INSERTCOLUMN, countCols, (LPARAM)&lvCol);
	++countCols;
}

void ListView::InsertNewRowWithFirstColumn(TCHAR* firstColumnValue, int &rowIndex)
{
	rowIndex = countRows;
	lvItem.iItem = countRows;
	lvItem.iSubItem = 0;
	lvItem.pszText = firstColumnValue;
	lvItem.mask = LVIF_TEXT;	
	SendMessage(hListView, LVM_INSERTITEM, 0, (LPARAM)&lvItem);
	++countRows;
}

void ListView::SetItem(int rowIndex, int columnIndex, TCHAR* value)
{
	lvItem.iSubItem = columnIndex;
	lvItem.pszText = value;
	SendMessage(hListView, LVM_SETITEM, 0, (LPARAM)&lvItem);
}

int ListView::GetCountColumns()
{
	return countCols;
}

void ListView::ChangeSize(int newX, int newY, int newWidth, int newHeight)
{
	MoveWindow(hListView, newX, newY, newWidth, newHeight, true);
	int widthVertScrollBar = GetSystemMetrics(SM_CXVSCROLL);
	int listViewWidth = (newWidth - widthVertScrollBar);
	int columnWidth;
	for (int i = 0; i < countCols; ++i)
	{
		columnWidth = (int)(columnRatioVector[i] * listViewWidth);
		ListView_SetColumnWidth(hListView, i, columnWidth);
	}
}

int ListView::GetSelectedRow()
{
	int selectedItemNumber;
	selectedItemNumber = SendMessage(hListView, LVM_GETSELECTIONMARK, NULL, NULL);	
	return selectedItemNumber;
}

void ListView::EditLabel(int index)
{
	SendMessage(hListView, LVM_EDITLABEL, index, 0);
}

void ListView::CancelEditingLabel()
{
	SendMessage(hListView, LVM_EDITLABEL, -1, 0);
}

void ListView::CancelSelection()
{
	SendMessage(hListView, LVM_SETSELECTIONMARK, 0, -1);	
}

void ListView::Clear()
{
	SendMessage(hListView, LVM_DELETEALLITEMS, NULL, NULL);
	for (int i = countCols - 1; i >= 0; --i)
	{
		ListView_DeleteColumn(hListView, i);
	}	
	InitParamsWithStartValue();
}

ListView::~ListView()
{	
}