#include "pch.h"
#include "CHangulCharset.h"

const char* charset_cho[19] =
{ "r","R","s","e","E","f","a","q","Q","t","T","d","w","W","c","z","x","v","g" };
const char* charset_jung[21] =
{ "k","o","i","O","j","p","u","P","h","hk","ho","hl","y","n","nj","np","nl","b","m","ml","l" };
const char* charset_jong[28] =
{ "", "r","R","rt","s","sw","sg","e","f","fr","fa","fq","ft","fx","fv","fg","a","q","qt","t","T","d","w","c","z","x","v","g" };

const char* charset_Useless[19] = { "F","A","D","C","Z","X","V","G","K","I","J","U","N","B","H","Y","M","L","S" };

int charset_single[40] = { 0x3131, 0x3132, 0x3134, 0x3137, 0x3138, 0x3139, 0x3141, 0x3142, 0x3143, 0x3145, 0x3146, 0x3147, 0x3148, 0x3149, 0x314A, 0x314B, 0x314C, 0x314D, 0x314E, 0x314F, 0x3150, 0x3151, 0x3152, 0x3153, 0x3154, 0x3155, 0x3156, 0x3157, 0x3158, 0x3159, 0x315A, 0x315B, 0x315C, 0x315D, 0x315E, 0x315F, 0x3160, 0x3161, 0x3162, 0x3163 };

std::map<int, std::string> mStrSetLower
{
	{ 0x41, "a" },
	{ 0x42, "b" },
	{ 0x43, "c" },
	{ 0x44, "d" },
	{ 0x45, "e" },
	{ 0x46, "f" },
	{ 0x47, "g" },
	{ 0x48, "h" },
	{ 0x49, "i" },
	{ 0x4A, "j" },
	{ 0x4B, "k" },
	{ 0x4C, "l" },
	{ 0x4D, "m" },
	{ 0x4E, "n" },
	{ 0x4F, "o" },
	{ 0x50, "p" },
	{ 0x51, "q" },
	{ 0x52, "r" },
	{ 0x53, "s" },
	{ 0x54, "t" },
	{ 0x55, "u" },
	{ 0x56, "v" },
	{ 0x57, "w" },
	{ 0x58, "x" },
	{ 0x59, "y" },
	{ 0x5A, "z" },
	{ 0x30, "0" }
};
std::map<int, std::string> mStrSetUpper
{
	{ 0x41, "a" },
	{ 0x42, "b" },
	{ 0x43, "c" },
	{ 0x44, "d" },
	{ 0x45, "E" },
	{ 0x46, "f" },
	{ 0x47, "g" },
	{ 0x48, "h" },
	{ 0x49, "i" },
	{ 0x4A, "j" },
	{ 0x4B, "k" },
	{ 0x4C, "l" },
	{ 0x4D, "m" },
	{ 0x4E, "n" },
	{ 0x4F, "O" },
	{ 0x50, "P" },
	{ 0x51, "Q" },
	{ 0x52, "R" },
	{ 0x53, "s" },
	{ 0x54, "T" },
	{ 0x55, "u" },
	{ 0x56, "v" },
	{ 0x57, "W" },
	{ 0x58, "x" },
	{ 0x59, "y" },
	{ 0x5A, "z" }
};

std::string CHangulCharset::StrFromVirtualKey(int nVirtualKey, bool bShiftPressed)
{
	std::string strRet;
	if (bShiftPressed)
		strRet = mStrSetUpper[nVirtualKey];
	else
		strRet = mStrSetLower[nVirtualKey];

	return strRet;
}

int CHangulCharset::GetIndexNum(const char* chararray[], int SizeofArray, const char* c)
{
	for (int i = 0; i < SizeofArray; i++)
	{
		if (strcmp(c, chararray[i]) == 0)
			return i;
	}
	return -1;
}

int CHangulCharset::AssemUnicode(ST_CONSTRUCT stCurrentConstruct)
{
	int nResult;
	if (stCurrentConstruct.choseong == CONSTRUCT_DEFAULT && stCurrentConstruct.jungseong != CONSTRUCT_DEFAULT)		// 초성은 없는데 중성이 있는 경우
		nResult = charset_single[stCurrentConstruct.jungseong + 19];
	else if (stCurrentConstruct.choseong != CONSTRUCT_DEFAULT && stCurrentConstruct.jungseong == CONSTRUCT_DEFAULT)	// 초성은 있는데 중성이 없는경우
		nResult = charset_single[stCurrentConstruct.choseong];
	else
		nResult = UNICODE_BASE + (((stCurrentConstruct.choseong * NUM_OF_JUNGSEONG) + stCurrentConstruct.jungseong) * NUM_OF_JONGSEONG) + stCurrentConstruct.jongseong;

	return nResult;
}

// 자음인지 모음인지 체크
int CHangulCharset::CheckStr(std::string c)
{
	std::string index = charset_cho[10];

	for (int i = 0; i < 19; i++)
	{
		index = charset_cho[i];
		if (strcmp(c.c_str(), index.c_str()) == 0) {
			return CONSONANT; // 있으면 자음
		}
	}
	return VOWEL; // 없으면 모음
}

void CHangulCharset::DeleteChar(int nVirtualKey, ST_STRING_CONTEXT& context)
{
	std::wstring strPreContext = context.strContext.substr(0, context.nCursorPos);
	std::wstring strPosContext = context.strContext.substr(context.nCursorPos);

	switch (state)
	{
	case BLANK:
	{
		strPreContext.pop_back();
		if (0 < context.nCursorPos)
			context.nCursorPos--;
		break;
	}
	case ONLY_CHOSEONG:
	{
		stCurrentConstruct.choseong = CONSTRUCT_DEFAULT;
		context.strUnderConstruct.clear();

		strPreContext.pop_back();
		state = BLANK;

		context.nCursorPos--;
		break;
	}
	case ONLY_JUNGSEONG:
	{
		stCurrentConstruct.jungseong = CONSTRUCT_DEFAULT;
		context.strUnderConstruct.clear();

		strPreContext.pop_back();
		state = BLANK;

		context.nCursorPos--;
		break;
	}
	case NO_JONGSEONG_COMB_ABLE_H:
	{
		stCurrentConstruct.jungseong = CONSTRUCT_DEFAULT;
		context.strUnderConstruct = AssemUnicode(stCurrentConstruct);

		strPreContext.pop_back();
		state = ONLY_CHOSEONG;
		break;
	}
	case NO_JONGSEONG_COMB_ABLE_N:
	{
		stCurrentConstruct.jungseong = CONSTRUCT_DEFAULT;
		context.strUnderConstruct = AssemUnicode(stCurrentConstruct);

		strPreContext.pop_back();
		state = ONLY_CHOSEONG;
		break;
	}
	case NO_JONGSEONG_COMB_ABLE_M:
	{
		stCurrentConstruct.jungseong = CONSTRUCT_DEFAULT;
		context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
		strPreContext.pop_back();

		state = ONLY_CHOSEONG;
		break;
	}
	case NO_JONGSEONG_COMB_UNABLE:
	{
		// 중성이 두개가 합쳐있는 경우
		if (stCurrentConstruct.jungseong == 9 || stCurrentConstruct.jungseong == 10 || stCurrentConstruct.jungseong == 11) // ㅗ
		{
			std::string strSingleVowel = charset_jung[stCurrentConstruct.jungseong];
			strSingleVowel.pop_back();
			stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, strSingleVowel.c_str());

			strPreContext.pop_back();
			state = NO_JONGSEONG_COMB_ABLE_H;
		}
		else if (stCurrentConstruct.jungseong == 14 || stCurrentConstruct.jungseong == 15 || stCurrentConstruct.jungseong == 16) // ㅜ
		{
			std::string strSingleVowel = charset_jung[stCurrentConstruct.jungseong];
			strSingleVowel.pop_back();
			stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, strSingleVowel.c_str());

			strPreContext.pop_back();
			state = NO_JONGSEONG_COMB_ABLE_N;
		}
		else if (stCurrentConstruct.jungseong == 19) // ㅡ
		{
			std::string strSingleVowel = charset_jung[stCurrentConstruct.jungseong];
			strSingleVowel.pop_back();
			stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, strSingleVowel.c_str());

			strPreContext.pop_back();
			state = NO_JONGSEONG_COMB_ABLE_M;
		}
		else // 나머지
		{
			stCurrentConstruct.jungseong = CONSTRUCT_DEFAULT;

			strPreContext.pop_back();
			state = ONLY_CHOSEONG;
		}
		context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
		break;
	}
	case ONE_JONGSEONG_COMB_ABLE_R:
	{
		stCurrentConstruct.jongseong = 0;
		context.strUnderConstruct = AssemUnicode(stCurrentConstruct);

		if (stCurrentConstruct.jungseong == 8) // 중성이 "ㅗ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_H;
		else if (stCurrentConstruct.jungseong == 13) // 중성이 "ㅜ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_N;
		else if (stCurrentConstruct.jungseong == 18) // 중성이 "ㅡ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_M;
		else
			state = NO_JONGSEONG_COMB_UNABLE;

		strPreContext.pop_back();
		break;
	}
	case ONE_JONGSEONG_COMB_ABLE_S:
	{
		stCurrentConstruct.jongseong = 0;
		context.strUnderConstruct = AssemUnicode(stCurrentConstruct);

		if (stCurrentConstruct.jungseong == 8) // 중성이 "ㅗ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_H;
		else if (stCurrentConstruct.jungseong == 13) // 중성이 "ㅜ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_N;
		else if (stCurrentConstruct.jungseong == 18) // 중성이 "ㅡ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_M;
		else
			state = NO_JONGSEONG_COMB_UNABLE;

		strPreContext.pop_back();
		break;
	}
	case ONE_JONGSEONG_COMB_ABLE_F:
	{
		stCurrentConstruct.jongseong = 0;
		context.strUnderConstruct = AssemUnicode(stCurrentConstruct);

		if (stCurrentConstruct.jungseong == 8) // 중성이 "ㅗ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_H;
		else if (stCurrentConstruct.jungseong == 13) // 중성이 "ㅜ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_N;
		else if (stCurrentConstruct.jungseong == 18) // 중성이 "ㅡ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_M;
		else
			state = NO_JONGSEONG_COMB_UNABLE;

		strPreContext.pop_back();
		break;
	}
	case ONE_JONGSEONG_COMB_ABLE_Q:
	{
		stCurrentConstruct.jongseong = 0;
		context.strUnderConstruct = AssemUnicode(stCurrentConstruct);

		if (stCurrentConstruct.jungseong == 8) // 중성이 "ㅗ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_H;
		else if (stCurrentConstruct.jungseong == 13) // 중성이 "ㅜ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_N;
		else if (stCurrentConstruct.jungseong == 18) // 중성이 "ㅡ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_M;
		else
			state = NO_JONGSEONG_COMB_UNABLE;

		strPreContext.pop_back();
		break;
	}
	case ONE_JONGSEONG_COMB_UNABLE:
	{
		stCurrentConstruct.jongseong = 0;
		context.strUnderConstruct = AssemUnicode(stCurrentConstruct);

		if (stCurrentConstruct.jungseong == 8) // 중성이 "ㅗ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_H;
		else if (stCurrentConstruct.jungseong == 13) // 중성이 "ㅜ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_N;
		else if (stCurrentConstruct.jungseong == 18) // 중성이 "ㅡ"인 경우
			state = NO_JONGSEONG_COMB_ABLE_M;
		else
			state = NO_JONGSEONG_COMB_UNABLE;

		strPreContext.pop_back();
		break;
	}
	case DOUBLE_JONGSEONG:
	{
		std::string strSingleConsonant = charset_jong[stCurrentConstruct.jongseong];
		strSingleConsonant.pop_back();
		stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, strSingleConsonant.c_str());
		context.strUnderConstruct = AssemUnicode(stCurrentConstruct);

		if (stCurrentConstruct.jongseong == 1)
			state = ONE_JONGSEONG_COMB_ABLE_R;
		else if (stCurrentConstruct.jongseong == 4)
			state = ONE_JONGSEONG_COMB_ABLE_S;
		else if (stCurrentConstruct.jongseong == 8)
			state = ONE_JONGSEONG_COMB_ABLE_F;
		else if (stCurrentConstruct.jongseong == 17)
			state = ONE_JONGSEONG_COMB_ABLE_Q;
		else
			state = ONE_JONGSEONG_COMB_UNABLE;

		strPreContext.pop_back();
		break;
	}
	}

	context.strContext = strPreContext + context.strUnderConstruct + strPosContext;
}

void CHangulCharset::Update(int nVirtualKey, ST_STRING_CONTEXT& context, bool bShiftPressed)
{
	__super::Update(nVirtualKey, context, bShiftPressed);

	if (nVirtualKey == VK_BACK)
	{
		if (context.nCursorPos != 0)
			DeleteChar(nVirtualKey, context);
		return;
	}

	std::string c = StrFromVirtualKey(nVirtualKey, bShiftPressed);
	std::wstring strPreContext = context.strContext.substr(0, context.nCursorPos);
	std::wstring strPosContext = context.strContext.substr(context.nCursorPos);

	if (nVirtualKey < 'A' || 'Z' < nVirtualKey)
	{
		context.strUnderConstruct.clear();
		stCurrentConstruct.clear();
		state = BLANK;
		return;
	}

	if (0x41 <= nVirtualKey && nVirtualKey <= 0x5A)
	{
		int style = CheckStr(c);
		switch (state)
		{
		case BLANK: // ex) ""
		{
			if (style == CONSONANT) //자음
			{
				stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, c.c_str());
				context.strUnderConstruct = (AssemUnicode(stCurrentConstruct));

				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;
				state = ONLY_CHOSEONG;
				context.nCursorPos++;
				break;
			}
			else if (style == VOWEL) // 모음
			{
				stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, c.c_str());
				context.strUnderConstruct = (AssemUnicode(stCurrentConstruct));

				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;
				state = ONLY_JUNGSEONG;
				context.nCursorPos++;
				break;
			}
		}
		case ONLY_CHOSEONG: // ex) "ㄱ"
		{
			if (style == CONSONANT) // 자음
			{

				stCurrentConstruct.clear();

				stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, c.c_str());
				context.strUnderConstruct = AssemUnicode(stCurrentConstruct);

				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;
				state = ONLY_CHOSEONG;
				context.nCursorPos++;
				break;
			}
			else if (style == VOWEL) // 모음일 경우
			{
				stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, c.c_str());
				context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
				strPreContext.pop_back();
				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

				if (c == "h")
				{
					state = NO_JONGSEONG_COMB_ABLE_H;
					break;
				}
				else if (c == "n")
				{
					state = NO_JONGSEONG_COMB_ABLE_N;
					break;
				}
				else if (c == "m")
				{
					state = NO_JONGSEONG_COMB_ABLE_M;
					break;
				}
				else
				{
					state = NO_JONGSEONG_COMB_UNABLE;
					break;
				}
				break;
			}
		}
		case ONLY_JUNGSEONG: // ex) "ㅏ"
		{
			if (style == CONSONANT) // 자음
			{

				stCurrentConstruct.clear();

				stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, c.c_str());
				context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

				state = ONLY_CHOSEONG;
				context.nCursorPos++;
				break;
			}
			else if (style == VOWEL) // 모음
			{

				stCurrentConstruct.clear();

				stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, c.c_str());
				context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

				state = ONLY_JUNGSEONG;
				context.nCursorPos++;
				break;
			}
		}
		case NO_JONGSEONG_COMB_ABLE_H: // ex) "고"
		{
			if (style == CONSONANT) // 자음
			{


				if (c == "r")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_R;
					break;
				}
				else if (c == "s")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_S;
					break;
				}
				else if (c == "f")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_F;
					break;
				}
				else if (c == "q")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_Q;
					break;
				}
				else if (c == "Q" || c == "W" || c == "E")
				{
					stCurrentConstruct.clear();
					stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONLY_CHOSEONG;
					context.nCursorPos++;
					break;
				}
				else
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_UNABLE;
					break;
				}
			}
			else if (style == VOWEL) // 모음
			{


				if (c == "k" || c == "o" || c == "l")
				{
					std::string strDoubleVowel = charset_jung[stCurrentConstruct.jungseong] + c;
					stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, strDoubleVowel.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = NO_JONGSEONG_COMB_UNABLE;
					break;
				}
				else
				{
					stCurrentConstruct.clear();
					stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONLY_JUNGSEONG;
					context.nCursorPos++;
					break;
				}

			}
		}
		case NO_JONGSEONG_COMB_ABLE_N: // ex) "구"
		{
			if (style == CONSONANT) // 자음
			{


				if (c == "r")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_R;
					break;
				}
				else if (c == "s")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_S;
					break;
				}
				else if (c == "f")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_F;
					break;
				}
				else if (c == "q")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_Q;
					break;
				}
				else if (c == "Q" || c == "W" || c == "E")
				{
					stCurrentConstruct.clear();
					stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONLY_CHOSEONG;
					context.nCursorPos++;
					break;
				}
				else
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_UNABLE;
					break;
				}
			}
			else if (style == VOWEL) // 모음
			{


				if (c == "j" || c == "p" || c == "l")
				{
					std::string strDoubleVowel = charset_jung[stCurrentConstruct.jungseong] + c;
					stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, strDoubleVowel.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = NO_JONGSEONG_COMB_UNABLE;
					break;
				}
				else
				{
					stCurrentConstruct.clear();
					stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONLY_JUNGSEONG;
					context.nCursorPos++;
					break;
				}
			}
		}
		case NO_JONGSEONG_COMB_ABLE_M: // ex) "그"
		{
			if (style == CONSONANT) // 자음
			{


				if (c == "r")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_R;
					break;
				}
				if (c == "s")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_S;
					break;
				}
				if (c == "f")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_F;
					break;
				}
				if (c == "q")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_Q;
					break;
				}
				if (c == "Q" || c == "W" || c == "E")
				{
					stCurrentConstruct.clear();
					stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONLY_CHOSEONG;
					context.nCursorPos++;
					break;
				}
				else
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_UNABLE;
					break;
				}
			}
			else if (style == VOWEL) // 모음
			{


				if (c == "l")
				{
					std::string strDoubleVowel = charset_jung[stCurrentConstruct.jungseong] + c;
					stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, strDoubleVowel.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = NO_JONGSEONG_COMB_UNABLE;
					break;
				}
				else
				{
					stCurrentConstruct.clear();
					stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONLY_JUNGSEONG;
					context.nCursorPos++;
					break;
				}
			}
		}
		case NO_JONGSEONG_COMB_UNABLE: // ex) "규" or "과"
		{
			if (style == CONSONANT)
			{


				if (c == "r")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_R;
					break;
				}
				else if (c == "s")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_S;
					break;
				}
				else if (c == "f")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_F;
					break;
				}
				else if (c == "q")
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_ABLE_Q;
					break;
				}
				else if (c == "Q" || c == "W" || c == "E")
				{
					stCurrentConstruct.clear();
					stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONLY_CHOSEONG;
					context.nCursorPos++;
					break;
				}
				else
				{
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONE_JONGSEONG_COMB_UNABLE;
					break;
				}
			}
			else if (style == VOWEL) // 모음
			{

				stCurrentConstruct.clear();
				stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, c.c_str());
				context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

				state = ONLY_JUNGSEONG;
				context.nCursorPos++;
				break;
			}
		}
		case ONE_JONGSEONG_COMB_ABLE_R: // ex) "각"
		{
			if (style == CONSONANT) // 자음
			{

				if (c == "t")
				{
					std::string strDoubleConsonant = charset_jong[stCurrentConstruct.jongseong] + c; //Warning : 숫자로 더해져서 이상한 값이 들어갈 수도 있음
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, strDoubleConsonant.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = DOUBLE_JONGSEONG;
					break;
				}
				else
				{
					stCurrentConstruct.clear();
					stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONLY_CHOSEONG;
					context.nCursorPos++;
					break;
				}
			}
			else if (style == VOWEL) // 모음
			{
				ST_CONSTRUCT stPreConstruct = stCurrentConstruct; //DisassemUnicode(context.strUnderConstruct);
				stCurrentConstruct.clear();
				std::string tmp = charset_jong[stPreConstruct.jongseong];
				stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, tmp.c_str());
				stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, c.c_str());
				stPreConstruct.jongseong = 0;

				strPreContext.pop_back();
				context.strUnderConstruct = AssemUnicode(stPreConstruct);
				context.strUnderConstruct.push_back(AssemUnicode(stCurrentConstruct));

				if (c == "h")
				{
					state = NO_JONGSEONG_COMB_ABLE_H;
				}
				else if (c == "n")
				{
					state = NO_JONGSEONG_COMB_ABLE_N;
				}
				else if (c == "m")
				{
					state = NO_JONGSEONG_COMB_ABLE_M;
				}
				else
				{
					state = NO_JONGSEONG_COMB_UNABLE;
				}

				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;
				context.nCursorPos++;
				break;
			}
		}
		case ONE_JONGSEONG_COMB_ABLE_S: // ex) "간"
		{
			if (style == CONSONANT)
			{

				if (c == "w" || c == "g")
				{
					std::string strDoubleConsonant = charset_jong[stCurrentConstruct.jongseong] + c; //Warning : 숫자로 더해져서 이상한 값이 들어갈 수도 있음
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, strDoubleConsonant.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = DOUBLE_JONGSEONG;
				}
				else
				{
					stCurrentConstruct.clear();
					stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONLY_CHOSEONG;
					context.nCursorPos++;
				}
				break;
			}
			else if (style == VOWEL)
			{

				ST_CONSTRUCT stPreConstruct = stCurrentConstruct; //DisassemUnicode(context.strUnderConstruct);
				stCurrentConstruct.clear();
				std::string tmp = charset_jong[stPreConstruct.jongseong];
				stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, tmp.c_str());
				stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, c.c_str());
				stPreConstruct.jongseong = 0;

				strPreContext.pop_back();
				context.strUnderConstruct = AssemUnicode(stPreConstruct);
				context.strUnderConstruct.push_back(AssemUnicode(stCurrentConstruct));

				if (c == "h")
				{
					state = NO_JONGSEONG_COMB_ABLE_H;
				}
				else if (c == "n")
				{
					state = NO_JONGSEONG_COMB_ABLE_N;
				}
				else if (c == "m")
				{
					state = NO_JONGSEONG_COMB_ABLE_M;
				}
				else
				{
					state = NO_JONGSEONG_COMB_UNABLE;
				}

				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;
				context.nCursorPos++;
				break;
			}
		}
		case ONE_JONGSEONG_COMB_ABLE_F: // ex) "갈"
		{
			if (style == CONSONANT) //자음
			{

				if (c == "r" || c == "a" || c == "q" || c == "t" || c == "x" || c == "v" || c == "g")
				{
					std::string strDoubleConsonant = charset_jong[stCurrentConstruct.jongseong] + c; //Warning : 숫자로 더해져서 이상한 값이 들어갈 수도 있음
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, strDoubleConsonant.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = DOUBLE_JONGSEONG;
				}
				else
				{
					stCurrentConstruct.clear();
					stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONLY_CHOSEONG;
					context.nCursorPos++;
				}
				break;
			}
			else if (style == VOWEL) // 모음
			{
				ST_CONSTRUCT stPreConstruct = stCurrentConstruct; //DisassemUnicode(context.strUnderConstruct);
				stCurrentConstruct.clear();
				std::string tmp = charset_jong[stPreConstruct.jongseong];
				stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, tmp.c_str());
				stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, c.c_str());
				stPreConstruct.jongseong = 0;

				strPreContext.pop_back();
				context.strUnderConstruct = AssemUnicode(stPreConstruct);
				context.strUnderConstruct.push_back(AssemUnicode(stCurrentConstruct));

				if (c == "h")
				{
					state = NO_JONGSEONG_COMB_ABLE_H;
				}
				else if (c == "n")
				{
					state = NO_JONGSEONG_COMB_ABLE_N;
				}
				else if (c == "m")
				{
					state = NO_JONGSEONG_COMB_ABLE_M;
				}
				else
				{
					state = NO_JONGSEONG_COMB_UNABLE;
				}

				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;
				context.nCursorPos++;
				break;
			}
		}
		case ONE_JONGSEONG_COMB_ABLE_Q: // ex) "갑"
		{
			if (style == CONSONANT)
			{
				context.strUnderConstruct.clear();
				if (c == "t")
				{
					std::string strDoubleConsonant = charset_jong[stCurrentConstruct.jongseong] + c; //Warning : 숫자로 더해져서 이상한 값이 들어갈 수도 있음
					stCurrentConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, strDoubleConsonant.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					strPreContext.pop_back();
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = DOUBLE_JONGSEONG;
				}
				else
				{
					stCurrentConstruct.clear();
					stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, c.c_str());
					context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
					context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

					state = ONLY_CHOSEONG;
					context.nCursorPos++;
				}
				break;
			}
			else if (style == VOWEL)
			{
				ST_CONSTRUCT stPreConstruct = stCurrentConstruct; //DisassemUnicode(context.strUnderConstruct);
				stCurrentConstruct.clear();
				std::string tmp = charset_jong[stPreConstruct.jongseong];
				stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, tmp.c_str());
				stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, c.c_str());
				stPreConstruct.jongseong = 0;

				strPreContext.pop_back();
				context.strUnderConstruct = AssemUnicode(stPreConstruct);
				context.strUnderConstruct.push_back(AssemUnicode(stCurrentConstruct));

				if (c == "h")
				{
					state = NO_JONGSEONG_COMB_ABLE_H;
				}
				else if (c == "n")
				{
					state = NO_JONGSEONG_COMB_ABLE_N;
				}
				else if (c == "m")
				{
					state = NO_JONGSEONG_COMB_ABLE_M;
				}
				else
				{
					state = NO_JONGSEONG_COMB_UNABLE;
				}

				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;
				context.nCursorPos++;
				break;
			}
		}
		case ONE_JONGSEONG_COMB_UNABLE: // ex) "갚"
		{
			if (style == CONSONANT) // 자음
			{
				context.strUnderConstruct.clear();
				stCurrentConstruct.clear();

				stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, c.c_str());
				context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

				state = ONLY_CHOSEONG;
				context.nCursorPos++;
				break;
			}
			else if (style == VOWEL) // 모음
			{
				ST_CONSTRUCT stPreConstruct = stCurrentConstruct; // DisassemUnicode(context.strUnderConstruct);
				stCurrentConstruct.clear();
				std::string tmp = charset_jong[stPreConstruct.jongseong];
				stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, tmp.c_str());
				stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, c.c_str());
				stPreConstruct.jongseong = 0;

				strPreContext.pop_back();
				context.strUnderConstruct = AssemUnicode(stPreConstruct);
				context.strUnderConstruct.push_back(AssemUnicode(stCurrentConstruct));

				if (c == "h")
				{
					state = NO_JONGSEONG_COMB_ABLE_H;
				}
				else if (c == "n")
				{
					state = NO_JONGSEONG_COMB_ABLE_N;
				}
				else if (c == "m")
				{
					state = NO_JONGSEONG_COMB_ABLE_M;
				}
				else
				{
					state = NO_JONGSEONG_COMB_UNABLE;
				}

				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;
				context.nCursorPos++;
				break;
			}
		}
		case DOUBLE_JONGSEONG: // ex) "값"
		{
			if (style == CONSONANT) // 자음
			{
				stCurrentConstruct.clear();


				stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, c.c_str());
				context.strUnderConstruct = AssemUnicode(stCurrentConstruct);
				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;

				state = ONLY_CHOSEONG;
				context.nCursorPos++;
				break;
			}
			else if (style == VOWEL) // 모음
			{
				ST_CONSTRUCT stPreConstruct = stCurrentConstruct; //DisassemUnicode(context.strUnderConstruct);
				stCurrentConstruct.clear();

				std::string strOriginConsonant = charset_jong[stPreConstruct.jongseong];
				std::string strNewConsonant = strOriginConsonant.substr(1, 1);
				strOriginConsonant.pop_back();
				stPreConstruct.jongseong = GetIndexNum(charset_jong, NUM_OF_JONGSEONG, strOriginConsonant.c_str());
				stCurrentConstruct.choseong = GetIndexNum(charset_cho, NUM_OF_CHOSEONG, strNewConsonant.c_str());
				stCurrentConstruct.jungseong = GetIndexNum(charset_jung, NUM_OF_JUNGSEONG, c.c_str());

				strPreContext.pop_back();
				context.strUnderConstruct = AssemUnicode(stPreConstruct);
				context.strUnderConstruct.push_back(AssemUnicode(stCurrentConstruct));

				if (c == "h")
				{
					state = NO_JONGSEONG_COMB_ABLE_H;
				}
				else if (c == "n")
				{
					state = NO_JONGSEONG_COMB_ABLE_N;
				}
				else if (c == "m")
				{
					state = NO_JONGSEONG_COMB_ABLE_M;
				}
				else
				{
					state = NO_JONGSEONG_COMB_UNABLE;
				}

				context.strContext = strPreContext + context.strUnderConstruct + strPosContext;
				context.nCursorPos++;
				break;
			}
		}
		}
	}
}