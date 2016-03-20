#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

#ifndef _LABEL
#define _LABEL

#pragma once
class Label
{
public:
	Label();
	Label(string str);
	~Label();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
};

#endif