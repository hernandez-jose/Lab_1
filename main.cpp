/*
Lab_1.cpp : Defines the entry point for the console application.
*/
#include<iostream>
#include<string>
#include <cstring>
#include "Wallet.h"


using namespace std;

void addPage(Wallet &);
void subtractPage(Wallet &);
void subtractByCurrency(string code, string name, string frac, Wallet &);
void addByCurrency(string code, string name, string frac, Wallet &);

int main()
{
	Wallet bag;
	string choice;
	bool menu = false;
	bool error = false;

	do
	{
		system("cls");

		if (error == true) // output errors
		{
			cout << "\t* Invalid selection choose again." << endl << endl;
			error = false;
		}
		cout << bag;

		cout << "\n * Select an option to add money in wallet." << endl;
		cout << endl << "**************** Main Menu ******************************" << endl;
		cout << "Please select from the following" << endl;
		cout << " 1) Add Currency" << endl;
		cout << " 2) Subtract Currency" << endl;
		cout << " 3) Empty Wallet" << endl;
		cout << " 4) Exit Program" << endl;
		cout << " Please input the letter and press enter" << endl << endl;
		cout << "*********************************************************" << endl;

		getline(cin, choice);

		if (choice == "1")
		{
			addPage(bag);
		}
		else if (choice == "2")
		{
			subtractPage(bag);
		}
		else if (choice == "3")
			bag.removeAllCurrency();
		else if (choice == "4")
			menu = true;
		else
			error = true;

	} while (menu == false);

	system("pause");

	return 0;
}


void addPage(Wallet &bag){
	string choice;
	bool menu = false;
	bool error = false;

	do
	{
		system("cls");
		if (error == true) // output errors
		{
			cout << "\t* Invalid selection choose again.\n" << endl;
			error = false;
		}
		cout << bag;

		cout << "\n*********************************************************\n" << " Add currency\n"
			<< "*********************************************************\n" <<
			"\nPlease select which form of currency from the following" << endl;
		cout << " 1) US Dollars\n";
		cout << " 2) Peso\n";
		cout << " 3) Rupee\n";
		cout << " 4) Yen\n";
		cout << " 5) Euro\n";
		cout << " 6) Return to Main Menu\n";


		getline(cin, choice);

		if (choice == "1")
		{
			addByCurrency("USD", "US Dollar", "Cents", bag);
			menu = true;
		}
		else if (choice == "2")
		{
			addByCurrency("MXN", "Peso", "Centavos", bag);
			menu = true;
		}
		else if (choice == "3")
		{
			addByCurrency("INR", "Rupee", "Paisa", bag);
			menu = true;
		}
		else if (choice == "4")
		{
			addByCurrency("JPY", "Yen", "Sen", bag);
			menu = true;
		}
		else if (choice == "5")
		{
			addByCurrency("EUR", "Euro", "Cents", bag);
			menu = true;
		}
		else if (choice == "6")
		{
			menu = true;
		}
		else
			error = true;


	} while (menu == false);
}

void subtractPage(Wallet &bag){
	string choice;
	bool menu = false;
	bool error = false;

	do
	{
		system("cls");

		if (error == true) // output errors
		{
			cout << "\t* Invalid selection choose again." << endl;
			error = false;
		}
		cout << bag;

		cout << "\n*********************************************************\n" << " Subtract currency\n"
			<< "*********************************************************\n" <<
			"\nPlease select which form of currency from the following" << endl;
		cout << " 1) US Dollars\n";
		cout << " 2) Peso\n";
		cout << " 3) Rupee\n";
		cout << " 4) Yen\n";
		cout << " 5) Euro\n";
		cout << " 6) Return to Main Menu\n";


		getline(cin, choice);

		if (choice == "1")
		{
			subtractByCurrency("USD", "US Dollar", "Cents", bag);
			menu = true;
		}
		else if (choice == "2")
		{
			subtractByCurrency("MXN", "Peso", "Centavos", bag);
			menu = true;
		}
		else if (choice == "3")
		{
			subtractByCurrency("INR", "Rupee", "Paisa", bag);
			menu = true;
		}
		else if (choice == "4")
		{
			subtractByCurrency("JPY", "Yen", "Sen", bag);
			menu = true;
		}
		else if (choice == "5")
		{
			subtractByCurrency("EUR", "Euro", "Cents", bag);
			menu = true;
		}
		else
			error = true;


	} while (menu == false);
}

void subtractByCurrency(string code, string name, string frac, Wallet &bag)
{
	system("cls");

	cout << bag;

	cout << "\n*********************************************************\n" << " Withdraw currency\n"
		<< "*********************************************************\n" <<
		"\nThis program will ask for the " << name << " value and \n" << frac << " value separately." << endl;
	// cin>> currency.fractionpart;

	bag.setWorkingCode(code);
	bag.setWorkingWholeName(name);
	bag.setWorkingFractionName(frac);
	bag.setWorkingOperation("subtraction");

	cout << "\nEnter Amount" << endl;

	cin >> bag;

}

void addByCurrency(string code, string name, string frac, Wallet &bag)
{
	system("cls");

	cout << bag;

	cout << "\n*********************************************************\n" << " Deposit currency\n"
		<< "*********************************************************\n" <<
		"\nThis program will ask for the " << name << " value and \n" << frac << " value separately." << endl;

	bag.setWorkingCode(code);
	bag.setWorkingWholeName(name);
	bag.setWorkingFractionName(frac);
	bag.setWorkingOperation("addition");

	cout << "\nEnter Amount" << endl;

	cin >> bag;

}

