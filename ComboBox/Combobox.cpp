#include "Combobox.h"



Combobox::Combobox()
{
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(handle, &cci);
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (i == 1 && j == 10)
			{
				position(22, 8);
				cout << "\x7C";
				position(24, 8);
				cout << "\x56";
			}
			if (i == 0 || i == 2)
			{
				position(7 + j, 7 + i);
				if (i == 0 && j == 0)
					cout << "\xDA";
				else if (i == 0 && j == 19)
					cout << "\xBF";
				else if (i == 2 && j == 0)
					cout << "\xC0";
				else if (i == 2 && j == 19)
					cout << "\xD9";
				else
					cout << "\xC4";
			}
			else
			{
				position(7, 7 + i);
				cout << "\xB3";
				position(26, 7 + i);
				cout << "\xB3";
			}
		}
	}
}


Combobox::~Combobox()
{
}


void Combobox::position(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(handle, pos);
}

void Combobox::getPosition(int &x, int &y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(handle, &csbi)) {
		x = csbi.dwCursorPosition.X;
		y = csbi.dwCursorPosition.Y;
	}
}