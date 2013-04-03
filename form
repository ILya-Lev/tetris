#pragma once
#include "field.h"
#include <cassert>

class Form{
public:
  virtual bool clear(const Field &) = 0;		//specific function for each type of form

	bool isFigure(const int x, const int y) const;
	bool canMoveForwad(const Field &, const int num_steps = 1) const;
	bool canMoveLeft(const Field &, const int num_steps = 1) const;
	bool canMoveRight(const Field &, const int num_steps = 1) const;

	void moveForward(const int num_steps = 1);
	void moveLeft(const int num_steps = 1);
	void moveRight(const int num_steps = 1);

	bool canRotRight(const Field &);
	bool canRotLeft(const Field &);
	void rotLeft();
	void rotRight();

	int getXcoord(const int num) const;		//these two functions are used in Manager.mekeStep()
	int getYcoord(const int num) const;		//to fill cells  in the Field screen;

protected:
	int x_coord[4], y_coord[4];
	int x_init, y_init, orient;

	virtual void rotLFRT(int *, int *) = 0;		//helps rotate the figure, depends on type of the form
	virtual void rotLSRS(int *, int *) = 0;		//arrays are coordinates {0-3}
	virtual void rotLTRF(int *, int *) = 0;		//F -- 0->1; S -- 1->2; T -- 2->3; Z -- 3->0
	virtual void rotLZRZ(int *, int *) = 0;		//F,S,T,Z <-> 0,1,2,3 --- are different oriantations of the figure
};

bool Form::isFigure(const int x, const int y) const
{
	for(int i = 0; i < 4; i++){
		if(x_coord[i] == x && y_coord[i] == y)
			return true;
	}
	return false;
}
bool Form::canMoveForwad(const Field &F, const int num_steps) const
{
	for(int i = 0; i < 4; i++){
		if(!F.isEmptyCell(x_coord[i]+num_steps, y_coord[i]))
			return false;
	}
	return true;
}
bool Form::canMoveLeft(const Field &F, const int num_steps) const
{
	for(int i = 0; i < 4 ;i++){
		if(!F.isEmptyCell(x_coord[i], y_coord[i]-num_steps))
			return false;
	}
	return true;
}
bool Form::canMoveRight(const Field &F, const int num_steps) const
{
	for(int i = 0; i < 4; i++){
		if(!F.isEmptyCell(x_coord[i], y_coord[i]+num_steps))
			return false;
	}
	return true;
}

void Form::moveForward(const int num_steps)
{
	for(int i = 0; i < 4; i++)
		x_coord[i] += num_steps;
}
void Form::moveLeft(const int num_steps)
{
	for(int i = 0; i < 4; i++)
		y_coord[i] -= num_steps;
}
void Form::moveRight(const int num_steps)
{
	for(int i = 0; i < 4; i++)
		y_coord[i] += num_steps;
}

void Form::rotLeft()
{
	switch(orient){
		case 0: rotLFRT(x_coord, y_coord);
			break;
		case 1: rotLSRS(x_coord, y_coord);
			break;
		case 2: rotLTRF(x_coord, y_coord);
			break;
		case 3: rotLZRZ(x_coord, y_coord);
			break;
	}	
	orient++;
	orient %= 4;		//orientation is always from 0 to 3
}
void Form::rotRight()
{
	switch(orient){
		case 0: rotLTRF(x_coord, y_coord);
			break;
		case 1: rotLSRS(x_coord, y_coord);
			break;
		case 2: rotLFRT(x_coord, y_coord);
			break;
		case 3: rotLZRZ(x_coord, y_coord);
			break;
	}	
	orient++;
	orient %= 4;
}

bool Form::canRotRight(const Field &F)
{
	int x[4], y[4], i;
	for(i = 0; i < 4; i++)
	{
		x[i] = x_coord[i];
		y[i] = y_coord[i];
	}

	switch(orient){
		case 0: rotLTRF(x_coord, y_coord);
			break;
		case 1: rotLSRS(x_coord, y_coord);
			break;
		case 2: rotLFRT(x_coord, y_coord);
			break;
		case 3: rotLZRZ(x_coord, y_coord);
			break;
	}	
	for(i = 0; i < 4; i++)
	{
		if(F.isEmptyCell(x[i], y[i]) == false)
			return false;
	}
	return true;
}
bool Form::canRotLeft(const Field &F)
{
	int x[4], y[4], i;
	for(i = 0; i < 4; i++)
	{
		x[i] = x_coord[i];
		y[i] = y_coord[i];
	}

	switch(orient){
		case 0: rotLFRT(x_coord, y_coord);
			break;
		case 1: rotLSRS(x_coord, y_coord);
			break;
		case 2: rotLTRF(x_coord, y_coord);
			break;
		case 3: rotLZRZ(x_coord, y_coord);
			break;
	}	

	for(i = 0; i < 4; i++)
	{
		if(F.isEmptyCell(x[i], y[i]) == false)
			return false;
	}
	return true;
}


int Form::getXcoord(const int num) const
{
	assert(num >= 0 && num < 4);
	return x_coord[num];
}
int Form::getYcoord(const int num) const
{
	assert(num >= 0 && num < 4);
	return y_coord[num];
}
