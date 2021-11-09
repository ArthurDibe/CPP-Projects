/********************************
Developed by: Dibe
********************************/
#include <cstring>
#include "Error.h"

namespace aid
{
	// Constructor that is used as default constructor and as a constructor to assign a c-string
	Error::Error(const char* errorMessage)
	{
		m_errorMessage = nullptr;
		message(errorMessage);
	}


	// Destructor that deallocates dynamic memory
	Error::~Error()
	{
		delete[] m_errorMessage;
		m_errorMessage = nullptr;
	}


	// Function that can be called by the Client's code to deallocate dynamic memory
	// and to assign to a safe empty state
	void Error::clear()
	{
		if (m_errorMessage != nullptr) {
			delete[] m_errorMessage;
			m_errorMessage = nullptr;
		}
	}


	// Function that checks if the current object is in a safe empty state
	bool Error::isClear() const
	{
		return (m_errorMessage == nullptr || m_errorMessage[0] == '\0') ? true : false;
	}


	// Function that assign some c-string data to the member data of the current object
	void Error::message(const char* str)
	{
		if (str != nullptr)
		{
			if (str[0] != '\0')
			{
				int size = strlen(str);
				if (m_errorMessage == nullptr)
				{
					m_errorMessage = new char[size + 1];
				}
				else
				{
					clear();
					m_errorMessage = new char[size + 1];
				}
				strncpy(m_errorMessage, str, size);
				m_errorMessage[size] = '\0';
			}
			else
			{
				if (m_errorMessage == nullptr) {
					m_errorMessage = new char;
				}
				m_errorMessage[0] = '\0';
			}
		}
		else
		{
			m_errorMessage = nullptr;
		}
	}


	// Function that returns the current object's message address if it is not
	// in a safe empty state, otherwise it returns nullptr
	const char* Error::message() const
	{
		return (!isClear()) ? m_errorMessage : nullptr;
	}


	// Helper function that display on screen the message of an object if
	// some message exists on its data member
	std::ostream& operator<<(std::ostream& os, const Error& rhs)
	{
		if (!rhs.isClear()) 
			os << rhs.message();

		return os;
	}
}