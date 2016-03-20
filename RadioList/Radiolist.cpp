#include "Radiolist.h"



Radiolist::Radiolist()
{
	for (int i = 0; i < options.size(); i++)
	{
		COORD c = { 7, i + 7 };
		SetConsoleCursorPosition(handle, c);
		CONSOLE_CURSOR_INFO cci = { 100, FALSE };
		SetConsoleCursorInfo(handle, &cci);
		if (i == 0)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY);
		else
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << options[i];
		position(7, 7);

	}
}


Radiolist::~Radiolist()
{
}


void Radiolist::position(int x, int y)
{
	COORD pos = { x, y };
	SetConsoleCursorPosition(handle, pos);
}

void Radiolist::getPosition(int & x, int & y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(handle, &csbi)) {
		x = csbi.dwCursorPosition.X;
		y = csbi.dwCursorPosition.Y;
	}
}