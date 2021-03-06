#include "stdafx.h"
#include <fstream>
#include <math.h>

using namespace std;

ifstream fin("joculet.in");
ofstream fout("joculet.out");

long long n, i, j, d[2001][2001], v[2001], comp[2001][2001];

long long max(const long long a, const long long b)
{
	return ((a > b) ? a : b);
}

int main()
{
	fin >> n;
	for (i = 1; i <= n; i++)
		fin >> v[i];

	///D[i][j] = diferenta maxima pe care o poate obtine jucatorul aflat la mutare pe o tabla cu numere de la i..j

	d[0][n] = v[n];
	for (i = n - 1; i >= 1; i--)
	{
		for (j = i; j <= n; j++)
		{
			if (i == j)
				d[1][i] = v[i];
			else
			{
				d[1][j] = max(v[i] - d[0][j], v[j] - d[1][j - 1]);
				d[1][j] = max(d[1][j], v[i] + v[j] - d[0][j - 1]);
			}
		}
		for (j = i; j <= n; j++)
			d[0][j] = d[1][j];
	}
	fout << d[1][n];
	return 0;
}