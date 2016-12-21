#pragma once

#include <string>

typedef std::basic_string<TCHAR> tstring;

#if defined(UNICODE) || defined(_UNICODE)
#define to_tstring std::to_wstring

#else
#define to_tstring std::to_string

#endif