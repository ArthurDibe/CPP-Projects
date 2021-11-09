/********************************
Developed by: Dibe
********************************/

#ifndef AID_GOOD_H
#define AID_GOOD_H

#include <iostream>
#include "Error.h"
#include "iGood.h"

namespace aid
{
	const int max_sku_length = 7;	// Maximum number of characters in a SKU (stock keeping unit)
	const int max_unit_length = 10;	// Maximum number of characters in the units� descriptor for a Good	
	const int max_name_length = 75; // Maximum number of characters in the user�s name descriptor for a Good
	const double tax_rate = 0.13;   // The current tax rate � 13%.

	class Good : public iGood
	{
		char m_goodType;
		char m_goodSku[max_sku_length + 1];
		char m_goodUnit[max_unit_length + 1];
		char* m_goodName;
		int m_goodUnitHand;
		int m_goodUnitNeed;
		double m_goodPriceUnit;		// without taxes
		bool m_goodTaxStatus;		// "true" if Good is Taxable
		

		void copyEverything(const Good& source);
		void emptyState(const char goodType);

	protected:
		Error m_errorState;			// holds the error state of the Good object
		void name(const char* goodName);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double itemPrice() const;
		double itemCost() const;
		void message(const char* errorMessage);
		bool isClear() const;

	public:
		Good(const char goodType = 'N');
		Good(const char* goodSku, const char* goodName,
			const char* goodUnit, int goodUnitHand = 0,
			bool goodTaxStatus = true, double goodPriceUnit = 0.0, int goodUnitNeed = 0);
		Good(const Good& source);
		Good& operator=(const Good& source);
		~Good();

		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);

		double total_cost() const;
		void quantity(int goodUnitHand);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;

		bool operator==(const char* goodSku) const;
		bool operator>(const char* goodSku) const;
		bool operator>(const iGood& goodName) const;
		int operator+=(int numberUnits);
	};

	std::ostream& operator<<(std::ostream& os, const iGood& source);
	std::istream& operator>>(std::istream& is, iGood& source);
	double operator+=(double& cost, const iGood& source);
}
#endif