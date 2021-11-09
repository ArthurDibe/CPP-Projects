/********************************
Developed by: Dibe
********************************/

#ifndef AID_DATE_H
#define AID_DATE_H

#include <iostream>

// Possible Error States
#define NO_ERROR 0
#define CIN_FAILED 1
#define DAY_ERROR 2
#define MON_ERROR 3
#define YEAR_ERROR 4
#define PAST_ERROR 5

namespace aid
{
	const int min_year = 2018;
	const int max_year = 2038;
	const int min_date = 751098;

	class Date {
		int m_year;			 // can be between the "min_year" and "max_year"
		int m_month;		 // can be between 1 and 12
		int m_day;			 // use function "mdays(int year, int month)" to find out how many days
		int m_cmprtrValue;	 // used to compare the date of the current object with the date of another object
		int m_errState;		 // error state variable

		void errCode(int errorCode);		  
		int mdays(int year, int month) const; 

		int cmprtrCalculus(int year, int month, int day);
		int checkNumbers(int year, int month, int day);
		void variablesAssign(int year, int month, int day, int cmprtrValue, int errorCode);
		bool isEmpty(const Date& rhs) const;

	public:
		Date();
		Date(int year, int month, int day);
		
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		
		int errCode() const;
		bool bad() const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;
	};

	std::ostream& operator<<(std::ostream& os, const Date& rhs);
	std::istream& operator>>(std::istream& is, Date& rhs);
}
#endif // !AID_DATE_H