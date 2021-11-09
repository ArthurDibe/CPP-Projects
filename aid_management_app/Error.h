/********************************
Developed by: Dibe
********************************/

#include <ostream>

#ifndef AID_ERROR_H
#define AID_ERROR_H

namespace aid
{
	class Error
	{
		char* m_errorMessage;

	public:
		explicit Error(const char* errorMessage = nullptr);
		~Error();
		void clear();
		bool isClear() const;
		void message(const char* str);
		const char* message() const;
	};
	std::ostream& operator<<(std::ostream& os, const Error& rhs);

}
#endif