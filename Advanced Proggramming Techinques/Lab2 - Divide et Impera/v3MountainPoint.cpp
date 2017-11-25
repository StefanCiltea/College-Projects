// v3MountainPoint.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

int maximDivideImpera(vector<int> &v,int st,int dr)
{
	if (dr - st == 1)
	{
		return (v[st] > v[dr]) ? v[st] : v[dr];
	}
	else
	{
		int r1 = maximDivideImpera(v, st, (st + dr) / 2.0);
		int r2 = maximDivideImpera(v, ((st + dr) / 2.0), dr);

		return (r1 > r2) ? r1 : r2;
	}

}

int main()
{
	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; i++)
	{
		cin >> v[i];
	}

	cout << maximDivideImpera(v, 0, n - 1);

    return 0;
}

