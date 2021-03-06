// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

int main()
{
	int n;
	ifstream fin("date.in");
	ofstream fout("date.out");

	fin >> n;

	vector<vector<int>> L(n+1);
	vector<bool> viz(n + 1, 0);

	vector<int> Sol;
	list<int> Add;
	
	int x, y;

	while (fin >> x >> y)
	{
		L[x].push_back(y);
		L[y].push_back(x);
	}

	// Pentru inceput se adauga frunzele la lista Add

	for (int i = 1; i <= n; i++)
	{
		if (L[i].size() == 1)
		{
			Add.push_back(i);
			viz[i] = true;
		}
	}

	while (!Add.empty())
	{
		list<int> Parinti;

		// Se adauga parintii
		// Se adauga nodurile la vectorul solutie

		while (!Add.empty())
		{
			int elem = Add.back();
			Add.pop_back();
			Sol.push_back(elem);
			
			for(int i=0;i<L[elem].size();i++)
				if (!viz[L[elem][i]])
				{
					viz[L[elem][i]] = true;
					Parinti.push_back(L[elem][i]);
				}
		}

		// Adaugam noile noduri
		while (!Parinti.empty())
		{
			int elem = Parinti.back();
			Parinti.pop_back();

			for (int i = 0; i < L[elem].size(); i++)
			{
				if (!viz[L[elem][i]])
				{
					Add.push_back(L[elem][i]);
					viz[L[elem][i]] = true;
				}
			}
		}
	}

	for (int i = 0; i < Sol.size(); i++)
	{
		cout << Sol[i] << " ";
	}

	fin.close();
	fout.close();
    return 0;
}

