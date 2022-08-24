#pragma once

#include <vector>
#include <string>

namespace unicode
{
	std::wstring	WCSFromWCS(std::wstring strInput);
	std::string		MBSFromMBS(std::string strInput);

	std::wstring	WCSFromMBS(std::string strInput);
	std::string		MBSFromWCS(std::wstring strInput);
	std::wstring	WCSFromUTF16(const WORD* pszInput, size_t tInputCch);
	std::wstring	WCSFromASCII(std::string strInput, size_t* ptReadSize = NULL);

	std::string		MBSFromUTF16(const WORD* pszInput, size_t tInputCch);
	std::string		MBSFromASCII(std::string strInput, size_t* ptReadSize = NULL);

	std::string		ASCIIFromMBS(std::string strInput);
	std::string		ASCIIFromWCS(std::wstring strInput);

	std::vector<WORD>	UTF16FromMBS(std::string strInput);
	std::vector<WORD>	UTF16FromWCS(std::wstring strInput);
}

