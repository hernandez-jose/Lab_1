/*
Lab_1.cpp : Defines the entry point for the console application.
*/
#include "stdafx.h"
#include<iostream>
#include<string>
#include "Wallet.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	Wallet bag;
	

	bag.setWorkingCode("USD");
	bag.setWorkingWholeName("US Dollar");
	bag.setWorkingFractionName("Cents");
	bag.setWorkingOperation("addition");

	cout << "Enter Amount" << endl;

	cin >> bag;

	bag.setWorkingCode("MXN");
	bag.setWorkingWholeName("Peso");
	bag.setWorkingFractionName("Centavos");
	bag.setWorkingOperation("addition");

	cin >> bag;

	cout << bag;
	
	system("pause");

	return 0;
}

