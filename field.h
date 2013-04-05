#pragma once
#include <cassert>
//contains everything thad felt on bottom of the screen; moreover delete lines
class Field{
public:
  	Field(const int num_rows = 20, const int num_columns = 20);
	~Field();
	bool isEmptyCell(const int row, const int column) const;
	bool fillCell(const int row, const int column);
	int deleteRows();
private:
	int **field;
	int hight, length;			//length - number of columns, i.e. length of each row
						//hight - number of rows
	bool isFullRow(const int row) const;
	void shiftRows(const int row);
};

Field::Field(const int num_rows, const int num_columns)
{
	if(num_rows < 10 || num_rows > 30){
		hight = 20;
	}
	else{
		hight = num_rows;
	}

	if(num_columns < 10 || num_columns > 30){
		length = 20;
	}
	else {
		length = num_columns;
	}

	field = new int * [hight];
	int i,j;
	for(i = 0; i < hight; i++)
	{
		field[i] = new int [length];
		assert(field[i] != 0);		//checks if there is enough memory to allocate for the field
	}
	for(i = 0; i < hight; i++){
		for(j = 0; j < length; j++)
			field[i][j] = 0;				//initially the field is empty
	}
}
Field::~Field()
{
	delete [] field;
}

bool Field::isEmptyCell(const int row, const int column) const
{
	if(row < 0 || row >= hight){ 				//indexes are out of the range
		return false;
	}
	if(column < 0  || column >= length){		//hense can't check if the cell is empty
		return false;
	}
	return field[row][column] == 0;			//if it's empty, returns true
}
bool Field::fillCell(const int row, const int column)
{
	bool ans = isEmptyCell(row, column);
	if(ans) field[row][column] = 1;			//filling the cell (by setting number 1)
	return ans;					//if can't fill the cell, return false
}
int Field::deleteRows()
{
	int amount=0, i, j;
	for(i = 0; i < hight; i++)
		if(isFullRow(i))
		{
			amount++;
			for(j = 0; j < length; j++)				//deleting i-row
				field[i][j] = 0;
			shiftRows(i);
			i--;				//not to loose some rows, 'cause of the shifting
		}
	return amount;
}
bool Field::isFullRow(const int row) const
{
	assert(row >= 0 && row < hight);
	for(int i = 0; i < length; i++) {
		if(field[row][i] == 0)
			return false;
	}
	return true;
}
void Field::shiftRows(const int row)			//line w number "row" has been deleted
{							//now all lines above are shifted down to fill the gap
	assert(row >= 0 && row < hight);
	int i,j;
	for(j = 0; j < length; j++){
		for(i = row-1; i >= 0; i--){
			field[i+1][j] = field[i][j];
		}
	}
	if(row != 0){
		for(j = 0; j < length; j++){
			field[0][j] = 0;	//null the first line, 'cause it could contain some elements
		}
	}
}
