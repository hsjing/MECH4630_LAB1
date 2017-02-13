// 4630lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Spring.h"
#include "User.h"
#include <conio.h>

CUser newuser;

int main()
{
	newuser.loadfile();
	newuser.iterate();

	_getch();
}