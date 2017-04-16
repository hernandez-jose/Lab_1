#ifndef WALLET_H
#define WALLET_H

#include<string>
class Currency;

const int MAX_CURRENCIES = 5;
const std::string currencyTypes[MAX_CURRENCIES] = { "USD", "MXN", "INR", "JPY", "EUR" };

class Wallet
{
private:
	std::string workingCode; // used when adding by currency
	std::string workingWholeName;
	std::string workingFractionName;
	std::string workingOperation;

	int numberOfCurrenciesInWallet;
	Currency* amountInWallet[MAX_CURRENCIES];
	Currency* tempCurrency[MAX_CURRENCIES];
	int		getCurrencyIndex(std::string);

public:
	bool	currencyExists(std::string);
	bool	addMoney(std::string, int, int);
	bool	subtractMoney(std::string, int, int);
	bool	removeAllCurrency();
	bool	checkIfEmpty();
	void	checkCurrency(Currency*, int);
	
	friend std::ostream &operator<<(std::ostream &, Wallet &);
	friend std::istream &operator>>(std::istream &, Wallet &);
	
	void tester();
	
	std::string getWorkingCode() { return workingCode; }
	std::string getWorkingWholeName() { return workingWholeName; }
	std::string getWorkingFractionName() { return workingFractionName; }
	std::string getWorkingOperation() { return workingOperation; }

	void setWorkingCode(std::string cod) { workingCode = cod; }
	void setWorkingWholeName(std::string whole) { workingWholeName = whole; }
	void setWorkingFractionName(std::string frac) { workingFractionName = frac; }
	void setWorkingOperation(std::string op) { workingOperation = op; }

	Wallet();
	~Wallet();
};

#endif
