#include <iostream>
#include <windows.h>
#include <string>
#include "Textbox.h"

using namespace std;

HANDLE hStdin;
DWORD fdwSaveOldMode;
string myString;

VOID KeyEventProc(KEY_EVENT_RECORD, Textbox t);
VOID MouseEventProc(MOUSE_EVENT_RECORD, Textbox t);

int main()
{
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0, countChar = 0;

	Textbox box;

	hStdin = GetStdHandle(STD_INPUT_HANDLE);

	while (counter++ <= 1000)
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

VOID KeyEventProc(KEY_EVENT_RECORD ker, Textbox t)
{
	int x = 0, y = 0, a, b;
	if (GetAsyncKeyState(VK_RETURN) != 0)
	{
		//nothing...
	}
	else if (GetAsyncKeyState(VK_BACK) != 0)
	{
		t.getPosition(x, y);
		a = x;
		b = y;
		if (x <= 8)
			t.position(8, 8);
		else
		{
			cout << "\b" << " " << "\b";
			myString.erase(x - 9, 1);
			t.position(8, 8);
			for (int j = 0; j < 18; j++)
			{
				t.position(8 + j, 8);
				cout << " ";
			}
			t.position(8, 8);
			cout << myString;
			t.position(a - 1, b);
		}


	}
	else if (GetAsyncKeyState(VK_LEFT) != 0)
	{
		t.getPosition(x, y);
		if (x <= 8)
			t.position(8, 8);
		else
			t.position(--x, y);
	}
	else if (GetAsyncKeyState(VK_RIGHT) != 0)
	{
		t.getPosition(x, y);
		if (x >= 25)
			t.position(25, 8);
		else
			t.position(++x, y);
	}
	else if (ker.bKeyDown)
	{
		t.getPosition(x, y);
		if (x >= 26)
		{
			t.position(25, 8);
			myString.pop_back();
		}
		myString += ker.uChar.AsciiChar;
		cout << ker.uChar.AsciiChar;
	}
}

VOID MouseEventProc(MOUSE_EVENT_RECORD mer, Textbox t)
{
	switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED && mer.dwMousePosition.Y == 8 && mer.dwMousePosition.X > 7 && mer.dwMousePosition.X < 26)
		{
			t.position(mer.dwMousePosition.X, 8);
		}
		break;
	default:
		//Nothing...
		break;
	}
}