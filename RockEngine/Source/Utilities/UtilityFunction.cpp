#include "UtilityFunction.h"

std::string UtilityFunction::read_file(const char* file_path)
{
	std::string data;
	std::ifstream file_stream;
	std::stringstream string_stream;
	file_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		file_stream.open(file_path);
		string_stream << file_stream.rdbuf();
		file_stream.close();
		data = string_stream.str();
	}
	catch (const std::ifstream::failure&)
	{
		std::cout << "Failed to read file." << std::endl;
	}

	return data;
}
