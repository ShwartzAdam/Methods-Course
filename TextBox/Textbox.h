#pragma once
#include <iostream>
#include <Windows.h>

using namespace std;


#ifndef _TEXTBOX
#define _TEXTBOX

class Textbox
{
public:
	Textbox();
	~Textbox();
	int x = 0, y = 0;
	void position(int, int);
	void getPosition(int &x, int &y);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
};


#endif _TEXTBOX
