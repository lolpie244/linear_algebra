#pragma once

#include <fstream>
#include <sstream>

namespace file_processor
{
using std::ifstream;
using std::ofstream;
using std::string;
using std::stringstream;



template <typename Type> class BaseFileProcessor
{
protected:
	virtual Type from_string_stream(stringstream& text) = 0;
	virtual stringstream to_string_stream(const Type& obj) = 0;

public:
	BaseFileProcessor(){}
	Type read_from_file(string filename)
	{
		ifstream file(filename);
		if (!file.good())
			throw "File \"" + filename + "\" don't exist";

		stringstream text;

		text << file.rdbuf();

		return this->from_string_stream(text);
	}

	void write_to_file(string filename, const Type& obj)
	{
		ofstream file(filename);
		file << this->to_string_stream(obj).rdbuf();
	}
};

} // namespace file_processor
