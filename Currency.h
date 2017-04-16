#ifndef CURRENCY_H
#define CURRENCY_H

#include<string>


class Currency
{
protected:
	std::string				currencyCode; // ISO 4217 standard 3 characters
	std::string				name;
	std::string				FracName;

	int						wholePart;
	int						fractionalPart;

public:
	std::string				getName() { return name; }
	int						getWholePart() { return wholePart; }
	int						getfractionalPart() { return fractionalPart; }
	std::string				getCurrencyCode() { return currencyCode; }
	std::string				getFracName() { return FracName; }
	
	void					setWholePart(int num) { wholePart = num; }
	void					setFractionalPart(int num) { fractionalPart = num; }

	Currency 				&operator+(Currency &);
	Currency 				&operator-(Currency &);

							Currency() : currencyCode("NONE"), name("NO NAME"), wholePart(0), fractionalPart(0) {};
	virtual					~Currency();
};

class Dollar : public Currency // code USD
{
public:
	Dollar();
	~Dollar();
};

class Peso : public Currency // code MXN
{
public:
	Peso();
	~Peso();
};

class Rupee : public Currency // code INR
{
public:
	Rupee();
	~Rupee();
};

class Yen : public Currency // code JPY
{
public:
	Yen();
	~Yen();
};

class Euro : public Currency // code EUR
{
public:
	Euro();
	~Euro();
};

#endif
