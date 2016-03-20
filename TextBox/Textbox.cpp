#include "Textbox.h"



Textbox::Textbox()
{
	DWORD wAttr = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(handle, wAttr);
	CONSOLE_SCREEN_BUFFER_INFO cbi;

	GetConsoleScreenBufferInfo(handle, &cbi);

	DWORD wAttr2 = cbi.wAttributes | BACKGROUND_RED;
	SetConsoleTextAttribute(handle, wAttr2);

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (i == 0 || i == 2)
			{
				position(7 + j, 7 + i);
				if (i == 0 && j == 0)
					cout << "\xC9";
				else if (i == 0 && j == 19)
					cout << "\xBB";
				else if (i == 2 && j == 0)
					cout << "\xC8";
				else if (i == 2 && j == 19)
					cout << "\xBC";
				else
					cout << "\xCD";
			}
			else
			{
				position(7, 7 + i);
				cout << "\xBA";
				position(26, 7 + i);
				cout << "\xBA";
			}
		}

	}
	position(8, 8);
	DWORD a = cbi.wAttributes &  ~(BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	SetConsoleTextAttribute(handle, a);
}


Textbox::~Textbox()
{
}

void Textbox::position(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(handle, pos);
}

void Textbox::getPosition(int &x, int &y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(handle, &csbi)) {
		x = csbi.dwCursorPosition.X;
		y = csbi.dwCursorPosition.Y;
	}
}