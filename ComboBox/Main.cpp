#include <iostream>
#include <windows.h>
#include <string>
#include "Combobox.h"

using namespace std;

HANDLE hStdin;
DWORD fdwSaveOldMode;
string myString;

VOID KeyEventProc(KEY_EVENT_RECORD, Combobox t);
VOID MouseEventProc(MOUSE_EVENT_RECORD, Combobox t);
void mouseMove(int _row, Combobox _t);
void mouseClick(int _y, Combobox t);
void showList(Combobox t);
int printed = 0, row = 0;

int main()
{
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0, countChar = 0;

	Combobox box;

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(hStdin, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

	while (TRUE)
	{
		if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead))

			fdwMode = ENABLE_WINDOW_INPUT;

		// Dispatch the events to the appropriate handler. 

		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				KeyEventProc(irInBuf[i].Event.KeyEvent, box);
				break;

			case MOUSE_EVENT: // mouse input 
				MouseEventProc(irInBuf[i].Event.MouseEvent, box);
				break;

			default:
				break;
			}
		}
	}
	getchar();
	return 0;
}

VOID KeyEventProc(KEY_EVENT_RECORD ker, Combobox t)
{
	if (printed == 0)
		return;
	int x = 0, y = 0;
	if (GetAsyncKeyState(VK_UP) != 0)
	{
		t.getPosition(x, y);
		if (y == 10)
			t.position(9, 10);
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			t.position(9, row + 10);
			cout << t.options[row];
			--row;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			t.position(9, row + 10);
			cout << t.options[row];
		}

	}
	else if (GetAsyncKeyState(VK_DOWN) != 0)
	{
		t.getPosition(x, y);
		if (y == 14)
			t.position(9, 14);
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			t.position(9, row + 10);
			cout << t.options[row];
			++row;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			t.position(9, row + 10);
			cout << t.options[row];
		}
	}
	else if (GetAsyncKeyState(VK_RETURN) != 0)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		t.position(7, 6);
		cout << "You chose: " << t.options[row];
	}
	else if (ker.bKeyDown)
	{
		//Do nothing...
	}
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer, Combobox t)
{
	switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mer.dwMousePosition.Y == 8 && mer.dwMousePosition.X > 20 && mer.dwMousePosition.X < 26)
			showList(t);
		else if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mer.dwMousePosition.Y > 9 && mer.dwMousePosition.X > 8 && mer.dwMousePosition.X < 17)
			mouseClick(mer.dwMousePosition.Y, t);
		break;
	case MOUSE_MOVED:
		if (mer.dwMousePosition.Y > 9 && mer.dwMousePosition.Y < 15 && mer.dwMousePosition.X > 8 && mer.dwMousePosition.X < 17)
		{
			mouseMove(mer.dwMousePosition.Y, t);
		}

		break;
	default:
		//Nothing...
		break;
	}
}

void showList(Combobox t)
{
	if (printed == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			if (i == 0)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			t.position(9, 10 + i);
			cout << t.options[i];
		}
		printed++;
		row = 0;
		t.position(9, 10);
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
		for (int j = 0; j < 5; j++)
		{
			t.position(9, 10 + j);
			for (int a = 0; a < 13; a++)
			{
				t.position(9 + a, 10 + j);
				cout << " ";
			}
		}
		printed--;
	}
}

void mouseMove(int _row, Combobox _t)
{
	if (printed == 0)
		return;
	for (int i = 0; i < 5; i++)
	{
		_t.position(9, 10 + i);
		if (i == _row - 10)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
		row = _row - 10;
		cout << _t.options[i];
	}
	_t.position(9, _row);
}

void mouseClick(int _y, Combobox t)
{
	if (printed == 0)
		return;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	t.position(7, 6);
	cout << "You chose: " << t.options[row];
}