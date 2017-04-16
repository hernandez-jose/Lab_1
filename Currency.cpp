/*
	Implementation notes: The default constructor of the derived classes (Dollar, Peso, Yen, etc) are initiated
	with a three letter ISO currency code. This creates a mechanism that prevents two different types of currencies
	from adding each other. Base classes have no currency code.
*/


#include "stdafx.h"
#include "Currency.h"
#include<iostream>

using namespace std;

// constructor

Currency::~Currency()
{
	cout << "Currency dtor" << endl;
}

/*
   overloader operators + and -
   takes care of rolling over decimal values to the left
*/
Currency &Currency::operator+(Currency* rh)
{
	int rightWhole, rightFrac, leftWhole, leftFrac, newWhole, newFrac;

	rightWhole = rh->getWholePart();
	rightFrac = rh->getfractionalPart();

	leftWhole = this->getWholePart();
	leftFrac = this->getfractionalPart();

	newWhole = leftWhole + rightWhole;
	newFrac = leftFrac + rightFrac;
	
	if (newFrac >= 100) // addition "rollover"
	{
		newFrac = newFrac % 100;
		this->setWholePart(newFrac + 1);
		this->setFractionalPart(newFrac);
	}
	else
	{
		this->setWholePart(newWhole);
		this->setFractionalPart(newFrac);
	}

	return *this;
}

Currency &Currency::operator-(Currency* rh)
{
	int rightWhole, rightFrac, leftWhole, leftFrac, newWhole, newFrac;

	rightWhole = rh->getWholePart();
	rightFrac = rh->getfractionalPart();

	leftWhole = this->getWholePart();
	leftFrac = this->getfractionalPart();

	newWhole = leftWhole - rightWhole;
	newFrac = leftFrac - rightFrac;

	// subtraction "rollover"
	if (newFrac < 0)
	{
		newFrac = 100 + newFrac;
		this->setWholePart(newWhole - 1);
		this->setFractionalPart(newFrac);
	}
	else
	{ 
		this->setWholePart(newWhole);
		this->setFractionalPart(newFrac);
	}
	return *this;
}

// derived currencies

// USD US dollar
Dollar::Dollar()
{
	currencyCode = "USD";
	name = "US Dollar";
	FracName = "Cents";
}

Dollar::~Dollar()
{
}

// MXN Mexican Peso
Peso::Peso()
{
	currencyCode = "MXN";
	name = "Peso";
	FracName = "Centavos";
}

Peso::~Peso()
{
}

// INR Indian Rupee
Rupee::Rupee()
{
	currencyCode = "INR";
	name = "Rupee";
	FracName = "Paisa";
}

Rupee::~Rupee()
{
}

// JPY Japanese yen
Yen::Yen()
{
	currencyCode = "JPY";
	name = "Yen";
	FracName = "Sen";
}

Yen::~Yen()
{
}

// EUR European euro
Euro::Euro()
{
	currencyCode = "EUR";
	name = "Euro";
	FracName = "Cents";
}

Euro::~Euro()
{
}

