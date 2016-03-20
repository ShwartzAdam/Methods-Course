#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

using namespace std;

#ifndef _RADIO
#define _RADIO

#pragma once
class Radiolist
{
public:
	Radiolist();
	~Radiolist();
	vector<string> options = { "( ) option 1", "( ) option 2", "( ) option 3", "( ) option 4", "( ) option 5" };
	int x = 0, y = 0;
	void position(int, int);
	void getPosition(int &x, int &y);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
};


#endif

