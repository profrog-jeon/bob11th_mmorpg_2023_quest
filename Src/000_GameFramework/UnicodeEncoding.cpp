#include "pch.h"
#include "UnicodeEncoding.h"

namespace unicode
{
	template<typename T>
	inline T InternalMIN(T a, T b)
	{
		return a < b? a : b;
	}

	template<typename T>
	inline T InternalMAX(T a, T b)
	{
		return a > b? a : b;
	}

	//////////////////////////////////////////////////////////////////////////
	size_t CalcUnicodeCchFromASCII(LPCSTR pSrc, size_t tSrcCch, size_t* ptSrcReadCch)
	{
		size_t tDestLen = 0;
		size_t tPos = 0;
		while(tPos < tSrcCch)
		{
			size_t tPrePos = tPos;
			if( pSrc[tPos] < 0 )
				tPos += 2;
			else
				tPos++;

			if (tPos > tSrcCch)
			{
				tPos = tPrePos;
				break;
			}

			tDestLen++;
		}

		if( ptSrcReadCch )
			*ptSrcReadCch = tPos;
		return tDestLen;
	}

	//////////////////////////////////////////////////////////////////////////
	size_t ASCII_TO_ASCII(const char* pSrc, size_t tSrcCch, char* pDest, size_t tDestCch)
	{
		if( pDest )
			memcpy(pDest, pSrc, InternalMIN(tSrcCch, tDestCch));
		return tSrcCch;
	}

	//////////////////////////////////////////////////////////////////////////
	size_t UTF16_TO_UTF16(const WORD* pSrc, size_t tSrcCch, WORD* pDest, size_t tDestCch)
	{
		if( pDest )
			memcpy(pDest, pSrc, InternalMIN(tSrcCch, tDestCch));
		return tSrcCch;
	}

	//////////////////////////////////////////////////////////////////////////
	size_t ASCII_TO_UTF16(LPCSTR pSrc, size_t tSrcCch, WORD* pDest, size_t tDestCch, size_t* ptReadSize)
	{
		try
		{
			if (tSrcCch == 0)
				return 0;

			size_t tSrcReadCch;
			size_t tReqDestCch = CalcUnicodeCchFromASCII(pSrc, tSrcCch, &tSrcReadCch);

			if (NULL == pDest)
			{
				size_t tDstLen = ::MultiByteToWideChar(CP_ACP, 0, pSrc, (int)tSrcReadCch, NULL, 0);
				if (0 == tDstLen)
					throw std::runtime_error("MultiByteToWideChar failure, calc requiredSize");
			}
			else
			{
				size_t tDstLen = ::MultiByteToWideChar(CP_ACP, 0, pSrc, (int)tSrcReadCch, (LPWSTR)pDest, (int)tDestCch);
				if (0 == tDstLen)
					throw std::runtime_error("MultiByteToWideChar failure, memory copy");
			}

			if (ptReadSize)
				*ptReadSize = tSrcReadCch;

			return tReqDestCch;
		}
		catch (std::exception& e)
		{
			int nRet = ::GetLastError();
			printf("Conv failure(MBS -> WCS) - %s, Error:%d\n", e.what(), nRet);
			return 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	size_t UTF16_TO_ASCII(const WORD* pSrc, size_t tSrcCch, char* pDest, size_t tDestCch)
	{
		size_t tDstLen = 0;

		try
		{
			if (tSrcCch == 0)
				return 0;

			if (NULL == pDest)
			{
				tDstLen = ::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pSrc, (int)tSrcCch, NULL, 0, NULL, NULL);
				if (0 == tDstLen)
					throw std::runtime_error("MultiByteToWideChar failure, calc requiredSize");
			}
			else
			{
				tDstLen = ::WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)pSrc, (int)tSrcCch, (LPSTR)pDest, (int)tDestCch, NULL, NULL);
				if (0 == tDstLen)
					throw std::runtime_error("MultiByteToWideChar failure, memory copy");
			}
		}
		catch (std::exception& e)
		{
			int nRet = ::GetLastError();
			printf("Conv failure(WCS -> MBS) - %s, Error:%d\n", e.what(), nRet);
			return 0;
		}

		return tDstLen;
	}
}
