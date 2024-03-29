#pragma once
#include "field.h"
#include "form.h"
#include "cube.h"
#include "triangle.h"
#include "gamaR.h"
#include "gamaL.h"
#include "stick.h"
#include "zetR.h"
#include "zetL.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::cin;
using std::endl;

class Manager{
public:
  	Manager(const int num_rows = 20, const int num_columns = 20, const int lev = 0);
	void makeStep();
	void print(const int flag=1) const;	//flag shows if the printing is last in the game session
private:
	int sizeR, sizeC;
	int level, scores;
	int num_fig;
	Field screen;
	Form *formPtr[7];
	Cube cube;
	Triangle trian;
	GamaR gamaR;
	GamaL gamaL;
	Stick stick;
	ZetR zetR;
	ZetL zetL;

	void usersAction();
};

Manager::Manager(const int num_rows, const int num_columns, const int lev)
	: screen(num_rows, num_columns), cube(0, num_columns/2-1, screen), trian(0, num_columns/2-1, screen),
	gamaR(0, num_columns/2-1, screen), gamaL(0, num_columns/2-1, screen), stick(0, num_columns/2-1, screen),
	zetR(0, num_columns/2-1, screen), zetL(0, num_columns/2-1, screen)
{
	formPtr[0] = &trian;
	formPtr[1] = &zetL;
	formPtr[2] = &zetR;
	formPtr[3] = &gamaR;
	formPtr[4] = &gamaL;
	formPtr[5] = &stick;
	formPtr[6] = &cube;
	level = lev;
	scores = 0;
	num_fig = 0;
	sizeR = num_rows;
	sizeC = num_columns;
	
	srand(time(0));			//'cause random numbers are used in makeStep()
}
void Manager::print(const int flag) const		//flag shows if the printing is last in the game session
{
	cout<<"---------------------------------------------------"<<endl;
	for(int i = 0, j; i < sizeR; i++, cout<<endl)
	{
		cout<<'|';
		for(j = 0; j < sizeC; j++){
			if(flag && formPtr[num_fig]->isFigure(i,j))
				cout<<'#';
			else if(screen.isEmptyCell(i,j))
				cout<<' ';
			else
				cout<<'*';
		}
		cout<<'|';
		switch(i){
			case 2: cout<<"level = "<<level;
				break;
			case 3: cout<<"score = "<<scores;
				break;
			case 4: cout<<"your commands:";
				break;
			case 5: cout<<"ml - move left";
				break;
			case 6: cout<<"mr - move right";
				break;
			case 7: cout<<"rl - rot left";
				break;
			case 8: cout<<"rr - rot right";
				break;
			case 9: cout<<"pd - push down";
				break;
		}
	}
	cout<<"---------------------------------------------------"<<endl;
}
void Manager::makeStep()
{
	num_fig = rand()%7;			//choose number of figure to "put into the game"
	while(formPtr[num_fig]->clear(screen))	//while can put new object in the game
	{
		while(formPtr[num_fig]->canMoveForwad(screen))
		{
			print();
			usersAction();
			if(formPtr[num_fig]->canMoveForwad(screen)){
				formPtr[num_fig]->moveForward();
			}
		}
		for(int i = 0; i < 4; i++){
			screen.fillCell(formPtr[num_fig]->getXcoord(i), formPtr[num_fig]->getYcoord(i));
		}
		scores += screen.deleteRows();

		num_fig = rand()%7;	//previous object has just been saved in the screen, time to choose next one
	}
	print(0);					//print screen the last time in the game session
	cout<<"the game is over. bye!"<<endl;
}
void Manager::usersAction()
{
	string choice;
	cout<<"enter a command: "<<endl;		//ml,mr,rl,rr,pd
	getline(cin, choice);

	if(choice.size() != 2) return ;			//can't analize choice if its size != 2

	if(choice.at(0) == 'm' || choice.at(0) == 'M')
	{
		if(choice.at(1) == 'l' || choice.at(1) == 'L'){
			if(formPtr[num_fig]->canMoveLeft(screen)){
				formPtr[num_fig]->moveLeft();
			}
			else {
				cout<<"can't move left"<<endl;
			}
		}
		else if(choice.at(1) == 'r' || choice.at(1) == 'R')
			if(formPtr[num_fig]->canMoveRight(screen)){
				formPtr[num_fig]->moveRight();
			}
			else {
				cout<<"can't move right"<<endl;
			}
	}
	else if(choice.at(0) == 'r' || choice.at(0) == 'R')
	{
		if(choice.at(1) == 'l' || choice.at(1) == 'L'){
			if(formPtr[num_fig]->canRotLeft(screen)){
				formPtr[num_fig]->rotLeft();
			}
			else {
				cout<<"can't rotate left"<<endl;
			}
		}
		else if(choice.at(1) == 'r' || choice.at(1) == 'R'){
			if(formPtr[num_fig]->canRotRight(screen)){
				formPtr[num_fig]->rotRight();
			}
			else {
				cout<<"can't rotate right"<<endl;
			}
		}
	}
	else if((choice.at(0) == 'p' || choice.at(0) == 'P') && (choice.at(1) == 'd' || choice.at(1) == 'D'))
		while(formPtr[num_fig]->canMoveForwad(screen)){
			formPtr[num_fig]->moveForward();
		}
}
