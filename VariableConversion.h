#pragma once
#include <string>
namespace vc 
{
	class VariableConversion{
	public:
		std::string constChar_tToString(const wchar_t* charToConvert);
		const wchar_t* stringToConstChar_t(std::string stringToConvert);
		const char* stringToChar(std::string stringToConvert);
	};
}
