#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int getElementFromCorner(int val, int dimcadran, int corner)
{
	int mij = dimcadran / 2;
	//cout << corner << endl;
	switch (corner)
	{
		case 1: {
			//cout << "Returniiiing: " << (val - (dimcadran * mij) - mij) << endl;
			return (val - (dimcadran * mij) - mij);
			break;
		}
		case 2: {
			//cout << "Returniiiing: " << (val - (dimcadran * mij)) << endl;
			return (val - (dimcadran * mij));
			break;
		}
		case 3: {
			//cout << "Returniiiing: " << (val - mij) << endl;
			return (val - mij);
			break;
		}
		case 4: {
			//cout << "Returniiiing: " << val << endl;
			return val;
			break;
		}
		default:{
			cerr << "Error on getelementfromcorner()\n";
			return -1;
		}
	}

}

int resolve(int lnup,int lndown,int left,int right, int posy, int posx,int elem,int dimcadran)
{
	if (posy == lnup)
	{
		// e pe linia de sus
		if (posx == right)
		{
			// coltul dreapta sus
			return elem - dimcadran;
		}
		else
		{
			// coltul stanga sus
			return elem - dimcadran - 1;
		}
	}
	else
	{
		// e pe linia de jos
		if (posx == right)
		{
			// coltul dreapta jos
			return elem;
		}
		else
		{
			// coltul stanga jos
			return elem - 1;
		}
	}
}

int findElement(int lnup, int lndown, int right, int left, int posx, int posy, int elem, int dimcadran)
{
	if (lndown - lnup == 1)
	{
		// rezolv direct cazul de baza
		return resolve(lnup, lndown, left, right, posy, posx, elem, dimcadran);
	}
	else
	{

		int mijlin = (lndown + lnup) / 2;
		int mijcol = (right + left) / 2;

		int dimCadranCurent = lndown / 2;
		if (posy > mijlin && posx > mijcol)    // Cadran 4
			return findElement(mijlin + 1, lndown, right, mijcol + 1, posx, posy, getElementFromCorner(elem, dimcadran, 4), dimcadran);
		else if (posy > mijlin && posx <= mijcol)   // Cadran 3
			return findElement(mijlin + 1, lndown, mijcol, left, posx, posy, getElementFromCorner(elem, dimcadran, 3), dimcadran);
		else if (posy <= mijlin && posx > mijcol)   // Cadran 2
			return findElement(lnup, mijlin, right, mijcol + 1, posx, posy, getElementFromCorner(elem, dimcadran, 2), dimcadran);
		else if (posy <= mijlin && posx <= mijcol)   // Cadran 1
			return findElement(lnup, mijlin, mijcol, left, posx, posy, getElementFromCorner(elem, dimcadran, 1), dimcadran);


	}

}

int zParcurgere(int lnup, int lndown, int right, int left, int posx, int posy, int elem)
{
	if (lndown - lnup == 1)
	{
		// cazul in care n = 1
		return resolve(lnup, lndown, left, right, posy, posx, elem, lndown);
	}
	else
	{

		int mij = (lndown + lnup) / 2.0;

		if (posy > mij && posx > mij)    // Cadran 4
			return findElement(mij + 1, lndown, right, mij + 1, posx, posy, elem, mij);
		else if (posy > mij && posx <= mij)   // Cadran 3
			return findElement(mij + 1, lndown, mij, left, posx, posy, elem - mij * mij, mij);
		else if (posy <= mij && posx > mij)   // Cadran 2
			return findElement(lnup, mij, right, mij + 1, posx, posy, elem - 2 * mij * mij, mij);
		else if (posy <= mij && posx <= mij)   // Cadran 1
			return findElement(lnup, mij, mij, left, posx, posy, elem - 3 * mij * mij, mij);
	}
}

int main(int argc, char const *argv[])
{

	int n, k;
	ifstream fin("date.txt");
	fin >> n >> k;

	int lim = (int)pow(2, n);

	for (int i = 0; i < k; ++i)
	{
		int x, y;
		fin >> x >> y;
		
		cout << zParcurgere(1,lim,lim,1,x,y,lim*lim) << endl;
	}
	fin.close();
	return 0;
}
