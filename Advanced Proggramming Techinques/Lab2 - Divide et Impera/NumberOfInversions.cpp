// NumberOfInversions.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;


int interclas(vector<int> &v, int st, int m, int dr)
{
	int nr = 0, i = st, j = m + 1, k = 0;
	vector<int> aux(dr - st + 2);

	while (i <= m && j <= dr)
	{
		if (v[i] > v[j])
		{
			nr += (m - i + 1);
			aux[k++] = v[j++];
		}
		else if(v[j] > v[i])
		{
			// DOES NOT WORK FOR IDENTIC ELEMENTS ! 
			aux[k++] = v[i++];

		}
	}
	while (i <= m)
		aux[k++] = v[i++];

	while (j <= dr)
	{
		aux[k++] = v[j++];
	}
	for (int idx = st; idx <= dr; idx++)
		v[idx] = aux[idx - st];

	return nr;
}

int numberOfInversions(vector<int> &v, int st, int dr)
{
	if (st == dr)
		return 0;
	else
	{
		int m = (st + dr) / 2;
		int n1 = numberOfInversions(v, st, m);
		int n2 = numberOfInversions(v, m + 1, dr);
		return interclas(v, st, m, dr) + n1 + n2;

	}
}

int main()
{
	int n;
	cin >> n;
	vector<int> v(n+1);

	for (int i = 1; i <= n; i++)
		cin >> v[i];

	cout << "Numarul de inversiuni este: " << numberOfInversions(v, 1, n);

    return 0;
}

