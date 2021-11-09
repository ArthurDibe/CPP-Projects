/********************************
Developed by: Dibe
********************************/

#include <cstring>
#include <fstream>
#include "Good.h"

namespace aid
{
	// Assign a Good's name to the current object
	void Good::name(const char* goodName)
	{
		if (goodName != nullptr) {
			/*int size = strlen(goodName);*/
			m_goodName = new char[max_name_length + 1];
			strncpy(m_goodName, goodName, max_name_length);
			m_goodName[max_name_length] = '\0';
		}
		else {
			m_goodName = new char;
			m_goodName = '\0';
		}
	}

	// Returns the good name if there is some 
	// good name stored in the current object
	const char* Good::name() const
	{
		return (m_goodName != nullptr && m_goodName[0] != '\0') ? m_goodName : nullptr;
	}

	// Returns the address of the C-style 
	// null-terminated string that holds the SKU
	const char* Good::sku() const
	{
		return m_goodSku;
	}

	// Returns the address of the C-style 
	// null-terminated string that holds the unit
	const char* Good::unit() const
	{
		return m_goodUnit;
	}

	// Returns the taxable status of the Good
	bool Good::taxed() const
	{
		return m_goodTaxStatus;
	}

	// Returns the price of a single item of the Good 
	// without tax
	double Good::itemPrice() const
	{
		return m_goodPriceUnit;
	}

	// Returns the price of a single item of the Good 
	// plus any tax that applies to the Good
	double Good::itemCost() const
	{
		double cost = itemPrice();

		if (m_goodTaxStatus)
			cost = cost * (1 + tax_rate);

		return cost;

	}

	// Receives the address of a C-style 
	// null-terminated string holding an error message 
	// and stores that message in the Error object to the current object.
	void Good::message(const char* errorMessage)
	{
		m_errorState.message(errorMessage);
	}

	// Returns true if the Error object is clear, 
	// false otherwise.
	bool Good::isClear() const
	{
		return m_errorState.isClear();
	}

	// Function that sets to empty state
	void Good::emptyState(const char goodType)
	{
		m_goodType = goodType;
		m_goodSku[0] = '\0';
		m_goodUnit[0] = '\0';
		m_goodName = nullptr;
		m_goodUnitHand = 0;
		m_goodUnitNeed = 0;
		m_goodPriceUnit = 0.0;
		m_goodTaxStatus = false;
		m_errorState.message(nullptr);
	}

	// Stores the character received in an instance variable;
	// sets the current object to a safe recognizable empty state
	Good::Good(const char goodType)
	{
		emptyState(goodType);
	}

	// Copy constructor of 7 parameters
	Good::Good(const char* goodSku, const char* goodName,
		const char* goodUnit, int goodUnitHand,
		bool goodTaxStatus, double goodPriceUnit, int goodUnitNeed)
	{
		bool invalid = true;

		if (goodName != nullptr && goodUnit != nullptr && goodSku != nullptr)
		{
			if (goodName[0] != '\0' || goodUnit[0] != '\0' || goodSku[0] != '\0')
			{
				invalid = false;

				if (strcmp("water", goodName) == 0) m_goodType = 'P';
				else m_goodType = 'N';

				name(goodName);

				strncpy(m_goodSku, goodSku, max_sku_length);
				m_goodSku[max_sku_length] = '\0';

				strncpy(m_goodUnit, goodUnit, max_unit_length);
				m_goodUnit[max_unit_length] = '\0';

				if (goodUnitHand >= 0) m_goodUnitHand = goodUnitHand;
				if (goodUnitNeed >= 0) m_goodUnitNeed = goodUnitNeed;
				if (goodPriceUnit >= 0.0) m_goodPriceUnit = goodPriceUnit;
				m_goodTaxStatus = goodTaxStatus;
			}
		}

		if (invalid) {
			if (m_goodType != 'P' || m_goodType != 'p') emptyState('N');
			else emptyState('P');
			name(goodName);
		}
	}

	// Function that copy all data from an object 
	// to the current object
	void Good::copyEverything(const Good& source)
	{
		name(source.m_goodName);

		strncpy(m_goodSku, source.m_goodSku, max_sku_length);
		m_goodSku[max_sku_length] = '\0';

		strncpy(m_goodUnit, source.m_goodUnit, max_unit_length);
		m_goodUnit[max_unit_length] = '\0';

		if (source.m_goodUnitHand >= 0) m_goodUnitHand = source.m_goodUnitHand;
		if (source.m_goodUnitNeed >= 0) m_goodUnitNeed = source.m_goodUnitNeed;
		if (source.m_goodPriceUnit >= 0.0) m_goodPriceUnit = source.m_goodPriceUnit;
		if (source.m_errorState.message()) m_errorState.message(source.m_errorState.message());

		m_goodTaxStatus = source.m_goodTaxStatus;
		m_goodType = source.m_goodType;
	}

	// Copies the object referenced to the current object
	Good::Good(const Good& source)
	{
		copyEverything(source);
	}

	// Copy assign operator that copies a Good object type
	// to the current object
	Good& Good::operator=(const Good& source)
	{
		copyEverything(source);
		return *this;
	}

	// Destructor to dealocate dynamic memory
	Good::~Good()
	{
		delete[] m_goodName;
		m_goodName = nullptr;
	}

	// Writes data into a file with "," character as a delimeter
	std::fstream& Good::store(std::fstream& file, bool newLine) const
	{
		file << m_goodType << ','
			<< m_goodSku << ','
			<< m_goodName << ','
			<< m_goodUnit << ','
			<< m_goodTaxStatus << ','
			<< m_goodPriceUnit << ','
			<< m_goodUnitHand << ','
			<< m_goodUnitNeed;

		if (newLine) file << std::endl;

		return file;
	}

	// reads data from a file and store into the current instance
	std::fstream& Good::load(std::fstream& file)
	{
		Good temporary;
		temporary.m_goodName = new char[max_name_length + 1];


		file.getline(temporary.m_goodSku, max_sku_length, ',');
		file.getline(temporary.m_goodName, max_name_length, ',');
		file.getline(temporary.m_goodUnit, max_unit_length, ',');
		file >> temporary.m_goodTaxStatus;
		file.ignore();
		file >>  temporary.m_goodPriceUnit;
		file.ignore();
		file >> temporary.m_goodUnitHand;
		file.ignore();
		file >> temporary.m_goodUnitNeed;

		if (!temporary.isEmpty()) *this = temporary;

		return file;
	}

	// Display current instance's data on the screen
	std::ostream& Good::write(std::ostream& os, bool linear) const
	{
		if (m_errorState.message() != nullptr) 
			os << m_errorState.message();

		os.setf(std::ios::fixed);
		if (!isEmpty() && isClear()) {
			if (linear) {
				os.setf(std::ios::left);
				os.width(max_sku_length);
				os << m_goodSku << "|";

				os.width(20);
				os << name() << "|";

				os.unsetf(std::ios::left);
				os.precision(2);
				os.width(7);

				os << itemCost() << "|"; 

				os.width(4);
				os << m_goodUnitHand << "|";

				os.setf(std::ios::left);
				os.width(10);
				os << m_goodUnit << "|";

				os.width(4);
				os.unsetf(std::ios::left);
				os << m_goodUnitNeed << "|";
			}
			else {
				os << " Sku: " << m_goodSku << std::endl;
				os << " Name (no spaces): ";
				os << m_goodName << std::endl;
				os << " Price: ";
				os << m_goodPriceUnit << std::endl;
				os << " Price after tax: ";

				if (m_goodTaxStatus) {
					os << itemCost() << std::endl;
				}
				else {
					os << " N/A" << std::endl;
				}

				os << " Quantity on Hand: " << m_goodUnitHand << ' ' << m_goodUnit << std::endl
					<< " Quantity needed: " << m_goodUnitNeed;
				if (strcmp("box", m_goodName) < 0) os << std::endl;
			}
		}

		return os;
	}

	// Extracts from the user the data fields for the current object
	// if one of the data fails, the extraction stops and show the
	// input error
	std::istream& Good::read(std::istream& is)
	{
		char sku[max_sku_length + 1];
		char name[max_name_length + 1];
		char unit[max_unit_length + 1];
		char tax;
		bool taxStatus;
		double price;
		int qntHand;
		int qntNeed;
		Error error;

		std::cout << " Sku: ";
		is >> sku;							
		std::cout << " Name (no spaces): ";
		is >> name;
		std::cout << " Unit: ";
		is >> unit;
		std::cout << " Taxed? (y/n): ";
		is >> tax;

		if (tax == 'y' || tax == 'Y') { taxStatus = true; }
		else if (tax == 'n' || tax == 'N') { taxStatus = false; }
		else {
			/*error.clear();*/
			is.setstate(std::ios::failbit);
			error.message("Only (Y)es or (N)o are acceptable");

		}

		if (!is.fail())
		{
			std::cout << " Price: ";
			is >> price;

			if (is.fail()) { error.message("Invalid Price Entry"); }
		}

		if (!is.fail())
		{
			std::cout << " Quantity on hand: ";
			is >> qntHand;

			if (is.fail()) { error.message("Invalid Quantity Entry"); }
		}

		if (!is.fail())
		{
			std::cout << " Quantity needed: ";
			is >> qntNeed;

			if (is.fail()) { error.message("Invalid Quantity Needed Entry"); }
		}

		if (!is.fail())
		{
			Good temp(sku, name, unit, qntHand, taxStatus, price, qntNeed);
			m_errorState.message(error.message());
			*this = temp;
		}
		else {
			Good temp;
			*this = temp;
			if (error.message() != nullptr) m_errorState.message(error.message());
		}

		return is;
	}

	// Returns the total cost of all items of the Good on hand, taxes included
	double Good::total_cost() const
	{
		return ((m_goodPriceUnit * m_goodUnitHand) * (1 + tax_rate));
	}

	// If this number of units of the Good that are on hand is positive-valued 
	// this function resets the number of units that are on hand to the number received; 
	// otherwise, this function does nothing 
	void Good::quantity(int goodUnitHand)
	{
		if (goodUnitHand > 0) m_goodUnitHand = goodUnitHand;
	}

	// Checks if the current instance is empty
	bool Good::isEmpty() const
	{
		return (m_goodSku[0] == '\0' && m_goodUnit[0] == '\0' && m_goodName == nullptr
			&& m_goodUnitHand == 0 && m_goodUnitNeed == 0 && m_goodPriceUnit == 0.0);
	}

	// Returns the number of units of the Good that are needed
	int Good::qtyNeeded() const
	{
		return m_goodUnitNeed;
	}

	// Returns the number of units of the Good that are on hand
	int Good::quantity() const
	{
		return m_goodUnitHand;
	}

	// Returns true if the string is identical to the SKU of the current object;
	// false otherwise
	bool Good::operator==(const char* goodSku) const
	{
		return (strncmp(m_goodSku, goodSku, max_sku_length) == 0) ? true : false;
	}

	// Returns true if the SKU of the current object is greater than the SKU string
	// passed to the function; false otherwise
	bool Good::operator>(const char* goodSku) const
	{
		return (strncmp(m_goodSku, goodSku, max_sku_length) > 0) ? true : false;
	}

	// Returns true if the Name of the current object is greater than the Name of the
	// Good object passed to the function; false otherwise
	bool Good::operator>(const iGood& source) const
	{
		return (strncmp(m_goodName, source.name(), strlen(m_goodName)) > 0) ? true : false;
	}

	// Return the number of goods units on hand added to a specifc number of units
	// passed to the function, if the number of units received is positive; 
	// otherwise it returns the number of units on hand that already existed before
	int Good::operator+=(int numberUnits)
	{
		if (numberUnits > 0) m_goodUnitHand += numberUnits;
		return m_goodUnitHand;
	}

	// Inserts a Good record into the std::ostream
	std::ostream& operator<<(std::ostream& os, const iGood& source)
	{
		source.write(os, true);
		return os;
	}

	// Extracts the Good record from the std::istream (user will input data)
	std::istream& operator>>(std::istream& is, iGood& source)
	{
		source.read(is);
		return is;
	}

	// Adds the total cost of the Good object to the double received and 
	// returns the updated double
	double operator+=(double& cost, const iGood& source)
	{
		cost += source.total_cost();
		return cost;
	}
}