#pragma once
#include "form.h"
#include "field.h"

class GamaL : public Form{
public:
 	GamaL(const int row_init, const int column_init, const Field &);
	virtual bool clear(const Field &);

private:
	virtual void rotLFRT(int *, int *);		//helps rotate the figure
	virtual void rotLSRS(int *, int *);		//arrays are coordinates {0-3}
	virtual void rotLTRF(int *, int *);		//F -- 0->1; S -- 1->2; T -- 2->3; Z -- 3->0
	virtual void rotLZRZ(int *, int *);		//F,S,T,Z <-> 0,1,2,3 --- are different oriantations of the figure
};

GamaL::GamaL(const int row_init, const int column_init, const Field &F)
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
bool GamaL::clear(const Field &F)
{
	if(!F.isEmptyCell(x_init, y_init+1) )	return false;
	if(!F.isEmptyCell(x_init+1, y_init+1) )	return false;
	if(!F.isEmptyCell(x_init+1, y_init) )	return false;
	if(!F.isEmptyCell(x_init+1, y_init-1) )	return false;

	orient = 0;
	x_coord[0] = x_init;
	x_coord[1] = x_coord[2] = x_coord[3] = x_init+1;
	y_coord[0] = y_coord[1] = y_init+1;
	y_coord[2] = y_init;
	y_coord[3] = y_init-1;
	return true;
}

void GamaL::rotLFRT(int *x, int *y)	//makes left rotation 0->1 and right rot 2->3
{
	x[0] = x[1] = x[2]-1;
	x[3] = x[2]+1;

	y[0] = y[2]-1;
	y[1] = y[3] = y[2];
}
void GamaL::rotLSRS(int *x, int *y)	//makes left rotation 1->2 and right rot 1->2
{
	x[0] = x[2]+1;
	x[1] = x[3] = x[2];

	y[0] = y[1] = y[2]-1;
	y[3] = y[2]+1;
}
void GamaL::rotLTRF(int *x, int *y)	//makes left rotation 2->3 and right rot 0->1
{
	x[0] = x[1] = x[2]+1;
	x[3] = x[2]-1;

	y[0] = y[2]+1;
	y[1] = y[3] = y[2];
}
void GamaL::rotLZRZ(int *x, int *y)	//makes left rotation 3->0 and right rot 3->0
{
	x[0] = x[2]-1;
	x[1] = x[3] = x[2];

	y[0] = y[1] = y[2]+1;
	y[3] = y[2]-1;
}
