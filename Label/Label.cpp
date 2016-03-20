#include "Label.h"



Label::Label()
{
}

Label::Label(string str)
{
	COORD c = { 15, 5 };
	SetConsoleCursorPosition(handle, c);
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(handle, &cci);
	SetConsoleTextAttribute(handle, 10);
	cout << str;
}


Label::~Label()
{
}
