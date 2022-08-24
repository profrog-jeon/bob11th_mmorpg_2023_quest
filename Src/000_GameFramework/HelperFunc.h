#pragma once

void TokenizeMessage(std::string strContext, std::vector<std::wstring>& outMessages, size_t tMaxTextLen = 60);
void TokenizeMessage(std::string strContext, std::vector<std::string>& outMessages, size_t tMaxTextLen = 60);
void TokenizeMessage(std::wstring strContext, std::vector<std::wstring>& outMessages, size_t tMaxTextLen = 60);
std::wstring Replace(std::wstring strContext, std::wstring strTarget, std::wstring strReplace);