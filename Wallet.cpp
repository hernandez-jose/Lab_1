#include "Wallet.h"
#include "Currency.h"
#include<iostream>

using namespace std;

Wallet::Wallet()
{
	numberOfCurrenciesInWallet = 0;

	// Currency array pointers set to nullprt for now
	amountInWallet[0] = nullptr;
	amountInWallet[1] = nullptr;
	amountInWallet[2] = nullptr;
	amountInWallet[3] = nullptr;
	amountInWallet[4] = nullptr;

}

// private function returns an index by currency type
int Wallet::getCurrencyIndex(string code)
{
	for (int i = 0; i < MAX_CURRENCIES; i++)
	{
		if (amountInWallet[i] != nullptr)
		{
			if (amountInWallet[i]->getCurrencyCode() == code)
				return i;
		}
	}
	return 0;
}

// this function checks if a particular type of currency exists
bool Wallet::currencyExists(string code)
{
	for (int i = 0; i < MAX_CURRENCIES; i++)
	{
		if (amountInWallet[i] != nullptr)
		{
			if (amountInWallet[i]->getCurrencyCode() == code)
				return true;
		}
	}
	return false;
}

/*
   This function adds currency to the wallet by currency type
*/
bool Wallet::addMoney(string code, int whole, int fraction)
{
	int index;

	// fractions larger than 100 and are negative do not add
	// 0 <= x < 100 and y > 0
	if ( !((0 <= fraction) && (fraction < 100) && (whole >= 0)) )
		return false;

	// O(n^2)
	if (currencyExists(code))
	{
		index = getCurrencyIndex(code);
	}
	else
	{
		// polymorphism -- parallel Currency pointer arrays
		// one for temp storage and one for holding values
		if (code == "USD")
		{
			amountInWallet[numberOfCurrenciesInWallet] = new Dollar;
			tempCurrency[numberOfCurrenciesInWallet] = new Dollar;
		}
		else if (code == "MXN")
		{
			amountInWallet[numberOfCurrenciesInWallet] = new Peso;
			tempCurrency[numberOfCurrenciesInWallet] = new Peso;
		}
		else if (code == "INR")
		{
			amountInWallet[numberOfCurrenciesInWallet] = new Rupee;
			tempCurrency[numberOfCurrenciesInWallet] = new Rupee;
		}
		else if (code == "JPY")
		{
			amountInWallet[numberOfCurrenciesInWallet] = new Yen;
			tempCurrency[numberOfCurrenciesInWallet] = new Yen;
		}
		else if (code == "EUR")
		{
			amountInWallet[numberOfCurrenciesInWallet] = new Euro;
			tempCurrency[numberOfCurrenciesInWallet] = new Euro;
		}
		else
			return false; // if not in the above list currency does not exist

		numberOfCurrenciesInWallet++; // increament after dynamic allocation

		index = getCurrencyIndex(code);
	}

	// add amount overloaded + operator
	tempCurrency[index]->setWholePart(whole);
	tempCurrency[index]->setFractionalPart(fraction);

	// returns address; Currency type + Currency* type -- takes care of "rollover"
	*amountInWallet[index] = *amountInWallet[index] + *tempCurrency[index];

	return true;
}

bool Wallet::subtractMoney(string code, int whole, int fraction)
{
	double walletDecimal, inputDecimal;
	// conditions to subtract
	if (!currencyExists(code))
		return false;
	
	// fractions larger than 100 and are negative do not add
	// also check negative values for whole amount
	// 0 <= x < 100
	if (! ((0 <= fraction) && (fraction < 100) && (whole >= 0)) )
		return false;

	// end conditions
	
	int index = getCurrencyIndex(code);

	// if amount subtracting is larger than in wallet amount return false
	// converts to decimal representation
	walletDecimal = (double)amountInWallet[index]->getWholePart() + ( (double)amountInWallet[index]->getfractionalPart()/100 );
	inputDecimal = (double)whole + ((double)fraction / 100);

	if (walletDecimal < inputDecimal)
		return false;

	// add amount overloaded
	tempCurrency[index]->setWholePart(whole);
	tempCurrency[index]->setFractionalPart(fraction);

	
	// returns address; Currency type - Currency* type -- takes care of "rollover"
	*amountInWallet[index] = *amountInWallet[index] - *tempCurrency[index];

	// delete currency from wallet when there is zero currency
	checkCurrency(amountInWallet[index], index);

	return true;
}

/*
  checks if currency value is zero than it deletes the memory allocated for it
  then it shifts over the arrays addresses, so as to not leave a "gap" in between
  the arrays
*/
void Wallet::checkCurrency(Currency* wallet, int index)
{
	// if no money in currency
	if ( (wallet->getWholePart() == 0) && (wallet->getfractionalPart() == 0))
	{
		// delete currency
		delete amountInWallet[index];
		delete tempCurrency[index];
		amountInWallet[index] = nullptr;
		tempCurrency[index] = nullptr;
		numberOfCurrenciesInWallet--;

		Currency* dummyAmount[MAX_CURRENCIES];
		Currency* dummyTemp[MAX_CURRENCIES];

		int x = 0;

		// organize array pointer -- 
		for (int i = 0; i < numberOfCurrenciesInWallet + 1; i++)
		{
			// temp address storage
			if (i != index)
			{
				dummyAmount[x] = amountInWallet[i];
				dummyTemp[x] = tempCurrency[i];
			}
			else
			{
				i++; // read one foward more than x, so there are no empty spaces in between
				dummyAmount[x] = amountInWallet[i];
				dummyTemp[x] = tempCurrency[i];
			}
			x++;
		}

		// copy addresses back to orginal pointer
		for (int i = 0; i < numberOfCurrenciesInWallet; i++)
		{
			amountInWallet[i] = dummyAmount[i];
			tempCurrency[i] = dummyTemp[i];

			// assign nullptr to the dangling item
			if (i == numberOfCurrenciesInWallet - 1)
			{
				amountInWallet[i + 1] = nullptr;
				tempCurrency[i + 1] = nullptr;
			}
		}

	}
}

// removes all currencies by deleting memory
bool  Wallet::removeAllCurrency()
{
	// delete memory if it exists
	for (int i = 0; i < MAX_CURRENCIES; i++)
	{
		// if amountInWallet[i] does not equal nullptr so does tempCurrency[i]
		if (amountInWallet[i] != nullptr)
		{
			delete amountInWallet[i];
			delete tempCurrency[i];
		}
		amountInWallet[i] = nullptr;
		tempCurrency[i] = nullptr;
	}
	numberOfCurrenciesInWallet = 0;
	return true;
}

/*
  Checks if the wallet is empty by first checking for null pointers
  returns true if empty
*/
bool Wallet::checkIfEmpty()
{
	for (int i = 0; i < MAX_CURRENCIES; i++)
	{
		if (amountInWallet[i] != nullptr)
			return false;
	}

	return true;
}

// friend overloaded operators
istream &operator>>(istream &inputStream, Wallet &wallet)
{
	int whole, fraction;
	string code, wholeName, fracName, operation;

	code = wallet.getWorkingCode();
	wholeName = wallet.getWorkingWholeName();
	fracName = wallet.getWorkingFractionName();
	operation = wallet.getWorkingOperation();

	cout << wholeName << ": ";
	inputStream >> whole;

	cout << fracName << ": ";
	inputStream >> fraction;

	inputStream.ignore();


	// add/subtract money
	if (operation == "addition")
	{
		if (wallet.addMoney(code, whole, fraction))
		{
			cout << "\nMoney was deposited into the wallet.\nPress enter to continue.\n\n" << endl;
			system("pause");
		}
		else
		{
			cout << "\nCould not deposit money into the wallet. Please do not \nenter inappropriate values.\nPress enter to continue.\n\n" << endl;
			system("pause");
		}
	}
	if (operation == "subtraction")
	{
		if (wallet.subtractMoney(code, whole, fraction))
		{
			cout << "\nMoney was withdrawn from the wallet.\nPress enter to continue.\n\n" << endl;
			system("pause");
		}
		else
		{
			cout << "\nCould not withdraw money from the wallet. Please do not \nenter inappropriate values.\nPress enter to continue.\n\n" << endl;
			system("pause");
		}
	}

	// reset
	wallet.setWorkingCode("");
	wallet.setWorkingWholeName("");
	wallet.setWorkingFractionName("");
	wallet.setWorkingOperation("");

	return inputStream;
}

ostream &operator<<(ostream &outStream, Wallet &wallet)
{
	if (!wallet.checkIfEmpty())
	{
		outStream << "*********************************************************\n" <<
					 " You have the following amount:" << endl;
	}
	for (int i = 0; i < wallet.numberOfCurrenciesInWallet; i++)
	{
		if (wallet.amountInWallet[i] != nullptr)
		{
			outStream << "*********************************************************\n\t"
				<< wallet.amountInWallet[i]->getWholePart() << " " << wallet.amountInWallet[i]->getName()
				<< " and " << wallet.amountInWallet[i]->getfractionalPart() << " "
				<< wallet.amountInWallet[i]->getFracName() << 
				"\n*********************************************************" << endl;
		}
	}
	if (wallet.checkIfEmpty())
		outStream << "*********************************************************\n"
				  << " There is no money in the wallet.\n"
				  << "*********************************************************" << endl;
	return outStream;
}

Wallet::~Wallet()
{
	// delete memory if it exists
	for (int i = 0; i < MAX_CURRENCIES; i++)
	{
		// if amountInWallet[i] does not equal nullptr so does tempCurrency[i]
		if (amountInWallet[i] != nullptr)
		{
			delete amountInWallet[i];
			delete tempCurrency[i];
			amountInWallet[i] = nullptr;
			tempCurrency[i] = nullptr;
		}
	}
	//cout << "destructor: Wallet" << endl;
}