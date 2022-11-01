#pragma once
#ifndef S2D_DATA_HEADER
#define S2D_DATA_HEADER
#include <S2Dcomponents.h>
#include <fstream>

#ifndef S2D_DATA_MACROS
#define S2D_DATA_MACROS

#endif

struct Environment
{
	std::vector<std::string> activeTypes;

};

class LevelSerializer
{
#define cstr const char*
public:
	cstr FILE_BEGIN = "FILE:";
	cstr FILE_END = "END";

	cstr SCOPE_BEGIN = "{";
	cstr SCOPE_END = "}";
	
	cstr ARR_BEGIN = "[";
	cstr ARR_END = "]";

	cstr ATTR_BEGIN = "(";
	cstr ATTR_END = ")";
	
	std::string SerializeLevel(Level* lvl)
	{
		using namespace std;
		fstream str;
		string result = "";
		result.append(FILE_BEGIN);
		
		result.append(FILE_END);
	}

#undef cstr
};

#endif