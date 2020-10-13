#ifndef UTILITY_FUNCTION_H
#define UTILITY_FUNCTION_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class UtilityFunction
{
public:
	static std::string read_file(const char* file_path);
};

#endif