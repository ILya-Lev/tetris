#pragma once
#include "form.h"
#include "field.h"

class Cube : public Form{
public:
 	Cube(const int row_init, const int column_init, const Field &);
	virtual bool clear(const Field &);

private:
	virtual void rotLFRT(int *, int *) { }		//helps rotate the figure
	virtual void rotLSRS(int *, int *) { }		//arrays are coordinates {0-3}
	virtual void rotLTRF(int *, int *) { }		//F -- 0->1; S -- 1->2; T -- 2->3; Z -- 3->0
	virtual void rotLZRZ(int *, int *) { }		//F,S,T,Z <-> 0,1,2,3 --- are different oriantations of the figure
};

Cube::Cube(const int row_init, const int column_init, const Field &F)
{
	orient = 0;
	x_init = row_init;
	y_init = column_init;
	if(clear(F) == false){
		for(int i = 0; i < 4; i++){
			x_coord[i] = y_coord[i] = 0;
		}
	}
}
bool Cube::clear(const Field &F)
{
	if(!F.isEmptyCell(x_init, y_init) )	return false;
	if(!F.isEmptyCell(x_init, y_init+1) )	return false;
	if(!F.isEmptyCell(x_init+1, y_init) )	return false;
	if(!F.isEmptyCell(x_init+1, y_init+1) )	return false;

	x_coord[0] = x_coord[1] = x_init;
	x_coord[2] = x_coord[3] = x_init+1;
	y_coord[0] = y_coord[2] = y_init;
	y_coord[1] = y_coord[3] = y_init+1;
	return true;
}
