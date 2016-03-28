#include <iostream>
#include "Label.h"

using namespace std;

VOID KeyEventProc(KEY_EVENT_RECORD);

int main()
{
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	int counter = 0;

	Label myLabel("Hello World! This Is A Label!");

	HANDLE handleMain = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(handleMain, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);

	while (TRUE)
	{
		if (!ReadConsoleInput(handleMain,irInBuf,128,&cNumRead)) 

			fdwMode = ENABLE_WINDOW_INPUT;

		// Dispatch the events to the appropriate handler. 

		for (i = 0; i < cNumRead; i++)
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				KeyEventProc(irInBuf[i].Event.KeyEvent);
				break;

			default:
				break;
			}
		}
	}
	getchar();
	return 0;
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
	if (ker.bKeyDown)
	{
		//Do nothing...
	}
}