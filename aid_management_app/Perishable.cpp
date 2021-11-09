/********************************
Developed by: Dibe
********************************/

#include "Perishable.h"
#include "Date.h"

namespace aid
{
	Perishable::Perishable() : Good('P') {}

	std::fstream& Perishable::store(std::fstream& file, bool newLine) const
	{
		Good::store(file, false);
		file << ',' << m_expiryDate;
		if (newLine) file << std::endl;

		return file;
	}

	std::fstream& Perishable::load(std::fstream& file)
	{
		Good::load(file);
		file.ignore();
		m_expiryDate.read(file);
		file.get();

		return file;
	}

	std::ostream& Perishable::write(std::ostream& os, bool linear) const
	{
		if (m_errorState.message() != nullptr)
			os << m_errorState.message();

		if (!isEmpty() && isClear()) {
			Good::write(os, linear);
			if (!linear) {
				os << " Expiry date: ";
				m_expiryDate.write(os);
			}
			else {
				/*os.clear();*/
				m_expiryDate.write(os);
			}
		}

		return os;
	}

	std::istream& Perishable::read(std::istream& is)
	{
		Good::read(is);
		if (!is.fail()) {
			std::cout << " Expiry date (YYYY/MM/DD): ";
			Date temporary;
			temporary.read(is);

			if (temporary.errCode()) {
				is.setstate(std::ios::failbit);
				switch (temporary.errCode()) {
				case CIN_FAILED:
					m_errorState.message("Invalid Date Entry");
					break;
				case DAY_ERROR:
					m_errorState.message("Invalid Day in Date Entry");
					break;
				case MON_ERROR:
					m_errorState.message("Invalid Month in Date Entry");
					break;
				case YEAR_ERROR:
					m_errorState.message("Invalid Year in Date Entry");
					break;
				case PAST_ERROR:
					m_errorState.message("Invalid Expiry in Date Entry");
					break;
				}
			}
			else {
				/*m_errorState.clear();*/
				m_expiryDate = temporary;
			}
		}
		return is;
	}

	const Date& Perishable::expiry() const
	{
		return m_expiryDate;
	}

	iGood* CreateProduct(char tag)
	{
		iGood* obj = nullptr;
		if (tag == 'N' || tag == 'n') obj = new Good();
		if (tag == 'P' || tag == 'p') obj = new Perishable();

		return obj;
	}
}