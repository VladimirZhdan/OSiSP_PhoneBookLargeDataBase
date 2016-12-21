#pragma once

#include <string>

typedef std::basic_string<TCHAR> tstring;

#if defined(UNICODE) || defined(_UNICODE)
#define tofstream std::wofstream

#else
#define tofstream std::ofstream

#endif