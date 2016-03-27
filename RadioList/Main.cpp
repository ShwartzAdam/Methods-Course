#include <iostream>
#include <Windows.h>
#include "Radiolist.h"

using namespace std;

HANDLE handleMain;
DWORD fdwSaveOldMode;

VOID KeyEventProc(KEY_EVENT_RECORD, Radiolist t);
VOID MouseEventProc(MOUSE_EVENT_RECORD, Radiolist t);
void mouseMove(int _row, Radiolist _t);
void mouseClick(int _y, Radiolist t);
void clearAll(Radiolist t);
int row = 0;
int chosen[5] = { 0, 0, 0, 0, 0 };

int main()
{
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0, countChar = 0;

	Radiolist list;

	handleMain = GetStdHandle(STD_INPUT_HANDLE);

	while (counter++ <= 1000)
	{
		// Wait for the events. 

		if (!ReadConsoleInput(
			handleMain,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 

			fdwMode = ENABLE_WINDOW_INPUT;

		// Dispatch the events to the appropriate handler. 

		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				KeyEventProc(irInBuf[i].Event.KeyEvent, list);
				break;

			case MOUSE_EVENT: // mouse input 
				MouseEventProc(irInBuf[i].Event.MouseEvent, list);
				break;

			default:
				break;
			}
		}
	}

	getchar();
	return 0;
}

VOID KeyEventProc(KEY_EVENT_RECORD ker, Radiolist t)
{
	int x = 0, y = 0;
	if (GetAsyncKeyState(VK_UP) != 0)
	{
		t.getPosition(x, y);
		if (y <= 7)
			t.position(7, 7);
		else
		{
			SetConsoleTextAttribute(t.handle, FOREGROUND_RED);
			t.position(7, row + 7);
			cout << t.options[row];
			if (chosen[row] == 1) {
				t.position(8, row + 7);
				cout << "o";
			}
			--row;
			SetConsoleTextAttribute(t.handle, FOREGROUND_GREEN);
			t.position(7, row + 7);
			cout << t.options[row];
			if (chosen[row] == 1) {
				t.position(8, row + 7);
				cout << "o";
			}
		}

	}
	else if (GetAsyncKeyState(VK_DOWN) != 0)
	{
		t.getPosition(x, y);
		if (y >= 11)
			t.position(7, 11);
		else
		{
			SetConsoleTextAttribute(t.handle, FOREGROUND_RED);
			t.position(7, row + 7);
			cout << t.options[row];
			if (chosen[row] == 1) {
				t.position(8, row + 7);
				cout << "o";
			}
			++row;
			SetConsoleTextAttribute(t.handle, FOREGROUND_GREEN);
			t.position(7, row + 7);
			cout << t.options[row];
			if (chosen[row] == 1) {
				t.position(8, row + 7);
				cout << "o";
			}
		}
	}
	else if (GetAsyncKeyState(VK_RETURN) != 0)
	{
		if (chosen[row] == 0) {
			clearAll(t);
			t.position(8, row + 7);
			cout << "o";
			chosen[row]++;
		}
		else {
			t.position(8, row + 7);
			cout << " ";
			chosen[row]--;
		}

	}
	else if (ker.bKeyDown)
	{
		//Do nothing...
	}
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer, Radiolist t)
{
	switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mer.dwMousePosition.Y > 6 && mer.dwMousePosition.Y < 12 && mer.dwMousePosition.X > 6 && mer.dwMousePosition.X < 19)
		{
			mouseClick(mer.dwMousePosition.Y, t);
		}
		break;
	case MOUSE_MOVED:
		if (mer.dwMousePosition.Y > 6 && mer.dwMousePosition.Y < 12 && mer.dwMousePosition.X > 6 && mer.dwMousePosition.X < 19)
		{
			mouseMove(mer.dwMousePosition.Y, t);
		}

		break;
	default:
		//Nothing...
		break;
	}
}


void mouseMove(int _row, Radiolist _t)
{
	for (int i = 0; i < 5; i++)
	{
		_t.position(7, 7 + i);
		if (i == _row - 7)
		{
			SetConsoleTextAttribute(_t.handle, FOREGROUND_GREEN);
		}
		else
		{
			SetConsoleTextAttribute(_t.handle, FOREGROUND_RED);
		}
		row = _row - 7;
		cout << _t.options[i];
		if (chosen[i] == 1) {
			_t.position(8, 7 + i);
			cout << "o";
		}
	}
	_t.position(7, _row);
}

void mouseClick(int _y, Radiolist t)
{
	if (chosen[_y - 7] == 0) {
		clearAll(t);
		t.position(8, _y);
		cout << "o";
		chosen[_y - 7]++;
	}
	else {
		t.position(8, _y);
		cout << " ";
		chosen[_y - 7]--;
	}
}

void clearAll(Radiolist t)
{
	for (int i = 0; i < 5; i++)
	{
		chosen[i] = 0;
		t.position(8, i + 7);
		cout << " ";
	}
}