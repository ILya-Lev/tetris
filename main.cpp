// tetris.cpp : Defines the entry point for the console application.
//MS VS 2010

#include "stdafx.h"
#include <iostream>
#include <conio.h>

#include "manager.h"

int _tmain()
{
  	Manager tetr;

	tetr.makeStep();

	_getch();		//to make program wait while user enter any key
	return 0;
}
