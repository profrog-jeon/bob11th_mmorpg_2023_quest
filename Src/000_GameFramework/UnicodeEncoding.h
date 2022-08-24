#pragma once

namespace unicode
{
	size_t CalcUnicodeCchFromASCII(LPCSTR pSrc, size_t tSrcCch, size_t* ptSrcReadCch);
	size_t ASCII_TO_ASCII(const char* pSrc, size_t tSrcCch, char* pDest, size_t tDestCch);
	size_t ASCII_TO_UTF16(LPCSTR pSrc, size_t tSrcCch, WORD* pDest, size_t tDestCch, size_t* ptReadSize);
	size_t UTF16_TO_UTF16(const WORD* pSrc, size_t tSrcCch, WORD* pDest, size_t tDestCch);
	size_t UTF16_TO_ASCII(const WORD* pSrc, size_t tSrcCch, char* pDest, size_t tDestCch);
}
