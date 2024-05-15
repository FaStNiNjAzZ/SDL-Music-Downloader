#include "VariableConversion.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace vc;

// Convert wchar_t to string
std::string VariableConversion::constChar_tToString(const wchar_t* charToConvert)
{
	std::wstring ws(charToConvert);
	std::string stringConverted(ws.begin(), ws.end());
	return stringConverted;
}

// Convert string to wchar_t
const wchar_t* VariableConversion::stringToConstChar_t(std::string stringToConvert)
{
	const char* stringConvertedToChar = stringToConvert.c_str();

	const size_t cSize = strlen(stringConvertedToChar) + 1;
	wchar_t* wcharConverted = new wchar_t[cSize];
	mbstowcs(wcharConverted, stringConvertedToChar, cSize);

	return wcharConverted;
}

const char* VariableConversion::stringToChar(std::string stringToConvert) 
{
	const char* convertedChar = stringToConvert.c_str();
	return convertedChar;
}