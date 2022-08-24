#include "pch.h"
#include "Unicode.h"
#include "UnicodeEncoding.h"

namespace unicode
{
	//////////////////////////////////////////////////////////////////////////
	std::wstring WCSFromMBS(std::string strInput)
	{
		std::wstring strRet;
		size_t tRequiredCch = ASCII_TO_UTF16(strInput.c_str(), strInput.length(), NULL, 0, NULL);
		strRet.resize(tRequiredCch);
		ASCII_TO_UTF16(strInput.c_str(), strInput.length(), (WORD*)strRet.c_str(), tRequiredCch, NULL);
		return strRet;
	}

	//////////////////////////////////////////////////////////////////////////
	std::string MBSFromWCS(std::wstring strInput)
	{
		std::string strRet;
		size_t tRequiredCch = UTF16_TO_ASCII((const WORD*)strInput.c_str(), strInput.length(), NULL, 0);
		strRet.resize(tRequiredCch);
		UTF16_TO_ASCII((const WORD*)strInput.c_str(), strInput.length(), (char*)strRet.c_str(), tRequiredCch);
		return strRet;
	}

	//////////////////////////////////////////////////////////////////////////
	std::wstring WCSFromUTF16(const WORD* pszInput, size_t tInputCch)
	{
		std::wstring strRet;
		strRet.resize(tInputCch);
		memcpy((void*)strRet.c_str(), pszInput, tInputCch * 2);
		return strRet;
	}

	//////////////////////////////////////////////////////////////////////////
	std::wstring WCSFromASCII(std::string strInput, size_t* ptReadSize)
	{
		std::wstring strRet;
		size_t tRequiredCch = ASCII_TO_UTF16(strInput.c_str(), strInput.length(), NULL, 0, ptReadSize);
		strRet.resize(tRequiredCch);
		ASCII_TO_UTF16(strInput.c_str(), strInput.length(), (WORD*)strRet.c_str(), tRequiredCch, ptReadSize);
		return strRet;
	}

	//////////////////////////////////////////////////////////////////////////
	std::string MBSFromUTF16(const WORD* pszInput, size_t tInputCch)
	{
		std::string strRet;
		size_t tRequiredCch = UTF16_TO_ASCII(pszInput, tInputCch, NULL, 0);
		strRet.resize(tRequiredCch);
		UTF16_TO_ASCII(pszInput, tInputCch, (char*)strRet.c_str(), tRequiredCch);	
		return strRet;
	}

	//////////////////////////////////////////////////////////////////////////
	std::string MBSFromASCII(std::string strInput, size_t* ptReadSize)
	{
		std::string strRet;
		strRet.resize(strInput.length());
		memcpy((void*)strRet.c_str(), strInput.c_str(), strInput.length());
		return strRet;
	}

	//////////////////////////////////////////////////////////////////////////
	std::wstring WCSFromWCS(std::wstring strInput)
	{
		return strInput;
	}

	//////////////////////////////////////////////////////////////////////////
	std::string MBSFromMBS(std::string strInput)
	{
		return strInput;
	}

	//////////////////////////////////////////////////////////////////////////
	std::string ASCIIFromMBS(std::string strInput)
	{
		return strInput;
	}

	//////////////////////////////////////////////////////////////////////////
	std::string ASCIIFromWCS(std::wstring strInput)
	{
		std::string strRet;
		size_t tRequiredCch = UTF16_TO_ASCII((const WORD*)strInput.c_str(), strInput.length(), NULL, 0);
		strRet.resize(tRequiredCch);
		UTF16_TO_ASCII((const WORD*)strInput.c_str(), strInput.length(), (char*)strRet.c_str(), tRequiredCch);
		return strRet;
	}

	//////////////////////////////////////////////////////////////////////////
	std::vector<WORD> UTF16FromMBS(std::string strInput)
	{
		std::vector<WORD> strRet;
		size_t tRequiredCch = ASCII_TO_UTF16(strInput.c_str(), strInput.length(), NULL, 0, NULL);
		strRet.resize(tRequiredCch);
		ASCII_TO_UTF16(strInput.c_str(), strInput.length(), &strRet[0], tRequiredCch, NULL);
		return strRet;
	}

	//////////////////////////////////////////////////////////////////////////
	std::vector<WORD> UTF16FromWCS(std::wstring strInput)
	{
		std::vector<WORD> strRet;
		strRet.resize(strInput.length());

		size_t i;
		for(i=0; i<strInput.length(); i++)
			strRet[i] = strInput.at(i);

		return strRet;
	}
}
