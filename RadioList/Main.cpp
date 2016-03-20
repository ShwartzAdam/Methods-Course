#include <iostream>
#include <Windows.h>
#include "Radiolist.h"

using namespace std;

HANDLE handleMain;
DWORD fdwSaveOldMode;

VOID KeyEventProc(KEY_EVENT_RECORD, Radiolist t);
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
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			t.position(7, row + 7);
			cout << t.options[row];
			if (chosen[row] == 1) {
				t.position(8, row + 7);
				cout << "o";
			}
			--row;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
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
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			t.position(7, row + 7);
			cout << t.options[row];
			if (chosen[row] == 1) {
				t.position(8, row + 7);
				cout << "o";
			}
			++row;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
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
		switch (row) {
		case 0:
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
			break;
		case 1:
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
			break;
		case 2:
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
			break;
		case 3:
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
			break;
		case 4:
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
			break;
		}
	}
	else if (ker.bKeyDown)
	{
		//Do nothing...
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