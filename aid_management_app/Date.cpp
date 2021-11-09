/********************************
Developed by: Dibe
********************************/

#include "Date.h"

namespace aid
{
	// sets the error state variable to one of the Error State values
	void Date::errCode(int errorCode)
	{
		switch (errorCode) {
			case 0:
				m_errState = NO_ERROR;
				break;
			case 1:
				m_errState = CIN_FAILED;
				break;
			case 2:
				m_errState = DAY_ERROR;
				break;
			case 3:
				m_errState = MON_ERROR;
				break;
			case 4:
				m_errState = YEAR_ERROR;
				break;
			case 5:
				m_errState = PAST_ERROR;
				break;
		}
	}


	// returns the number of days in a given month for a given year
	int Date::mdays(int year, int mon) const 
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}


	// default constructor: Initialize the object to a safe Empty State
	Date::Date() 
	{
		m_year = 0;
		m_month = 0;
		m_day = 0;
		m_cmprtrValue = 0;
		m_errState = NO_ERROR;
	}


	// constructor that checks if each number is in range, 
	// in the order of year, month and day and value
	Date::Date(int year, int month, int day)
	{
		int errorStatus = checkNumbers(year, month, day);

		if (errorStatus == NO_ERROR)
		{
			variablesAssign(year, month, day, cmprtrCalculus(year, month, day), errorStatus);
		}
		else {
			variablesAssign(0, 0, 0, 0, errorStatus);
		}
	}


	// calculate the value of the date
	int Date::cmprtrCalculus(int year, int month, int day) {
		return (year * 372 + month * 31 + day);
	}


	// check the numbers and return the error status value
	
	int Date::checkNumbers(int year, int month, int day) 
	{
		int errorStatus = NO_ERROR;

		if (year >= min_year && year <= max_year) {
			if (month >= 1 && month <= 12) {
				if (day >= 1 && day <= mdays(year, month)) 
				{
					if (cmprtrCalculus(year, month, day) >= min_date) {
						errorStatus = NO_ERROR;
					}
					else {
						errorStatus = PAST_ERROR;
					}
				}
				else {
					errorStatus = DAY_ERROR;
				}
			}
			else {
				errorStatus = MON_ERROR;
			}
		}
		else {
			errorStatus = YEAR_ERROR;
		}
		return errorStatus;
	}


	// assign variables to data members (the errorCode change depending on the error)
	void Date::variablesAssign(int year, int month, int day, int cmprtrValue, int errorCode) {
		m_year = year;
		m_month = month;
		m_day = day;
		m_cmprtrValue = cmprtrValue;
		errCode(errorCode);
	}


	// check if the current object and/or another object is in a safe empty state
	bool Date::isEmpty(const Date& rhs) const 
	{
		return ((rhs.m_year == 0 && rhs.m_month == 0 && rhs.m_day == 0) ||
			    (m_year == 0 && m_month == 0 && m_day == 0)) ? true : false;
	}


	// check if the date of the current object is equal to another one
	bool Date::operator==(const Date& rhs) const 
	{
		bool notValid = false;

		if (isEmpty(rhs)) {
			notValid = true;
		}
		else {
			if (m_year != rhs.m_year || m_month != rhs.m_month || m_day != rhs.m_day)
				notValid = true;
		}
		return notValid ? false : true;
	}


	// check if the date of the current object is not equal to another one
	bool Date::operator!=(const Date& rhs) const
	{
		bool notValid = false;

		if (isEmpty(rhs)) {
			notValid = true;
		}
		else {
			if (m_year == rhs.m_year && m_month == rhs.m_month && m_day == rhs.m_day)
				notValid = true;
		}
		return notValid ? false : true;
	}


	// check if the date of the current object is less than another one
	bool Date::operator<(const Date& rhs) const
	{
		bool notValid = false;

		if (isEmpty(rhs)) {
			notValid = true;
		}
		else {
			if (m_year > rhs.m_year || m_month > rhs.m_month || m_day > rhs.m_day || *this == rhs)
				notValid = true;
		}
		return notValid ? false : true;
	}


	// check if the date of the current object is greater than another one
	bool Date::operator>(const Date& rhs) const
	{
		bool notValid = false;

		if (isEmpty(rhs)) {
			notValid = true;
		}
		else {
			if (m_year < rhs.m_year || m_month < rhs.m_month || m_day < rhs.m_day || *this == rhs)
				notValid = true;
		}
		return notValid ? false : true;
	}


	// check if the date of the current object is less or equal to another one
	bool Date::operator<=(const Date& rhs) const
	{
		bool notValid = false;

		if (isEmpty(rhs)) {
			notValid = true;
		}
		else {
			if (m_year > rhs.m_year || m_month > rhs.m_month || m_day > rhs.m_day)
				notValid = true;
		}
		return notValid ? false : true;
	}


	// check if the date of the current object is greater or equal to another one
	bool Date::operator>=(const Date& rhs) const
	{
		bool notValid = false;

		if (isEmpty(rhs)) {
			notValid = true;
		}
		else {
			if (m_year < rhs.m_year || m_month < rhs.m_month || m_day < rhs.m_day)
				notValid = true;
		}
		return notValid ? false : true;
	}


	// returns the error state as an error code value.
	int Date::errCode() const 
	{
		return m_errState;
	}


	// test if there is an error state
	bool Date::bad() const
	{
		return m_errState != NO_ERROR ? true : false;
	}


	// reads the date from the console in the following format "YYYY?MM?DD"
	std::istream& Date::read(std::istream& istr)
	{
		Date date;
		char separator1, separator2;
		bool wrongData = false;

		istr >> date.m_year >> separator1 >> date.m_month >> separator2 >> date.m_day;

		if (!istr.fail()) {
			if (separator1 == separator2) {
				int errorStatus = checkNumbers(date.m_year, date.m_month, date.m_day);
				if (errorStatus == NO_ERROR)
				{
					int cmprtrValue = cmprtrCalculus(date.m_year, date.m_month, date.m_day);
					variablesAssign(date.m_year, date.m_month, date.m_day, cmprtrValue, errorStatus);
				}
				else {
					errCode(errorStatus);
				}
			}
			else {
				wrongData = true;
			}
		}
		else {
			wrongData = true;
		}

		if(wrongData) errCode(CIN_FAILED);

		return istr;
	}


	// prints the date on the console and return the reference of std::ostream
	std::ostream& Date::write(std::ostream& ostr) const {
		ostr.fill('0');
		ostr << m_year << "/";
		ostr.width(2);
		ostr << m_month;
		ostr << "/";
		ostr.width(2);
		ostr << m_day;
		ostr.fill(' ');
		return ostr;
	}


	// call the write function to print the date on the console
	std::ostream& operator<<(std::ostream& os, const Date& rhs) {
		rhs.write(os);
		return os;
	}


	// call the read function to get the date from the console
	std::istream& operator>>(std::istream& is, Date& rhs) {
		rhs.read(is);
		return is;
	}
}
