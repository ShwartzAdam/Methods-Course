#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

#ifndef _COMBO
#define _COMBO



class Combobox
{
public:
	Combobox();
	~Combobox();
	int x = 0, y = 0;
	void position(int, int);
	void getPosition(int &x, int &y);
	vector<string> options = { "Option 1", "Option 2", "Option 3", "Option 4", "Option 5" };
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
};


#endif

