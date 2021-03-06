// Joc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main()
{
	vector<int> table;
	
	ifstream fin("date.in");

	int sumPar = 0, sumImpar = 0,aux;

	cout << "Table: ";
	
	while (fin >> aux)
	{
		cout << aux << " ";
		table.push_back(aux);
	}

	fin.close();		// Close file
	cout << endl;


	for (int i=0;i<table.size();i++)
	{
		if (i % 2 == 0)
			sumPar += table[i];
		else
			sumImpar += table[i];
	}

	bool strategy;			// 0 - mergem pe pozitii pare 1 - mergem pe impare

	if (sumPar > sumImpar)
		strategy = 0;
	else
		strategy = 1;

	int L = 0, R = table.size() - 1;
	int playerSum = 0, computerSum = 0;

	while (L < R)
	{
		// Player turn
		if (strategy == 0)
		{
			if (L % 2 == 0)
				playerSum += table[L++], cout << "Player picked the number " << table[L - 1] << " at position " << L - 1 << endl;
			else
				playerSum += table[R--], cout << "Player picked the number " << table[R - 1] << " at position " << R - 1 << endl;
		}
		else
		{
			if (R % 2 == 0)
				playerSum += table[R--], cout << "Player picked the number " << table[L - 1] << " at position " << L - 1 << endl;
			else
				playerSum += table[L++], cout << "Player picked the number " << table[R - 1] << " at position " << R - 1 << endl;
		}

		// Computer turn
		cout << endl;
		bool computerPick = rand() % 2;				// 0 = alege din dreapta, 1 = alege din stanga
		
		if (computerPick == 0)
		{
			computerSum += table[R--];
			cout << "Computer picked the number " << table[R - 1] << " at position " << R - 1 << endl;
		}
		else
		{
			computerSum += table[L++];
			cout << "Computer picked the number " << table[L - 1] << " at position " << L - 1 << endl;
		}

	}

	cout << "------------------------------------------- RESULT --------------------------------------------------------------\n";
	cout << "Player sum = " << playerSum << endl;
	cout << "Computer sum = " << computerSum << endl;

	(playerSum > computerSum) ? cout << "Player Wins !\n" : cout << "Computer Wins !\n";

    return 0;
}

