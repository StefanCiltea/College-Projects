/*
	Subproblema: d[i][j] = Dimensiunea maxima a unui patrat ce are coltul stanga-sus pe pozitia (i,j)
	
	Recurenta:	0, daca a[i][j] = 1
				d[i][j] = d[i+1][j+1] + 1, altfel
	
	Solutia se afla in d[0][0]

	Ordinea de calcul: i=n-1,0 si j = m-1,0

*/					

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

bool a[2000][2000];
int d[2000][2000];

int min3(const int a, const int b, const int c)
{
	if (a <= b && a <= c)
		return a;
	else if (b <= a && b <= c)
		return b;
	else
		return c;
}

int main()
{
	int n, m, k;
	ifstream fin("date.in");

	fin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			fin >> a[i][j];

	fin >> k;
	fin.close();

	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = m - 1; j >= 0; j--)
		{
			if (i == n - 1 || j == m - 1)
				d[i][j] = 1;
			else
			{
				d[i][j] = (a[i][j] == 0) ? min3(d[i + 1][j], d[i + 1][j + 1], d[i][j + 1]) + 1 : 0;
			}
		}
	}

	/* Se cauta maximul in matricea d[][] */

	int imax, jmax, dmax = -1, cnt = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		for (int j = m - 1; j >= 0; j--)
		{
			if (d[i][j] > dmax)
			{
				imax = i;
				jmax = j;
				dmax = d[i][j];
			}
			if (d[i][j] >= k)
			{
				cnt += (d[i][j] - k + 1);
			}
		}
	}

	cout << dmax << endl << imax + 1 << " " << jmax + 1 << endl;
	cout << "Sunt " << cnt << " patrate cu elemente 0 de latura mai mare decat " << k << endl;

	return 0;
}

