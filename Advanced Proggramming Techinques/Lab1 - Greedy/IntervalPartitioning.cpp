// Lab1-V3-P3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>

using namespace std;

struct Interval {
	int start, finish, index;
};

struct Sala {
	static int cnt;
	int id,disp;
};

bool comp(const Interval a, const Interval b)
{
	return (a.start < b.start);
}

class salaCmp {
public:
	bool operator() (const Sala a, const Sala b)
	{
		return(a.disp < b.disp);
	}
};

int Sala::cnt = 0;			// Se initializeaza variabila statica

int main()
{
	ifstream fin("date.in");
	ofstream fout("date.out");

	int n;
	fin >> n;
	vector<Interval> S(n);
	fout << "Activitati: \n";
	for (int i = 0; i < n; i++)
	{
		int a, b;
		fin >> a >> b;
		S[i].start = a;
		S[i].finish = b;
		S[i].index = i;
		fout << "Activitatea " << i + 1 << " : [" << a << "," << b << "]\n";
	}
	fout << "\n Repartizarea in sali: \n";

	// Se sorteaza
	sort(S.begin(), S.end(), comp);

	vector<vector<int>> repartitie;
	priority_queue<Sala, vector<Sala>, salaCmp> pq;

	pq.push({0,S[0].finish});
	Sala::cnt++;
	
	repartitie.push_back(vector<int>());
	repartitie[0].push_back(S[0].index);


	for (int i = 1; i < S.size(); i++)
	{
		Sala min = pq.top();
	
		if (min.disp < S[i].start)
		{
			Sala newVal;
			
			newVal.id = min.id;
			newVal.disp = S[i].finish;
			
			pq.pop();
			pq.push(newVal);

			repartitie[min.id].push_back(S[i].index);
		}
		else
		{
			Sala salaNoua;
			salaNoua.id = Sala::cnt;
			salaNoua.disp = S[i].finish;

			repartitie.push_back(vector<int>());
			repartitie[repartitie.size()-1].push_back(S[i].index);

			Sala::cnt++;
			pq.push(salaNoua);

		}
	}

	for (int i = 0; i < repartitie.size(); i++)
	{
		fout << "Clasa " << i << "=> ";
		for (int j = 0; j < repartitie[i].size(); j++)
			fout << repartitie[i][j]+1 << " ";
		fout << endl;
	}
	fin.close();
	fout.close();
	return 0;
}