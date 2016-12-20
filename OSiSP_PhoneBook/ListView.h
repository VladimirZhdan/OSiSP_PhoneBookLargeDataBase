#pragma once

#include <CommCtrl.h>
#include <vector>

class ListView
{
public:
	ListView(int X, int Y, int nWidth, int nHeight, HWND hWndParent, int listViewIdentifier, HINSTANCE hInst);
	HWND GetHWND();		
	void AddColumn(TCHAR *nameColumn, double columnRatio);
	void InsertNewRowWithFirstColumn(TCHAR* firstColumnValue, int &rowIndex);
	void SetItem(int rowIndex, int columnIndex, TCHAR* value);
	int GetCountColumns();
	void ChangeSize(int newX, int newY, int newWidth, int newHeight);
	int GetSelectedRow();
	void EditLabel(int index);
	void CancelEditingLabel();
	void CancelSelection();
	void Clear();
	~ListView();
private:
	void InitParamsWithStartValue();
	HWND hListView;
	LVITEM lvItem;
	LVCOLUMN lvCol;
	int countCols;
	int countRows;
	std::vector<double> columnRatioVector;	

};

